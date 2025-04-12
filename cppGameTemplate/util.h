#pragma once
#include <graphics.h>
#include <cmath>
#include <algorithm>
#include <Windows.h>
#pragma comment(lib, "MSIMG32.LIB")

#define M_PI 3.14159265358979323846

#define _USE_MATH_DEFINES
#ifndef M_RD
#define M_RD 0.01745329251994329576923690768489
#endif


inline void putimage_alpha(int dst_x, int dst_y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

inline void putimage_rotate_alpha(int dst_x, int dst_y, IMAGE* img, double angle)
{
    if (img == NULL) return;

    // 获取原始图像尺寸
    int width = img->getwidth();
    int height = img->getheight();

    // 计算旋转后的尺寸
    double radian = angle * M_PI / 180.0;
    double cos_angle = fabs(cos(radian));
    double sin_angle = fabs(sin(radian));
    int new_width = (int)(width * cos_angle + height * sin_angle) + 2;
    int new_height = (int)(width * sin_angle + height * cos_angle) + 2;

    // 创建临时图像
    IMAGE* rotated = new IMAGE(new_width, new_height);
    if (!rotated) return;

    // 清除旋转图像（全透明黑色）
    SetWorkingImage(rotated);
    setbkcolor(BLACK);
    cleardevice();
    SetWorkingImage(NULL);

    // 获取图像数据指针
    DWORD* dst_bits = GetImageBuffer(rotated);
    DWORD* src_bits = GetImageBuffer(img);

    if (!dst_bits || !src_bits) {
        delete rotated;
        return;
    }

    // 计算中心点
    int center_x = new_width / 2;
    int center_y = new_height / 2;
    int src_center_x = width / 2;
    int src_center_y = height / 2;

    // 执行旋转，直接复制像素（包括Alpha通道）
    for (int y = 0; y < new_height; y++) {
        for (int x = 0; x < new_width; x++) {
            // 计算源像素坐标
            int src_x = (int)((x - center_x) * cos(radian) - (y - center_y) * sin(radian) + src_center_x);
            int src_y = (int)((x - center_x) * sin(radian) + (y - center_y) * cos(radian) + src_center_y);

            // 检查源像素是否在原图范围内
            if (src_x >= 0 && src_x < width && src_y >= 0 && src_y < height) {
                // 直接复制像素（包括Alpha通道）
                dst_bits[y * new_width + x] = src_bits[src_y * width + src_x];
            }
        }
    }

    // 计算绘制位置（居中）
    int draw_x = dst_x - center_x;
    int draw_y = dst_y - center_y;

    // 使用你已有的putimage_alpha函数绘制
    putimage_alpha(draw_x, draw_y, rotated);

    // 清理
    delete rotated;
}
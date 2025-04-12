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

    // ��ȡԭʼͼ��ߴ�
    int width = img->getwidth();
    int height = img->getheight();

    // ������ת��ĳߴ�
    double radian = angle * M_PI / 180.0;
    double cos_angle = fabs(cos(radian));
    double sin_angle = fabs(sin(radian));
    int new_width = (int)(width * cos_angle + height * sin_angle) + 2;
    int new_height = (int)(width * sin_angle + height * cos_angle) + 2;

    // ������ʱͼ��
    IMAGE* rotated = new IMAGE(new_width, new_height);
    if (!rotated) return;

    // �����תͼ��ȫ͸����ɫ��
    SetWorkingImage(rotated);
    setbkcolor(BLACK);
    cleardevice();
    SetWorkingImage(NULL);

    // ��ȡͼ������ָ��
    DWORD* dst_bits = GetImageBuffer(rotated);
    DWORD* src_bits = GetImageBuffer(img);

    if (!dst_bits || !src_bits) {
        delete rotated;
        return;
    }

    // �������ĵ�
    int center_x = new_width / 2;
    int center_y = new_height / 2;
    int src_center_x = width / 2;
    int src_center_y = height / 2;

    // ִ����ת��ֱ�Ӹ������أ�����Alphaͨ����
    for (int y = 0; y < new_height; y++) {
        for (int x = 0; x < new_width; x++) {
            // ����Դ��������
            int src_x = (int)((x - center_x) * cos(radian) - (y - center_y) * sin(radian) + src_center_x);
            int src_y = (int)((x - center_x) * sin(radian) + (y - center_y) * cos(radian) + src_center_y);

            // ���Դ�����Ƿ���ԭͼ��Χ��
            if (src_x >= 0 && src_x < width && src_y >= 0 && src_y < height) {
                // ֱ�Ӹ������أ�����Alphaͨ����
                dst_bits[y * new_width + x] = src_bits[src_y * width + src_x];
            }
        }
    }

    // �������λ�ã����У�
    int draw_x = dst_x - center_x;
    int draw_y = dst_y - center_y;

    // ʹ�������е�putimage_alpha��������
    putimage_alpha(draw_x, draw_y, rotated);

    // ����
    delete rotated;
}
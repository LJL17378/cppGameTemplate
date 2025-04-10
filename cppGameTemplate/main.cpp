#include <graphics.h>
#include <conio.h>
#include <Windows.h>
#include "sceneManager.h"
#include "scene.h"
#include "camera.h"
#include "atlas.h"
#include "scene1.h"
#include "scene2.h"

Atlas coin_atlas; // 精灵图集
sceneManager scene_manager; // 场景管理器实例
Camera camera; // 摄像机实例

Scene* scene1 = nullptr; // 场景指针
Scene* scene2 = nullptr; // 另一个场景指针

// 游戏配置
#define FPS 60            // 目标帧率
#define WINDOW_WIDTH 800  // 窗口宽度
#define WINDOW_HEIGHT 600 // 窗口高度

void load_resources() {
	// 加载资源
	coin_atlas.load_from_file(_T("assets/image/coinAni2_0%d.png"), 10); // 加载10张金币图片
}


int main() {
    // 初始化图形窗口
    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT, EW_SHOWCONSOLE);
    // 开启批量绘图模式（提升绘制效率）
    load_resources();
    BeginBatchDraw();

    // 消息变量
    ExMessage msg;

	scene1 = new Scene1();
	scene2 = new Scene2();

	scene_manager.set_current_scene(scene2); // 设置初始场景

    // 游戏主循环
    while (true) {
        DWORD frame_start_time = GetTickCount();

        // 处理输入消息
        while (peekmessage(&msg)) {
            scene_manager.on_input(msg);
        }

        // 计算时间差
        static DWORD last_tick_time = GetTickCount();
        DWORD current_tick_time = GetTickCount();
        DWORD delta_tick = current_tick_time - last_tick_time;

        // 更新游戏逻辑
        scene_manager.on_update(delta_tick);
        last_tick_time = current_tick_time;

        // 清屏
        cleardevice();

        // 绘制游戏内容
        scene_manager.on_draw(camera);

        // 批量绘制
        FlushBatchDraw();

        // 帧率控制
        DWORD frame_end_time = GetTickCount();
        DWORD frame_delta_time = frame_end_time - frame_start_time;
        if (frame_delta_time < 1000 / FPS) {
            Sleep(1000 / FPS - frame_delta_time);
        }
    }

    // 关闭图形窗口（通常不会执行到这里）
    EndBatchDraw();
    return 0;
}
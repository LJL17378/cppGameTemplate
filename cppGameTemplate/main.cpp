#include <graphics.h>
#include <conio.h>
#include <Windows.h>
#include "sceneManager.h"
#include "scene.h"
#include "camera.h"
#include "atlas.h"
#include "scene1.h"
#include "scene2.h"

Atlas coin_atlas; // ����ͼ��
sceneManager scene_manager; // ����������ʵ��
Camera camera; // �����ʵ��

Scene* scene1 = nullptr; // ����ָ��
Scene* scene2 = nullptr; // ��һ������ָ��

// ��Ϸ����
#define FPS 60            // Ŀ��֡��
#define WINDOW_WIDTH 800  // ���ڿ��
#define WINDOW_HEIGHT 600 // ���ڸ߶�

void load_resources() {
	// ������Դ
	coin_atlas.load_from_file(_T("assets/image/coinAni2_0%d.png"), 10); // ����10�Ž��ͼƬ
}


int main() {
    // ��ʼ��ͼ�δ���
    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT, EW_SHOWCONSOLE);
    // ����������ͼģʽ����������Ч�ʣ�
    load_resources();
    BeginBatchDraw();

    // ��Ϣ����
    ExMessage msg;

	scene1 = new Scene1();
	scene2 = new Scene2();

	scene_manager.set_current_scene(scene2); // ���ó�ʼ����

    // ��Ϸ��ѭ��
    while (true) {
        DWORD frame_start_time = GetTickCount();

        // ����������Ϣ
        while (peekmessage(&msg)) {
            scene_manager.on_input(msg);
        }

        // ����ʱ���
        static DWORD last_tick_time = GetTickCount();
        DWORD current_tick_time = GetTickCount();
        DWORD delta_tick = current_tick_time - last_tick_time;

        // ������Ϸ�߼�
        scene_manager.on_update(delta_tick);
        last_tick_time = current_tick_time;

        // ����
        cleardevice();

        // ������Ϸ����
        scene_manager.on_draw(camera);

        // ��������
        FlushBatchDraw();

        // ֡�ʿ���
        DWORD frame_end_time = GetTickCount();
        DWORD frame_delta_time = frame_end_time - frame_start_time;
        if (frame_delta_time < 1000 / FPS) {
            Sleep(1000 / FPS - frame_delta_time);
        }
    }

    // �ر�ͼ�δ��ڣ�ͨ������ִ�е����
    EndBatchDraw();
    return 0;
}
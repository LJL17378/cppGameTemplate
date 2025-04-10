#pragma once
#pragma once
#include "scene.h"
#include "sceneManager.h"
#include "camera.h"
#include "animation.h"

extern sceneManager scene_manager;

class Scene2 : public Scene
{
public:
	void on_enter() 
	{
		std::cout << "Scene2 on_enter" << std::endl;
	}
	void on_update(int delta) 
	{
	}
	void on_draw(const Camera& camera) 
	{
	}
	void on_input(const ExMessage& msg) 
	{
		if (msg.message == WM_LBUTTONDOWN) {
			scene_manager.switch_scene(sceneManager::SceneType::SCENE_TYPE_1);
		}
	}
	void on_exit() 
	{
		std::cout << "Scene2 on_exit" << std::endl;
	}
private:
};

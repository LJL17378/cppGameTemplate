#pragma once
#include "scene.h"
#include "sceneManager.h"
#include "camera.h"
#include "atlas.h"
#include "animation.h"
#include <graphics.h>
#include <iostream>

extern Atlas coin_atlas;

extern sceneManager scene_manager;

class Scene1 : public Scene
{
public:
	void on_enter()
	{
		std::cout << "Scene1 on_enter" << std::endl;
		coin_animation.set_atlas(&coin_atlas);
		coin_animation.set_interval(60);
		coin_animation.set_loop(true);
	}
	void on_update(int delta)
	{
		coin_animation.on_update(delta);
	}
	void on_draw(const Camera& camera) 
	{
		coin_animation.on_draw(100, 100);
	}
	void on_input(const ExMessage& msg) 
	{
		if (msg.message == WM_LBUTTONDOWN) {
			scene_manager.switch_scene(sceneManager::SceneType::SCENE_TYPE_2);
		}
	}
	void on_exit() 
	{
		std::cout << "Scene1 on_exit" << std::endl;
	}
private:
	Animation coin_animation;
};
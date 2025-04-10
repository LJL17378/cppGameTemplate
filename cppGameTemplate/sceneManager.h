#pragma once
#include "scene.h"

extern Scene* scene1;
extern Scene* scene2;

class sceneManager {
public:
	enum class SceneType {
		SCENE_TYPE_1,
		SCENE_TYPE_2,
		// ÖîÈç´ËÀà
	};
	sceneManager() = default;
	~sceneManager() = default;

	void set_current_scene(Scene* scene) {
		this->current_scene = scene;
		if (current_scene) {
			current_scene->on_enter();
		}
	}

	void switch_scene(SceneType type) {
		if (current_scene) {
			current_scene->on_exit();
		}
		switch (type) {
		case SceneType::SCENE_TYPE_1:
			current_scene = scene1;
			break;
		case SceneType::SCENE_TYPE_2:
			current_scene = scene2;
			break;
		default:
			break;
		}
		if (current_scene) {
			current_scene->on_enter();
		}
	}

	void on_update(int delta) {
		current_scene->on_update(delta);
	}
	void on_draw(Camera& camera) {
		current_scene->on_draw(camera);
	}
	void on_input(const ExMessage& msg) {
		current_scene->on_input(msg);
	}
private:
	Scene* current_scene = nullptr;
};

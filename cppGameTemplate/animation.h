#pragma once

#include "util.h"
#include "atlas.h"

#include<functional>
#include<graphics.h>

class Animation
{
public:
	Animation() = default;
	~Animation() = default;
	void reset()
	{
		timer = 0;
		idx_frame = 0;
	}

	void set_atlas(Atlas* new_atlas)
	{
		reset();
		atlas = new_atlas;
	}

	void set_loop(bool flag) {
		is_loop = flag;
	}

	void set_interval(int interval) {
		frame_interval = interval;
	}

	int get_idx_frame() const {
		return idx_frame;
	}

	IMAGE* get_frame() const {
		return atlas->get_image(idx_frame);
	}

	bool check_finished() const {
		if (is_loop)
			return false;
		else
			return idx_frame == atlas->get_size() - 1;
	}

	void set_callback(std::function<void()> func) {
		this->callback = func;
	}

	void on_update(int delta)
	{
		timer += delta;
		if (timer >= frame_interval) {
			timer = 0;
			idx_frame++;
			if (idx_frame >= atlas->get_size()) {
				idx_frame = is_loop ? 0 : atlas->get_size() - 1;
				if (!is_loop && callback) {
					callback();
				}
			}
		}
	};

	void on_draw(int x, int y ,double angle) const
	{
		putimage_rotate_alpha(x, y, atlas->get_image(idx_frame),angle);
	}
private:
	bool is_loop;
	Atlas* atlas = nullptr;
	int idx_frame = 0;
	int frame_interval = 0;
	int timer = 0;
	std::function<void()> callback;
};
#pragma once
#include "graphics.h"
#include "input.h"

namespace Krabby {



	struct Config {
		const char* name;
		int width;
		int height;
	};



	namespace App {
		void init(const Config& config);
		void cleanup();
		bool running();
		void start_render();
		void end_render();
		bool key_pressed(Key key);
		bool key_down(Key key);
		bool key_released(Key key);
	}
}
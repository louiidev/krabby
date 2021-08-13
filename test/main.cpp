#include <stdio.h>
#include <krabby.h>


using namespace Krabby;
using namespace Graphics;
using namespace Math;


#define SDL_MAIN_HANDLED


int main(int argc, char* argv[]) {
	Config config;
	config.name = "testing";
	config.width = 1280;
	config.height = 720;

	App::init(config);
	
	while (App::running()) {
		if (App::key_down(Key::Up)) {
			printf("released \n");
		}

		App::start_render();
		clear_framebuffer(Color::black);
		draw_rect(Vec2(0.0f, 0.0f), Vec2(50.0f, 50.0f), Color::red);
		App::end_render();
	}

	App::cleanup();
	return 0;
}
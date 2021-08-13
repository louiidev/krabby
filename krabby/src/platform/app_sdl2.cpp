#define KRABBY_PLATFORM_SDL2

#ifdef KRABBY_PLATFORM_SDL2


#include <SDL.h>
#include "platform.h"
#include "input.h";
#include <assert.h>
#include <stdio.h>
#include "../third_party/glad/glad.h"

#if _WIN32
#include <SDL_syswm.h>
// on Windows we're using the C++ <filesystem> API for now
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winuser.h>	// for SetProcessDPIAware
#include <filesystem>	// for File Reading/Writing
#include <shellapi.h>	// for file explore
#else
// on non-Windows we use POSIX standard file system stuff
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <cstring>
#endif

namespace Krabby {


	// Blah SDL2 Platform State
	struct SDL2Platform
	{
		SDL_Window* window = nullptr;
		SDL_GLContext context = nullptr;
		bool running = false;
	};
}



using namespace Krabby;



static Krabby::SDL2Platform g_platform;


void App::init(const Config& config) {

	g_platform = SDL2Platform();


	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0)
	{
		printf("ERROR: Failed to initialize SDL2\n");
		assert(false);
	}
	else {
		g_platform.window =
			SDL_CreateWindow(
				config.name,
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				config.width,
				config.height,
				SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
			);
		if (g_platform.window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			assert(false);
		}
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(
		SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Create context
	g_platform.context = SDL_GL_CreateContext(g_platform.window);
	bool success = true;
	if (g_platform.context == NULL)
	{
		printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Use Vsync
		if (SDL_GL_SetSwapInterval(1) < 0)
		{
			printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
		}
	}

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		printf("Failed to initialize GLAD \n");
	}

	// init_shaders();
	glViewport(0, 0, config.width, config.height);
	printf("opengl init \n");
	Graphics::init();
	g_platform.running = true;
}



bool App::running() {
	return g_platform.running;
}

void resize(int w, int h) {
	glViewport(0, 0, w, h);
}


Uint8* input_current_keyboard_state = new Uint8[512];
Uint8* input_previous_keyboard_state = new Uint8[512];

void App::start_render() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE || event.type == SDL_QUIT) {
			g_platform.running = false;
			break;
		}

		if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
			resize(event.window.data1, event.window.data2);
		}
		
	}
	memcpy(input_previous_keyboard_state, input_current_keyboard_state, 512);
	memcpy(input_current_keyboard_state, SDL_GetKeyboardState(NULL), 512);
}


bool App::key_released(Key key) {
	return !input_current_keyboard_state[key] && input_previous_keyboard_state[key];
}

bool App::key_down(Key key) {
	return input_current_keyboard_state[key];
}

bool App::key_pressed(Key key) {
	return input_current_keyboard_state[key] && !input_previous_keyboard_state[key];
}


void App::end_render() {
	SDL_GL_SwapWindow(g_platform.window);
}


void App::cleanup() {
	SDL_GL_DeleteContext(g_platform.context);
	//Destroy window
	SDL_DestroyWindow(g_platform.window);

	//Quit SDL subsystems
	SDL_Quit();
	delete input_current_keyboard_state;
	delete input_previous_keyboard_state;
}





#endif
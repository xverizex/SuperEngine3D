#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <stdio.h>
#include "main.h"
#include <levels.h>
#include "camera.h"
#include <time.h>

static uint32_t screen_width;
static uint32_t screen_height;

static WindowSize *globalSize;

static ILevel *lvl;

WindowSize::WindowSize()
{

}

WindowSize *WindowSize::getInstance (){
	if (!globalSize) {
		globalSize = new WindowSize ();
		globalSize->width = screen_width;
		globalSize->height = screen_height;
	}

	return globalSize;
}

void handle_event(SDL_Event& event)
{
	switch(event.type) {
		case SDL_MOUSEBUTTONUP:
			{
				SDL_MouseButtonEvent *m = static_cast<SDL_MouseButtonEvent *>(&event.button);
				int y = screen_height - m->y;
				lvl->click(m->x, y);
			}
			break;
	}
}

static int threadS(void *_data)
{
	SDL_Event event;
	while(SDL_WaitEvent(&event)){ 
		handle_event (event);
	}

	return 0;
}

int main(int argc, char **argv)
{
	srand(time(0));

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);


	SDL_DisplayMode mode;

	SDL_GetDesktopDisplayMode(0, &mode);

	screen_width = mode.w;
	screen_height = mode.h;

	SDL_Window *window = SDL_CreateWindow(
		"Office",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		screen_width,
		screen_height,
		SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL
	);

	

	SDL_GLContext glc = SDL_GL_CreateContext(window);

	gladLoadGL();



	glEnable (GL_PROGRAM_POINT_SIZE);
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_BLEND);

    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport (0, 0, screen_width, screen_height);

	init_shaders ();

	SDL_CreateThread(threadS, "thread", nullptr);

/*
 * Here set up your level 
 */
#if 0
	lvl = new LevelForest();
#endif
	lvl->init ();

	Camera *camera = Camera::getInstance();

#ifdef WIN32
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		handle_event(event);
#else
	while (1) {
#endif	

		glClearColor (0x30 / 255.f, 0x90 / 255.f, 0xa5 / 255.f, 1.f);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		lvl->update();

		lvl->render();

		SDL_GL_SwapWindow(window);
		SDL_Delay(16);
	}
}

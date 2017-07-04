#include <string>
#include <SDL.h>

#include <libretro.h>
#include "Application.h"
#include "chaigame/chaigame.h"

#include <iostream>

Application* Application::m_instance = NULL;
retro_input_state_t Application::input_state_cb = NULL;
retro_input_poll_t Application::input_poll_cb = NULL;

bool Application::isRunning() {
	return m_instance != NULL;
}
void Application::destroy() {
	m_instance = NULL;
}

Application* Application::getInstance() {
	if (!m_instance) {
		m_instance = new Application;
	}
	return m_instance;
}

void Application::quit(void) {
	joystick.unload();
	filesystem.unload();
	image.unload();
	sound.unload();
	SDL_Quit();
}

bool Application::load(const std::string& file) {
	// Initialize SDL.
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		printf("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// Build the Screen.
	screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE | SDL_SRCALPHA | SDL_RESIZABLE);
	if (screen == NULL) {
		printf("Unable to create screen: %s", SDL_GetError());
		SDL_Quit();
		return false;
	}

	// Enable video buffering.
	videoBuffer = (unsigned int *)screen->pixels;

	// Fix alpha blending.
	if (SDL_SetAlpha(screen, SDL_SRCALPHA, 0) == -1) {
		printf("Warning: Enabling alpha blending failed.");
	}

	// Initalize the chaigame subsystems.
	filesystem.init(file);
	graphics.load();
	keyboard.load();
	joystick.load();
	math.load();
	mouse.load();
	image.load();
	sound.load();
	script = new chaigame::script();
	script->load();

	// Set up the game timer.
	tick = SDL_GetTicks();

	return true;
}

bool Application::update() {
	// Update some of the sub-systems.
	sound.update();
	keyboard.update();
	joystick.update();

	// Poll all SDL events.
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				return false;
				break;
			case SDL_MOUSEMOTION:
				mouse.motionEvent(event.motion);
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouse.buttonEvent(event.button);
				break;
			case SDL_MOUSEBUTTONUP:
				mouse.buttonEvent(event.button);
				break;
		}
	}

	// Retrieve the new game time.
	Uint32 current = SDL_GetTicks();

	// Update the game.
	float delta = (float)(current) - (float)(tick);
	script->update(delta);
	tick = current;

	return true;
}

/**
 * Render the application.
 */
void Application::draw(){
	graphics.clear();

	// Test drawing a rectangle.
	static int x = 10;
	static int y = 10;

	if (keyboard.isDown("up")) {
		y -= 2;
	}
	if (keyboard.isDown("down")) {
		y += 2;
	}
	if (keyboard.isDown("left")) {
		x -= 2;
	}
	if (keyboard.isDown("right")) {
		x += 2;
	}
	if (mouse.isDown(1)) {
		x += 2;
	}
	if (mouse.isDown(2)) {
		x -= 2;
	}
	graphics.rectangle("fill", x, y, 50, 50);

	// Render the game.
	script->draw();

	// Update the screen.
	SDL_UpdateRect(screen, 0, 0, 0, 0);
	SDL_Flip(screen);
}

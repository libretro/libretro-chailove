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
	window.unload();
}

bool Application::load(const std::string& file) {
	// Initalize the chaigame subsystems.
	filesystem.init(file);
	script = new chaigame::script();
	script->conf(config);
	window.load(config);
	graphics.load();
	keyboard.load();
	joystick.load();
	math.load();
	mouse.load();
	image.load();
	sound.load();
	timer.load();
	script->load();

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

	timer.step();
	script->update(timer.getDelta());

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
		y -= 0.5f * timer.getDelta();
	}
	if (keyboard.isDown("down")) {
		y += 0.5f * timer.getDelta();
	}
	if (keyboard.isDown("left")) {
		x -= 0.5f * timer.getDelta();
	}
	if (keyboard.isDown("right")) {
		x += 0.5f * timer.getDelta();
	}
	if (mouse.isDown(1)) {
		x += 3;
	}
	if (mouse.isDown(2)) {
		x -= 0.5f;
	}
	graphics.rectangle("fill", x, y, 50, 50);

	// Render the game.
	script->draw();

	// Update the screen.
	SDL_UpdateRect(screen, 0, 0, 0, 0);

	// Flip the buffer.
	if (SDL_Flip(screen) == -1) {
		printf("Failed to swap the buffers: %s\n", SDL_GetError());
	}
}

#include <string>
#include <SDL.h>

#include <libretro.h>
#include "Application.h"
#include "chaigame/chaigame.h"

#include <iostream>

Application* Application::m_instance = NULL;
retro_input_state_t Application::input_state_cb = NULL;
retro_input_poll_t Application::input_poll_cb = NULL;

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
	// Quit all the subsystems.
	joystick.unload();
	image.unload();
	sound.unload();
	filesystem.unload();
	window.unload();
}

bool Application::load(const std::string& file) {
	// Initalize all the subsystems.
	filesystem.init(file);
	script = new chaigame::script();
	script->conf(config);
	#ifdef __HAVE_TESTS__
	test.conf(config);
	#endif
	window.load(config);
	sound.load();
	graphics.load();
	image.load();
	keyboard.load();
	joystick.load();
	math.load();
	mouse.load();
	timer.load();
	script->load();

	#ifdef __HAVE_TESTS__
	test.load();
	#endif

	return true;
}

bool Application::update() {
	if (!running) {
		return false;
	}

	sound.update();

	// Poll all SDL events.
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				return running = false;
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

	// Update some of the sub-systems.
	joystick.update();
	keyboard.update();

	// Step forward the timer, and update the game.
	timer.step();
	script->update(timer.getDelta());

	#ifdef __HAVE_TESTS__
	test.update(timer.getDelta());
	#endif

	return running;
}

/**
 * Render the application.
 */
void Application::draw() {
	if (running) {
		// Clear the screen.
		graphics.clear();

		// Render the game.
		script->draw();

		#ifdef __HAVE_TESTS__
		test.draw();
		#endif

		// Update the screen.
		SDL_UpdateRect(screen, 0, 0, 0, 0);

		// Flip the buffer.
		if (SDL_Flip(screen) == -1) {
			printf("Failed to swap the buffers: %s\n", SDL_GetError());
		}
	}
}

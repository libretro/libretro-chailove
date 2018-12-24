#include <string>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include "libretro.h"
#include "ChaiLove.h"

static retro_video_refresh_t video_cb;
// This is needed to allow SDL-libretro to compile.
// @see SDL_LIBRETROaudio.c:37
retro_audio_sample_t audio_cb;

void retro_set_video_refresh(retro_video_refresh_t cb) {
	video_cb = cb;
}

void retro_set_audio_sample(retro_audio_sample_t cb) {
	ChaiLove::getInstance()->sound.audio_cb = cb;
}

void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb) {
	ChaiLove::getInstance()->sound.audio_batch_cb = cb;
}

void retro_set_input_poll(retro_input_poll_t cb) {
	ChaiLove::input_poll_cb = cb;
}

void retro_set_input_state(retro_input_state_t cb) {
	ChaiLove::input_state_cb = cb;
}

#ifdef __cplusplus
extern "C" {
#endif

void libretro_audio_cb(int16_t left, int16_t right) {
	// Nothing, since we're using libretro-common.
	// audio_cb(left, right);
}

/**
 * libretro-sdl callback; Send through the input state.
 */
short int libretro_input_state_cb(unsigned port, unsigned device, unsigned index, unsigned id) {
	return ChaiLove::input_state_cb(port, device, index, id);
}
#ifdef __cplusplus
}
#endif

/**
 * libretro callback; Sets up the environment based on the system variables.
 */
void retro_set_environment(retro_environment_t cb) {
	// Set the environment callback.
	ChaiLove::environ_cb = cb;

	// The core supports having no game.
	bool no_rom = true;
	cb(RETRO_ENVIRONMENT_SET_SUPPORT_NO_GAME, &no_rom);

	// Set the Variables.
	struct retro_variable variables[] = {
		{
			"chailove_alphablending", "Alpha Blending; enabled|disabled",
		},
		{
			"chailove_highquality", "High Quality; enabled|disabled",
		},
		{ NULL, NULL },
	};
	cb(RETRO_ENVIRONMENT_SET_VARIABLES, variables);
}

/**
 * libretro callback; Updates the core option variables.
 */
static void update_variables(void) {
	ChaiLove* app = ChaiLove::getInstance();
	app->system.updateVariables(app->config);
}

#ifdef __cplusplus
extern "C" {
#endif
/**
 * libretro callback; Load the labels for the input buttons.
 */
void init_descriptors() {
	struct retro_input_descriptor desc[] = {
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT, "D-Pad Left" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP, "D-Pad Up" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN, "D-Pad Down" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT, "D-Pad Right" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B, "B" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "A" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_X, "X" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_Y, "Y" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "Left Shoulder" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "Right Shoulder" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "Select" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START, "Start" },

		{ 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT, "D-Pad Left" },
		{ 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP, "D-Pad Up" },
		{ 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN, "D-Pad Down" },
		{ 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT, "D-Pad Right" },
		{ 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B, "B" },
		{ 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "A" },
		{ 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_X, "X" },
		{ 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_Y, "Y" },
		{ 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "Left Shoulder" },
		{ 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "Right Shoulder" },
		{ 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "Select" },
		{ 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START, "Start" },

		{ 2, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT, "D-Pad Left" },
		{ 2, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP, "D-Pad Up" },
		{ 2, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN, "D-Pad Down" },
		{ 2, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT, "D-Pad Right" },
		{ 2, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B, "B" },
		{ 2, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "A" },
		{ 2, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_X, "X" },
		{ 2, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_Y, "Y" },
		{ 2, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "Left Shoulder" },
		{ 2, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "Right Shoulder" },
		{ 2, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "Select" },
		{ 2, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START, "Start" },

		{ 3, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT, "D-Pad Left" },
		{ 3, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP, "D-Pad Up" },
		{ 3, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN, "D-Pad Down" },
		{ 3, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT, "D-Pad Right" },
		{ 3, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B, "B" },
		{ 3, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "A" },
		{ 3, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_X, "X" },
		{ 3, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_Y, "Y" },
		{ 3, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "Left Shoulder" },
		{ 3, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "Right Shoulder" },
		{ 3, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "Select" },
		{ 3, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START, "Start" },

		{ 4, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT, "D-Pad Left" },
		{ 4, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP, "D-Pad Up" },
		{ 4, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN, "D-Pad Down" },
		{ 4, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT, "D-Pad Right" },
		{ 4, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B, "B" },
		{ 4, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "A" },
		{ 4, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_X, "X" },
		{ 4, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_Y, "Y" },
		{ 4, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "Left Shoulder" },
		{ 4, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "Right Shoulder" },
		{ 4, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "Select" },
		{ 4, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START, "Start" },
		{ 0 },
	};

	ChaiLove::environ_cb(RETRO_ENVIRONMENT_SET_INPUT_DESCRIPTORS, desc);
}
#ifdef __cplusplus
}
#endif

/**
 * libretro callback; Retrieve information about the core.
 */
void retro_get_system_info(struct retro_system_info *info) {
	memset(info, 0, sizeof(*info));

	// The name of the core.
	info->library_name = "ChaiLove";
#ifndef GIT_VERSION
#define GIT_VERSION ""
#endif

	// The ChaiLove version.
	info->library_version  = CHAILOVE_VERSION_STRING GIT_VERSION;

	// When loading a game, request the full path to the game.
	info->need_fullpath = true;

	// File extensions that are used.
	info->valid_extensions = "chai|chailove";

	// Do not extract .zip files.
	info->block_extract = true;
}

/**
 * libretro callback; Set the audio/video settings.
 */
void retro_get_system_av_info(struct retro_system_av_info *info) {
	std::cout << "[ChaiLove] retro_get_system_av_info" << std::endl;
	if (!ChaiLove::hasInstance()) {
		return;
	}
	unsigned int width = 640;
	unsigned int height = 480;

	ChaiLove* app = ChaiLove::getInstance();
	if (app != NULL) {
		width = app->config.window.width;
		height = app->config.window.height;
	}

	info->geometry.base_width   = width;
	info->geometry.base_height  = height;
	info->geometry.max_width    = width;
	info->geometry.max_height   = width;
	info->geometry.aspect_ratio = static_cast<float>(width) / static_cast<float>(height);

	info->timing.fps = 60.0;
	info->timing.sample_rate = 44100.0;
}

void retro_set_controller_port_device(unsigned port, unsigned device) {
	std::cout << "[ChaiLove] retro_set_controller_port_device" << std::endl;
	(void)port;
	(void)device;
}

/**
 * libretro callback; Return the amount of bytes required to save a state.
 */
size_t retro_serialize_size(void) {
	// Save states will be 8 KB.
	return 8192;
}

/**
 * libretro callback; Serialize the current state to save a slot.
 */
bool retro_serialize(void *data, size_t size) {
	if (!ChaiLove::hasInstance()) {
		return false;
	}

	// Ask ChaiLove for save data.
	ChaiLove* app = ChaiLove::getInstance();
	std::string state = app->savestate();
	if (state.empty()) {
		return false;
	}

	// Encode the JSON state data. Disabled for speed.
	// state = app->data.encode("string", "base64", state);
	// state = app->data.compress(state);

	// Save the information to the state data.
	std::copy(state.begin(), state.end(), reinterpret_cast<char*>(data));
	return true;
}

/**
 * libretro callback; Unserialize the given data and load the state.
 */
bool retro_unserialize(const void *data, size_t size) {
	if (!ChaiLove::hasInstance() || size <= 0) {
		return false;
	}

	// Create a string stream from the data.
	std::stringstream ss(std::string(
		reinterpret_cast<const char*>(data),
		reinterpret_cast<const char*>(data) + size));

	// Port the string stream to a straight string.
	std::string loadData = ss.str();

	// Pass the string to the script.
	ChaiLove* app = ChaiLove::getInstance();

	// Decompress the state data. Disabled for speed.
	// loadData = app->data.decode("string", "base64", loadData);
	// loadData = app->data.decompress(loadData);

	// Finally, load the string.
	return app->loadstate(loadData);
}

/**
 * libretro callback; Reset the enabled cheats.
 */
void retro_cheat_reset(void) {
	if (ChaiLove::hasInstance()) {
		ChaiLove::getInstance()->cheatreset();
	}
}

/**
 * libretro callback; Set the given cheat.
 */
void retro_cheat_set(unsigned index, bool enabled, const char *code) {
	if (ChaiLove::hasInstance()) {
		std::string codeString(code);
		ChaiLove::getInstance()->cheatset(index, enabled, codeString);
	}
}

/**
 * libretro callback; Step the core forwards a step.
 */
void frame_time_cb(retro_usec_t usec) {
	if (ChaiLove::hasInstance()) {
		float delta = (float)usec / 1000000.0f;
		ChaiLove::getInstance()->timer.step(delta);
	}
}

/**
 * libretro callback; Step the audio forwards a step.
 */
void retro_audio_cb() {
	// Update the sound system.
	ChaiLove::getInstance()->sound.update();
}

/**
 * libretro callback; Set the current state of the audio.
 */
void audio_set_state(bool enabled) {
	// TODO(RobLoach): Act on whether or not audio is enabled/disabled?
	std::cout << "[ChaiLove] audio_set_state(" << (enabled ? "true" : "false") << ")" << std::endl;
}

/**
 * libretro callback; Load the given game.
 */
bool retro_load_game(const struct retro_game_info *info) {
	// Update the core options.
	update_variables();

	// Update the input button descriptions.
	init_descriptors();

	// Set the frame rate callback.
	struct retro_frame_time_callback frame_cb = { frame_time_cb, 1000000 / 60 };
	ChaiLove::environ_cb(RETRO_ENVIRONMENT_SET_FRAME_TIME_CALLBACK, &frame_cb);

	// Set the audio callback.
	struct retro_audio_callback retro_audio = { retro_audio_cb, audio_set_state };
	ChaiLove::environ_cb(RETRO_ENVIRONMENT_SET_AUDIO_CALLBACK, &retro_audio);

	// Find the game path.
	std::string gamePath(info ? info->path : "");
	if (gamePath == ".") {
		gamePath = "main.chai";
	}
	void* data = NULL;
	if (info != NULL) {
		data = (void*)info->data;
	}
	return ChaiLove::getInstance()->load(gamePath, data);
}

/**
 * libretro callback; Loads the given special game.
 */
bool retro_load_game_special(unsigned game_type, const struct retro_game_info *info, size_t num_info) {
	std::cout << "[ChaiLove] retro_load_game_special" << std::endl;
	return retro_load_game(info);
}

/**
 * libretro callback; Unload the current game.
 */
void retro_unload_game(void) {
	std::cout << "[ChaiLove] retro_unload_game()" << std::endl;

	// Invoke the quit event.
	if (ChaiLove::hasInstance()) {
		ChaiLove::getInstance()->event.m_shouldclose = true;
	}
}

/**
 * libretro callback; Retrieve the active region.
 */
unsigned retro_get_region(void) {
	return RETRO_REGION_NTSC;
}

/**
 * libretro callback; Get the libretro API version.
 */
unsigned retro_api_version(void) {
	return RETRO_API_VERSION;
}

/**
 * libretro callback; Get the given memory ID.
 */
void *retro_get_memory_data(unsigned id) {
	return NULL;
}

/**
 * libretro callback; Get the size of the given memory ID.
 */
size_t retro_get_memory_size(unsigned id) {
	return 0;
}

/**
 * libretro callback; Initialize the core.
 */
void retro_init(void) {
	// Pixel Format
	enum retro_pixel_format fmt = RETRO_PIXEL_FORMAT_XRGB8888;
	if (!ChaiLove::environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &fmt)) {
		std::cout << "[ChaiLove] Pixel format XRGB8888 not supported by platform, cannot use." << std::endl;
	}
}

/**
 * libretro callback; Deinitialize the core.
 */
void retro_deinit(void) {
	std::cout << "[ChaiLove] retro_deinit()" << std::endl;
	ChaiLove::destroy();
}

/**
 * libretro callback; The frontend requested to reset the game.
 */
void retro_reset(void) {
	std::cout << "[ChaiLove] retro_reset()" << std::endl;
	if (ChaiLove::hasInstance()) {
		ChaiLove::getInstance()->reset();
	}
}

/**
 * libretro callback; Run a game loop in the core.
 */
void retro_run(void) {
	// Ensure there is a game running.
	if (!ChaiLove::hasInstance()) {
		return;
	}

	// Check if the game should be closed.
	ChaiLove* app = ChaiLove::getInstance();
	if (app->event.m_shouldclose) {
		return;
	}

	bool updated = false;
	if (ChaiLove::environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE_UPDATE, &updated) && updated) {
		update_variables();
	}

	// Update the game.
	app->update();

	// Render the game.
	app->draw();

	// Copy the video buffer to the screen.
	video_cb(app->videoBuffer, app->config.window.width, app->config.window.height, app->config.window.width << 2);

	// See if the game requested to close itself.
	if (app->event.m_shouldclose) {
		ChaiLove::environ_cb(RETRO_ENVIRONMENT_SHUTDOWN, 0);
	}
}

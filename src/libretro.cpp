#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include "libretro.h"
#include "ChaiLove.h"

const char *retro_save_directory;
const char *retro_system_directory;
const char *retro_content_directory;
static bool use_audio_cb;
int16_t audio_buffer[2 * (44100 / 60)];
static retro_video_refresh_t video_cb;
retro_audio_sample_t audio_cb;
static retro_audio_sample_batch_t audio_batch_cb;

void retro_set_video_refresh(retro_video_refresh_t cb) {
	video_cb = cb;
}

void retro_set_audio_sample(retro_audio_sample_t cb) {
	audio_cb = cb;
}

void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb) {
	audio_batch_cb = cb;
}

void retro_set_input_poll(retro_input_poll_t cb) {
	ChaiLove::input_poll_cb = cb;
}

void retro_set_input_state(retro_input_state_t cb) {
	ChaiLove::input_state_cb = cb;
}

static void emit_audio(void) {
	if (ChaiLove::hasInstance()) {
		ChaiLove::getInstance()->audio.mixer_render(audio_buffer);
		audio_batch_cb(audio_buffer, 44100 / 60);
	}
}

static void audio_set_state(bool enable) {
	(void)enable;
}

#ifdef __cplusplus
extern "C" {
#endif
/**
 * libretro-sdl callback; Send through the audio.
 */
void libretro_audio_cb(int16_t left, int16_t right) {
	audio_cb(left, right);
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
	ChaiLove* game = ChaiLove::getInstance();
	struct retro_variable var = {0};

	// Alpha Blending
	var.key = "chailove_alphablending";
	var.value = NULL;
	if (ChaiLove::environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value) {
		std::string varvalue(var.value);
		if (varvalue == "disabled") {
			game->config.options["alphablending"] = false;
		}
	}

	// High Quality
	var.key = "chailove_highquality";
	var.value = NULL;
	if (ChaiLove::environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value) {
		std::string varvalue(var.value);
		if (varvalue == "disabled") {
			game->config.options["highquality"] = false;
		}
	}
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
	(void)port;
	(void)device;
}

/**
 * libretro callback; Return the amount of bytes required to save a state.
 */
size_t retro_serialize_size(void) {
	// Save states will be 10 kilobytes.
	return 10000;
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

	// Compress the JSON state data.
	state = app->data.compress(state);

	// Save the information to the state data.
	std::copy(state.begin(), state.end(), reinterpret_cast<char*>(data));
	return true;
}

/**
 * libretro callback; Unserialize the given data and load the state.
 */
bool retro_unserialize(const void *data, size_t size) {
	if (!ChaiLove::hasInstance()) {
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

	// Decompress the state data.
	loadData = app->data.decompress(loadData);

	// Finally, load the string.
	return app->loadstate(loadData);
}

/**
 * libretro callback; Reset the enabled cheats.
 */
void retro_cheat_reset(void) {
	// Nothing.
}

/**
 * libretro callback; Set the given cheat.
 */
void retro_cheat_set(unsigned index, bool enabled, const char *code) {
	(void)index;
	(void)enabled;
	(void)code;
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

	// Make the audio callback.
	struct retro_audio_callback audio_cb = { emit_audio, audio_set_state };
	use_audio_cb = ChaiLove::environ_cb(RETRO_ENVIRONMENT_SET_AUDIO_CALLBACK, &audio_cb);

	// Find the game path.
	std::string gamePath(info ? info->path : "");
	if (gamePath == ".") {
		gamePath = "main.chai";
	}
	return ChaiLove::getInstance()->load(gamePath);
}

/**
 * libretro callback; Loads the given special game.
 */
bool retro_load_game_special(unsigned game_type, const struct retro_game_info *info, size_t num_info) {
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
	const char *system_dir = NULL;

	// System Directory
	if (ChaiLove::environ_cb(RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY, &system_dir) && system_dir) {
		retro_system_directory = system_dir;
	}

	// Content Directory
	const char *content_dir = NULL;
	if (ChaiLove::environ_cb(RETRO_ENVIRONMENT_GET_CONTENT_DIRECTORY, &content_dir) && content_dir) {
		retro_content_directory = content_dir;
	}

	// Save Directory
	const char *save_dir = NULL;
	if (ChaiLove::environ_cb(RETRO_ENVIRONMENT_GET_SAVE_DIRECTORY, &save_dir) && save_dir) {
		// If save directory is defined use it, otherwise use system directory
		retro_save_directory = *save_dir ? save_dir : retro_system_directory;
	} else {
		retro_save_directory = retro_system_directory;
	}

	// Pixel Format
	enum retro_pixel_format fmt = RETRO_PIXEL_FORMAT_XRGB8888;
	if (!ChaiLove::environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &fmt)) {
		std::cout << "[ChaiLove] Pixel format XRGB8888 not supported by platform, cannot use." << std::endl;
	}

	ChaiLove::getInstance();
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
	if (ChaiLove::hasInstance()) {
		ChaiLove::getInstance()->reset();
	}
}

/**
 * libretro callback; Run a game loop in the core.
 */
void retro_run(void) {
	if (!ChaiLove::hasInstance()) {
		return;
	}

	ChaiLove* app = ChaiLove::getInstance();
	if (app->event.m_shouldclose) {
		ChaiLove::destroy();
		ChaiLove::environ_cb(RETRO_ENVIRONMENT_SHUTDOWN, 0);
		return;
	}

	// Update the game.
	app->update();

	// Render the game.
	app->draw();

	// Copy the video buffer to the screen.
	video_cb(app->videoBuffer, app->config.window.width, app->config.window.height, app->config.window.width << 2);
}

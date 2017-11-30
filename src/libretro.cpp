#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include "libretro.h"
#include "ChaiLove.h"

char RETRO_DIR[512];
const char *retro_save_directory;
const char *retro_system_directory;
const char *retro_content_directory;
// char retro_system_conf[512];
static bool use_audio_cb;
int16_t audio_buffer[2 * (44100 / 60)];

static retro_video_refresh_t video_cb;
static retro_environment_t environ_cb;
retro_audio_sample_t audio_cb;
static retro_audio_sample_batch_t audio_batch_cb;
// static retro_input_poll_t input_poll_cb;

// retro_input_state_t input_state_cb;

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

static void emit_audio(void)
{
	ChaiLove* app = ChaiLove::getInstance();
	app->audio.mixer_render(audio_buffer);
	audio_batch_cb(audio_buffer, (44100 / 60));
}

static void audio_set_state(bool enable)
{
   (void)enable;
}

// these 2 funtions have to be implemented for Libretro SDL port
#ifdef __cplusplus
extern "C" {
#endif
void libretro_audio_cb(int16_t left, int16_t right) {
	audio_cb(left, right);
}

short int libretro_input_state_cb(unsigned port, unsigned device, unsigned index, unsigned id) {
	return ChaiLove::input_state_cb(port, device, index, id);
}
#ifdef __cplusplus
}
#endif

void retro_set_environment(retro_environment_t cb) {
	bool no_rom = false;
	environ_cb = cb;
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

static void update_variables(void) {
	ChaiLove* game = ChaiLove::getInstance();
	struct retro_variable var = {0};

	// Alpha Blending
	var.key = "chailove_alphablending";
	var.value = NULL;
	if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value) {
		std::string varvalue(var.value);
		if (varvalue == "disabled") {
			game->config.options["alphablending"] = false;
		}
	}

	// High Quality
	var.key = "chailove_highquality";
	var.value = NULL;
	if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value) {
		std::string varvalue(var.value);
		if (varvalue == "disabled") {
			game->config.options["highquality"] = false;
		}
	}
}

#ifdef __cplusplus
extern "C" {
#endif
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
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "L" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "R" },
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
		{ 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "L" },
		{ 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "R" },
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
		{ 2, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "L" },
		{ 2, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "R" },
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
		{ 3, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "L" },
		{ 3, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "R" },
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
		{ 4, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "L" },
		{ 4, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "R" },
		{ 4, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "Select" },
		{ 4, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START, "Start" },
		{ 0 },
	};

	environ_cb(RETRO_ENVIRONMENT_SET_INPUT_DESCRIPTORS, desc);
}
#ifdef __cplusplus
}
#endif

void retro_get_system_info(struct retro_system_info *info) {
	memset(info, 0, sizeof(*info));
	info->library_name = "ChaiLove";
#ifndef GIT_VERSION
#define GIT_VERSION ""
#endif
	info->library_version  = CHAILOVE_VERSION_STRING GIT_VERSION;
	info->need_fullpath = true;
	info->valid_extensions = "chai|chailove";
	info->block_extract = true;
}

void retro_get_system_av_info(struct retro_system_av_info *info) {
	ChaiLove* app = ChaiLove::getInstance();
	unsigned int width = 640;
	unsigned int height = 480;
	if (app != NULL) {
		width = app->config.window.width;
		height = app->config.window.height;
	}

	info->geometry.base_width   = width;
	info->geometry.base_height  = height;
	info->geometry.max_width    = width;
	info->geometry.max_height   = width;
	info->geometry.aspect_ratio = (float)width / (float)height;

	info->timing.fps = 60.0;
	info->timing.sample_rate = 44100.0;
}

void retro_set_controller_port_device(unsigned port, unsigned device) {
	(void)port;
	(void)device;
}

/**
 * Return the amount of bytes required to save a state.
 */
size_t retro_serialize_size(void) {
	// Save states will be 10 kilobytes.
	return 10000;
}

/**
 * Serialize the current state to save a slot.
 */
bool retro_serialize(void *data, size_t size) {
	// Ask ChaiLove for save data.
	ChaiLove* app = ChaiLove::getInstance();
	std::string state = app->savestate();
	if (state.empty()) {
		return false;
	}

	// Compress the JSON state data.
	state = app->math.compress(state);

	// Save the information to the state data.
	std::copy(state.begin(), state.end(), reinterpret_cast<char*>(data));
	return true;
}

/**
 * Unserialize the given data and load the state.
 */
bool retro_unserialize(const void *data, size_t size) {
	// Create a string stream from the data.
	std::stringstream ss(std::string(
		reinterpret_cast<const char*>(data),
		reinterpret_cast<const char*>(data) + size));

	// Port the string stream to a straight string.
	std::string loadData = ss.str();

	// Pass the string to the script.
	ChaiLove* app = ChaiLove::getInstance();

	// Decompress the state data.
	loadData = app->math.decompress(loadData);

	// Finally, load the string.
	return app->loadstate(loadData);
}

void retro_cheat_reset(void) {
	// Nothing.
}

void retro_cheat_set(unsigned index, bool enabled, const char *code) {
	(void)index;
	(void)enabled;
	(void)code;
}

void texture_init(){
	ChaiLove* app = ChaiLove::getInstance();
	if (app->videoBuffer) {
		memset(app->videoBuffer, 0, sizeof(app->videoBuffer));
	}
}

void frame_time_cb(retro_usec_t usec) {
	float delta = usec / 1000000.0;
	ChaiLove* app = ChaiLove::getInstance();
	app->timer.step(delta);
}

bool retro_load_game(const struct retro_game_info *info) {
	// Update the core options.
	update_variables();

	// Update the input button descriptions.
	init_descriptors();

	// Set the frame rate callback.
	struct retro_frame_time_callback frame_cb = { frame_time_cb, 1000000 / 60 };
	environ_cb(RETRO_ENVIRONMENT_SET_FRAME_TIME_CALLBACK, &frame_cb);

	// Make the audio callback.
	struct retro_audio_callback audio_cb = { emit_audio, audio_set_state };
	use_audio_cb = environ_cb(RETRO_ENVIRONMENT_SET_AUDIO_CALLBACK, &audio_cb);

	// Load the game.
	std::string full(info ? info->path : "main.chai");
	return ChaiLove::getInstance()->load(full);
}

bool retro_load_game_special(unsigned game_type, const struct retro_game_info *info, size_t num_info) {
	init_descriptors();
	(void)game_type;
	(void)info;
	(void)num_info;
	return false;
}

void retro_unload_game(void) {
	std::cout << "[ChaiLove] retro_unload_game()" << std::endl;

	// Invoke the quit event.
	ChaiLove* app = ChaiLove::getInstance();
	app->event.quit();
}

unsigned retro_get_region(void) {
	return RETRO_REGION_NTSC;
}

unsigned retro_api_version(void)
{
	return RETRO_API_VERSION;
}

void *retro_get_memory_data(unsigned id) {
	return NULL;
}

size_t retro_get_memory_size(unsigned id) {
	return 0;
}

void retro_init(void) {
	const char *system_dir = NULL;

	if (environ_cb(RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY, &system_dir) && system_dir) {
		// if defined, use the system directory
		retro_system_directory = system_dir;
	}

	const char *content_dir = NULL;

	if (environ_cb(RETRO_ENVIRONMENT_GET_CONTENT_DIRECTORY, &content_dir) && content_dir) {
		// if defined, use the system directory
		retro_content_directory = content_dir;
	}

	const char *save_dir = NULL;

	if (environ_cb(RETRO_ENVIRONMENT_GET_SAVE_DIRECTORY, &save_dir) && save_dir) {
		// If save directory is defined use it, otherwise use system directory
		retro_save_directory = *save_dir ? save_dir : retro_system_directory;
	}
	else {
		// make retro_save_directory the same in case RETRO_ENVIRONMENT_GET_SAVE_DIRECTORY is not implemented by the frontend
		retro_save_directory = retro_system_directory;
	}
	/*
	if (retro_system_directory == NULL) {
		std::cout << "[ChaiLove] " << RETRO_DIR << std::endl;
	}
	else {
		std::cout << "[ChaiLove] " << RETRO_DIR << retro_system_directory << std::endl;
	}
	*/

	enum retro_pixel_format fmt = RETRO_PIXEL_FORMAT_XRGB8888;
	if (!environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &fmt)) {
		std::cout << "[ChaiLove] Pixel format XRGB8888 not supported by platform, cannot use." << std::endl;
		exit(0);
	}
}

void retro_deinit(void) {
	std::cout << "[ChaiLove] retro_deinit()" << std::endl;
	ChaiLove* app = ChaiLove::getInstance();
	if (app) {
		app->event.quit();
		app->quit();
	}
}

/**
 * The frontend requested to reset the game.
 */
void retro_reset(void) {
	ChaiLove* app = ChaiLove::getInstance();
	if (app) {
		app->reset();
	}
}

void retro_run(void) {
	ChaiLove* app = ChaiLove::getInstance();
	if (!app->event.quitstatus) {
		// Poll all the inputs.
		ChaiLove::input_poll_cb();

		// Update the game.
		if (!app->update()) {
			environ_cb(RETRO_ENVIRONMENT_SHUTDOWN, 0);
			return;
		}

		// Render the game.
		app->draw();

		// Copy the video buffer to the screen.
		video_cb(app->videoBuffer, app->config.window.width, app->config.window.height, app->config.window.width << 2);
	}
}

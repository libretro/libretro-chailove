#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "libretro.h"
#include "Game.h"

char RETRO_DIR[512];
const char *retro_save_directory;
const char *retro_system_directory;
const char *retro_content_directory;
//char retro_system_conf[512];
bool opt_awesome;
static bool use_audio_cb;
int16_t audio_buffer[2 * (44100 / 60)];

static retro_video_refresh_t video_cb;
static retro_environment_t environ_cb;
retro_audio_sample_t audio_cb;
static retro_audio_sample_batch_t audio_batch_cb;
//static retro_input_poll_t input_poll_cb;

//retro_input_state_t input_state_cb;

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
	Game::input_poll_cb = cb;
}

void retro_set_input_state(retro_input_state_t cb) {
	Game::input_state_cb = cb;
}

static void emit_audio(void)
{
	Game* app = Game::getInstance();
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
	audio_cb(left,right);
}

short int libretro_input_state_cb(unsigned port, unsigned device, unsigned index, unsigned id) {
	return Game::input_state_cb(port, device, index, id);
}
#ifdef __cplusplus
}
#endif

void retro_set_environment(retro_environment_t cb) {
	bool no_rom = true;
	environ_cb = cb;
	cb(RETRO_ENVIRONMENT_SET_SUPPORT_NO_GAME, &no_rom);
	struct retro_variable variables[] = {
		{
			"awesomeoption","Use Awesome; OFF|ON",
		},
		{ NULL, NULL },
	};
	cb(RETRO_ENVIRONMENT_SET_VARIABLES, variables);
}

static void update_variables(void) {
	struct retro_variable var = {0};

	var.key = "awesomeoption";
	var.value = NULL;

	if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value) {
		fprintf(stderr, "Awesome: %s\n", var.value);
		if (strcmp(var.value, "OFF") == 0)
			opt_awesome = false;
		if (strcmp(var.value, "ON") == 0)
			opt_awesome = true;

		fprintf(stderr, "[libretro-chaigame]: Awesome: %s.\n", opt_awesome ? "ON" : "OFF");
	}
}

void retro_get_system_info(struct retro_system_info *info) {
	memset(info, 0, sizeof(*info));
	info->library_name = "ChaiGame";
	info->library_version = "0.2.0";
	info->need_fullpath = true;
	info->valid_extensions = "chai|chaigame";
	info->block_extract = true;
}

void retro_get_system_av_info(struct retro_system_av_info *info) {
	Game* app = Game::getInstance();
	unsigned int width = 640;
	unsigned int height = 480;
	if (app != NULL) {
		width = app->config.window.width;
		height = app->config.window.height;
	}

	struct retro_game_geometry geom = {
		width,
		height,
		width,
		height,
		(float)width / (float)height
	};
	info->geometry = geom;

	struct retro_system_timing timing = {
		60.0,
		44100.0
	};
	info->timing = timing;
}

void retro_set_controller_port_device(unsigned port, unsigned device) {
	(void)port;
	(void)device;
}

size_t retro_serialize_size(void) {
	return 0;
}

bool retro_serialize(void *data, size_t size) {
	return false;
}

bool retro_unserialize(const void *data, size_t size) {
	return false;
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
	Game* app = Game::getInstance();
	if (app->videoBuffer) {
        memset(app->videoBuffer, 0, sizeof(app->videoBuffer));
	}
}

void frame_time_cb(retro_usec_t usec) {
	Game* app = Game::getInstance();
	double delta = usec / 1000000.0;
	app->timer.step(delta);
}

bool retro_load_game(const struct retro_game_info *info) {
	struct retro_frame_time_callback frame_cb = { frame_time_cb, 1000000 / 60 };
	environ_cb(RETRO_ENVIRONMENT_SET_FRAME_TIME_CALLBACK, &frame_cb);

	struct retro_audio_callback audio_cb = { emit_audio, audio_set_state };
	use_audio_cb = environ_cb(RETRO_ENVIRONMENT_SET_AUDIO_CALLBACK, &audio_cb);

	std::string full(info ? info->path : "main.chai");
	return Game::getInstance()->load(full);
}

bool retro_load_game_special(unsigned game_type, const struct retro_game_info *info, size_t num_info) {
	(void)game_type;
	(void)info;
	(void)num_info;
	return false;
}

void retro_unload_game(void) {
	// Nothing.
	printf("retro_unload_game\n");
	Game* app = Game::getInstance();
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

	if (retro_system_directory == NULL) {
		sprintf(RETRO_DIR, "%s\n",".");
	}
	else {
		sprintf(RETRO_DIR, "%s\n", retro_system_directory);
	}

	//sprintf(retro_system_conf, "%s/testsdl.cfg\n",RETRO_DIR);

	printf("Retro SYSTEM_DIRECTORY %s\n",retro_system_directory);
	printf("Retro SAVE_DIRECTORY %s\n",retro_save_directory);
	printf("Retro CONTENT_DIRECTORY %s\n",retro_content_directory);

	enum retro_pixel_format fmt = RETRO_PIXEL_FORMAT_XRGB8888;
	if (!environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &fmt)) {
		fprintf(stderr, "Pixel format XRGB8888 not supported by platform, cannot use.\n");
		exit(0);
	}

	struct retro_input_descriptor inputDescriptors[] = {
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "A" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B, "B" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_X, "X" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_Y, "Y" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "Select" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START, "Start" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT, "Right" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT, "Left" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP, "Up" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN, "Down" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "R" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "L" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R2, "R2" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L2, "L2" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R3, "R3" },
		{ 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L3, "L3" }
	};
	environ_cb(RETRO_ENVIRONMENT_SET_INPUT_DESCRIPTORS, &inputDescriptors);

	update_variables();
}

void retro_deinit(void) {
	printf("retro_deinit\n");
	Game* app = Game::getInstance();
	if (app) {
		app->event.quit();
		app->quit();
	}
}

void retro_reset(void) {
	// Nothing.
	printf("retro_reset\n");
}

void retro_run(void) {
	Game* app = Game::getInstance();
	if (app != NULL && app->event.quitstatus == false) {
		// Poll all the inputs.
		Game::input_poll_cb();

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

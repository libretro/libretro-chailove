/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997-2012 Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    Sam Lantinga
    slouken@libsdl.org
*/
#include "SDL_config.h"

/* Dummy SDL video driver implementation; this is just enough to make an
 *  SDL-based application THINK it's got a working video driver, for
 *  applications that call SDL_Init(SDL_INIT_VIDEO) when they don't need it,
 *  and also for use as a collection of stubs when porting SDL to a new
 *  platform for which you haven't yet written a valid video driver.
 *
 * This is also a great way to determine bottlenecks: if you think that SDL
 *  is a performance problem for a given platform, enable this driver, and
 *  then see if your application runs faster without video overhead.
 *
 * Initial work by Ryan C. Gordon (icculus@icculus.org). A good portion
 *  of this was cut-and-pasted from Stephane Peter's work in the AAlib
 *  SDL video driver.  Renamed to "DUMMY" by Sam Lantinga.
 */

#include "SDL_video.h"
#include "SDL_mouse.h"
#include "../SDL_sysvideo.h"
#include "../SDL_pixels_c.h"
#include "../../events/SDL_events_c.h"

#include "SDL_LIBRETROvideo.h"
#include "SDL_LIBRETROevents_c.h"
#include "SDL_LIBRETROmouse_c.h"
#include "SDL_LIBRETROkeyboard_c.h"

#if 0
/************************************
 * libretro implementation
 ************************************/

#include "libretro.h"

#define LOGI printf

char RPATH[512];
char RETRO_DIR[512];
const char *retro_save_directory;
const char *retro_system_directory;
const char *retro_content_directory;
char retro_system_DATA[512];

bool opt_analog;
static bool firstcall=true;

int retrow=768;
int retroh=544;

int pauseg=0;

uint32_t *videoBuffer;

static retro_video_refresh_t video_cb;
static retro_environment_t environ_cb;
static retro_audio_sample_batch_t audio_batch_cb;
retro_audio_sample_t audio_cb;
retro_input_poll_t input_poll_cb;
retro_input_state_t input_state_cb;

void retro_set_video_refresh(retro_video_refresh_t cb) { video_cb = cb; }
void retro_set_audio_sample(retro_audio_sample_t cb) { audio_cb  =cb; }
void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb) { audio_batch_cb = cb; }
void retro_set_input_poll(retro_input_poll_t cb) { input_poll_cb = cb; }
void retro_set_input_state(retro_input_state_t cb) { input_state_cb = cb; }

void libretro_audio_cb(int16_t left, int16_t right){
	audio_cb(left,right);
}

short int libretro_input_state_cb(unsigned port,unsigned device,unsigned index,unsigned id){
	return input_state_cb(port,device,index,id);
} 


void retro_set_environment(retro_environment_t cb)
{
   environ_cb = cb;

   struct retro_variable variables[] = {
      {
         "sdl_analog","Use Analog; OFF|ON",
      },
      { NULL, NULL },
   };

   cb(RETRO_ENVIRONMENT_SET_VARIABLES, variables);
}

static void update_variables(void)
{
   struct retro_variable var = {0};

 
   var.key = "sdl_analog";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      fprintf(stderr, "value: %s\n", var.value);
      if (strcmp(var.value, "OFF") == 0)
         opt_analog = false;
      if (strcmp(var.value, "ON") == 0)
         opt_analog = true;

        fprintf(stderr, "[libretro-test]: Analog: %s.\n",opt_analog?"ON":"OFF");
   }

}

void retro_get_system_info(struct retro_system_info *info)
{
    	memset(info, 0, sizeof(*info));
	info->library_name = "libretro-sdl";
	info->library_version = "0.0";
	info->need_fullpath = true;
	info->valid_extensions = "*";
}


void retro_get_system_av_info(struct retro_system_av_info *info)
{
//FIXME handle vice PAL/NTSC
   struct retro_game_geometry geom = { retrow, retroh,retrow, retroh ,4.0 / 3.0 };
   struct retro_system_timing timing = { 60.0, 44100.0 };

   info->geometry = geom;
   info->timing   = timing;
}

void retro_set_controller_port_device(unsigned port, unsigned device)
{
    (void)port;
    (void)device;
}

size_t retro_serialize_size(void)
{
	return 0;
}

bool retro_serialize(void *data, size_t size)
{
    return false;
}

bool retro_unserialize(const void *data, size_t size)
{
    return false;
}

void retro_cheat_reset(void)
{}

void retro_cheat_set(unsigned index, bool enabled, const char *code)
{
    (void)index;
    (void)enabled;
    (void)code;
}

bool retro_load_game(const struct retro_game_info *info)
{    
	const char *full_path;

    	full_path = info->path;

	strcpy(RPATH,full_path);

	printf("LOAD EMU\n");

    	return true;
}

bool retro_load_game_special(unsigned game_type, const struct retro_game_info *info, size_t num_info)
{
    (void)game_type;
    (void)info;
    (void)num_info;
    return false;
}

void retro_unload_game(void)
{
     pauseg=-1;
}

unsigned retro_get_region(void)
{
    return RETRO_REGION_NTSC;
}

unsigned retro_api_version(void)
{
    return RETRO_API_VERSION;
}

void *retro_get_memory_data(unsigned id)
{
    return NULL;
}

size_t retro_get_memory_size(unsigned id)
{
    return 0;
}

void retro_init(void)
{
   const char *system_dir = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY, &system_dir) && system_dir)
   {
      // if defined, use the system directory			
      retro_system_directory=system_dir;		
   }		   

   const char *content_dir = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_CONTENT_DIRECTORY, &content_dir) && content_dir)
   {
      // if defined, use the system directory			
      retro_content_directory=content_dir;		
   }			

   const char *save_dir = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_SAVE_DIRECTORY, &save_dir) && save_dir)
   {
      // If save directory is defined use it, otherwise use system directory
      retro_save_directory = *save_dir ? save_dir : retro_system_directory;      
   }
   else
   {
      // make retro_save_directory the same in case RETRO_ENVIRONMENT_GET_SAVE_DIRECTORY is not implemented by the frontend
      retro_save_directory=retro_system_directory;
   }

   if(retro_system_directory==NULL)sprintf(RETRO_DIR, "%s\0",".");
   else sprintf(RETRO_DIR, "%s\0", retro_system_directory);

   sprintf(retro_system_DATA, "%s\\DATA\0",RETRO_DIR);

   LOGI("Retro SYSTEM_DIRECTORY %s\n",retro_system_directory);
   LOGI("Retro SAVE_DIRECTORY %s\n",retro_save_directory);
   LOGI("Retro CONTENT_DIRECTORY %s\n",retro_content_directory);


    enum retro_pixel_format fmt = RETRO_PIXEL_FORMAT_XRGB8888;
    if (!environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &fmt))
    {
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

/*
    struct retro_keyboard_callback cbk = { keyboard_cb };
    environ_cb(RETRO_ENVIRONMENT_SET_KEYBOARD_CALLBACK, &cbk);
*/
  	update_variables();

	libretro_init_extra();
}

void retro_deinit(void)
{ 

    libretro_deinit_extra();

     auseg=-1;

        printf("Retro DeInit\n");
}

void retro_reset(void)
{
}
#ifdef __LINUX__
//unused need for sdl-1.2.15-libretro
void libretro_setbuffer(void *pix,unsigned short int x,unsigned short int  y){
}
#endif


void retro_run(void)
{
	bool updated = false;
//printf("fc:%d\n",firstcall);
	if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE_UPDATE, &updated) && updated)
      		update_variables(); 


	libretro_do_logic(RPATH); 
        video_cb(videoBuffer, retrow, retroh, retrow << 2);
	libretro_do_switch(RPATH); 
}
#endif

/* Initialization/Query functions */
static int LIBRETRO_VideoInit(_THIS, SDL_PixelFormat *vformat);
static SDL_Rect **LIBRETRO_ListModes(_THIS, SDL_PixelFormat *format, Uint32 flags);
static SDL_Surface *LIBRETRO_SetVideoMode(_THIS, SDL_Surface *current, int width, int height, int bpp, Uint32 flags);
static int LIBRETRO_SetColors(_THIS, int firstcolor, int ncolors, SDL_Color *colors);
static void LIBRETRO_VideoQuit(_THIS);

/* Hardware surface functions */
static int LIBRETRO_AllocHWSurface(_THIS, SDL_Surface *surface);
static int LIBRETRO_LockHWSurface(_THIS, SDL_Surface *surface);
static void LIBRETRO_UnlockHWSurface(_THIS, SDL_Surface *surface);
static void LIBRETRO_FreeHWSurface(_THIS, SDL_Surface *surface);
static int LIBRETRO_FlipHWSurface(_THIS, SDL_Surface *surface);

static int  LIBRETRO_CheckHWBlit(_THIS, SDL_Surface *src, SDL_Surface *dst);
static int  LIBRETRO_HWAccelBlit(SDL_Surface *src, SDL_Rect *srcrect,
                                SDL_Surface *dst, SDL_Rect *dstrect);
static int LIBRETRO_SetHWColorKey(_THIS, SDL_Surface *surface, Uint32 key);
static int LIBRETRO_SetHWAlpha(_THIS, SDL_Surface *surface, Uint8 alpha);
static int LIBRETRO_FillHWRect(_THIS, SDL_Surface *dst, SDL_Rect *dstrect, Uint32 color);
/* etc. */
static void LIBRETRO_UpdateRects(_THIS, int numrects, SDL_Rect *rects);

/* DUMMY driver bootstrap functions */

static int LIBRETRO_FillHWRect(_THIS, SDL_Surface *dst, SDL_Rect *dstrect, Uint32 color)
{

  SDL_FillRect (dst, dstrect, color);         

  return 0;
}

static int LIBRETRO_SetHWAlpha(_THIS, SDL_Surface *surface, Uint8 alpha)
{
  return 0;
}

static int LIBRETRO_SetHWColorKey(_THIS, SDL_Surface *src, Uint32 key)
{
  return 0;
}

static int LIBRETRO_Available(void)
{
	return 1;
}

static void LIBRETRO_DeleteDevice(SDL_VideoDevice *device)
{
	SDL_free(device->hidden);
	SDL_free(device);
}

static SDL_VideoDevice *LIBRETRO_CreateDevice(int devindex)
{
	SDL_VideoDevice *device;

	/* Initialize all variables that we clean on shutdown */
	device = (SDL_VideoDevice *)SDL_malloc(sizeof(SDL_VideoDevice));
	if ( device ) {
		SDL_memset(device, 0, (sizeof *device));
		device->hidden = (struct SDL_PrivateVideoData *)
				SDL_malloc((sizeof *device->hidden));
	}
	if ( (device == NULL) || (device->hidden == NULL) ) {
		SDL_OutOfMemory();
		if ( device ) {
			SDL_free(device);
		}
		return(0);
	}
	SDL_memset(device->hidden, 0, (sizeof *device->hidden));

	/* Set the function pointers */
	device->VideoInit = LIBRETRO_VideoInit;
	device->ListModes = LIBRETRO_ListModes;
	device->SetVideoMode = LIBRETRO_SetVideoMode;
	device->CreateYUVOverlay = NULL;
	device->SetColors = LIBRETRO_SetColors;
	device->UpdateRects =LIBRETRO_UpdateRects;
	device->VideoQuit = LIBRETRO_VideoQuit;
	device->AllocHWSurface = NULL;//LIBRETRO_AllocHWSurface;
	device->CheckHWBlit = NULL;//LIBRETRO_CheckHWBlit;
	device->FillHWRect = NULL;//LIBRETRO_FillHWRect;
	device->SetHWColorKey = NULL;//LIBRETRO_SetHWColorKey;
	device->SetHWAlpha = NULL;//LIBRETRO_SetHWAlpha;
	device->LockHWSurface = LIBRETRO_LockHWSurface;
	device->UnlockHWSurface = LIBRETRO_UnlockHWSurface;
	device->FlipHWSurface = NULL;//LIBRETRO_FlipHWSurface;
	device->FreeHWSurface = LIBRETRO_FreeHWSurface;
	device->SetCaption = NULL;
	device->SetIcon = NULL;
	device->IconifyWindow = NULL;
	device->GrabInput = NULL;
	device->GetWMInfo = NULL;

	device->FreeWMCursor    = NULL;//LIBRETRO_FreeWMCursor;
	device->CreateWMCursor  = NULL;//LIBRETRO_CreateWMCursor;
	device->ShowWMCursor    = NULL;//LIBRETRO_ShowWMCursor;
	device->MoveWMCursor = NULL;//LIBRETRO_CURSOR_Move;

	device->InitOSKeymap = LIBRETRO_InitOSKeymap;
	device->PumpEvents = LIBRETRO_PumpEvents;

//	device->info.blit_hw=1;

	device->free = LIBRETRO_DeleteDevice;
       
	return device;
} 

VideoBootStrap LIBRETRO_bootstrap = {
	"LIBRETROvideo", "LIBRETRO Video",
	LIBRETRO_Available, LIBRETRO_CreateDevice
};


int LIBRETRO_VideoInit(_THIS, SDL_PixelFormat *vformat)
{
	/*
	fprintf(stderr, "WARNING: You are using the SDL dummy video driver!\n");
	*/

	/* Determine the screen depth (use default 8-bit depth) */
	/* we change this during the SDL_SetVideoMode implementation... */
        vformat->BitsPerPixel = 32;
        vformat->BytesPerPixel = 4;

	vformat->Amask = 0xff000000;
	vformat->Rmask = 0x00ff0000;
	vformat->Gmask = 0x0000ff00;
	vformat->Bmask = 0x000000ff;

//	LIBRETRO_InitMouse(this);
	LIBRETRO_InitKeyboard(this);

	/* We're done! */
	return(0);
}


const static SDL_Rect
	
    RECT_1920x1080={ 0,0,1920, 1080}, // 1080p
    RECT_1280x720={ 0,0,1280, 720}, // 720p
    RECT_1024x768={ 0,0,1024, 768}, 
    RECT_832x588={ 0,0,832, 588}, 
    RECT_768x544={ 0,0,768, 544}, 
    RECT_720x480={ 0,0,720, 480 }, // 480p
    RECT_720x576={ 0,0,720, 576 }, // 576p
    RECT_640x480={ 0,0,640, 480 },
    RECT_320x240={ 0,0,320, 240 }
;

const static SDL_Rect *vid_modes[] = {
	&RECT_1920x1080,
	&RECT_1280x720,	
	&RECT_1024x768,
	&RECT_832x588,
	&RECT_768x544,
	&RECT_720x480,
	&RECT_720x576,
	&RECT_640x480,
	&RECT_320x240,
	NULL
};

SDL_Rect **LIBRETRO_ListModes(_THIS, SDL_PixelFormat *format, Uint32 flags)
{

	switch(format->BitsPerPixel) {
	
	case 32:		
		return (SDL_Rect **) -1;//&vid_modes;
	default:
		return NULL;
	}
	//return (SDL_Rect **) -1;
}

SDL_Surface *LIBRETRO_SetVideoMode(_THIS, SDL_Surface *current,
				int width, int height, int bpp, Uint32 flags)
{
	if ( this->hidden->buffer ) {
		SDL_free( this->hidden->buffer );
	}

	this->hidden->buffer = SDL_malloc(width * height * (bpp / 8));
	if ( ! this->hidden->buffer ) {
		SDL_SetError("Couldn't allocate buffer for requested mode");
		return(NULL);
	}

/* 	printf("Setting mode %dx%d\n", width, height); */

	SDL_memset(this->hidden->buffer, 0, width * height * (bpp / 8));

	/* Allocate the new pixel format for the screen */
	if ( ! SDL_ReallocFormat(current, bpp, 0, 0, 0, 0) ) {
		SDL_free(this->hidden->buffer);
		this->hidden->buffer = NULL;
		SDL_SetError("Couldn't allocate new pixel format for requested mode");
		return(NULL);
	}

	/* Set up the new mode framebuffer */
	current->flags = flags & SDL_FULLSCREEN;
	this->hidden->w = current->w = width;
	this->hidden->h = current->h = height;
	current->pitch = current->w * (bpp / 8);
	current->pixels = this->hidden->buffer;
//videoBuffer = this->hidden->buffer;

	LIBRETRO_InitMouse(this);

	/* We're done */
	return(current);
}

/* We don't actually allow hardware surfaces other than the main one */
static int LIBRETRO_AllocHWSurface(_THIS, SDL_Surface *surface)
{
	return(-1);
}
static void LIBRETRO_FreeHWSurface(_THIS, SDL_Surface *surface)
{
	return;
}

/* We need to wait for vertical retrace on page flipped displays */
static int LIBRETRO_LockHWSurface(_THIS, SDL_Surface *surface)
{
	return(0);
}

static void LIBRETRO_UnlockHWSurface(_THIS, SDL_Surface *surface)
{
	return;
}

extern void libretro_setbuffer(void *pix,Uint16 x,Uint16 y){

}

static void LIBRETRO_UpdateRects(_THIS, int numrects, SDL_Rect *rects)
{
	/* do nothing. */
	libretro_setbuffer(this->screen->pixels,this->hidden->_omx,this->hidden->_omy);

}

int LIBRETRO_SetColors(_THIS, int firstcolor, int ncolors, SDL_Color *colors)
{
	/* do nothing of note. */
	return(1);
}

/* Note:  If we are terminated, this could be called in the middle of
   another SDL video routine -- notably UpdateRects.
*/
void LIBRETRO_VideoQuit(_THIS)
{    
	LIBRETRO_QuitMouse(this);
	LIBRETRO_QuitKeyboard(this);
	if (this->screen->pixels != NULL)
	{
		SDL_free(this->screen->pixels);
		this->screen->pixels = NULL;
	}
}


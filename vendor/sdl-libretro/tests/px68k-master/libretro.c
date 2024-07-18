
#include <string.h>
#include <stdio.h>
#include <stdlib.h>  

#include "libretro.h"

#define LOGI printf
#define RENDER16B 1

char RPATH[512];
char RETRO_DIR[512];
const char *retro_save_directory;
const char *retro_system_directory;
const char *retro_content_directory;
char retro_system_conf[512];

bool opt_analog;

int retrow=800;
int retroh=600;
int CHANGEAV=0;

int pauseg=0;

signed short soundbuf[1024*2];

uint16_t *videoBuffer;

static retro_video_refresh_t video_cb;
static retro_environment_t environ_cb;
static retro_audio_sample_batch_t audio_batch_cb;
static  retro_input_poll_t input_poll_cb;

retro_input_state_t input_state_cb;
retro_audio_sample_t audio_cb;

void retro_set_video_refresh(retro_video_refresh_t cb) { video_cb = cb; }
void retro_set_audio_sample(retro_audio_sample_t cb) { audio_cb  =cb; }
void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb) { audio_batch_cb = cb; }
void retro_set_input_poll(retro_input_poll_t cb) { input_poll_cb = cb; }
void retro_set_input_state(retro_input_state_t cb) { input_state_cb = cb; }

// these 2 funtions have to be implemented for Libretro SDL port
#ifdef __cplusplus
extern "C" {
#endif
void libretro_audio_cb(int16_t left, int16_t right){
	audio_cb(left,right);
}

short int libretro_input_state_cb(unsigned port,unsigned device,unsigned index,unsigned id){
	return input_state_cb(port,device,index,id);

} 
#ifdef __cplusplus
}
#endif

#define LOGI printf

//Args for experimental_cmdline
static char ARGUV[64][1024];
static unsigned char ARGUC=0;

// Args for Core
static char XARGV[64][1024];
static const char* xargv_cmd[64];
int PARAMCOUNT=0;

extern int cmain(int argc, char *argv[]);

void parse_cmdline( const char *argv );

void Add_Option(const char* option)
{
   static int first=0;

   if(first==0)
   {
      PARAMCOUNT=0;	
      first++;
   }

   sprintf(XARGV[PARAMCOUNT++],"%s\0",option);
}

int pre_main(const char *argv)
{
   int i;
   int Only1Arg;

   parse_cmdline(argv); 

   Only1Arg = (strcmp(ARGUV[0],"px68k") == 0) ? 0 : 1;

   for (i = 0; i<64; i++)
      xargv_cmd[i] = NULL;


   if(Only1Arg)
   {  
      int cfgload=0;

      Add_Option("px68k");

      if (strlen(RPATH) >= strlen("hdf")){
	if(!strcasecmp(&RPATH[strlen(RPATH)-strlen("hdf")], "hdf")){
			Add_Option("-h");
			cfgload=1;
	}
      }

      if(cfgload==0) {
		//Add_Option("-verbose");
		//Add_Option(retro_system_tos);
		//Add_Option("-8");
      }

      Add_Option(RPATH);
   }
   else
   { // Pass all cmdline args
      for(i = 0; i < ARGUC; i++)
         Add_Option(ARGUV[i]);
   }

   for (i = 0; i < PARAMCOUNT; i++)
   {
      xargv_cmd[i] = (char*)(XARGV[i]);
      LOGI("%2d  %s\n",i,XARGV[i]);
   }

   pmain(PARAMCOUNT,( char **)xargv_cmd); 

   xargv_cmd[PARAMCOUNT - 2] = NULL;

   return 0;
}

void parse_cmdline(const char *argv)
{
	char *p,*p2,*start_of_word;
	int c,c2;
	static char buffer[512*4];
	enum states { DULL, IN_WORD, IN_STRING } state = DULL;
	
	strcpy(buffer,argv);
	strcat(buffer," \0");

	for (p = buffer; *p != '\0'; p++)
   {
      c = (unsigned char) *p; /* convert to unsigned char for is* functions */
      switch (state)
      {
         case DULL: /* not in a word, not in a double quoted string */
            if (isspace(c)) /* still not in a word, so ignore this char */
               continue;
            /* not a space -- if it's a double quote we go to IN_STRING, else to IN_WORD */
            if (c == '"')
            {
               state = IN_STRING;
               start_of_word = p + 1; /* word starts at *next* char, not this one */
               continue;
            }
            state = IN_WORD;
            start_of_word = p; /* word starts here */
            continue;
         case IN_STRING:
            /* we're in a double quoted string, so keep going until we hit a close " */
            if (c == '"')
            {
               /* word goes from start_of_word to p-1 */
               //... do something with the word ...
               for (c2 = 0,p2 = start_of_word; p2 < p; p2++, c2++)
                  ARGUV[ARGUC][c2] = (unsigned char) *p2;
               ARGUC++; 

               state = DULL; /* back to "not in word, not in string" state */
            }
            continue; /* either still IN_STRING or we handled the end above */
         case IN_WORD:
            /* we're in a word, so keep going until we get to a space */
            if (isspace(c))
            {
               /* word goes from start_of_word to p-1 */
               //... do something with the word ...
               for (c2 = 0,p2 = start_of_word; p2 <p; p2++,c2++)
                  ARGUV[ARGUC][c2] = (unsigned char) *p2;
               ARGUC++; 

               state = DULL; /* back to "not in word, not in string" state */
            }
            continue; /* either still IN_WORD or we handled the end above */
      }	
   }
}

#include "SDL.h"
SDL_Surface *mysdl_surface;
extern SDL_Event ev;
// prototype for sdlapp.c
extern void init_app();
extern void quit_app();
extern void exec_app();

void quit_app(void){
	end_loop_retro();
	SDL_Quit();
}
void init_app(){}
void checkInput(){}
void exec_app(){
	exec_app_retro();
}

void texture_init(){
        memset(videoBuffer, 0, sizeof(videoBuffer));
} 

void retro_set_environment(retro_environment_t cb)
{
//   bool no_rom = true;

   environ_cb = cb;

 //  cb(RETRO_ENVIRONMENT_SET_SUPPORT_NO_GAME, &no_rom);

   struct retro_variable variables[] = {
      {
         "sdlmandel_analog","Use Analog; OFF|ON",
      },
      { NULL, NULL },
   };

   cb(RETRO_ENVIRONMENT_SET_VARIABLES, variables);

}

static void update_variables(void)
{
   struct retro_variable var = {0};

 
   var.key = "sdlpx68k_analog";
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

void update_input()
{
  input_poll_cb();
}


#if 0
static void keyboard_cb(bool down, unsigned keycode, uint32_t character, uint16_t mod)
{
}
#endif

/************************************
 * libretro implementation
 ************************************/

//static struct retro_system_av_info g_av_info;

void retro_get_system_info(struct retro_system_info *info)
{
    memset(info, 0, sizeof(*info));
	info->library_name = "sdlgfx";
	info->library_version = "0";
	info->need_fullpath = true;
	info->valid_extensions = "dim|zip|img|d88|88d|hdm|dup|2hd|xdf|hdf";
}


void retro_get_system_av_info(struct retro_system_av_info *info)
{
//FIXME handle vice PAL/NTSC
   struct retro_game_geometry geom = { retrow, retroh,800, 600 ,4.0 / 3.0 };
   struct retro_system_timing timing = { 60.0, 44100.0 };

   info->geometry = geom;
   info->timing   = timing;
}

void update_geometry()
{
   struct retro_system_av_info system_av_info;
   system_av_info.geometry.base_width = retrow;
   system_av_info.geometry.base_height = retroh;
   system_av_info.geometry.aspect_ratio = (float)4/3;// retro_aspect;
   environ_cb(RETRO_ENVIRONMENT_SET_GEOMETRY, &system_av_info);
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

//	(void)info;

	printf("LOAD EMU\n");

//	init_app();

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
     pauseg=0;
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

   sprintf(retro_system_conf, "%s/keropi\0",RETRO_DIR);

   LOGI("Retro SYSTEM_DIRECTORY %s\n",retro_system_directory);
   LOGI("Retro SAVE_DIRECTORY %s\n",retro_save_directory);
   LOGI("Retro CONTENT_DIRECTORY %s\n",retro_content_directory);

/*
    enum retro_pixel_format fmt = RETRO_PIXEL_FORMAT_XRGB8888;
    if (!environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &fmt))
    {
        fprintf(stderr, "Pixel format XRGB8888 not supported by platform, cannot use.\n");
        exit(0);
    }
*/   
   enum retro_pixel_format fmt = RETRO_PIXEL_FORMAT_RGB565;
   if (!environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &fmt))
   {
      fprintf(stderr, "RGB565 is not supported.\n");
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

}

void retro_deinit(void)
{
	quit_app();
        printf("Retro DeInit\n");
}

void retro_reset(void)
{
}

static int firstcall=1;

void retro_run(void)
{       

	if(firstcall){
   		pre_main(RPATH);
		firstcall=0;
		printf("INIT done\n");
		return;
	}

   	if (CHANGEAV == 1){
      		update_geometry();
		printf("w:%d h:%d a:%f\n",retrow,retroh,(float)(4/3));
      		CHANGEAV=0;
   	}


	update_input();

	if(pauseg!=-1){

	}

	exec_app();

        video_cb(videoBuffer, retrow, retroh, /*retrow*/ 800 << 1/*2*/);

}


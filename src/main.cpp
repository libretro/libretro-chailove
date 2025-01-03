#define PNTR_PHYSFS_IMPLEMENTATION
#include "pntr_physfs.h"

#define PNTR_APP_IMPLEMENTATION
#define PNTR_ENABLE_DEFAULT_FONT
#define PNTR_ENABLE_TTF
//#define PNTR_ENABLE_VARGS
#define PNTR_ENABLE_MATH
#define PNTR_NO_STDIO
#define PNTR_NO_SAVE_IMAGE
#include "pntr_app.h"

#include "ChaiLove.h"

typedef struct AppData {
    pntr_image* image;
    ChaiLove* chailove;
} AppData;

bool Init(pntr_app* app) {
    // Set up the initial app data.
    AppData* appData = (AppData*)pntr_load_memory(sizeof(AppData));
    pntr_app_set_userdata(app, appData);



    // Initialize PhysFS
    if (PHYSFS_init((const char*)pntr_app_libretro_environ_cb(app)) == 0) {
        pntr_app_log(PNTR_APP_LOG_ERROR, "PHYSFS_init() failed");
        return false;
    }

    // if (PHYSFS_mount("examples", "ex", 1) == 0) {
    //     pntr_app_log(PNTR_APP_LOG_ERROR, "PHYSFS_mount() failed");
    //     return false;
    // };

    // Load the given file.
    unsigned int size;
    void* fileData = pntr_app_load_arg_file(app, &size);
    if (fileData == NULL) {
        pntr_app_log(PNTR_APP_LOG_ERROR, "Failed to load file");
        return false;
    }

    if (PHYSFS_mountMemory((const char*)fileData, (PHYSFS_uint64)size, &pntr_unload_memory, "chailove.zip", NULL, 1) == 0) {

        pntr_unload_memory(fileData);
    }
    if (fileData) {
        appData->image = pntr_load_image_from_memory(PNTR_IMAGE_TYPE_PNG, (const unsigned char*)fileData, size);
    }
    else {
        pntr_app_log(PNTR_APP_LOG_ERROR, "Failed to load file");
    }
	// Find the game path.
	// std::string gamePath(info ? info->path : "");
	// if (gamePath == ".") {
	// 	gamePath = "main.chai";
	// }
	// void* data = NULL;
	// if (info != NULL) {
	// 	data = (void*)info->data;
	// }

    return true;
}

bool Update(pntr_app* app, pntr_image* screen) {
    AppData* appData = (AppData*)pntr_app_userdata(app);

    // Clear the screen
    pntr_clear_background(screen, PNTR_RAYWHITE);

    pntr_draw_image(screen, appData->image, 0, 0);

    // Draw some text
    //pntr_draw_text(screen, appData->font, "Congrats! You created your first pntr_app!", 35, screen->height - 30, PNTR_DARKGRAY);

    return true;
}

void Close(pntr_app* app) {
    AppData* appData = (AppData*)pntr_app_userdata(app);



    ChaiLove::destroy();
}

pntr_app Main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    return (pntr_app) {
        .width = 640,
        .height = 480,
        .title = "libretro_chailove",
        .init = Init,
        .update = Update,
        .close = Close,
        .fps = 0
    };
}

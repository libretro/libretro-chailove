#include "nuklear.h"
#include "../ChaiLove.h"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_IMPLEMENTATION
#define NK_SDL_IMPLEMENTATION
#include "../../vendor/nuklear_sdl_12/nuklear/nuklear.h"
#include "../../vendor/nuklear_sdl_12/nuklear_sdl_12.h"

namespace Modules {
bool nuklear::load() {
	ChaiLove* app = ChaiLove::getInstance();
	ctx = nk_sdl_init(app->graphics.getScreen());
}

void nuklear::draw() {
	ChaiLove* app = ChaiLove::getInstance();
	Color c = app->graphics.getBackgroundColor();
	nk_sdl_render(nk_rgb(c.r, c.g, c.b));
}

void nuklear::unload() {
    nk_sdl_shutdown();
}

void nuklear::inputHandleEvent(SDL_Event *event) {
	nk_sdl_handle_event(event);
}

void nuklear::inputBegin() {
	nk_input_begin(ctx);
}

void nuklear::inputEnd() {
	nk_input_end(ctx);
}

void nuklear::setStyle(int style) {
/*
    set_style(ctx, THEME_WHITE);
    set_style(ctx, THEME_RED);
    set_style(ctx, THEME_BLUE);
    set_style(ctx, THEME_DARK);
*/
}
}

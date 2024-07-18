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

#include "SDL.h"
#include "../../events/SDL_sysevents.h"
#include "../../events/SDL_events_c.h"
#include "SDL_LIBRETROvideo.h"
#include "SDL_LIBRETROevents_c.h"

#include "libretro.h"

void LIBRETRO_PumpMouse(_THIS);
void LIBRETRO_PumpKeyboard(_THIS);

void LIBRETRO_PumpEvents(_THIS)
{
       // input_poll_cb();

	static Uint32 last=0;
	Uint32 now;

	now  = SDL_GetTicks()-last;
	if(now<10)return;

	LIBRETRO_PumpMouse(this);
        LIBRETRO_PumpKeyboard(this);

	last  = SDL_GetTicks();
}

void LIBRETRO_InitOSKeymap(_THIS)
{
	/* do nothing. */
}

/* end of SDL_dcevents.c ... */


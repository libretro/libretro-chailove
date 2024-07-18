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

#ifndef _SDL_LIBRETROvideo_h
#define _SDL_LIBRETROvideo_h

#include "SDL_mouse.h"
#include "SDL_mutex.h"
#include "../SDL_sysvideo.h"

/* Hidden "this" pointer for the video functions */
#define _THIS	SDL_VideoDevice *this

#define u32 Uint32
#define u16 Uint16

/*
typedef struct {
  u32 width;
  u32 height;
  u32 *pixels;
  u32 pitch;
} Bitmap;
*/

struct SDL_PrivateVideoData {

    SDL_bool _mouseConnected;
    Uint8 _mouseButtons;
    int _omx;
    int _omy;

    char Key_Sate[512];
    char old_Key_Sate[512];
/*
   Bitmap    	  bitmap;   
   u32 width;
   u32 height;
*/
    int w, h;
    void *buffer;
    int pitch;
#if 0
   WMcursor* BlankCursor;
   struct
   {
                WMcursor*  Current;                        /* Current mouse cursor */
                uint32_t   X;                                      /* Cursor X Position */
                uint32_t   Y;                                      /* Cursor Y Position */
   }       Cursor;

#endif

};

#define SDL_BlankCursor       (this->hidden->BlankCursor)

#endif /* _SDL_dcvideo_h */

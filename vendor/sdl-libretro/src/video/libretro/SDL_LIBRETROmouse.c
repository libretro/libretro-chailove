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

#include <stdio.h>

#include "SDL_mouse.h"
#include "../../events/SDL_events_c.h"

#include "SDL_LIBRETROmouse_c.h"

#include "SDL_config.h"
#include "SDL_events.h"
//#include "../../events/SDL_mouse_c.h"
#include "libretro.h"

extern short int libretro_input_state_cb(unsigned port,unsigned device,unsigned index,unsigned id);
/*
extern retro_input_state_t input_state_cb;
#define libretro_input_state_cb  input_state_cb
*/

void updateMouseButtons(_THIS) {
   
    Uint8 butt=0;

    if(libretro_input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_LEFT))butt |= 0x1;
    if(libretro_input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_RIGHT))butt |= 0x2;
    if(libretro_input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_MIDDLE))butt |= 0x4;

      
    // Check left mouse button changes
    bool oldLMB = this->hidden->_mouseButtons & 1;
    bool newLMB = butt & 1;
    if (newLMB != oldLMB) {
       // SDL_SendMouseButton(window, newLMB ? SDL_PRESSED : SDL_RELEASED, SDL_BUTTON_LEFT);
        SDL_PrivateMouseButton(newLMB ? SDL_PRESSED : SDL_RELEASED,SDL_BUTTON_LEFT, 0, 0);

    }

    // Check rigth mouse button changes
    bool oldRMB = this->hidden->_mouseButtons & 2;
    bool newRMB = butt & 2;
    if (newRMB != oldRMB) {
      //  SDL_SendMouseButton(window, newRMB ? SDL_PRESSED : SDL_RELEASED, SDL_BUTTON_RIGHT);
         SDL_PrivateMouseButton(newRMB ? SDL_PRESSED : SDL_RELEASED,SDL_BUTTON_RIGHT,0,0);
    }

    // Check middle mouse button changes
    bool oldMMB = this->hidden->_mouseButtons & 4;
    bool newMMB = butt & 4;
    if (newMMB != oldMMB) {
       // SDL_SendMouseButton(window, newMMB ? SDL_PRESSED : SDL_RELEASED, SDL_BUTTON_MIDDLE);
       SDL_PrivateMouseButton(newMMB ? SDL_PRESSED : SDL_RELEASED, SDL_BUTTON_MIDDLE, 0,0);
    }

    this->hidden->_mouseButtons = butt;
}

void updateMousePosition(_THIS) {

    int tmx,tmy;
    static int oldx=160,oldy=120;

    tmx=libretro_input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_X);
    tmy=libretro_input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_Y);

   // printf("t(%d,%d)-",tmx,tmy);
/*
    if(tmx<0)tmx=-1;
    if(tmx>0)tmx=1;
    if(tmy<0)tmy=-1;
    if(tmy>0)tmy=1;
*/
   // printf("t2(%d,%d)-",tmx,tmy);

    this->hidden->_omx += tmx;//libretro_input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_X);
    this->hidden->_omy += tmy;//libretro_input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_Y);

   // printf("o(%d,%d)-",this->hidden->_omx,this->hidden->_omy);

    if(this->hidden->_omx<0)this->hidden->_omx=0;
    if(this->hidden->_omy<0)this->hidden->_omy=0;
    if(this->hidden->_omx>this->hidden->w-1)this->hidden->_omx=this->hidden->w-1;
    if(this->hidden->_omy>this->hidden->h-1)this->hidden->_omy=this->hidden->h-1;

   // printf("abs(%d,%d)\n",this->hidden->_omx,this->hidden->_omy);

    
     // Mouse movement is relative
    //SDL_PrivateMouseMotion(0, 1, tmx,tmy);
    if(oldx!=this->hidden->_omx || oldy!=this->hidden->_omy)
        SDL_PrivateMouseMotion(0, 0, this->hidden->_omx,this->hidden->_omy);

    oldx=this->hidden->_omx;
    oldy=this->hidden->_omy;

}

void updateMouseWheel(_THIS) {

    int     mouse_wu = libretro_input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_WHEELUP);
    int     mouse_wd = libretro_input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_WHEELDOWN);

    if(mouse_wu || mouse_wd){
        SDL_PrivateMouseButton(	SDL_PRESSED, mouse_wd?SDL_BUTTON_WHEELDOWN:SDL_BUTTON_WHEELUP, 0, 0);
        SDL_PrivateMouseButton(	SDL_RELEASED,mouse_wd?SDL_BUTTON_WHEELDOWN:SDL_BUTTON_WHEELUP, 0, 0);
    }
	
   // SDL_SendMouseWheel(window, mouse->tilt, mouse->wheel);
}

void
LIBRETRO_PumpMouse(_THIS)
{
    updateMouseButtons(this);
    updateMousePosition(this);
    updateMouseWheel(this);
}

void
LIBRETRO_InitMouse(_THIS)
{
    this->hidden->_mouseConnected = true;
    this->hidden->_mouseButtons = 0;
    this->hidden->_omx=this->hidden->w/2;//libretro_input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_Y);
    this->hidden->_omy=this->hidden->h/2;//libretro_input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_Y);
    // printf("[%d,%d]-[%d,%d]\n",this->hidden->w,this->hidden->h,this->hidden->_omx,this->hidden->_omy);
    SDL_PrivateMouseMotion(0, 0, this->hidden->_omx,this->hidden->_omy);
}

void
LIBRETRO_QuitMouse(_THIS)
{

}

/* vi: set ts=4 sw=4 expandtab: */

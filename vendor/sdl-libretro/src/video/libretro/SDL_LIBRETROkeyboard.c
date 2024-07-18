/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997-2010 Sam Lantinga

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
#include "SDL_events.h"

//#include "../../events/SDL_keyboard_c.h"
#include "../SDL_sysvideo.h"
#include "../../events/SDL_sysevents.h"
#include "../../events/SDL_events_c.h"

#include "libretro.h"

#include "SDL_LIBRETROkeyboard_c.h"
extern short int libretro_input_state_cb(unsigned port,unsigned device,unsigned index,unsigned id);
/*
extern retro_input_state_t libretro_input_state_cb;
#define libretro_input_state_cb  input_state_cb
*/

#define RETROMOD(a,i) {\
        SDL_keysym sym;\
        memset(&sym, 0, sizeof(SDL_keysym));\
        sym.scancode=i;\
        sym.sym=i;\
        SDL_PrivateKeyboard(a ? SDL_PRESSED : SDL_RELEASED, &sym);\
}

 void Process_key(_THIS)
{
    int i;

    for (i = 0; i < 322; i++)
            this->hidden->Key_Sate[i]=libretro_input_state_cb(0, RETRO_DEVICE_KEYBOARD, 0,i) ? 0x80: 0;

    if (memcmp(this->hidden->Key_Sate,this->hidden->old_Key_Sate , sizeof(this->hidden->Key_Sate))) {
        for (i = 0; i < 322; i++) {
            if(this->hidden->Key_Sate[i] && this->hidden->Key_Sate[i]!=this->hidden->old_Key_Sate[i])
            {

                if(i==RETROK_RCTRL){
                    //CTRLON=-CTRLON;
                    //printf("Modifier crtl pressed %d \n",CTRLON);
                    RETROMOD(1,i);
                    continue;
                }
                if(i==RETROK_RSHIFT){
                    //SHITFON=-SHITFON;
                    //printf("Modifier shift pressed %d \n",SHIFTON);
                    RETROMOD(1,i);
                    continue;
                }

                if(i==RETROK_LCTRL){
                    //CTRLON=-CTRLON;
                    //printf("Modifier crtl pressed %d \n",CTRLON);
                    RETROMOD(1,i);
                    continue;
                }
                if(i==RETROK_LSHIFT){
                    //SHITFON=-SHITFON;
                    //printf("Modifier shift pressed %d \n",SHIFTON);
                    RETROMOD(1,i);
                    continue;
                }

                if(i==RETROK_LALT){
                    //KBMOD=-KBMOD;
                    //printf("Modifier alt pressed %d \n",KBMOD);
                    RETROMOD(1,i);
                    continue;
                }
                if(i==RETROK_RALT){
                    //KBMOD=-KBMOD;
                    //printf("Modifier alt pressed %d \n",KBMOD);
                    RETROMOD(1,i);
                    continue;
                }

                if(i==RETROK_LMETA){
                    //KBMOD=-KBMOD;
                    //printf("Modifier alt pressed %d \n",KBMOD);
                    RETROMOD(1,i);
                    continue;
                }
                if(i==RETROK_RMETA){
                    //KBMOD=-KBMOD;
                    //printf("Modifier alt pressed %d \n",KBMOD);
                    RETROMOD(1,i);
                    continue;
                }

                //printf("press: %d \n",i);
                    RETROMOD(1,i);
                //retro_key_down(i);

            }
            else if ( !this->hidden->Key_Sate[i] && this->hidden->Key_Sate[i]!=this->hidden->old_Key_Sate[i])
            {
                if(i==RETROK_RCTRL){
                    //CTRLON=-CTRLON;
                    //printf("Modifier crtl released %d \n",CTRLON);
                    RETROMOD(0,i);
                    continue;
                }
                if(i==RETROK_RSHIFT){
                    //SHIFTON=-SHIFTON;
                    //printf("Modifier shift released %d \n",SHIFTON);
                    RETROMOD(0,i);
                    continue;
                }

                if(i==RETROK_LCTRL){
                    //CTRLON=-CTRLON;
                    //printf("Modifier crtl pressed %d \n",CTRLON);
                    RETROMOD(0,i);
                    continue;
                }
                if(i==RETROK_LSHIFT){
                    //SHITFON=-SHITFON;
                    //printf("Modifier shift pressed %d \n",SHIFTON);
                    RETROMOD(0,i);
                    continue;
                }

                if(i==RETROK_LALT){
                    //KBMOD=-KBMOD;
                    //printf("Modifier alt released %d \n",KBMOD);
                    RETROMOD(0,i);
                    continue;
                }
                if(i==RETROK_RALT){
                    //KBMOD=-KBMOD;
                    //printf("Modifier alt pressed %d \n",KBMOD);
                    RETROMOD(0,i);
                    continue;
                }

                if(i==RETROK_LMETA){
                    //KBMOD=-KBMOD;
                    //printf("Modifier alt pressed %d \n",KBMOD);
                    RETROMOD(0,i);
                    continue;
                }
                if(i==RETROK_RMETA){
                    //KBMOD=-KBMOD;
                    //printf("Modifier alt pressed %d \n",KBMOD);
                    RETROMOD(0,i);
                    continue;
                }

                //printf("release: %d \n",i);
                RETROMOD(0,i);
                //retro_key_up(i);
            }
        }
    }

    memcpy(this->hidden->old_Key_Sate,this->hidden->Key_Sate , sizeof(this->hidden->Key_Sate) );

}


void LIBRETRO_PumpKeyboard(_THIS)
{
    Process_key(this);
}

void
LIBRETRO_InitKeyboard(_THIS)
{

}

void
LIBRETRO_QuitKeyboard(_THIS)
{

}


/* vi: set ts=4 sw=4 expandtab: */

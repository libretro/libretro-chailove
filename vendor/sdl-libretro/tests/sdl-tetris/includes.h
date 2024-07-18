
// Includes.
#include <stdlib.h>
#include <unistd.h>
#include "SDL.h"
#include <time.h>

#include <math.h>
#define PI 3.1415927

#include "ctypes.h"

#include "menu.h"
#include "game.h"
#include "frame.h"
#include "render.h"
#include "font.h"
#include "sfx.h"

// Define.
#define SCR_Width 320
#define SCR_Height 240

enum
{
	TRIG_UP = 0,
	TRIG_DOWN,	// Trig down et return => pour le menu.
	TRIG_RIGHT,
	TRIG_LEFT,
	TRIG_Return,
	TRIG_Space,
	TRIG_KeyP,
	TRIG_MaxKeys
};

enum
{
	MENU_Null = 0,		// Codes de sortie du menu.
	MENU_Main,
	MENU_Quit,
	MENU_Game,
	MENU_Options,
	MENU_HallOfFame,
	MENU_MaxItem
};

enum
{
	GAME_Null = 0,		// Codes de sortie du jeu.
	GAME_GameOver,
	GAME_Quit,
	GAME_MaxItem
};

enum
{
	OPT_Ghost = 1,
	OPT_Rotation = 1 << 1,
	OPT_BlocksSet = 1 << 2,
	OPT_Sound = 1 << 3,
};

// Types de variables.
struct SGene
{
	SDL_Surface *pScreen;	// Ptr sur le buffer écran.
	u8	*pKeys;		// Buffer clavier (ira pointer une table fournie par SDL).
	u8	pKeysTrig[TRIG_MaxKeys];	// Trigger.

	SDL_Color	pColors[256];	// Palette générale.
	SDL_Color	pCurPal[256];	// Palette lors des fades, pour le Scale 2x en 32 BPP.

	SDL_Surface *pBackground;	// Ptr sur l'image de décor.
	SDL_Surface *pBkgMenu;		// L'image de fond du menu.
	SDL_Surface *pFont1616;		// Ptr sur l'image contenant la fonte.

	u32	nOptFlags;		// Options.

};

struct SExchange	// Echanges entre les modules.
{
	u32	nStartingLevel;		// Niveau de départ.
	u32	nHandicap;		// Handicap de départ.
	u32	nScore;			// Score en sortie.
};

// Variables générales.
extern struct SGene gVar;
extern struct SExchange gExg;



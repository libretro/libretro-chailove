
//-----------------------
//
// A Little Tetris Game
// Done by Clément CORDE
// c1702@yahoo.com
//
//-----------------------

#include "includes.h"


// Variables générales.
struct SGene gVar;
struct SExchange gExg;


// Gestionnaire d'évènements.
int EventHandler(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			// Triggers.
			if (event.key.keysym.sym == SDLK_UP) gVar.pKeysTrig[TRIG_UP] = 1;
			if (event.key.keysym.sym == SDLK_DOWN) gVar.pKeysTrig[TRIG_DOWN] = 1;
			if (event.key.keysym.sym == SDLK_RIGHT) gVar.pKeysTrig[TRIG_RIGHT] = 1;
			if (event.key.keysym.sym == SDLK_LEFT) gVar.pKeysTrig[TRIG_LEFT] = 1;
			if (event.key.keysym.sym == SDLK_p) gVar.pKeysTrig[TRIG_KeyP] = 1;
			if (event.key.keysym.sym == SDLK_RETURN) gVar.pKeysTrig[TRIG_Return] = 1;
			if (event.key.keysym.sym == SDLK_SPACE) gVar.pKeysTrig[TRIG_Space] = 1;

			// Ingame toggles.
			if (event.key.keysym.sym == SDLK_r) gVar.nOptFlags ^= OPT_Rotation;
			if (event.key.keysym.sym == SDLK_g) gVar.nOptFlags ^= OPT_Ghost;

			if (gVar.pKeys[SDLK_ESCAPE]) exit(0);//return (1);	// Arrêt d'urgence !

			// Toggle fullscreen/windowed.
			if (gVar.pKeys[SDLK_F10])
			{
				gRender.nFullscreenMode ^= 1;
				Render_SetVideoMode();
			}
			// Toggle render mode.
			if (gVar.pKeys[SDLK_F9])
			{
				if (++gRender.nRenderMode >= e_RenderMode_MAX) gRender.nRenderMode = 0;
				Render_SetVideoMode();
			}

			break;

		case SDL_KEYUP:
			break;

		case SDL_QUIT:		// Fermeture de la fenêtre.
			exit(0);
			break;
		}
	}
	return (0);
}

// Load image.
void LoadPic(SDL_Surface **pDst, char *pFilename)
{
	*pDst = SDL_LoadBMP(pFilename);
	if (*pDst == NULL) {
		fprintf(stderr, "Couldn't load picture '%s': %s\n", pFilename, SDL_GetError());
		exit(1);
	}
}

// Le Menu (générique).
u32 Menu(void (*pFctInit)(void), u32 (*pFctMain)(void))
{
	u32	i;
	u32	nMenuVal = MENU_Null;

	// Copie de la palette qui va bien.
	for (i = 0; i < gVar.pBkgMenu->format->palette->ncolors; i++)
		gVar.pColors[i] = gVar.pBkgMenu->format->palette->colors[i];

	// Sets up palette.
	//SDL_SetColors(gVar.pScreen, gVar.pBkgMenu->format->palette->colors, 0, gVar.pBkgMenu->format->palette->ncolors);
//	SDL_SetPalette(gVar.pScreen, SDL_LOGPAL, gVar.pBkgMenu->format->palette->colors, 0, gVar.pBkgMenu->format->palette->ncolors);
	SDL_SetPalette(gVar.pScreen, SDL_LOGPAL, gVar.pColors, 0, 256);

	// Main loop.
	(*pFctInit)();
	FrameInit();
	while (nMenuVal == MENU_Null)
	{
		// Nettoyage du trigger.
		for (i = 0; i < TRIG_MaxKeys; i++) gVar.pKeysTrig[i] = 0;

		// Gestion des évenements.
		EventHandler();

		SDL_BlitSurface(gVar.pBkgMenu, NULL, gVar.pScreen, NULL);	// Recopie le décor.
		nMenuVal = (*pFctMain)();		// Menu Main.
		RenderFlip(1);	// Wait for frame, Flip.

	}

	return (nMenuVal);
}

// Le jeu.
void Game(void)
{
	u32	i;
	u32	nTetVal = GAME_Null;

	// Copie de la palette qui va bien.
	for (i = 0; i < gVar.pBackground->format->palette->ncolors; i++)
		gVar.pColors[i] = gVar.pBackground->format->palette->colors[i];

	// Sets up palette.
	//SDL_SetColors(gVar.pScreen, gVar.pBackground->format->palette->colors, 0, gVar.pBackground->format->palette->ncolors);
//	SDL_SetPalette(gVar.pScreen, SDL_LOGPAL, gVar.pBackground->format->palette->colors, 0, gVar.pBackground->format->palette->ncolors);
	SDL_SetPalette(gVar.pScreen, SDL_LOGPAL, gVar.pColors, 0, 256);

	// Main loop.
	TetrisInit();
	FrameInit();
	while (nTetVal == GAME_Null)
	{
		// Nettoyage du trigger.
		for (i = 0; i < TRIG_MaxKeys; i++) gVar.pKeysTrig[i] = 0;

		// Gestion des évenements.
		EventHandler();

		SDL_BlitSurface(gVar.pBackground, NULL, gVar.pScreen, NULL);	// Recopie le décor.
		nTetVal = TetrisMain();		// Game.
		RenderFlip(1);	// Wait for frame, Flip.

	}

	// High score ?
	if (nTetVal == GAME_GameOver)
	{
		if (Scr_CheckHighSc(gExg.nScore) >= 0)
		{
			// Saisie du nom.
			Menu(MenuGetNameInit, MenuGetName);
			// Affichage de la table des high scores.
			Menu(MenuMainInit, MenuHighScores);	// !!! Même init que main !!!
		}
	}

}

// Point d'entrée.
#ifdef __LIBRETRO__
int tmain(int argc, char *argv[])
#else
int main(int argc, char *argv[])
#endif
{
	u32	nLoop = 1;
	u32	nMenuVal;

	// SDL Init.
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}
#ifndef __LIBRETRO__
	// atexit : Quand on quittera (exit, return...), SDL_Quit() sera appelée.
	atexit(SDL_Quit);
#endif

	// Video mode init.
	Render_InitVideo();
	SDL_WM_SetCaption("Tetris", NULL);		// Nom de la fenêtre.
	gRender.nRenderMode = e_RenderMode_Scale2x;
	Render_SetVideoMode();

	gVar.pKeys = SDL_GetKeyState(NULL);		// Init du ptr clavier.

	// Load backgound picture.
	LoadPic(&gVar.pBackground, "gfx/bkg.bmp");
	// Load menu backgound picture.
	LoadPic(&gVar.pBkgMenu, "gfx/bkg_menu.bmp");
	// Load bitmap 16x16 font.
	LoadPic(&gVar.pFont1616, "gfx/fnt.bmp");

	// Init sound.
	Sfx_SoundInit();
	Sfx_LoadWavFiles();
	Sfx_SoundOn();	// Starts playback.

	Scr_Load();		// Lecture du fichier des high scores.
	Opt_Load();		// Lecture des options.

	MenuInitMisc();

	SDL_ShowCursor(SDL_DISABLE);	// Cache le pointeur de la souris.

	// Boucle infinie.
	gExg.nStartingLevel = 1;
	gExg.nHandicap = 0;
	nMenuVal = MENU_Main;
	while (nLoop)
	{
		switch (nMenuVal)
		{
		case MENU_Main:		// Main menu.
			nMenuVal = Menu(MenuMainInit, MenuMain);
			break;

		case MENU_Game:		// Jeu.
			Game();
			nMenuVal = MENU_Main;
			break;

		case MENU_HallOfFame:	// High scores.
			Menu(MenuMainInit, MenuHighScores);	// !!! Même init que main !!!
			nMenuVal = MENU_Main;
			break;

		case MENU_Options:	// Options.
			Menu(MenuMainInit, MenuOptions);	// !!! Même init que main !!!
			nMenuVal = MENU_Main;
			break;

		case MENU_Quit:		// Sortie.
			nLoop = 0;
			break;
		}

	}

	SDL_ShowCursor(SDL_ENABLE);		// Réautorise l'affichage du curseur de la souris.

	Sfx_SoundOff();		// Stops playback.
	Sfx_FreeWavFiles();	// Libère les ressources des fx.

	// Free the allocated BMP surfaces.
	SDL_FreeSurface(gVar.pBackground);
	SDL_FreeSurface(gVar.pBkgMenu);
	SDL_FreeSurface(gVar.pFont1616);

	// Libère les ressources de rendu.
	RenderRelease();

	return (0);
}



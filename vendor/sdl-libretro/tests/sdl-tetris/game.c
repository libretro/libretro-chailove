
#include "includes.h"

// Lg jeu = 10. +1 mur et 2 vides de chaque côté.
// Ht jeu = 18. +4 en haut pour apparition, +1 sol et 2 vides en dessous.
#define	TET_AREA_LG 16	//16
#define TET_AREA_HT 25

#define	TET_DRAW_LG 10	//10
#define TET_DRAW_HT 18

#define TET_GFX_OFFSX	26	// Offset aire de jeu.
#define TET_GFX_OFFSY	12
#define TET_GFX_OffsNextX	207	// Offset Next pièce.
#define TET_GFX_OffsNextY	30

#define TET_Score_Block		4
#define TET_Score_1Line		10
#define TET_Score_2Lines	25
#define TET_Score_3Lines	50
#define TET_Score_4Lines	100

#define TET_LinesPerLevel	10
#define TET_MaxLevel		10

enum
{
	TET_State_Play = 0,
	TET_State_GameOver,
	TET_State_Pause,
	TET_State_Intro,
	TET_State_FadeOut,
};

#define MAX_PIECES 15

#define	BLOCKS_MOD_NORM	7
#define	BLOCKS_MOD_EXT	MAX_PIECES

// Les pièces sur tous leurs 4 angles.
u8 gpPieces[MAX_PIECES][4][16] =		// 4 angles * tableau 4*4.
{
	// Pièce 1 : Barre.
	{
		{ 0,0,0,0,
		  1,1,1,1,
		  0,0,0,0,
		  0,0,0,0 },
		{ 0,1,0,0,
		  0,1,0,0,
		  0,1,0,0,
		  0,1,0,0 },
		{ 0,0,0,0,
		  1,1,1,1,
		  0,0,0,0,
		  0,0,0,0 },
		{ 0,1,0,0,
		  0,1,0,0,
		  0,1,0,0,
		  0,1,0,0 }
	},
	// Pièce 2 : L à l'endroit.
	{
		{ 0,7,0,0,
		  0,7,0,0,
		  0,7,7,0,
		  0,0,0,0 },
		{ 0,0,0,0,
		  7,7,7,0,
		  7,0,0,0,
		  0,0,0,0 },
		{ 0,7,7,0,
		  0,0,7,0,
		  0,0,7,0,
		  0,0,0,0 },
		{ 0,0,7,0,
		  7,7,7,0,
		  0,0,0,0,
		  0,0,0,0 }
	},
	// Pièce 3 : L à l'envers.
	{
		{ 0,0,5,0,
		  0,0,5,0,
		  0,5,5,0,
		  0,0,0,0 },
		{ 5,0,0,0,
		  5,5,5,0,
		  0,0,0,0,
		  0,0,0,0 },
		{ 0,5,5,0,
		  0,5,0,0,
		  0,5,0,0,
		  0,0,0,0 },
		{ 0,0,0,0,
		  5,5,5,0,
		  0,0,5,0,
		  0,0,0,0 }
	},
	// Pièce 4 : T retourné.
	{
		{ 0,0,0,0,
		  0,4,0,0,
		  4,4,4,0,
		  0,0,0,0 },
		{ 0,4,0,0,
		  0,4,4,0,
		  0,4,0,0,
		  0,0,0,0 },
		{ 0,0,0,0,
		  4,4,4,0,
		  0,4,0,0,
		  0,0,0,0 },
		{ 0,4,0,0,
		  4,4,0,0,
		  0,4,0,0,
		  0,0,0,0 }
	},
	// Pièce 5 : Carré.
	{
		{ 0,0,0,0,
		  0,3,3,0,
		  0,3,3,0,
		  0,0,0,0 },
		{ 0,0,0,0,
		  0,3,3,0,
		  0,3,3,0,
		  0,0,0,0 },
		{ 0,0,0,0,
		  0,3,3,0,
		  0,3,3,0,
		  0,0,0,0 },
		{ 0,0,0,0,
		  0,3,3,0,
		  0,3,3,0,
		  0,0,0,0 }
	},
	// Pièce 6 : S.
	{
		{ 0,6,0,0,
		  0,6,6,0,
		  0,0,6,0,
		  0,0,0,0 },
		{ 0,0,0,0,
		  0,6,6,0,
		  6,6,0,0,
		  0,0,0,0 },
		{ 0,6,0,0,
		  0,6,6,0,
		  0,0,6,0,
		  0,0,0,0 },
		{ 0,0,0,0,
		  0,6,6,0,
		  6,6,0,0,
		  0,0,0,0 }
	},
	// Pièce 7 : S à l'envers.
	{
		{ 0,0,2,0,
		  0,2,2,0,
		  0,2,0,0,
		  0,0,0,0 },
		{ 0,0,0,0,
		  2,2,0,0,
		  0,2,2,0,
		  0,0,0,0 },
		{ 0,0,2,0,
		  0,2,2,0,
		  0,2,0,0,
		  0,0,0,0 },
		{ 0,0,0,0,
		  2,2,0,0,
		  0,2,2,0,
		  0,0,0,0 }
	},

	// Extended blocks.
	// Pièce 8.
	{
		{ 1,1,0,0,
		  0,1,0,0,
		  0,1,1,0,
		  0,0,0,0 },
		{ 0,0,1,0,
		  1,1,1,0,
		  1,0,0,0,
		  0,0,0,0 },
		{ 1,1,0,0,
		  0,1,0,0,
		  0,1,1,0,
		  0,0,0,0 },
		{ 0,0,1,0,
		  1,1,1,0,
		  1,0,0,0,
		  0,0,0,0 },
	},
	// Pièce 9.
	{
		{ 2,0,0,0,
		  2,0,0,0,
		  2,2,2,0,
		  0,0,0,0 },
		{ 2,2,2,0,
		  2,0,0,0,
		  2,0,0,0,
		  0,0,0,0 },
		{ 2,2,2,0,
		  0,0,2,0,
		  0,0,2,0,
		  0,0,0,0 },
		{ 0,0,2,0,
		  0,0,2,0,
		  2,2,2,0,
		  0,0,0,0 },
	},
	// Pièce 10.
	{
		{ 0,0,3,0,
		  0,3,3,0,
		  3,3,0,0,
		  0,0,0,0 },
		{ 3,0,0,0,
		  3,3,0,0,
		  0,3,3,0,
		  0,0,0,0 },
		{ 0,3,3,0,
		  3,3,0,0,
		  3,0,0,0,
		  0,0,0,0 },
		{ 3,3,0,0,
		  0,3,3,0,
		  0,0,3,0,
		  0,0,0,0 },
	},
	// Pièce 11.
	{
		{ 0,4,0,0,
		  4,4,4,0,
		  0,4,0,0,
		  0,0,0,0 },
		{ 0,4,0,0,
		  4,4,4,0,
		  0,4,0,0,
		  0,0,0,0 },
		{ 0,4,0,0,
		  4,4,4,0,
		  0,4,0,0,
		  0,0,0,0 },
		{ 0,4,0,0,
		  4,4,4,0,
		  0,4,0,0,
		  0,0,0,0 },
	},
	// Pièce 12.
	{
		{ 0,5,5,0,
		  0,5,5,0,
		  0,5,0,0,
		  0,0,0,0 },
		{ 0,0,0,0,
		  5,5,5,0,
		  0,5,5,0,
		  0,0,0,0 },
		{ 0,5,0,0,
		  5,5,0,0,
		  5,5,0,0,
		  0,0,0,0 },
		{ 5,5,0,0,
		  5,5,5,0,
		  0,0,0,0,
		  0,0,0,0 },
	},
	// Pièce 13.
	{
		{ 0,6,6,0,
		  6,6,0,0,
		  0,6,0,0,
		  0,0,0,0 },
		{ 0,6,0,0,
		  6,6,6,0,
		  0,0,6,0,
		  0,0,0,0 },
		{ 0,6,0,0,
		  0,6,6,0,
		  6,6,0,0,
		  0,0,0,0 },
		{ 6,0,0,0,
		  6,6,6,0,
		  0,6,0,0,
		  0,0,0,0 },
	},
	// Pièce 14.
	{
		{ 7,7,7,0,
		  0,7,0,0,
		  0,7,0,0,
		  0,0,0,0 },
		{ 0,0,7,0,
		  7,7,7,0,
		  0,0,7,0,
		  0,0,0,0 },
		{ 0,7,0,0,
		  0,7,0,0,
		  7,7,7,0,
		  0,0,0,0 },
		{ 7,0,0,0,
		  7,7,7,0,
		  7,0,0,0,
		  0,0,0,0 },
	},
	// Pièce 15.
	{
		{ 0,0,0,0,
		  1,0,1,0,
		  1,1,1,0,
		  0,0,0,0 },
		{ 0,1,1,0,
		  0,1,0,0,
		  0,1,1,0,
		  0,0,0,0 },
		{ 0,0,0,0,
		  1,1,1,0,
		  1,0,1,0,
		  0,0,0,0 },
		{ 1,1,0,0,
		  0,1,0,0,
		  1,1,0,0,
		  0,0,0,0 },
	},

};



struct STetris
{
	u8	pArea[TET_AREA_LG * TET_AREA_HT];	// Aire de jeu.
	u8	pLines[TET_AREA_HT];			// Flag pour ligne complète.

	u8	pRndLimit[MAX_PIECES];		// Pour limite des pièces identiques.

	u32	nCurPiece;
	u32	nNextPiece;

	u32	nPosX, nPosY;		// Pos (x,y) de la pièce (du bloc 4*4) dans l'aire de jeu.
	u32	nSpeed, nSpdInc;
	u32	nAngle;			// [0;3].

	u32	nGameState, nLastState;	// Phase en cours.
	u32	nWait;			// Attente. Divers usages.

	s32	nFadeVal;		// Valeur du fade.

	u32	nScore, nLines, nLevel;

};
struct STetris	gTetris;



// Nouvelle pièce.
void NewBlock(void)
{
	static	u8	nCnt;	// Incrémentée à chaque passage. Si on tire trop de blocs étendus, c'est injouable.

/*
// Version 1 :
	// Tirage de la nouvelle pièce.
	gTetris.nCurPiece = gTetris.nNextPiece;
	//gTetris.nNextPiece = rand() % (gVar.nOptFlags & OPT_BlocksSet ? BLOCKS_MOD_EXT : BLOCKS_MOD_NORM);
	gTetris.nNextPiece = rand() % ((gVar.nOptFlags & OPT_BlocksSet) && (++nCnt & 1) ? BLOCKS_MOD_EXT : BLOCKS_MOD_NORM);
*/


// Version 2 :
	// Quand toutes les pièces "normales" on été tirées au moins 1 fois, on décrémente les cases.
	// Entre temps, chaque pièce ne sort au maximum que 2 fois.
	u32	i;

	// Tirage de la nouvelle pièce.
	gTetris.nCurPiece = gTetris.nNextPiece;
	gTetris.nNextPiece = rand() % ((gVar.nOptFlags & OPT_BlocksSet) && (++nCnt & 1) ? BLOCKS_MOD_EXT : BLOCKS_MOD_NORM);
	while (gTetris.pRndLimit[gTetris.nNextPiece] > 1)
	{
		gTetris.nNextPiece++;
		if (gTetris.nNextPiece >= BLOCKS_MOD_NORM) gTetris.nNextPiece = 0;
	}
	gTetris.pRndLimit[gTetris.nNextPiece]++;
	for (i = 0; i < BLOCKS_MOD_NORM; i++) if (gTetris.pRndLimit[i] == 0) break;
	if (i == BLOCKS_MOD_NORM)
	{
		for (i = 0; i < BLOCKS_MOD_NORM; i++) gTetris.pRndLimit[i]--;	// On décrémente les pièces normales...
		for (; i < MAX_PIECES; i++) gTetris.pRndLimit[i] = 0;			// ... et on raz des pièces étendues.
	}


	// Reset position.
	gTetris.nPosX = (TET_AREA_LG / 2) - 2;	// Le bloc fait 4x4.
	gTetris.nPosY = 0;
	gTetris.nAngle = 0;
	// RAZ virgule vitesse.
	gTetris.nSpeed = 0;
}

// Initialise la vitesse en fonction du niveau.
void InitSpeed(void)
{
	// Level de 1 à 10.
	gTetris.nSpdInc = (0x30 * gTetris.nLevel) / TET_MaxLevel;

}

// Init générale.
void TetrisInit(void)
{
	u32	i;

	// Clean toute la zone.
	for (i = 0; i < TET_AREA_LG * TET_AREA_HT; i++)
	{
		gTetris.pArea[i] = 0;
	}
	// Place les murs (limites droite et gauche).
	for (i = 0; i < TET_AREA_HT; i++)
	{
		gTetris.pArea[2 + (i * TET_AREA_LG)] = 1;
		gTetris.pArea[3 + TET_DRAW_LG + (i * TET_AREA_LG)] = 1;
		gTetris.pLines[i] = 0;				// + clear flag lignes complètes.
	}
	// Place le sol.
	for (i = 0; i < TET_AREA_LG; i++)
	{
		gTetris.pArea[i + ((TET_AREA_HT - 3) * TET_AREA_LG)] = 1;
	}

	// Placement du handicap de départ (si nécessaire).
	for (i = 0; i < gExg.nHandicap * 2; i++)
	{
		u32	j, k;

		for (j = 0; j < 3; j++)
		{
			k = rand() % TET_DRAW_LG;
			gTetris.pArea[k + 3 + ((TET_AREA_HT - 3 - (i+1)) * TET_AREA_LG)] = 1;
		}
	}

	// Clean table des pièces identiques.
	for (i = 0; i < MAX_PIECES; i++) gTetris.pRndLimit[i] = 0;

	// Init de la nouvelle pièce. 2 fois pour init Next et Current.
	srand(time(NULL));		// Init hasard.
	NewBlock();
	NewBlock();

	// Misc.
	gTetris.nFadeVal = -1;		// Fade arrêt.
	//
	gTetris.nGameState = TET_State_Intro;
	gTetris.nWait = (TET_DRAW_HT << 2) | 0x03;
	gTetris.nNextPiece = gTetris.nCurPiece;
	//
	gTetris.nFadeVal = 0;
	//
	gTetris.nScore = 0;
	gTetris.nLines = 0;
	gTetris.nLevel = gExg.nStartingLevel;
	InitSpeed();			// Initialise la vitesse.

}

// Check !
// On regarde s'il y a collision en (x,y) pour une pièce.
u32 Check(u32 nPosX, u32 nPosY, u32 nAngle)
{
	u32	x, y;

	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			if (gpPieces[gTetris.nCurPiece][nAngle][(y * 4) + x] &&
					gTetris.pArea[((nPosY + y) * TET_AREA_LG) + (nPosX + x)])
			{
				return (1);	// Collision.
			}
		}
	}

	// Il n'y a pas eu de collisions.
	return (0);
}

// Dessine un bloc à l'écran.
// !!! L'écran doit être locké !!!
void DrawBlockGfx(u32 nScrPosX, u32 nScrPosY, u32 nColor)
{
	u32	j;
	u8	*pDst, *pSrc;
	s32	nDstPitch, nSrcPitch;

	// Init Src et Dst.
	pDst = (u8 *)gVar.pScreen->pixels;
	nDstPitch = gVar.pScreen->pitch;
	pSrc = (u8 *)gVar.pBackground->pixels;
	nSrcPitch = gVar.pBackground->pitch;
	pSrc += (SCR_Height * nSrcPitch) + (nColor * 12);
	// Dessin du bloc 12x12.
	for (j = 0; j < 12; j++)
	{
		// Optim minimum.
		*(u32 *)(pDst + ((j + nScrPosY) * nDstPitch) + nScrPosX) = *(u32 *)(pSrc + (j * nSrcPitch));
		*(u32 *)(pDst + ((j + nScrPosY) * nDstPitch) + nScrPosX + 4) = *(u32 *)(pSrc + (j * nSrcPitch) + 4);
		*(u32 *)(pDst + ((j + nScrPosY) * nDstPitch) + nScrPosX + 8) = *(u32 *)(pSrc + (j * nSrcPitch) + 8);
	}

}

// Dessin de l'aire de jeu.
void Draw(void)
{
	u32	x, y;
	u32	nVal;

	SDL_LockSurface(gVar.pScreen);

	// Parcours de l'aire de jeu.
	for (y = 0; y < TET_DRAW_HT; y++)
	{
		for (x = 0; x < TET_DRAW_LG; x++)
		{
			nVal = gTetris.pArea[((y + 4) * TET_AREA_LG) + (x + 3)];
			if (nVal)
			{
				DrawBlockGfx((x * 12) + TET_GFX_OFFSX, (y * 12) + TET_GFX_OFFSY, nVal - 1);
			}
		}
	}

	// Ghost ?
	if (gVar.nOptFlags & OPT_Ghost)
	{
		u32	nGhostY;

		// Recherche de la position du ghost.
		nGhostY = gTetris.nPosY;
		while (Check(gTetris.nPosX, nGhostY + 1, gTetris.nAngle) == 0) nGhostY++;
		// Dessin du ghost.
		if (nGhostY != gTetris.nPosY)
		for (y = 0; y < 4; y++)
		{
			if ((s32)(y + nGhostY - 4) >= 0)
			for (x = 0; x < 4; x++)
			{
				nVal = gpPieces[gTetris.nCurPiece][gTetris.nAngle][(y * 4) + x];
				if (nVal)
				{
					DrawBlockGfx(((x + gTetris.nPosX - 3) * 12) + TET_GFX_OFFSX, ((y + nGhostY - 4) * 12) + TET_GFX_OFFSY, 8);
				}
			}
		}
	}

	// Dessin de la pièce en cours.
	for (y = 0; y < 4; y++)
	{
		if ((s32)(y + gTetris.nPosY - 4) >= 0)
		for (x = 0; x < 4; x++)
		{
			nVal = gpPieces[gTetris.nCurPiece][gTetris.nAngle][(y * 4) + x];
			if (nVal)
			{
				DrawBlockGfx(((x + gTetris.nPosX - 3) * 12) + TET_GFX_OFFSX, ((y + gTetris.nPosY - 4) * 12) + TET_GFX_OFFSY, nVal - 1);
			}
		}
	}

	SDL_UnlockSurface(gVar.pScreen);

}

// Dessine la Next Piece.
void DrawNext(void)
{
	s32	x, y, offsx, offsy;
	u32	nVal;
	s8	pOffs[MAX_PIECES * 2] =
		{ 6,12, 6,12, 6,12, 12,0, 6,6, 6,12, 6,12,				// Normaux.
		  12,12, 12,12, 12,12, 12,12, 6,12, 12,12, 12,12, 12,6 };		// Extended.

	SDL_LockSurface(gVar.pScreen);

	// Décalages suivant les pièces.
	offsx = TET_GFX_OffsNextX + pOffs[gTetris.nNextPiece * 2];
	offsy = TET_GFX_OffsNextY + pOffs[(gTetris.nNextPiece * 2) + 1];

	// Dessin de la pièce suivante.
	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			nVal = gpPieces[gTetris.nNextPiece][0][(y * 4) + x];
			if (nVal)
			{
				DrawBlockGfx((x  * 12) + offsx, (y * 12) + offsy, nVal - 1);
			}
		}
	}

	SDL_UnlockSurface(gVar.pScreen);

}

// Pause, s'il y a qque chose à dessiner, c'est ici.
void DrawPause(void)
{
	if (gTetris.nGameState != TET_State_Pause) return;

	FontPrint((gVar.pScreen->pitch * 112) + 46, "PAUSE");

}

// Intro, petite présentation au départ.
// L'aire de jeu est pleine et se vide.
void DrawIntro(void)
{
	s32	y, x;

	if (gTetris.nGameState != TET_State_Intro) return;

	SDL_LockSurface(gVar.pScreen);

	// Dessin des lignes.
	x = 0;
	for (y = gTetris.nWait >> 2; y > 0; y--)
	{
		for (x = 0; x < TET_DRAW_LG; x++)
		{
			DrawBlockGfx((x * 12) + TET_GFX_OFFSX, ((TET_DRAW_HT - y) * 12) + TET_GFX_OFFSY, 7);
		}
	}

	SDL_UnlockSurface(gVar.pScreen);

}

// Game Over.
// L'aire de jeu se remplit de lignes.
void DrawGameOver(void)
{
	s32	y, x;

	if (gTetris.nGameState != TET_State_GameOver) return;

	SDL_LockSurface(gVar.pScreen);

	// Dessin des lignes.
	x = 0;
	for (y = TET_DRAW_HT - (gTetris.nWait >> 2); y > 0; y--)
	{
		for (x = 0; x < TET_DRAW_LG; x++)
		{
			DrawBlockGfx((x * 12) + TET_GFX_OFFSX, ((TET_DRAW_HT - y) * 12) + TET_GFX_OFFSY, 7);
		}
	}

	SDL_UnlockSurface(gVar.pScreen);

}

// Fade.
void Fade(s32 nFadeVal)
{
	if (nFadeVal < 0) return;

	SDL_Color	*pSrc = gVar.pColors;
	u32	i, nNbColors;

	nNbColors = 256;
	if (nFadeVal > 255) nFadeVal = 255;
	for (i = 0; i < nNbColors; i++)
	{
		gVar.pCurPal[i].r = (pSrc->r * nFadeVal) / 255;
		gVar.pCurPal[i].g = (pSrc->g * nFadeVal) / 255;
		gVar.pCurPal[i].b = (pSrc->b * nFadeVal) / 255;
		pSrc++;
	}
	SDL_SetPalette(Render_GetRealVideoSurfPtr(), SDL_PHYSPAL, gVar.pCurPal, 0, nNbColors);		// Pour le fade, c'est bien la palette PHYSIQUE de la surface écran réelle.

}

// Gestion état Wait : En attente avant de faire disparaitre les lignes complètes.
void TetrisWait(void)
{
	u32	x, y;
	u32	y2;

	gTetris.nWait--;
	if (gTetris.nWait == 0)
	{
		// Timer à 0, on dégage les lignes.

		// Suppression des lignes.
		for (y = TET_DRAW_HT + 4 - 1; y >= 1; y--)
		{
			if (gTetris.pLines[y])
			{
				// Recopie.
				for (y2 = y; y2 >= 1; y2--)
				{
					for (x = 0; x < TET_DRAW_LG; x++)
					{
						gTetris.pArea[(y2 * TET_AREA_LG) + (x + 3)] =
							gTetris.pArea[((y2 - 1) * TET_AREA_LG) + (x + 3)];
					}
					gTetris.pLines[y2] = gTetris.pLines[y2 - 1];
				}
				// Première ligne à 0.
				for (x = 0; x < TET_DRAW_LG; x++)
				{
					gTetris.pArea[x + 3] = 0;
				}
				gTetris.pLines[0] = 0;
				y++;
			}
		}

		// RAZ flags lignes.
		for (y = 0; y < TET_AREA_HT; y++)
		{
			gTetris.pLines[y] = 0;
		}

	}
	else
	{
		// En attente.

		// On fait clignoter les lignes complètes.
		for (y = 0; y < TET_DRAW_HT; y++)
		{
			if (gTetris.pLines[y + 4])
			for (x = 0; x < TET_DRAW_LG; x++)
			{
				gTetris.pArea[((y + 4) * TET_AREA_LG) + (x + 3)] = gTetris.nWait & 7;
			}
		}

	}

}

#define	KB_REPEAT_1ST	12
// Game : La gestion du jeu normal.
void TetrisGame(void)
{
	u32	x, y;
	u32	nLn, nLn2;
	u32	nVal;

	static	u32	nRepeatR, nRepeatL;

	// Gestion de la répétition des touches.
	if (gVar.pKeys[SDLK_RIGHT] == 0) nRepeatR = 0;
	nRepeatR++;
	if (nRepeatR > KB_REPEAT_1ST && (nRepeatR & 0x03) == 0) gVar.pKeysTrig[TRIG_RIGHT] = 1;
	if (gVar.pKeys[SDLK_LEFT] == 0) nRepeatL = 0;
	nRepeatL++;
	if (nRepeatL > KB_REPEAT_1ST && (nRepeatL & 0x03) == 0) gVar.pKeysTrig[TRIG_LEFT] = 1;

	// Déplacement ?
	if (gVar.pKeysTrig[TRIG_RIGHT])
	{
		if (Check(gTetris.nPosX + 1, gTetris.nPosY, gTetris.nAngle) == 0)
		{
			gTetris.nPosX += 1;
		}
	}
	if (gVar.pKeysTrig[TRIG_LEFT])
	{
		if (Check(gTetris.nPosX - 1, gTetris.nPosY, gTetris.nAngle) == 0)
		{
			gTetris.nPosX -= 1;
		}
	}
	// Rotation ?
	if (gVar.pKeysTrig[TRIG_UP])
	{
		s32	nRot = (gVar.nOptFlags & OPT_Rotation ? -1 : 1);	// Sens de rotation.
		u8	nPrevAngle = gTetris.nAngle;

		if (Check(gTetris.nPosX, gTetris.nPosY, (gTetris.nAngle + nRot) & 3) == 0)
		{
			gTetris.nAngle += nRot;
			gTetris.nAngle &= 3;
		}

		else
		{
			// Aide : Si on ne peut pas tourner, on regarde une case à droite et à gauche.
			// Si ça passe, on y va.
			if (Check(gTetris.nPosX - 1, gTetris.nPosY, (gTetris.nAngle + nRot) & 3) == 0)
			{
				gTetris.nPosX -= 1;
				gTetris.nAngle += nRot;
				gTetris.nAngle &= 3;
			}
			else
			if (Check(gTetris.nPosX + 1, gTetris.nPosY, (gTetris.nAngle + nRot) & 3) == 0)
			{
				gTetris.nPosX += 1;
				gTetris.nAngle += nRot;
				gTetris.nAngle &= 3;
			}

		}

		// Sfx.
		if (gTetris.nAngle != nPrevAngle) Sfx_PlaySfx(e_Sfx_PieceRotate, e_SfxPrio_10);

	}

	// Vitesse.
	if (gVar.pKeysTrig[TRIG_Space])	// Espace : On pose la pièce directement.
	{
		// On teste toutes les lignes jusqu'à ce qu'on ne puisse plus descendre.
		while (Check(gTetris.nPosX, gTetris.nPosY + 1, gTetris.nAngle) == 0) gTetris.nPosY++;
		gTetris.nSpeed |= 0x100;	// On va forcer la dernière descente de ligne.
	}
	if (gVar.pKeys[SDLK_DOWN])
	{
		// Accélération.
		gTetris.nSpeed += 0x80;		// Revoir. Pas bien. Quand une pièce pose, il faut un trigger pour ne pas descendre la suivante.
	}
	else
	{
		// Vitesse normale.
		gTetris.nSpeed += gTetris.nSpdInc;
	}
	// Faut-il descendre d'une ligne ?
	if (gTetris.nSpeed & ~0xFF)
	{
		gTetris.nSpeed &= 0xFF;

		// Peut-on descendre d'une ligne ?
		if (Check(gTetris.nPosX, gTetris.nPosY + 1, gTetris.nAngle) == 0)
		{
			// Oui.
			gTetris.nPosY += 1;
		}
		else
		{
			// Non, on incruste la pièce dans l'aire de jeu.
			for (y = 0; y < 4; y++)
			{
				for (x = 0; x < 4; x++)
				{
					if (gpPieces[gTetris.nCurPiece][gTetris.nAngle][(y * 4) + x])
					{
						gTetris.pArea[((gTetris.nPosY + y) * TET_AREA_LG) + (gTetris.nPosX + x)] =
							gpPieces[gTetris.nCurPiece][gTetris.nAngle][(y * 4) + x];
					}
				}
			}
			// Score de la pièce.
			gTetris.nScore += TET_Score_Block;

			// Test des lignes.
			nLn2 = 0;
			for (y = 0; y < TET_DRAW_HT + 4; y++)
			{
				nLn = 0;
				for (x = 0; x < TET_DRAW_LG; x++)
				{
					nVal = gTetris.pArea[(y * TET_AREA_LG) + (x + 3)];
					if (nVal)
					{
						nLn++;
					}
				}
				// Ligne complète ?
				if (nLn == TET_DRAW_LG)
				{
					gTetris.pLines[y] = 1;		// On flague.
					gTetris.nWait = 10;		// Attente de x frames.
					nLn2++;
				}
			}
			// Y-a-t'il eu des lignes ?
			if (nLn2)
			{
				// Score pour lignes.
				u32	pScLn[4] = { TET_Score_1Line, TET_Score_2Lines, TET_Score_3Lines, TET_Score_4Lines };
				gTetris.nScore += pScLn[nLn2 - 1];
				// Nb de lignes ++.
				u32	nOld = gTetris.nLines;
				gTetris.nLines += nLn2;
				// Level passé ?
				if (gTetris.nLevel < TET_MaxLevel &&
					gTetris.nLines / TET_LinesPerLevel != nOld / TET_LinesPerLevel)	// Avec les /, permet de changer de niveau même en ne començant pas au niveau 1.
				{
					// Level up !
					gTetris.nLevel++;
					InitSpeed();
					// Sfx.
					Sfx_PlaySfx(e_Sfx_LevelUp, e_SfxPrio_20);
				}

				// Sfx ligne complète.
				Sfx_PlaySfx(e_Sfx_Explosion2, e_SfxPrio_10);

			}
			else
			{
				// Sfx pièce posée.
				Sfx_PlaySfx(e_Sfx_PieceSticks, e_SfxPrio_10);
			}

			// Nouvelle pièce.
			NewBlock();
			// Pas de pb pour la nouvelle pièce ?
			if (Check(gTetris.nPosX, gTetris.nPosY, gTetris.nAngle) != 0)
			{
				// Si. Game Over.
				gTetris.nGameState = TET_State_GameOver;
				gTetris.nWait = (TET_DRAW_HT << 2) | 0x03;

				gTetris.nNextPiece = gTetris.nCurPiece;		// Pour éviter les deux Next pièces qui s'enchainent quand perdu.

				// On met toutes les pièces en gris.

				//... (ligne à ligne ?)

			}

			gVar.pKeys[SDLK_DOWN] = 0;	// RAZ flèche bas. Oblige à relacher et réappuyer.

		}
	}

}

// Tetris - Main.
u32 TetrisMain(void)
{
	u32	nRetVal = GAME_Null;		/// Valeur de sortie.

	// Selon l'état.
	switch (gTetris.nGameState)
	{
	case TET_State_Play :
		// En attente quand des lignes sont faites ?
		if (gTetris.nWait)
		{
			// En attente.
			TetrisWait();
		}
		else
		{
			// Boucle normale.
			TetrisGame();
		}
		// On veut une pause ?
		if (gVar.pKeysTrig[TRIG_KeyP])
		{
			gTetris.nLastState = gTetris.nGameState;
			gTetris.nGameState = TET_State_Pause;
		}
		break;

	case TET_State_GameOver :
		// D'abord les lignes.
		if (gTetris.nWait)
		{
			gTetris.nWait--;
			// Si terminé, fade out.
			if (gTetris.nWait == 0) gTetris.nFadeVal = 256;
		}
		else
		// Fade out.
		{
			if (gTetris.nFadeVal >= 0)
			{
				gTetris.nFadeVal -= 4;	// Attention, ça tombe bien...
			}
			else
			{
				// On quitte ici, quand FadeVal tombe sous 0.
				gExg.nScore = gTetris.nScore;	// Pour les High scores.
				nRetVal = GAME_GameOver;
			}
		}
		break;

	case TET_State_Intro :
		// D'abord, le fade.
		if (gTetris.nFadeVal >= 0 && gTetris.nFadeVal < 256)
		{
			gTetris.nFadeVal += 4;
		}
		else
		// Ensuite les lignes qui descendent.
		{
			gTetris.nFadeVal = -1;	// Arrêt du fade.

			// Terminé ?
			if (--gTetris.nWait == 0)
			{
				gTetris.nGameState = TET_State_Play;
				//gTetris.nWait = 0;	/// RAZ timer attente.
				NewBlock();		// => On récupère la Next pièce => Affichage correct !
			}
		}
		break;

	case TET_State_Pause :
		// On reprend ?
		if (gVar.pKeysTrig[TRIG_KeyP])
		{
			gTetris.nGameState = gTetris.nLastState;
		}
		break;

	}

	// Dessin du jeu.
	Draw();
	DrawNext();

	// Score, Lines, Level.
	char	pStr[] = "       ";

	MyItoa(gTetris.nLevel, pStr);
	FontPrint((gVar.pScreen->pitch * 124) + 188, pStr);

	MyItoa(gTetris.nLines, pStr);
	FontPrint((gVar.pScreen->pitch * 168) + 188, pStr);

	MyItoa(gTetris.nScore, pStr);
	FontPrint((gVar.pScreen->pitch * 212) + 188, pStr);

	DrawPause();
	DrawIntro();
	DrawGameOver();
	Fade(gTetris.nFadeVal);

	return (nRetVal);
}



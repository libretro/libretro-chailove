
#include "includes.h"

#define NBELEM(tab) (sizeof(tab) / sizeof(tab[0]))

#define CURS_Acc 0x200

enum
{
	MENU_State_FadeIn = 0,
	MENU_State_Input,
	MENU_State_FadeOut,
};

#define OPT_Filename "tetris.opt"

#define	MENU_SFX_VALIDATION	e_Sfx_MenuValidate
#define	MENU_SFX_CLIC	e_Sfx_MenuClic

#define HISC_Nb	8
#define HISC_NameLg (10+1)
#define HISC_Filename "high.scr"
struct SScore
{
	char	pName[HISC_NameLg];
	u32	nScore;
};
struct SScore	gpHighScores[HISC_Nb];

struct SMenu
{
	u32	nChoix;
	u32	nState;		// Etat (fade in...).

	s32	nFadeVal;

	u8	nSin;		// Pour bouffoner le titre.

	s16	nCursPos;	// Pour faire bouger le curseur.
	s16	nCursAccel;

	// Variables pour saisie du nom.
	u32	nScIdx;			// Pos dans la chaîne. / Pas remis à 0 !
	char	pScName[HISC_NameLg];	// Nom saisi. / Pas remis à 0 !

	u8	pScKeyDown;	// Pour pseudo trigger.
	u32	nScRank;	// Rang de classement.

};
struct SMenu gMenu;

struct SMenuItm
{
	u32	nRval;		// Valeur renvoyée. MENU_Null => Pas une ligne à valider.
	u32	*pVal;		// Si valeur à afficher dans une ligne, un ptr dessus.
	u32	nValMin, nValMax;	// Bornes de la valeur ci dessus.
	char	pStr[16];	// Texte affiché. On remplace le @ par la valeur.
};



// Curseur - Init.
void CurseurInit(void)
{
	gMenu.nCursPos = 0;
	gMenu.nCursAccel = CURS_Acc;
}

// Curseur - Déplacement.
void CurseurMove(void)
{
	gMenu.nCursAccel -= 0x20;		// Gravité.
	gMenu.nCursPos += gMenu.nCursAccel;
	if (gMenu.nCursPos < 0) CurseurInit();
}

// Menu principal - Init.
// On pourrait passer un prm au cas où il y a ait plusieurs menus du même genre.
void MenuMainInit(void)
{

	gMenu.nChoix = 0;

	gMenu.nState = MENU_State_FadeIn;
	gMenu.nFadeVal = 0;

	gMenu.nSin = 0;
	CurseurInit();

}

// Menu - Init misc.
void MenuInitMisc(void)
{
	MenuMainInit();

	char pEmptyName[HISC_NameLg] = "..........";
	gMenu.nScIdx = 0;
	strcpy(gMenu.pScName, pEmptyName);

}

// Menu principal.
#define	MENUMAIN_INTERLIGNE	28
u32 MenuMain(void)
{
	// >>> Possibilité de sortir ça pour faire un autre menu du même type.
	struct SMenuItm pItems[] =
	{
		{ MENU_Game, NULL, 0, 0, "PLAY" },
		{ MENU_Null, &gExg.nStartingLevel, 1, 5, "LEVEL : @" },
		{ MENU_Null, &gExg.nHandicap, 0, 5, "HANDICAP : @" },
		{ MENU_HallOfFame, NULL, 0, 0, "HALL OF FAME" },
		{ MENU_Options, NULL, 0, 0, "OPTIONS" },
		{ MENU_Quit, NULL, 0, 0, "QUIT" },
	};
	u32	nNbLines = NBELEM(pItems);
	// <<<

	u32	nRet = MENU_Null;
	u32	i;
	u32	nPosX, nPosY;


	// Selon l'état.
	switch (gMenu.nState)
	{
	case MENU_State_FadeIn:
		gMenu.nFadeVal += 4;
		if (gMenu.nFadeVal > 256)
		{
			gMenu.nState = MENU_State_Input;
			gMenu.nFadeVal = -1;
		}
		break;

	case MENU_State_FadeOut:
		gMenu.nFadeVal -= 4;
		if (gMenu.nFadeVal < 0)
		{
			nRet = pItems[gMenu.nChoix].nRval;	// Valeur choisie par l'utilisateur.
		}
		break;

	case MENU_State_Input:
		// Gestion du clavier.
		if (gVar.pKeysTrig[TRIG_UP])
		{
			if (--gMenu.nChoix >= nNbLines) gMenu.nChoix = nNbLines - 1;
			Sfx_PlaySfx(MENU_SFX_CLIC, e_SfxPrio_10);
		}
		if (gVar.pKeysTrig[TRIG_DOWN])
		{
			if (++gMenu.nChoix >= nNbLines) gMenu.nChoix = 0;
			Sfx_PlaySfx(MENU_SFX_CLIC, e_SfxPrio_10);
		}

		// Une valeur numérique à changer ?
		if (pItems[gMenu.nChoix].pVal != NULL)
		{
			if (gVar.pKeysTrig[TRIG_RIGHT])
			{
				if (++*pItems[gMenu.nChoix].pVal > pItems[gMenu.nChoix].nValMax)
					*pItems[gMenu.nChoix].pVal = pItems[gMenu.nChoix].nValMax;
				else
					Sfx_PlaySfx(MENU_SFX_CLIC, e_SfxPrio_10);
			}
			if (gVar.pKeysTrig[TRIG_LEFT])
			{
				if (--*(s32 *)pItems[gMenu.nChoix].pVal < (s32)pItems[gMenu.nChoix].nValMin)
					*pItems[gMenu.nChoix].pVal = pItems[gMenu.nChoix].nValMin;
				else
					Sfx_PlaySfx(MENU_SFX_CLIC, e_SfxPrio_10);
			}
		}

		// Validation.
		if ((gVar.pKeysTrig[TRIG_Return] || gVar.pKeysTrig[TRIG_Space]) && pItems[gMenu.nChoix].nRval != MENU_Null)
		{
			gMenu.nState = MENU_State_FadeOut;
			gMenu.nFadeVal = 256;
			Sfx_PlaySfx(MENU_SFX_VALIDATION, e_SfxPrio_10);
		}
		break;
	}

	// Affichage.
	CurseurMove();

	// Affichage des lignes.
	nPosX = 40;
	nPosY = (SCR_Height - ((nNbLines * MENUMAIN_INTERLIGNE) - (MENUMAIN_INTERLIGNE / 2))) / 2;
	for (i = 0; i < nNbLines; i++)
	{
		// Une valeur numérique ?
		if (pItems[i].pVal != NULL)
		{
			char *pPtr = strchr(pItems[i].pStr, '@');
			if (pPtr != NULL) *pPtr = (char)(0x30 + *pItems[i].pVal);
		}

		// Print.
		FontPrint((gVar.pScreen->pitch * (nPosY + (i * MENUMAIN_INTERLIGNE))) + nPosX, pItems[i].pStr);
		// Curseur.
		if (i == gMenu.nChoix)
		{
			FontPrint((gVar.pScreen->pitch * (nPosY + (i * MENUMAIN_INTERLIGNE))) + (nPosX - 24) - (gMenu.nCursPos >> 8), ">");
		}
	}

	// Le titre.
	nPosX = (s32) (cos(gMenu.nSin * 2 * PI / 256) * ((SCR_Width - (6*16)) / 2));	// Faire préca table si trop lent.
	FontPrint((gVar.pScreen->pitch * 8) + ((SCR_Width - (6*16)) / 2) + nPosX, "TETRIS");
	FontPrint((gVar.pScreen->pitch * (SCR_Height - 16 - 8)) + ((SCR_Width - (6*16)) / 2) - nPosX, "TETRIS");
	gMenu.nSin++;

	Fade(gMenu.nFadeVal);

	return (nRet);		// Renvoie le choix.
}


// Menu item options
struct SOptMenuItm
{
	u32	nRval;		// Valeur renvoyée. MENU_Null => Pas une ligne à valider.
	u32	nBit;		// Bit à XORer.
	char	pStr[16];	// Texte affiché.
	u8	nSkipLn;	// Sauter ligne ou pas.
	char	pStrBit0[10];	// Texte affiché quand bit = 0.
	char	pStrBit1[10];	// Texte affiché quand bit = 1.
};

// Menu des options.
#define	MENUOPT_INTERLIGNE	28
#define	MENUOPT_INTERLIGNE2	20
u32 MenuOptions(void)
{
	struct SOptMenuItm pItems[] =
	{
		{ MENU_Null, OPT_Ghost, "GHOST:", 0, "OFF", "ON" },
		{ MENU_Null, OPT_Rotation, "ROTATION:", 1, "CLOCKWISE", "REVERSE" },
		{ MENU_Null, OPT_BlocksSet, "BLOCKS SET:", 1, "NORMAL", "EXTENDED" },
		{ MENU_Null, OPT_Sound, "SOUND:", 0, "OFF", "ON" },
		{ MENU_Main, 0, "MAIN MENU", 0, "", "" },
	};
	u32	nNbLines = NBELEM(pItems);

	u32	nRet = MENU_Null;
	u32	i;
	u32	nPosX, nPosY;


	// Selon l'état.
	switch (gMenu.nState)
	{
	case MENU_State_FadeIn:
		gMenu.nFadeVal += 4;
		if (gMenu.nFadeVal > 256)
		{
			gMenu.nState = MENU_State_Input;
			gMenu.nFadeVal = -1;
		}
		break;

	case MENU_State_FadeOut:
		gMenu.nFadeVal -= 4;
		if (gMenu.nFadeVal < 0)
		{
			Opt_Save();
			nRet = pItems[gMenu.nChoix].nRval;	// Valeur choisie par l'utilisateur.
		}
		break;

	case MENU_State_Input:
		// Gestion du clavier.
		if (gVar.pKeysTrig[TRIG_UP])
		{
			if (--gMenu.nChoix >= nNbLines) gMenu.nChoix = nNbLines - 1;
			Sfx_PlaySfx(MENU_SFX_CLIC, e_SfxPrio_10);
		}
		if (gVar.pKeysTrig[TRIG_DOWN])
		{
			if (++gMenu.nChoix >= nNbLines) gMenu.nChoix = 0;
			Sfx_PlaySfx(MENU_SFX_CLIC, e_SfxPrio_10);
		}

		// Une valeur à changer ?
		if (pItems[gMenu.nChoix].nBit != 0)
		{
			if (gVar.pKeysTrig[TRIG_Return] || gVar.pKeysTrig[TRIG_Space] ||
				gVar.pKeysTrig[TRIG_LEFT] || gVar.pKeysTrig[TRIG_RIGHT])
			{
				gVar.nOptFlags ^= pItems[gMenu.nChoix].nBit;
				Sfx_PlaySfx(MENU_SFX_CLIC, e_SfxPrio_10);
			}
		}

		// Validation.
		if ((gVar.pKeysTrig[TRIG_Return] || gVar.pKeysTrig[TRIG_Space]) && pItems[gMenu.nChoix].nRval != MENU_Null)
		{
			gMenu.nState = MENU_State_FadeOut;
			gMenu.nFadeVal = 256;
			Sfx_PlaySfx(MENU_SFX_VALIDATION, e_SfxPrio_10);
		}
		break;
	}

	// Affichage.
	CurseurMove();

	// Titre.
	char	pTitle[] = "OPTIONS";
	FontPrint((gVar.pScreen->pitch * 8) + ((SCR_Width - (strlen(pTitle) * 16)) / 2), pTitle);

	// Affichage des lignes.
	nPosX = 40;
	nPosY = 45;
	for (i = 0; i < nNbLines; i++)
	{
		// Curseur.
		if (i == gMenu.nChoix)
		{
			FontPrint((gVar.pScreen->pitch * nPosY) + (nPosX - 24) - (gMenu.nCursPos >> 8), ">");
		}
		// Print.
		FontPrint((gVar.pScreen->pitch * nPosY) + nPosX, pItems[i].pStr);
		// Valeur du bit.
		if (pItems[i].nBit)
		{
			char	*pStr = (gVar.nOptFlags & pItems[i].nBit ? pItems[i].pStrBit1 : pItems[i].pStrBit0);
			if (pItems[i].nSkipLn) nPosY += MENUOPT_INTERLIGNE2;
			FontPrint((gVar.pScreen->pitch * nPosY) + SCR_Width - (strlen(pStr) * 16) - 16, pStr);
		}
		nPosY += MENUOPT_INTERLIGNE;
	}

	Fade(gMenu.nFadeVal);

	return (nRet);		// Renvoie le choix.
}


// Menu des High-scores.
u32 MenuHighScores(void)
{
	u32	nRet = MENU_Null;
	u32	i;
	u32	nPosX, nPosY;


	// Selon l'état.
	switch (gMenu.nState)
	{
	case MENU_State_FadeIn:
		gMenu.nFadeVal += 4;
		if (gMenu.nFadeVal > 256)
		{
			gMenu.nState = MENU_State_Input;
			gMenu.nFadeVal = -1;
		}
		break;

	case MENU_State_FadeOut:
		gMenu.nFadeVal -= 4;
		if (gMenu.nFadeVal < 0)
		{
			nRet = MENU_Main;	// Sortie.
		}
		break;

	case MENU_State_Input:
		// Gestion du clavier.
		if (gVar.pKeysTrig[TRIG_Return] || gVar.pKeysTrig[TRIG_Space])
		{
			gMenu.nState = MENU_State_FadeOut;
			gMenu.nFadeVal = 256;
			Sfx_PlaySfx(MENU_SFX_VALIDATION, e_SfxPrio_10);
		}
		break;
	}

	// Affichage.
	//CurseurMove();

	// Titre.
	char	pTitle[] = "HALL OF FAME";
	FontPrint((gVar.pScreen->pitch * 8) + ((SCR_Width - (strlen(pTitle) * 16)) / 2), pTitle);

	// Affichage des lignes.
	nPosX = 8;
	nPosY = 40;
	for (i = 0; i < HISC_Nb; i++)
	{
		char	pStr[] = "       ";

		// Nom.
		FontPrint((gVar.pScreen->pitch * (nPosY + (i * 24))) + nPosX, gpHighScores[i].pName);
		// Score.
		MyItoa(gpHighScores[i].nScore, pStr);
		FontPrint((gVar.pScreen->pitch * (nPosY + (i * 24))) + SCR_Width - (7 * 16) - 8, pStr);

//		/// Curseur. / Voir plus tard, pour marquer le score qui vient d'être fait ?
//		if (i == gMenu.nChoix)
//		{
//			FontPrint((gVar.pScreen->pitch * (nPosY + (i * 32))) + (nPosX - 24) - (gMenu.nCursPos >> 8), ">");
//		}
	}

	Fade(gMenu.nFadeVal);

	return (nRet);
}


// Scores - Check si un score entre au Hall of Fame.
// Out : -1, pas dedans / >= 0, rang.
s32 Scr_CheckHighSc(u32 nScorePrm)
{
	s32	i, nRank;

	nRank = -1;
	for (i = HISC_Nb - 1; i >= 0; i--)
	{
		if (nScorePrm >= gpHighScores[i].nScore)
		{
			nRank = i;
		}
	}

	return (nRank);
}

// Insère un nom dans la table.
void Scr_PutNameInTable(char *pName, u32 nScore)
{
	s32	nRank = Scr_CheckHighSc(nScore);
	s32	i;

	if (nRank < 0) return;		// Ne devrait pas arriver.

	// Décalage de la table.
	for (i = HISC_Nb - 2; i >= nRank; i--)
	{
		strcpy(gpHighScores[i + 1].pName, gpHighScores[i].pName);
		gpHighScores[i + 1].nScore = gpHighScores[i].nScore;
	}
	// Le score à insérer.
	strcpy(gpHighScores[nRank].pName, pName);
	gpHighScores[nRank].nScore = nScore;

}


// RAZ de la table des high scores.
void Scr_RazTable(void)
{
	char	pDefault[HISC_NameLg] = "..........";
	u32	i;

	for (i = 0; i < HISC_Nb; i++)
	{
		strcpy(gpHighScores[i].pName, pDefault);
		gpHighScores[i].nScore = 0;
	}

}

// Calcule le checksum de la table des scores.
u32 Scr_CalcChecksum(void)
{
	u32	i, j;
	u32	nChk = 0;

	for (i = 0; i < HISC_Nb; i++)
	{
		nChk += gpHighScores[i].nScore;
		for (j = 0; j < HISC_NameLg; j++) nChk += ((u32)gpHighScores[i].pName[j]) << (8 * (j & 3));
	}
	return (nChk);
}

// Lecture du fichier des high scores.
void Scr_Load(void)
{
	FILE	*pFile;
	u32	nChk;

	if ((pFile = fopen(HISC_Filename, "rb")) != NULL)
	{
		// Le fichier existe, lecture.
		fread(gpHighScores, sizeof(struct SScore), HISC_Nb, pFile);
		fread(&nChk, sizeof(u32), 1, pFile);
		fclose(pFile);
		// Checksum ok ?
		if (nChk != Scr_CalcChecksum())
		{
			// Wrong checksum, RAZ table.
			printf("Scr_Load: Wrong checksum! Resetting table.\n");
			Scr_RazTable();
		}
	}
	else
	{
		// Le fichier n'existe pas, RAZ table.
		Scr_RazTable();
	}

}

// Sauvegarde du fichier des high scores.
void Scr_Save(void)
{
	FILE	*pFile;
	u32	nChk;

	if ((pFile = fopen(HISC_Filename, "wb")) == NULL)
	{
		printf("Unable to save highscores table.\n");
		return;
	}
	// Sauvegarde des enregistrements.
	fwrite(gpHighScores, sizeof(struct SScore), HISC_Nb, pFile);
	// Checksum.
	nChk = Scr_CalcChecksum();
	fwrite(&nChk, sizeof(u32), 1, pFile);
	fclose(pFile);

}


// Lecture du fichier des options.
void Opt_Load(void)
{
	FILE	*pFile;

	if ((pFile = fopen(OPT_Filename, "rb")) != NULL)
	{
		// Le fichier existe, lecture.
		fread(&gVar.nOptFlags, sizeof(gVar.nOptFlags), 1, pFile);
		fclose(pFile);
	}
	else
	{
		// Le fichier n'existe pas, raz flags.
		gVar.nOptFlags = OPT_Rotation | OPT_Sound;
	}

}

// Sauvegarde du fichier des options.
void Opt_Save(void)
{
	FILE	*pFile;

	if ((pFile = fopen(OPT_Filename, "wb")) == NULL)
	{
		printf("Unable to save options.\n");
		return;
	}
	// Sauvegarde des flags.
	fwrite(&gVar.nOptFlags, sizeof(gVar.nOptFlags), 1, pFile);
	fclose(pFile);

}

// Init.
void MenuGetNameInit(void)
{
	MenuMainInit();
	gMenu.pScKeyDown = 0;	// Pseudo trigger pour saisie du nom.
	gMenu.nScRank = Scr_CheckHighSc(gExg.nScore);	// Rang.

}

// Saisie du nom quand high-score.
u32 MenuGetName(void)
{
	u32	nRet = MENU_Null;
	u32	i;
	static	u8	nCligno = 0;	// POur clignotement du curseur.

	// Selon l'état.
	switch (gMenu.nState)
	{
	case MENU_State_FadeIn :
		gMenu.nFadeVal += 4;
		if (gMenu.nFadeVal > 256)
		{
			gMenu.nState = MENU_State_Input;
			gMenu.nFadeVal = -1;
		}
		break;

	case MENU_State_FadeOut :
		gMenu.nFadeVal -= 4;
		if (gMenu.nFadeVal < 0)
		{
			// Si pas de nom, mettre John Doe.
			char	pDefName[] = "JOHN DOE..";
			if (gMenu.nScIdx == 0)
			{
				strcpy(gMenu.pScName, pDefName);
				gMenu.nScIdx = strlen(pDefName);
			}
			// Rajoute le nom à la table.
			Scr_PutNameInTable(gMenu.pScName, gExg.nScore);
			Scr_Save();		// Sauvegarde du fichier.

			nRet = MENU_Main;	// Sortie.
		}
		break;

	case MENU_State_Input :
		// Gestion du clavier.
		if (gVar.pKeysTrig[TRIG_Return])
		{
			gMenu.nState = MENU_State_FadeOut;
			gMenu.nFadeVal = 256;
			Sfx_PlaySfx(MENU_SFX_VALIDATION, e_SfxPrio_10);
			break;
		}

		// On regarde quelle touche est enfoncée.
		u32	nChr = 0;

		if (gVar.pKeys[SDLK_SPACE]) nChr = ' ';
		for (i = SDLK_a; i <= SDLK_z; i++)
		{
			if (gVar.pKeys[i])
			{
				nChr = i - SDLK_a + 'A';
				break;
			}
		}
		for (i = SDLK_0; i <= SDLK_9; i++)
		{
			if (gVar.pKeys[i])
			{
				nChr = i - SDLK_0 + '0';
				break;
			}
		}
		if (gVar.pKeys[SDLK_BACKSPACE])
		{
			nChr = SDLK_BACKSPACE;
		}

		// Pseudo trigger.
		if (gMenu.pScKeyDown == 0 && nChr)
		{
			if (nChr == SDLK_BACKSPACE)
			{
				if (gMenu.nScIdx) gMenu.pScName[--gMenu.nScIdx] = '.';
			}
			else if (gMenu.nScIdx < strlen(gMenu.pScName))
			{
				gMenu.pScName[gMenu.nScIdx++] = nChr;
			}
			gMenu.pScKeyDown = 1;
			Sfx_PlaySfx(MENU_SFX_CLIC, e_SfxPrio_10);
		}
		else if (gMenu.pScKeyDown == 1 && nChr == 0)
		{
			gMenu.pScKeyDown = 0;		// Release.
		}
		break;
	}

	// Affichage.

	// Lignes.
	char pWin[][20] =
	{
		"CONGRATULATIONS!",
		"YOU RANKED #@",
		"ENTER YOUR NAME:"
	};
	// On rajoute le rank dans sa ligne.
	char *pPtr = strchr(pWin[1], '@');
	if (pPtr != NULL) *pPtr = (char)(0x31 + gMenu.nScRank);

	FontPrint((gVar.pScreen->pitch * (8+16+16)) + ((SCR_Width - (strlen(pWin[0]) * 16)) / 2), pWin[0]);
	FontPrint((gVar.pScreen->pitch * (40+40+16)) + ((SCR_Width - (strlen(pWin[1]) * 16)) / 2), pWin[1]);
	FontPrint((gVar.pScreen->pitch * (72+64+16)) + ((SCR_Width - (strlen(pWin[2]) * 16)) / 2), pWin[2]);
	FontPrint((gVar.pScreen->pitch * (104+64+16)) + ((SCR_Width - (strlen(gMenu.pScName) * 16)) / 2), gMenu.pScName);
	// Curseur.
	if (nCligno & 16) FontPrint((gVar.pScreen->pitch * (104+64+28)) + ((SCR_Width - (strlen(gMenu.pScName) * 16)) / 2) + (gMenu.nScIdx * 16), "-");
	nCligno++;

	Fade(gMenu.nFadeVal);

	return (nRet);
}




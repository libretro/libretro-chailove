
#include "includes.h"


// itoa.
void MyItoa(u32 nNb, char *pDst)
{
	char	*pPtr;
	u32	nTmp;

	pPtr = pDst + strlen(pDst) - 1;
	nTmp = nNb;
	do
	{
		*pPtr-- = (char)((nTmp % 10) + '0');
	} while (pPtr >= pDst && (nTmp /= 10) > 0);

}


// Affichage avec une fonte 16x16.
// !!! Attention, ce n'est pas prévu pour afficher en dehors de l'écran !!!
void FontPrint(u32 nOffset, char *pStr)
{
	u32	nOffTmp;
	u32	nOffFnt;
	u32	y;
	char	cChr;
	u8	*pScr, *pFnt;
	s32	nScrPitch, nFntPitch;

	pScr = (u8 *)gVar.pScreen->pixels;
	nScrPitch = gVar.pScreen->pitch;
	pFnt = (u8 *)gVar.pFont1616->pixels;
	nFntPitch = gVar.pFont1616->pitch;

	SDL_LockSurface(gVar.pScreen);

	nOffTmp = nOffset;
	while (*pStr)
	{
		cChr = *pStr++;
		if (cChr != ' ')
		{
			nOffFnt = (((u32)cChr) - ' ') << 4;
			for (y = 0; y < 16; y++)
			{
				// On fait un OR + la fonte est en couleur 255 : Transparence.
				*(u32 *)(pScr + nOffTmp + (y * nScrPitch)) |= *(u32 *)(pFnt + nOffFnt + (y * nFntPitch));
				*(u32 *)(pScr + nOffTmp + (y * nScrPitch) + 4) |= *(u32 *)(pFnt + nOffFnt + (y * nFntPitch) + 4);
				*(u32 *)(pScr + nOffTmp + (y * nScrPitch) + 8) |= *(u32 *)(pFnt + nOffFnt + (y * nFntPitch) + 8);
				*(u32 *)(pScr + nOffTmp + (y * nScrPitch) + 12) |= *(u32 *)(pFnt + nOffFnt + (y * nFntPitch) + 12);
			}
		}
		nOffTmp += 16;
	}

	SDL_UnlockSurface(gVar.pScreen);

}




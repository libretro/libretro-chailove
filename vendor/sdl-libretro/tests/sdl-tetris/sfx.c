
#include "includes.h"


struct SSfxGene
{
	u8	nInit;		// Son initialisé (1) ou pas (0).
	SDL_AudioSpec	sAudioSpec;
    SDL_AudioCVT	pCvt[e_Sfx_LAST];

};
struct SSfxGene	gSfx;


#define SFX_MAX_SOUNDS	2
struct SSample
{
	u8	*pData;
	u32	nDPos;
	u32	nDLen;
	u8	nPrio;	// Priorité du son en cours.
} gpSounds[SFX_MAX_SOUNDS];

// Mixer, appelé par SDL.
void Sfx_MixAudio(void *unused, u8 *stream, int len)
{
    u32	i;
    u32	amount;

    for (i = 0; i < SFX_MAX_SOUNDS; i++)
    {
        amount = (gpSounds[i].nDLen - gpSounds[i].nDPos);
        if (amount > (u32)len)
        {
            amount = len;
        }
        SDL_MixAudio(stream, &gpSounds[i].pData[gpSounds[i].nDPos], amount, SDL_MIX_MAXVOLUME);
        gpSounds[i].nDPos += amount;
    }
}

// Nettoyage des canaux.
void Sfx_ClearChannels(void)
{
	u32	i;

    for (i = 0; i < SFX_MAX_SOUNDS; i++)
    {
		gpSounds[i].nDPos = 0;
		gpSounds[i].nDLen = 0;
	}

}


// Sound, initialisation. A appeler 1 fois.
void Sfx_SoundInit(void)
{
	gSfx.nInit = 0;

	// Set 16-bit stereo audio at 22Khz.
	gSfx.sAudioSpec.freq = 22050;
	gSfx.sAudioSpec.format = AUDIO_S16;
	gSfx.sAudioSpec.channels = 2;
	gSfx.sAudioSpec.samples = 512;        // A good value for games.
	gSfx.sAudioSpec.callback = Sfx_MixAudio;
	gSfx.sAudioSpec.userdata = NULL;

	// Open the audio device and start playing sound!
	if (SDL_OpenAudio(&gSfx.sAudioSpec, NULL) < 0)
	{
		//fprintf(stderr, "Unable to open audio: %s\n", SDL_GetError());
		//exit(1);
		printf("Unable to open audio: %s\n", SDL_GetError());
		printf("Sound disabled.\n");
		return;
	}

	gSfx.nInit = 1;		// Ok.

	Sfx_ClearChannels();	// Nettoyage des structures.

}

// Sound on.
void Sfx_SoundOn(void)
{
	if (!gSfx.nInit) return;
	SDL_PauseAudio(0);

}

// Sound off.
void Sfx_SoundOff(void)
{
	if (!gSfx.nInit) return;
	SDL_CloseAudio();

}


// Chargement de tous les fichiers WAV.
void Sfx_LoadWavFiles(void)
{
	u32	i;

    SDL_AudioSpec sWave;
    u8	*pData;
    Uint32	nDLen;

	char	*pSfxFilenames[e_Sfx_LAST] = {
		"sfx/_menu_click.wav", "sfx/_menu_validate.wav", "sfx/_explosion2.wav",
		"sfx/_level_up.wav", "sfx/_piece_sticks.wav", "sfx/_piece_rotate.wav",
	};

	if (!gSfx.nInit) return;

	for (i = 0; i < e_Sfx_LAST; i++)
	{
		// Load the sound file and convert it to 16-bit stereo at 22kHz
		if (SDL_LoadWAV(pSfxFilenames[i], &sWave, &pData, &nDLen) == NULL)
		{
			fprintf(stderr, "Couldn't load %s: %s\n", pSfxFilenames[i], SDL_GetError());
			return;
		}
		SDL_BuildAudioCVT(&gSfx.pCvt[i], sWave.format, sWave.channels, sWave.freq,
			gSfx.sAudioSpec.format, gSfx.sAudioSpec.channels, gSfx.sAudioSpec.freq);

		gSfx.pCvt[i].buf = (u8*)malloc(nDLen * gSfx.pCvt[i].len_mult);
		memcpy(gSfx.pCvt[i].buf, pData, nDLen);
		gSfx.pCvt[i].len = nDLen;
		SDL_ConvertAudio(&gSfx.pCvt[i]);
		SDL_FreeWAV(pData);

	}

}

// Libère les ressources occupées par les fichiers WAV.
void Sfx_FreeWavFiles(void)
{
	u32	i;

	if (!gSfx.nInit) return;

	for (i = 0; i < e_Sfx_LAST; i++)
	{
		free(gSfx.pCvt[i].buf);
	}

}


// Joue un son.
// Le minimum :
// On commence par chercher un canal vide.
// Si il n'y en a pas, on note celui qui à la priorité la plus faible.
// Si plusieurs ont la même priorité, on note celui qui est le plus proche de la fin.
// Enfin, si la prio du son à jouer est ok, on le joue dans le canal noté.
void Sfx_PlaySfx(u32 nSfxNo, u32 nSfxPrio)
{
	u32	index;

	u8	nPrioMinVal = 255;
	u32	nPrioMinPos = 0;
	u32	nPrioMinDiff = (u32)-1;

	if (!(gVar.nOptFlags & OPT_Sound)) return;	// Pas si sound off.

	if (nSfxNo >= e_Sfx_LAST) return;	// Sécurité.

    // Look for an empty (or finished) sound slot.
    for (index = 0; index < SFX_MAX_SOUNDS; index++)
    {
        if (gpSounds[index].nDPos == gpSounds[index].nDLen)
        {
            break;
        }
        //
        if (gpSounds[index].nPrio < nPrioMinVal)
        {
			nPrioMinVal = gpSounds[index].nPrio;
			nPrioMinPos = index;
        	nPrioMinDiff = gpSounds[index].nDLen - gpSounds[index].nDPos;
		}
		else if (gpSounds[index].nPrio == nPrioMinVal)
		{
			if (gpSounds[index].nDLen - gpSounds[index].nDPos < nPrioMinDiff)
			{
				//nPrioMinVal = sounds[index].nPrio;
				nPrioMinPos = index;
				nPrioMinDiff = gpSounds[index].nDLen - gpSounds[index].nDPos;
			}
		}

    }

	// On a trouvé un emplacement libre ?
    if (index == SFX_MAX_SOUNDS)
    {
    	// Non, la prio demandée est > ou == à la prio mini en cours ?
		if (nSfxPrio < nPrioMinVal) return;
		index = nPrioMinPos;
    }

    // Put the sound data in the slot (it starts playing immediately).
    SDL_LockAudio();
    gpSounds[index].pData = gSfx.pCvt[nSfxNo].buf;
    gpSounds[index].nDLen = gSfx.pCvt[nSfxNo].len_cvt;
    gpSounds[index].nDPos = 0;
    gpSounds[index].nPrio = (u8)nSfxPrio;
    SDL_UnlockAudio();

}


/*
void _PlaySound(char *file)
{
    int index;
    SDL_AudioSpec wave;
    Uint8 *data;
    Uint32 dlen;
    SDL_AudioCVT cvt;

    // Look for an empty (or finished) sound slot
    for ( index=0; index<SFX_MAX_SOUNDS; ++index ) {
        if ( sounds[index].dpos == sounds[index].dlen ) {
            break;
        }
    }
    if ( index == SFX_MAX_SOUNDS )
        return;

    // Load the sound file and convert it to 16-bit stereo at 22kHz
    if ( SDL_LoadWAV(file, &wave, &data, &dlen) == NULL ) {
        fprintf(stderr, "Couldn't load %s: %s\n", file, SDL_GetError());
        return;
    }
    SDL_BuildAudioCVT(&cvt, wave.format, wave.channels, wave.freq,
                            AUDIO_S16,   2,             22050);
    cvt.buf = (u8*)malloc(dlen*cvt.len_mult);
    memcpy(cvt.buf, data, dlen);
    cvt.len = dlen;
    SDL_ConvertAudio(&cvt);
    SDL_FreeWAV(data);

    // Put the sound data in the slot (it starts playing immediately)
    if ( sounds[index].data ) {
        free(sounds[index].data);
    }
    SDL_LockAudio();
    sounds[index].data = cvt.buf;
    sounds[index].dlen = cvt.len_cvt;
    sounds[index].dpos = 0;
    SDL_UnlockAudio();
}
*/


/*
#include "SDL.h"
#include "SDL_audio.h"
{
    extern void mixaudio(void *unused, Uint8 *stream, int len);
    SDL_AudioSpec fmt;

    // Set 16-bit stereo audio at 22Khz
    fmt.freq = 22050;
    fmt.format = AUDIO_S16;
    fmt.channels = 2;
    fmt.samples = 512;        // A good value for games
    fmt.callback = mixaudio;
    fmt.userdata = NULL;

    // Open the audio device and start playing sound!
    if ( SDL_OpenAudio(&fmt, NULL) < 0 ) {
        fprintf(stderr, "Unable to open audio: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_PauseAudio(0);

    ...

    SDL_CloseAudio();
}


#define NUM_SOUNDS 2
struct sample {
    Uint8 *data;
    Uint32 dpos;
    Uint32 dlen;
} sounds[NUM_SOUNDS];

void mixaudio(void *unused, Uint8 *stream, int len)
{
    int i;
    Uint32 amount;

    for ( i=0; i<NUM_SOUNDS; ++i ) {
        amount = (sounds[i].dlen-sounds[i].dpos);
        if ( amount > len ) {
            amount = len;
        }
        SDL_MixAudio(stream, &sounds[i].data[sounds[i].dpos], amount, SDL_MIX_MAXVOLUME);
        sounds[i].dpos += amount;
    }
}

void PlaySound(char *file)
{
    int index;
    SDL_AudioSpec wave;
    Uint8 *data;
    Uint32 dlen;
    SDL_AudioCVT cvt;

    // Look for an empty (or finished) sound slot
    for ( index=0; index<NUM_SOUNDS; ++index ) {
        if ( sounds[index].dpos == sounds[index].dlen ) {
            break;
        }
    }
    if ( index == NUM_SOUNDS )
        return;

    // Load the sound file and convert it to 16-bit stereo at 22kHz
    if ( SDL_LoadWAV(file, &wave, &data, &dlen) == NULL ) {
        fprintf(stderr, "Couldn't load %s: %s\n", file, SDL_GetError());
        return;
    }
    SDL_BuildAudioCVT(&cvt, wave.format, wave.channels, wave.freq,
                            AUDIO_S16,   2,             22050);
    cvt.buf = malloc(dlen*cvt.len_mult);
    memcpy(cvt.buf, data, dlen);
    cvt.len = dlen;
    SDL_ConvertAudio(&cvt);
    SDL_FreeWAV(data);

    // Put the sound data in the slot (it starts playing immediately)
    if ( sounds[index].data ) {
        free(sounds[index].data);
    }
    SDL_LockAudio();
    sounds[index].data = cvt.buf;
    sounds[index].dlen = cvt.len_cvt;
    sounds[index].dpos = 0;
    SDL_UnlockAudio();
}

*/




// Prototypes.
void Sfx_SoundInit(void);
void Sfx_SoundOn(void);
void Sfx_SoundOff(void);
void Sfx_LoadWavFiles(void);
void Sfx_FreeWavFiles(void);
void Sfx_PlaySfx(u32 nSfxNo, u32 nSfxPrio);


// Enums.
enum
{
	e_Sfx_MenuClic,
	e_Sfx_MenuValidate,
	e_Sfx_Explosion2,
	e_Sfx_LevelUp,
	e_Sfx_PieceSticks,
	e_Sfx_PieceRotate,

	e_Sfx_LAST
};


enum
{
	e_SfxPrio_0 = 0,
	e_SfxPrio_10 = 10,
	e_SfxPrio_20 = 20,
	e_SfxPrio_30 = 30,
	e_SfxPrio_40 = 40,
	e_SfxPrio_Max = 254,
};

#ifndef _FLUIDLITE_VERSION_H
#define _FLUIDLITE_VERSION_H


#ifdef __cplusplus
extern "C" {
#endif

#define FLUIDLITE_VERSION       "1.2.2"
#define FLUIDLITE_VERSION_MAJOR 1
#define FLUIDLITE_VERSION_MINOR 2
#define FLUIDLITE_VERSION_MICRO 2


FLUIDSYNTH_API void fluid_version(int *major, int *minor, int *micro);

FLUIDSYNTH_API char* fluid_version_str(void);


#ifdef __cplusplus
}
#endif

#endif /* _FLUIDLITE_VERSION_H */

#ifndef SDL2PP_EXPORT_H
#define SDL2PP_EXPORT_H

#ifdef SDL2PP_STATIC_DEFINE
#  define SDL2PP_EXPORT
#  define SDL2PP_NO_EXPORT
#else
#  ifndef SDL2PP_EXPORT
#    ifdef SDL2pp_EXPORTS
        /* We are building this library */
#      define SDL2PP_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define SDL2PP_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef SDL2PP_NO_EXPORT
#    define SDL2PP_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef SDL2PP_DEPRECATED
#  define SDL2PP_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef SDL2PP_DEPRECATED_EXPORT
#  define SDL2PP_DEPRECATED_EXPORT SDL2PP_EXPORT SDL2PP_DEPRECATED
#endif

#ifndef SDL2PP_DEPRECATED_NO_EXPORT
#  define SDL2PP_DEPRECATED_NO_EXPORT SDL2PP_NO_EXPORT SDL2PP_DEPRECATED
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define SDL2PP_NO_DEPRECATED
#endif

#endif

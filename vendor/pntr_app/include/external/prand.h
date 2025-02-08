/**********************************************************************************************
*
*   prand - Pseudo-random number generator for C89.
*
*   HOMEPAGE:
*       https://github.com/RobLoach/prand
*
*   FEATURES:
*       - Avoids global state, so that there can be multiple random number generators
*       - Pseudo-random values generation, 32 bits: [0..4294967295]
*       - Using standard and proven prng algorithm (Xoshiro128**)
*       - State initialized with a separate generator (SplitMix64)
*       - Built upon raylib's rprand.h https://github.com/raysan5/raylib/blob/master/src/external/rprand.h
*
*   DEPENDENCIES:
*       - C89+ (stdint.h)
*
*   LICENSE: zlib/libpng
*
*   prand is licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software:
*
*   Copyright (c) 2023 Ramon Santamaria (@raysan5), Rob Loach (@RobLoach)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#ifndef PRAND_H__
#define PRAND_H__

#ifndef PRANDAPI
    #define PRANDAPI
#endif

#include <stdint.h> /* uint64_t, uint32_t, UINT32_MAX */

#ifndef PRAND_RAND_MAX
    #define PRAND_RAND_MAX UINT32_MAX
#endif

/**
 * Pseudo-random number generator.
 *
 * @see prand_init()
 */
typedef struct prand_t {
    uint64_t seed;
    uint32_t state[4];
} prand_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize the given pseudo-random number generator with the provided seed.
 *
 * @param prand The pseudo-random number generator.
 * @param seed The seed to set. If set to 0, a default seed will be used.
 *
 * @code
 * prand_t prand;
 * prand_init(&prand, 0);
 * @endcode
 */
PRANDAPI void prand_init(prand_t* prand, uint64_t seed);

/**
 * Generate a random unsigned integer between 0 and UINT32_MAX.
 *
 * Xoshiro128** generator info:
 *
 * Written in 2018 by David Blackman and Sebastiano Vigna (vigna@acm.org)
 *
 * To the extent possible under law, the author has dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * See <http://creativecommons.org/publicdomain/zero/1.0/>.
 *
 * @details This is xoshiro128** 1.1, one of our 32-bit all-purpose, rock-solid
 * generators. It has excellent speed, a state size (128 bits) that is
 * large enough for mild parallelism, and it passes all tests we are aware
 * of.
 *
 * Note that version 1.0 had mistakenly s[0] instead of s[1] as state
 * word passed to the scrambler.
 *
 * For generating just single-precision (i.e., 32-bit) floating-point
 * numbers, xoshiro128+ is even faster.
 *
 * The state must be seeded so that it is not everywhere zero.
 *
 * @param prand The pseudo-random number generator.
 *
 * @return A random number between 0 and UINT32_MAX.
 */
PRANDAPI uint32_t prand_rand(prand_t* prand);

/**
 * Generate an integer between the given min and max values.
 *
 * @param prand The pseudo-random number generator.
 * @param min The minimum value to generate.
 * @param max The maximum value to generate.
 *
 * @return A random integer between the min and max values.
 */
PRANDAPI int prand_int(prand_t* prand, int min, int max);

/**
 * Generate an unsigned 32-bit integer between the given min and max values.
 *
 * @param prand The pseudo-random number generator.
 * @param min The minimum value to generate.
 * @param max The maximum value to generate.
 *
 * @return A random unsigned 32-bit integer between the min and max values.
 */
PRANDAPI uint32_t prand_uint32(prand_t* prand, uint32_t min, uint32_t max);

/**
 * Generate an unsigned integer between the given min and max values.
 *
 * @param prand The pseudo-random number generator.
 * @param min The minimum value to generate.
 * @param max The maximum value to generate.
 *
 * @return A random unsigned integer between the min and max values.
 */
PRANDAPI unsigned int prand_uint(prand_t* prand, unsigned int min, unsigned int max);

/**
 * Generate an float between the given min and max values.
 *
 * @param prand The pseudo-random number generator.
 * @param min The minimum value to generate.
 * @param max The maximum value to generate.
 *
 * @return A random float between the given min and max values.
 */
PRANDAPI float prand_float(prand_t* prand, float min, float max);

/**
 * Rotate the pseudo random number generator bits to the left.
 *
 * @internal
 */
PRANDAPI uint32_t prand_rotate_left(const uint32_t x, int k);

#ifdef __cplusplus
}
#endif

#endif /* PRAND_H__ */

#ifdef PRAND_IMPLEMENTATION
#ifndef PRAND_IMPLEMENTATION_ONCE

#ifndef NULL
    #include <stddef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

uint64_t prand_splitmix64(prand_t* prand) {
    uint64_t z = (prand->seed += 0x9e3779b97f4a7c15);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
    z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
    return z ^ (z >> 31);
}

inline uint32_t prand_rotate_left(const uint32_t x, int k) {
    return (x << k) | (x >> (32 - k));
}

uint32_t prand_rand(prand_t* prand) {
    const uint32_t result = prand_rotate_left(prand->state[1] * 5, 7) * 9;
    const uint32_t t = prand->state[1] << 9;

    prand->state[2] ^= prand->state[0];
    prand->state[3] ^= prand->state[1];
    prand->state[1] ^= prand->state[2];
    prand->state[0] ^= prand->state[3];
    prand->state[2] ^= t;
    prand->state[3] = prand_rotate_left(prand->state[3], 11);

    return result;
}

PRANDAPI void prand_init(prand_t* prand, uint64_t seed) {
    if (prand == NULL) {
        return;
    }

    /* Default SplitMix64 seed */
    if (seed == 0) {
        seed = 0xAABBCCDD;
    }

    prand->seed = seed;

    /* To generate the Xoshiro128** state, we use SplitMix64 generator first
     * We generate 4 pseudo-random 64bit numbers that we combine using their LSB|MSB */
    prand->state[0] = (uint32_t)(prand_splitmix64(prand) & 0xffffffff);
    prand->state[1] = (uint32_t)((prand_splitmix64(prand) & 0xffffffff00000000) >> 32);
    prand->state[2] = (uint32_t)(prand_splitmix64(prand) & 0xffffffff);
    prand->state[3] = (uint32_t)((prand_splitmix64(prand) & 0xffffffff00000000) >> 32);
}

PRANDAPI int prand_int(prand_t* prand, int min, int max) {
    return (int)(prand_rand(prand) % (uint32_t)INT32_MAX) % (max - min + 1) + min;
}

PRANDAPI uint32_t prand_uint32(prand_t* prand, uint32_t min, uint32_t max) {
    return prand_rand(prand) % (max - min + 1) + min;
}

PRANDAPI unsigned int prand_uint(prand_t* prand, unsigned int min, unsigned int max) {
    return prand_rand(prand) % (max - min + 1) + min;
}

PRANDAPI float prand_float(prand_t* prand, float min, float max) {
    float scale = (float)prand_rand(prand) / (float)PRAND_RAND_MAX;
    return ((max - min) * scale) + min;
}

#ifdef __cplusplus
}
#endif

#endif /* PRAND_IMPLEMENTATION_ONCE */
#endif /* PRAND_IMPLEMENTATION */

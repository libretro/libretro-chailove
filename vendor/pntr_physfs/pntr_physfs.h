/**********************************************************************************************
*
*   pntr_physfs - Integrate PhysFS virtual file system with pntr.
*
*   Copyright 2023 Rob Loach (@RobLoach)
*
*   DEPENDENCIES:
*       pntr https://github.com/robloach/pntr
*       physfs https://github.com/icculus/physfs
*
*   LICENSE: zlib/libpng
*
*   pntr_physfs is licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software:
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

#ifndef PNTR_PHYSFS_H_
#define PNTR_PHYSFS_H_

#include <stdbool.h> // bool

#ifndef PNTR_PHYSFS_API
    #ifdef PNTR_API
        #define PNTR_PHYSFS_API PNTR_API
    #else
        #define PNTR_PHYSFS_API
    #endif
#endif

#ifndef PNTR_LOAD_FILE
    #define PNTR_LOAD_FILE pntr_physfs_load_file
#endif

#ifndef PNTR_SAVE_FILE
    #define PNTR_SAVE_FILE pntr_physfs_save_file
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Loads a file using PhysFS.
 *
 * @param fileName The name of the file to load from PhysFS.
 * @param bytesRead The output variable to save the amount of bytes that were read.
 *
 * @see pntr_load_file()
 * @see PNTR_LOAD_FILE
 */
PNTR_PHYSFS_API unsigned char* pntr_physfs_load_file(const char *fileName, unsigned int *bytesRead);

/**
 * Saves a file using PhysFS.
 *
 * @param fileName The name of the file to save into PhysFS.
 * @param data The file data to save into PhysFS.
 * @param bytesToWrite The size of the file.
 *
 * @see pntr_save_file()
 * @see PNTR_SAVE_FILE
 */
PNTR_PHYSFS_API bool pntr_physfs_save_file(const char *fileName, const void *data, unsigned int bytesToWrite);

#ifdef __cplusplus
}
#endif

#endif  // PNTR_PHYSFS_H_

#ifdef PNTR_PHYSFS_IMPLEMENTATION
#ifndef PNTR_PHYSFS_IMPLEMENTATION_ONCE
#define PNTR_PHYSFS_IMPLEMENTATION_ONCE

#ifndef PNTR_LOAD_FILE
    #define PNTR_LOAD_FILE pntr_physfs_load_file
#endif

#ifndef PNTR_SAVE_FILE
    #define PNTR_SAVE_FILE pntr_physfs_save_file
#endif

#ifndef PNTR_PHYSFS_PHYSFS_H
#define PNTR_PHYSFS_PHYSFS_H "physfs.h"
#endif
#include PNTR_PHYSFS_PHYSFS_H

#ifdef __cplusplus
extern "C" {
#endif

PNTR_PHYSFS_API void pntr_unload_memory(void* pointer);
PNTR_PHYSFS_API void* pntr_load_memory(size_t size);

PNTR_PHYSFS_API unsigned char* pntr_physfs_load_file(const char *fileName, unsigned int *bytesRead) {
    // Open up the file.
    PHYSFS_File* handle = PHYSFS_openRead(fileName);
    if (handle == 0) {
        if (bytesRead != NULL) {
            *bytesRead = 0;
        }
        return 0;
    }

    // Check to see how large the file is.
    PHYSFS_sint64 size = PHYSFS_fileLength(handle);
    if (size == -1) {
        if (bytesRead != NULL) {
            *bytesRead = 0;
        }
        PHYSFS_close(handle);
        return 0;
    }

    // Close safely when it's empty.
    if (size == 0) {
        if (bytesRead != NULL) {
            *bytesRead = 0;
        }
        PHYSFS_close(handle);
        return 0;
    }

    // Read the file, return if it's empty.
    void* buffer = pntr_load_memory((size_t)(size + 1));
    int read = PHYSFS_readBytes(handle, buffer, (PHYSFS_uint64)size);
    if (read < 0) {
        if (bytesRead != NULL) {
            *bytesRead = 0;
        }
        pntr_unload_memory(buffer);
        PHYSFS_close(handle);
        return 0;
    }

    // Close the file handle, and return the bytes read and the buffer.
    PHYSFS_close(handle);
    if (bytesRead != NULL) {
        *bytesRead = read;
    }

    return (unsigned char*) buffer;
}

PNTR_PHYSFS_API bool pntr_physfs_save_file(const char *fileName, const void *data, unsigned int bytesToWrite) {
    // Protect against empty writes.
    if (bytesToWrite == 0 || data == NULL) {
        return false;
    }

    // Open the file.
    PHYSFS_File* handle = PHYSFS_openWrite(fileName);
    if (handle == 0) {
        return false;
    }

    // Write the data to the file handle.
    if (PHYSFS_writeBytes(handle, data, bytesToWrite) < 0) {
        PHYSFS_close(handle);
        return false;
    }

    PHYSFS_close(handle);

    return true;
}

#ifdef __cplusplus
}
#endif

#endif  // PNTR_PHYSFS_IMPLEMENTATION_ONCE
#endif  // PNTR_PHYSFS_IMPLEMENTATION

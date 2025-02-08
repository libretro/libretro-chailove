/**********************************************************************************************
*
*   emscripten_clipboard.h - Clipboard Event API for Emscripten.
*
*   HOMEPAGE:
*       https://github.com/RobLoach/emscripten_clipboard
*
*   FEATURES:
*       - Use the Clipboard API from Emscripten:
*         https://developer.mozilla.org/en-US/docs/Web/API/ClipboardEvent
*
*   DEPENDENCIES:
*       - C
*       - Emscripten
*
*   LICENSE: zlib/libpng
*
*   emscripten_clipboard.h is licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software:
*
*   Copyright 2024 Rob Loach (@RobLoach)
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

#ifndef EMSCRIPTEN_CLIPBOARD_H__
#define EMSCRIPTEN_CLIPBOARD_H__

#ifndef EMSCRIPTEN_CLIPBOARD_API
    #define EMSCRIPTEN_CLIPBOARD_API
#endif

#ifndef EMSCRIPTEN_CLIPBOARD_MAX
    #define EMSCRIPTEN_CLIPBOARD_MAX 1024
#endif

typedef struct emscripten_clipboard {
    char text[EMSCRIPTEN_CLIPBOARD_MAX];
    void* user_data;
} emscripten_clipboard;

/**
 * Initializes a clipboard object, and registers the clipboard events.
 *
 * @code
 * emscripten_clipboard clipboard;
 * emscripten_clipboard_init(&clipboard);
 * @endcode
 *
 * @param clipboard The clipboard object to initialize.
 *
 * @see emscripten_clipboard_set()
 * @see emscripten_clipboard_get()
 */
EMSCRIPTEN_CLIPBOARD_API void emscripten_clipboard_init(emscripten_clipboard* clipboard);

/**
 * Gets the clipboard text from the given clipboard object.
 *
 * @param clipboard The clipboard object to get the text from.
 *
 * @return The clipboard text.
 *
 * @see emscripten_clipboard_init()
 * @see emscripten_clipboard_set()
 */
EMSCRIPTEN_CLIPBOARD_API const char* emscripten_clipboard_get(emscripten_clipboard* clipboard);

/**
 * Sets the clipboard text for the given clipboard object.
 *
 * @param clipboard The clipboard object to set the text for.
 * @param text The text to set for the clipboard.
 *
 * @see emscripten_clipboard_init()
 * @see emscripten_clipboard_get()
 */
EMSCRIPTEN_CLIPBOARD_API void emscripten_clipboard_set(emscripten_clipboard* clipboard, const char* text);

#endif  // EMSCRIPTEN_CLIPBOARD_H__

#ifdef EMSCRIPTEN_CLIPBOARD_IMPLEMENTATION
#ifndef EMSCRIPTEN_CLIPBOARD_IMPLEMENTATION_ONCE
#define EMSCRIPTEN_CLIPBOARD_IMPLEMENTATION_ONCE

#include <emscripten.h>

#ifndef EMSCRIPTEN_CLIPBOARD_STRNCPY
    #include <string.h>
    #define EMSCRIPTEN_CLIPBOARD_STRNCPY strncpy
#endif

#ifndef EMSCRIPTEN_CLIPBOARD_STRLEN
    #include <string.h>
    #define EMSCRIPTEN_CLIPBOARD_STRLEN strlen
#endif

/**
 * Registers the clipboard events for the given clipboard object.
 *
 * @param clipboard The clipboard object to register the events for.
 * @param text A pointer to the clipboard buffer.
 * @param text_size The size of the clipboard buffer.
 *
 * TODO(RobLoach): Add UTF-8 support to the web clipboard.
 */
EM_JS(void, emscripten_clipboard__register, (void* clipboard, const char* text, int text_size), {
    function emscripten_clipboard__change_event(e) {
        const newText = e.clipboardData.getData('text/plain');
        let i;
        for (i = 0; i < newText.length && i < text_size - 1; i++) {
            Module.HEAPU8[text + i] = newText.charCodeAt(i);
        }
        Module.HEAPU8[text + i] = 0;
    }
    document.addEventListener('clipboardchange', emscripten_clipboard__change_event);
    document.addEventListener('paste', emscripten_clipboard__change_event);
})

EMSCRIPTEN_CLIPBOARD_API const char* emscripten_clipboard_get(emscripten_clipboard* clipboard) {
    if (clipboard == NULL) {
        return NULL;
    }

    // TODO(RobLoach): Add a way to indicate that new clipboard content is requested?

    return clipboard->text;
}

/**
 * Writes the given text to the clipboard.
 *
 * @param text The text to write to the clipboard.
 */
EM_JS(void, emscripten_clipboard__write_text, (const char* text), {
    navigator.clipboard.writeText(UTF8ToString(text));
})

EMSCRIPTEN_CLIPBOARD_API void emscripten_clipboard_set(emscripten_clipboard* clipboard, const char* text) {
    if (clipboard == NULL) {
        return;
    }

    // Make sure it doesn't exceed the maximum length.
    int length = EMSCRIPTEN_CLIPBOARD_STRLEN(text);
    if (length >= EMSCRIPTEN_CLIPBOARD_MAX) {
        length = EMSCRIPTEN_CLIPBOARD_MAX - 1;
    }

    // Copy the string to the internal clipboard.
    EMSCRIPTEN_CLIPBOARD_STRNCPY(clipboard->text, text, length);
    clipboard->text[length] = '\0';

    // Tell the browser there is new clipboard text.
    emscripten_clipboard__write_text(clipboard->text);
}

EMSCRIPTEN_CLIPBOARD_API void emscripten_clipboard_init(emscripten_clipboard* clipboard) {
    clipboard->user_data = NULL;
    clipboard->text[0] = '\0';

    // Register the clipboard events for the object.
    emscripten_clipboard__register(clipboard, clipboard->text, EMSCRIPTEN_CLIPBOARD_MAX);
}

#endif  // EMSCRIPTEN_CLIPBOARD_IMPLEMENTATION_ONCE
#endif  // EMSCRIPTEN_CLIPBOARD_IMPLEMENTATION

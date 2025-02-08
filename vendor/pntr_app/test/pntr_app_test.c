#define PNTR_APP_IMPLEMENTATION
#define PNTR_ENABLE_DEFAULT_FONT
#define PNTR_APP_DISABLE_TERMBOX
#define PNTR_ENABLE_VARGS
#include "pntr_app.h"
#include "pntr_assert.h"

typedef struct AppData {
    pntr_font* font;
    float timePassed;
} AppData;

#include <stdio.h> // sprintf

#define ASSERT(condition) PNTR_ASSERT(condition)

bool Init(pntr_app* app) {
    // pntr_app_userdata
    {
        pntr_app_set_userdata(app, NULL);
        void* userData = pntr_app_userdata(app);
        ASSERT(userData == NULL);
        void* userData2 = pntr_load_memory(20);
        pntr_app_set_userdata(app, userData2);
        userData = pntr_app_userdata(app);
        ASSERT(userData == userData2);
        pntr_unload_memory(userData2);
    }

    // pntr_app_width
    {
        int width = pntr_app_width(app);
        ASSERT(width == 80);
    }

    // pntr_app_height
    {
        int height = pntr_app_height(app);
        ASSERT(height == 24);
    }

    // pntr_app_set_size
    {
        ASSERT(pntr_app_set_size(app, 50, 10));
        ASSERT(pntr_app_width(app) == 50);
        ASSERT(pntr_app_height(app) == 10);

        ASSERT(pntr_app_set_size(app, 80, 24));
        ASSERT(pntr_app_width(app) == 80);
        ASSERT(pntr_app_height(app) == 24);
    }

    // pntr_app_set_title
    {
        pntr_app_set_title(app, "Hello World!");
        const char* title = pntr_app_title(app);
        ASSERT(title[0] == 'H');
        ASSERT(title[1] == 'e');
        ASSERT(title[2] == 'l');
    }

    // pntr_app_key_pressed()
    {
        ASSERT(pntr_app_key_up(app, PNTR_APP_KEY_B));
        ASSERT(!pntr_app_key_down(app, PNTR_APP_KEY_B));
        ASSERT(!pntr_app_key_released(app, PNTR_APP_KEY_B));
        ASSERT(!pntr_app_key_pressed(app, PNTR_APP_KEY_B));

        // Force push a button.
        pntr_app_event e = {0};
        e.app = app;
        e.key = PNTR_APP_KEY_A;
        e.type = PNTR_APP_EVENTTYPE_KEY_DOWN;
        pntr_app_process_event(app, &e);

        ASSERT(pntr_app_key_down(app, PNTR_APP_KEY_A));
        ASSERT(pntr_app_key_pressed(app, PNTR_APP_KEY_A));
    }

    // pntr_app_random_seed(), pntr_app_random_set_seed()
    {
        // Make sure resetting the random seed works.
        pntr_app_random_set_seed(app, 0);
        int random = pntr_app_random(app, 0, 100);
        ASSERT(random == 39);

        pntr_app_random_set_seed(app, 0);
        random = pntr_app_random(app, 0, 100);
        ASSERT(random == 39);

        pntr_app_random_set_seed(app, 5);
        random = pntr_app_random(app, 0, 100);
        ASSERT(random != 39);
    }

    // pntr_app_random(), pntr_app_random_float()
    {
        for (int i = 0; i < 1000; i++) {
            int randomValue = pntr_app_random(app, 5000, 10000);
            ASSERT(randomValue >= 5000);
            ASSERT(randomValue <= 10000);
        }
        for (int x = 0; x < 1000; x++) {
            float randomValue = pntr_app_random_float(app, 0.5f, 2.0f);
            ASSERT(randomValue >= 0.5f);
            ASSERT(randomValue <= 2.0f);
        }
    }

    // pntr_app_clipboard(), pntr_app_set_clipboard()
    {
        pntr_app_set_clipboard(app, "Hello World!", 0);
        const char* clipboard = pntr_app_clipboard(app);
        ASSERT(clipboard[0] == 'H');
        ASSERT(clipboard[1] == 'e');
        ASSERT(clipboard[2] == 'l');
        ASSERT(clipboard[3] == 'l');
        ASSERT(clipboard[4] == 'o');

        pntr_app_set_clipboard(app, "Goodbye World!", 4);
        clipboard = pntr_app_clipboard(app);
        ASSERT(clipboard[0] == 'G');
        ASSERT(clipboard[1] == 'o');
        ASSERT(clipboard[2] == 'o');
        ASSERT(clipboard[3] == 'd');
        ASSERT(clipboard[4] == '\0');
    }

    // Set up the application data.
    AppData* appData = pntr_load_memory(sizeof(AppData));
    pntr_app_set_userdata(app, appData);
    appData->timePassed = 0.0f;

    // Load the font
    appData->font = pntr_load_font_default();
    ASSERT(appData->font != NULL);

    pntr_app_log(PNTR_APP_LOG_INFO, "[pntr_app] Tests passed");

    return true;
}

bool Update(pntr_app* app, pntr_image* screen) {
    AppData* appData = (AppData*)pntr_app_userdata(app);

    // Clear the screen
    pntr_clear_background(screen, PNTR_BLACK);

    // Draw some text
    pntr_draw_text(screen, appData->font, "pntr_app", 7, 4, PNTR_WHITE);
    pntr_draw_text(screen, appData->font, "Tests Passed", 1, 13, PNTR_WHITE);

    // Finish running after one loop
    if (appData->timePassed != 0) {
        return false;
    }

    float dt = pntr_app_delta_time(app);
    appData->timePassed += dt;

    return true;
}

void Close(pntr_app* app) {
    AppData* appData = (AppData*)pntr_app_userdata(app);
    pntr_unload_font(appData->font);
    pntr_unload_memory(appData);
}

pntr_app Main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    return (pntr_app) {
        .width = 80,
        .height = 24,
        .title = "pntr_app: Test",
        .init = Init,
        .update = Update,
        .close = Close,
        .fps = 5
    };
}

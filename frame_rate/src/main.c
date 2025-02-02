#include "common.h"

game_state_t game_state;

int main(int argc, char *argv[]) {
    memset(&game_state, 0, sizeof(game_state_t));

    if (!init()) {
        printf("App Initialization failed!\n");
        exit(1);
    }

    texture_init(&time_text_texture);
    texture_init(&fps_text_texture);
    // The frame per second timer.
    timer_init(&fps_timer);
    timer_init(&timer);

    if (!load_media()) {
        printf("Load media image failed %s\n", SDL_GetError());
        exit(1);
    }

    game_state.is_running = true;

    // SDL Event handle system.
    // - Key press. (SDL_KeyboardEvent)
    // - Mouse motion. (SDL_MouseMotionEvent)
    // - Joy button press. (SDL_JoyButtonEvent)
    SDL_Event event;
    SDL_Color text_color = { 0x0, 0x0, 0x0, 0xFF };
    // In memory text stream.
    char time_text[50];
    // Start counting frames per second.
    int counted_frames = 0;

    timer_start(&fps_timer);

    // This is the game loop.
    // The core of any game application.
    while (game_state.is_running) {
        // Calculate and correct fps.
        float avg_fps = counted_frames / (timer_get_ticks(&fps_timer) / 1000.f);
        if (avg_fps > 2000000) {
            avg_fps = 0.0;
        }

        do_inputs(&event, time_text);
        snprintf(time_text, 50, "Average frames per seconds %.2f", avg_fps);

        if (!texture_load_from_rendered_text(&fps_text_texture, time_text, text_color)) {
            printf("Unable to render time texture!\n");
            exit(1);
        }

        render();
        // Blit here.
        texture_render(&fps_text_texture, (SCREEN_WIDTH - fps_text_texture.w) / 2, (SCREEN_HEIGHT - fps_text_texture.h) / 2, NULL, 0.0, NULL, SDL_FLIP_NONE);
        present();

        ++counted_frames;
    }

    cleanup();

    return EXIT_SUCCESS;
}

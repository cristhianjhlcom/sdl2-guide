#include "common.h"

game_state_t game_state;

int main(int argc, char *argv[]) {
    memset(&game_state, 0, sizeof(game_state_t));

    if (!init()) {
        printf("App Initialization failed!\n");
        exit(1);
    }

    texture_init(&time_text_texture);
    texture_init(&start_prompt_text_texture);
    texture_init(&pause_prompt_text_texture);
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
    char time_text[50];

    // This is the game loop.
    // The core of any game application.
    while (game_state.is_running) {
        do_inputs(&event, time_text);

        if (!texture_load_from_rendered_text(&time_text_texture, time_text, text_color)) {
            printf("Unable to render time texture!\n");
            exit(1);
        }

        render();
        // Blit here.
        texture_render(&start_prompt_text_texture, (SCREEN_WIDTH - start_prompt_text_texture.w) / 2, 0, NULL, 0.0, NULL, SDL_FLIP_NONE);
        texture_render(&pause_prompt_text_texture, (SCREEN_WIDTH - pause_prompt_text_texture.w) / 2, 30, NULL, 0.0, NULL, SDL_FLIP_NONE);
        texture_render(&time_text_texture, (SCREEN_WIDTH - time_text_texture.w) / 2, (SCREEN_HEIGHT - time_text_texture.h) / 2, NULL, 0.0, NULL, SDL_FLIP_NONE);
        present();
    }

    cleanup();

    return EXIT_SUCCESS;
}

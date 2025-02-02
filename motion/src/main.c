#include "common.h"

game_state_t game_state;

int main(int argc, char *argv[]) {
    memset(&game_state, 0, sizeof(game_state_t));

    if (!init()) {
        printf("App Initialization failed!\n");
        exit(1);
    }

    // texture_init(&time_text_texture);

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

    // This is the game loop.
    // The core of any game application.
    while (game_state.is_running) {
        do_inputs(&event);
        render();
        // Blit here.
        // texture_render(&fps_text_texture, 0, 0, NULL, 0.0, NULL, SDL_FLIP_NONE);
        present();
    }

    cleanup();

    return EXIT_SUCCESS;
}

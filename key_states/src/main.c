#include "common.h"

game_state_t game_state;

int main(void) {
    memset(&game_state, 0, sizeof(game_state_t));

    if (!init()) {
        printf("App Initialization failed!\n");
        exit(1);
    }

    // texture_init(&button_sprite_sheet);

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

        present();
    }

    cleanup();

    return EXIT_SUCCESS;
}

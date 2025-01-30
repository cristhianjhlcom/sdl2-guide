#include "common.h"

game_state_t game_state;

int main(void) {
    memset(&game_state, 0, sizeof(game_state_t));

    if (!init()) {
        printf("App Initialization failed!\n");
        exit(1);
    }

    texture_init(&button_sprite_sheet);

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
        // Event loop.
        // Handle events on queue.
        // Keep proccesing the event queue until it is empty.
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                // User requests quit the game.
                case SDL_QUIT:
                    game_state.is_running = false;
                    break;
            }

            for (int idx = 0; idx < TOTAL_BUTTONS; idx++) {
                button_handle_event(&buttons[idx], &event);
            }
        }

        // Set clearing white color on every frame.
        // Instead of set once on the init function.
        // Explained later!
        SDL_SetRenderDrawColor(game_state.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        // Clear screen.
        // Fills the screen we the color that we define on init function
        // - SDL_SetRenderDrawColor
        SDL_RenderClear(game_state.renderer);

        // Blit here.
        for (int idx = 0; idx < TOTAL_BUTTONS; idx++) {
            button_render(&buttons[idx]);
        }

        // Now we have to user RenderPresent because we are not using
        // surface anymore then update screen.
        SDL_RenderPresent(game_state.renderer);
    }

    cleanup();

    return EXIT_SUCCESS;
}

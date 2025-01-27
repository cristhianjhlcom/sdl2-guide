#include "common.h"

state_t state;

int main(void) {
    memset(&state, 0, sizeof(state_t));

    if (!init()) {
        printf("App Initialization failed!\n");
        exit(1);
    }

    if (!load_media()) {
        printf("Load image failed!\n");
        exit(1);
    }

    state.is_running = true;

    // SDL Event handle system.
    // - Key press. (SDL_KeyboardEvent)
    // - Mouse motion. (SDL_MouseMotionEvent)
    // - Joy button press. (SDL_JoyButtonEvent)
    SDL_Event event;

    // This is the game loop.
    // The core of any game application.
    while (state.is_running) {
        // Event loop.
        // Handle events on queue.
        // Keep proccesing the event queue until it is empty.
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                // User requests quit the game.
                case SDL_QUIT:
                    state.is_running = false;
                    break;
                default:
                    break;
            }
        }

        // Set clearing white color on every frame.
        // Instead of set once on the init function.
        // Explained later!
        SDL_SetRenderDrawColor(state.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        // Clear screen.
        // Fills the screen we the color that we define on init function
        // - SDL_SetRenderDrawColor
        SDL_RenderClear(state.renderer);

        // Blit here.

        // Now we have to user RenderPresent because we are not using surface
        // anymore then update screen.
        SDL_RenderPresent(state.renderer);
    }

    cleanup();

    return EXIT_SUCCESS;
}

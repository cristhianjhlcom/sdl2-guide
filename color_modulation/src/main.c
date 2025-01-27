#include "common.h"

game_state_t game_state;

int main(void) {
    memset(&game_state, 0, sizeof(game_state_t));

    if (!init()) {
        printf("App Initialization failed!\n");
        exit(1);
    }

    texture_init(&modulated_texture);

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

    // Modulation components.
    Uint8 r = 255;
    Uint8 g = 255;
    Uint8 b = 255;

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
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_q:
                            r += 32;
                            break;
                        case SDLK_w:
                            g += 32;
                            break;
                        case SDLK_e:
                            b += 32;
                            break;
                        case SDLK_a:
                            r -= 32;
                            break;
                        case SDLK_s:
                            g -= 32;
                            break;
                        case SDLK_d:
                            b -= 32;
                            break;
                        default:
                            break;
                    }
                default:
                    break;
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
        texture_set_color(&modulated_texture, r, g, b);
        texture_render(&modulated_texture, 0, 0, NULL);

        // Now we have to user RenderPresent because we are not using
        // surface anymore then update screen.
        SDL_RenderPresent(game_state.renderer);
    }

    cleanup();

    return EXIT_SUCCESS;
}

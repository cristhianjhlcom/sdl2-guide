#include "common.h"
#include "constants.h"

game_state_t game_state;

int main(void) {
    memset(&game_state, 0, sizeof(game_state_t));

    if (!init()) {
        printf("App Initialization failed!\n");
        exit(1);
    }

    texture_init(&arrow_texture);

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

    // Angle of rotation.
    double degrees = 0;
    // Flip type.
    SDL_RendererFlip flip_type = SDL_FLIP_NONE;

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
                        // Increase alpha on w.
                        case SDLK_a:
                            degrees -= 60;
                            break;
                        case SDLK_d:
                            degrees += 60;
                            break;
                        case SDLK_q:
                            flip_type = SDL_FLIP_HORIZONTAL;
                            break;
                        case SDLK_w:
                            flip_type = SDL_FLIP_NONE;
                            break;
                        case SDLK_e:
                            flip_type = SDL_FLIP_VERTICAL;
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
        SDL_SetRenderDrawColor(game_state.renderer, 0x0, 0x0, 0x0, 0x0);
        // Clear screen.
        // Fills the screen we the color that we define on init function
        // - SDL_SetRenderDrawColor
        SDL_RenderClear(game_state.renderer);

        // Blit here.
        texture_render(&arrow_texture, (SCREEN_WIDTH - arrow_texture.w) / 2,
                       (SCREEN_HEIGHT - arrow_texture.h) / 2, NULL, degrees,
                       NULL, flip_type);

        // Now we have to user RenderPresent because we are not using
        // surface anymore then update screen.
        SDL_RenderPresent(game_state.renderer);
    }

    cleanup();

    return EXIT_SUCCESS;
}

#include "common.h"

game_state_t game_state;

int main(void) {
    memset(&game_state, 0, sizeof(game_state_t));

    if (!init()) {
        printf("App Initialization failed!\n");
        exit(1);
    }

    texture_init(&sprite_sheet_texture);

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

    // Current animation frame.
    int frame = 0;

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
                        case SDLK_w:
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
        SDL_Rect *current_clip = &sprite_clips[frame / 4];
        texture_render(&sprite_sheet_texture,
                       (SCREEN_WIDTH - current_clip->w) / 2,
                       (SCREEN_HEIGHT - current_clip->h) / 2, current_clip);

        // Now we have to user RenderPresent because we are not using
        // surface anymore then update screen.
        SDL_RenderPresent(game_state.renderer);

        // Go next frame.
        ++frame;
        // Cycle animation.
        if (frame / 4 >= WALKING_ANIMATION_FRAMES) {
            frame = 0;
        }
    }

    cleanup();

    return EXIT_SUCCESS;
}

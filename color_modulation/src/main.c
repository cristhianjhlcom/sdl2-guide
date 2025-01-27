#include "common.h"
#include "texture.h"

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
        // #IMPORTANT. Can be called render or blit.
        // Render top left sprite.
        texture_render(&sprite_sheet_texture, 0, 0, &sprite_clips[0]);
        // Render top right sprite.
        texture_render(&sprite_sheet_texture,
                       (SCREEN_WIDTH - sprite_clips[1].w), 0, &sprite_clips[1]);
        // Render bottom left sprite.
        texture_render(&sprite_sheet_texture, 0,
                       (SCREEN_HEIGHT - sprite_clips[2].h), &sprite_clips[2]);
        // Render bottom right sprite.
        texture_render(&sprite_sheet_texture, (SCREEN_WIDTH - sprite_clips[3].w),
                       (SCREEN_HEIGHT - sprite_clips[3].h), &sprite_clips[3]);

        // Now we have to user RenderPresent because we are not using surface
        // anymore then update screen.
        SDL_RenderPresent(game_state.renderer);
    }

    cleanup();

    return EXIT_SUCCESS;
}

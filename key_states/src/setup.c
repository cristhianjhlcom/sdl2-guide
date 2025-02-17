#include "common.h"

bool init(void) {
    // Initialize SDL.
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Init SDL failed %s.\n", SDL_GetError());
        return false;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf("[warning] linear texture filtering not enabled.\n");
    }

    SDL_Rect display_bounds;

    if (SDL_GetDisplayBounds(0, &display_bounds) != 0) {
        SDL_Log("Could not get display bounds %s.\n", SDL_GetError());
        return false;
    }

    // int window_x = display_bounds.x + (display_bounds.w - SCREEN_WIDTH) / 2;
    // int window_y = display_bounds.y + (display_bounds.h - SCREEN_HEIGHT) / 2;
    int window_x = display_bounds.x + display_bounds.w;
    int window_y = display_bounds.y + display_bounds.h;

    printf("window x %d window y %d\n", window_x, window_y);

    // Create windows.
    game_state.window =
        SDL_CreateWindow("Game", window_x, window_y, SCREEN_WIDTH,
                         SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (game_state.window == NULL) {
        printf("Window creation failed %s.\n", SDL_GetError());
        return false;
    }

    game_state.renderer = SDL_CreateRenderer(
        game_state.window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (game_state.renderer == NULL) {
        printf("Renderer creation failed %s.\n", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(game_state.renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Initialize PNG image resources.
    int image_flags = IMG_INIT_PNG;
    if (!(IMG_Init(image_flags) & image_flags)) {
        printf("SDL_image initalization failed %s.\n", IMG_GetError());
        return false;
    }

    printf("Game Started!\n");
    return true;
}

bool load_media(void) {
    // Load scene resources.
    if (!texture_load_from_image(&press_texture,
                                 "assets/graphics/press.png")) {
        printf("Press graphics load failed.\n");
        return false;
    }

    if (!texture_load_from_image(&up_texture,
                                 "assets/graphics/up.png")) {
        printf("Up graphics load failed.\n");
        return false;
    }

    if (!texture_load_from_image(&down_texture,
                                 "assets/graphics/down.png")) {
        printf("Down graphics load failed.\n");
        return false;
    }

    if (!texture_load_from_image(&left_texture,
                                 "assets/graphics/left.png")) {
        printf("Left graphics load failed.\n");
        return false;
    }

    if (!texture_load_from_image(&right_texture,
                                 "assets/graphics/right.png")) {
        printf("Right graphics load failed.\n");
        return false;
    }

    return true;
}

void render(void) {
    // Set clearing white color on every frame.
    // Instead of set once on the init function.
    // Explained later!
    SDL_SetRenderDrawColor(game_state.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    // Clear screen.
    // Fills the screen we the color that we define on init function
    // - SDL_SetRenderDrawColor
    SDL_RenderClear(game_state.renderer);
}

void present(void) {
    // Now we have to user RenderPresent because we are not using
    // surface anymore then update screen.
    SDL_RenderPresent(game_state.renderer);
}

void cleanup(void) {
    // Free loaded images resources.
    texture_free(&current_texture);
    texture_free(&press_texture);
    texture_free(&up_texture);
    texture_free(&down_texture);
    texture_free(&left_texture);
    texture_free(&right_texture);
    // Destroy window.
    SDL_DestroyRenderer(game_state.renderer);
    SDL_DestroyWindow(game_state.window);
    game_state.renderer = NULL;
    game_state.window = NULL;
    // Quit SDL subsystems.
    IMG_Quit();
    SDL_Quit();
}

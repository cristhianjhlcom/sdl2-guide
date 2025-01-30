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
    if (!texture_load_from_image(&button_sprite_sheet,
                                 "assets/graphics/button.png")) {
        printf("Button graphics load failed.\n");
        return false;
    }

    for (int idx = 0; idx < BUTTON_SPRITE_MOUSE_TOTAL; ++idx) {
        sprites_clips[idx].x = 0;
        sprites_clips[idx].y = idx * 200;
        sprites_clips[idx].w = BUTTON_WIDTH;
        sprites_clips[idx].h = BUTTON_HEIGHT;
    }

    button_set_position(&buttons[0], 0, 0);
    button_set_position(&buttons[1], SCREEN_WIDTH - BUTTON_WIDTH, 0);
    button_set_position(&buttons[2], 0, SCREEN_HEIGHT - BUTTON_HEIGHT);
    button_set_position(&buttons[3], SCREEN_WIDTH - BUTTON_WIDTH,
                        SCREEN_HEIGHT - BUTTON_HEIGHT);

    return true;
}

void cleanup(void) {
    // Free loaded images resources.
    texture_free(&button_sprite_sheet);
    // Destroy window.
    SDL_DestroyRenderer(game_state.renderer);
    SDL_DestroyWindow(game_state.window);
    game_state.renderer = NULL;
    game_state.window = NULL;
    // Quit SDL subsystems.
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

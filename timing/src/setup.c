#include "common.h"

bool init(void) {
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf("[warning] linear texture filtering not enabled.\n");
    }

    // Initialize SDL.
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Init SDL failed %s.\n", SDL_GetError());
        return false;
    }

    // Create windows.
    game_state.window = SDL_CreateWindow(
        "Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (game_state.window == NULL) {
        printf("Window creation failed %s.\n", SDL_GetError());
        return false;
    }

    game_state.renderer = SDL_CreateRenderer(game_state.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

    // Initialize SDL_Mizer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_Mixer initialization failed %s.\n", Mix_GetError());
        return false;
    }

    printf("Game Started!\n");
    return true;
}

bool load_media(void) {
    // Load scene resources.
    // Load textures.
    if (!texture_load_from_image(&time_text_texture, "assets/graphics/prompt.png")) {
        printf("Press graphics load failed.\n");
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
    texture_free(&time_text_texture);
    // Destroy window.
    SDL_DestroyRenderer(game_state.renderer);
    SDL_DestroyWindow(game_state.window);
    game_state.renderer = NULL;
    game_state.window = NULL;
    // Quit SDL subsystems.
    IMG_Quit();
    SDL_Quit();
}

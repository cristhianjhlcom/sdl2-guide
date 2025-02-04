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
        SDL_WINDOW_SHOWN);
    if (game_state.window == NULL) {
        printf("Window creation failed %s.\n", SDL_GetError());
        return false;
    }

    game_state.renderer = SDL_CreateRenderer(game_state.window, -1, SDL_RENDERER_ACCELERATED);
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

    // Initialize SDL_ttf.
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize SDL_ttf error %s.\n", TTF_GetError());
        return false;
    }

    return true;
}

bool load_media(void) {
    // Load scene resources.
    // Load fonts.
    font = TTF_OpenFont("assets/fonts/lazy.ttf", 28);
    if (font == NULL) {
        printf("Lazy font load failed SDL_ttf %s\n", TTF_GetError());
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
    // texture_free(&time_text_texture);
    // Destroy window.
    SDL_DestroyRenderer(game_state.renderer);
    SDL_DestroyWindow(game_state.window);
    game_state.renderer = NULL;
    game_state.window = NULL;
    // Quit SDL subsystems.
    IMG_Quit();
    SDL_Quit();
}

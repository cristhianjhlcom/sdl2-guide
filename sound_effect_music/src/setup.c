#include "common.h"

bool init(void) {
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf("[warning] linear texture filtering not enabled.\n");
    }

    if (!SDL_SetHint("SDL_AUDIODRIVER", "dsp")) {
        printf("[warning] directsound not enabled.\n");
    }

    // Initialize SDL.
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Init SDL failed %s.\n", SDL_GetError());
        return false;
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
    if (!texture_load_from_image(&prompt_texture,
                                 "assets/graphics/prompt.png")) {
        printf("Press graphics load failed.\n");
        return false;
    }

    // Load music.
    music = Mix_LoadMUS("assets/sounds/beat.wav");
    if (music == NULL) {
        printf("Failed to load beat music SDL_mixer error %s\n",
               Mix_GetError());
        return false;
    }

    scratch = Mix_LoadWAV("assets/sounds/scratch.wav");
    if (scratch == NULL) {
        printf("Failed to load scratch sound effect SDL_mixer error %s\n",
               Mix_GetError());
        return false;
    }

    high = Mix_LoadWAV("assets/sounds/high.wav");
    if (high == NULL) {
        printf("Failed to load high sound effect SDL_mixer error %s\n",
               Mix_GetError());
        return false;
    }

    medium = Mix_LoadWAV("assets/sounds/medium.wav");
    if (medium == NULL) {
        printf("Failed to load medium sound effect SDL_mixer error %s\n",
               Mix_GetError());
        return false;
    }

    low = Mix_LoadWAV("assets/sounds/low.wav");
    if (low == NULL) {
        printf("Failed to load low sound effect SDL_mixer error %s\n",
               Mix_GetError());
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
    texture_free(&prompt_texture);
    // Free the sound effects.
    Mix_FreeChunk(scratch);
    Mix_FreeChunk(high);
    Mix_FreeChunk(medium);
    Mix_FreeChunk(low);
    scratch = NULL;
    high = NULL;
    medium = NULL;
    low = NULL;
    // Free the music.
    Mix_FreeMusic(music);
    music = NULL;
    // Destroy window.
    SDL_DestroyRenderer(game_state.renderer);
    SDL_DestroyWindow(game_state.window);
    game_state.renderer = NULL;
    game_state.window = NULL;
    // Quit SDL subsystems.
    IMG_Quit();
    SDL_Quit();
}

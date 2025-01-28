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
    // Load scene image resources.
    if (!texture_load_from_image(&sprite_sheet_texture, "graphics/foo.png")) {
        printf("Load foo texture image failed.\n");
        return false;
    }

    // Set sprite clips.
    sprite_clips[0].x = 0;
    sprite_clips[0].y = 0;
    sprite_clips[0].w = 64;
    sprite_clips[0].h = 205;

    sprite_clips[1].x = 64;
    sprite_clips[1].y = 0;
    sprite_clips[1].w = 64;
    sprite_clips[1].h = 205;

    sprite_clips[2].x = 128;
    sprite_clips[2].y = 0;
    sprite_clips[2].w = 64;
    sprite_clips[2].h = 205;

    sprite_clips[3].x = 192;
    sprite_clips[3].y = 0;
    sprite_clips[3].w = 64;
    sprite_clips[3].h = 205;

    return true;
}

SDL_Texture *load_texture(const char *path) {
    // The final texture.
    SDL_Texture *new_texture = NULL;

    // Load image at specified path.
    SDL_Surface *loaded_surface = IMG_Load(path);
    if (loaded_surface == NULL) {
        printf("Unabled to load image %s SDL_Error %s.\n", path,
               SDL_GetError());
        return NULL;
    }

    // Create texture from surface pixels.
    new_texture =
        SDL_CreateTextureFromSurface(game_state.renderer, loaded_surface);
    if (loaded_surface == NULL) {
        printf("Unabled create texture from %s SDL_Error %s.\n", path,
               SDL_GetError());
        return NULL;
    }

    // Get rid of old loaded texture.
    SDL_FreeSurface(loaded_surface);

    return new_texture;
}

void cleanup(void) {
    // Free loaded images resources.
    texture_free(&sprite_sheet_texture);
    // Destroy window.
    SDL_DestroyRenderer(game_state.renderer);
    SDL_DestroyWindow(game_state.window);
    game_state.renderer = NULL;
    game_state.window = NULL;
    // Quit SDL subsystems.
    IMG_Quit();
    SDL_Quit();
}

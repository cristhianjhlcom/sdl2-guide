#include "common.h"

extern state_t state;

bool init(void) {
    // Initialize SDL.
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
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
    state.window = SDL_CreateWindow("Game", window_x, window_y, SCREEN_WIDTH,
                                    SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (state.window == NULL) {
        printf("Window creation failed %s.\n", SDL_GetError());
        return false;
    }

    state.renderer =
        SDL_CreateRenderer(state.window, -1, SDL_RENDERER_ACCELERATED);
    if (state.renderer == NULL) {
        printf("Renderer creation failed %s.\n", SDL_GetError());
        return false;
    }

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
    // Load PNG image resources.
    /*
    texture = load_texture("graphics/viewport.png");
    if (texture == NULL) {
        printf("Load texture image failed.\n");
        return false;
    }
    */
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
    new_texture = SDL_CreateTextureFromSurface(state.renderer, loaded_surface);
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
    // Destroy window.
    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
    state.renderer = NULL;
    state.window = NULL;
    // Quit SDL subsystems.
    IMG_Quit();
    SDL_Quit();
}

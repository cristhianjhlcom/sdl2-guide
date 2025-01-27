#include "common.h"

void texture_init(texture_t *t) {
    t->w = 0;
    t->h = 0;
    t->texture = NULL;
}

void texture_free(texture_t *t) {
    if (t->texture == NULL)
        return;

    if (t->texture != NULL) {
        SDL_DestroyTexture(t->texture);
        t->texture = NULL;
        t->w = 0;
        t->h = 0;
    }
}

void texture_render(texture_t *t, int x, int y) {
    SDL_Rect dest;
    dest.w = t->w;
    dest.h = t->h;
    dest.x = x;
    dest.y = y;
    SDL_RenderCopy(game_state.renderer, t->texture, NULL, &dest);
}

bool texture_load_from_image(texture_t *t, const char *path) {
    texture_free(t);

    // The final texture.
    SDL_Texture *new_texture = NULL;

    // Load image at specified path.
    SDL_Surface *loaded_surface = IMG_Load(path);
    if (loaded_surface == NULL) {
        printf("Unabled to load image %s SDL_Error %s.\n", path,
               SDL_GetError());
        return false;
    }

    // Color key image.
    SDL_SetColorKey(loaded_surface, SDL_TRUE,
                    SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0xFF));
    // Create texture from surface pixels.
    new_texture = SDL_CreateTextureFromSurface(game_state.renderer, loaded_surface);
    if (loaded_surface == NULL) {
        printf("Unabled create texture from %s SDL_Error %s.\n", path,
               SDL_GetError());
        return false;
    }

    t->w = loaded_surface->w;
    t->h = loaded_surface->h;

    // Get rid of old loaded texture.
    SDL_FreeSurface(loaded_surface);

    t->texture = new_texture;

    return t->texture != NULL;
}

texture_t foo_texture;
texture_t background_texture;

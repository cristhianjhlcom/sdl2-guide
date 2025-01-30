#include "common.h"

// #IMPORTANT. Always defines your global (extern) variables on your .c files.
// e.g We define two variables on our texture.h
// - extern texture_t sprite_sheet_texture;
// - extern SDL_Rect sprite_clips[4];
// Now we have to define on our texture.c this make the variable available on
// other modules.
// texture_t button_sprite_sheet;

// Initializes variables.
void texture_init(texture_t *t) {
    t->w = 0;
    t->h = 0;
    t->texture = NULL;
}

// Deallocates texture.
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

// Renders texture at given point.
void texture_render(texture_t *t, int x, int y, SDL_Rect *clip, double angle,
                    SDL_Point *center, SDL_RendererFlip flip) {
    // Set rendering space and render to screen.
    SDL_Rect dest;
    dest.w = t->w;
    dest.h = t->h;
    dest.x = x;
    dest.y = y;

    // Set clip rendering dimensions.
    if (clip != NULL) {
        dest.x = clip->x;
        dest.y = clip->y;
    }

    // Render to screen.
    SDL_RenderCopyEx(game_state.renderer, t->texture, clip, &dest, angle,
                     center, flip);
}

// Set blending.
void texture_set_blend_mode(texture_t *t, SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(t->texture, blending);
}

// Set alpha modulation.
void texture_set_alpha(texture_t *t, Uint8 alpha) {
    SDL_SetTextureAlphaMod(t->texture, alpha);
}

// Set color modulation.
void texture_set_color(texture_t *t, Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(t->texture, red, green, blue);
}

// Loads image at specified path.
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
    new_texture =
        SDL_CreateTextureFromSurface(game_state.renderer, loaded_surface);
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

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include "../include/structs.h"
#include "common.h"

extern texture_t texture;

static bool load_from_file(const char *path);

void init_texture(void) {
    memset(&texture, 0, sizeof(texture_t));

    texture.load_from_file = load_from_file;
}

static bool load_from_file(const char *path) {
    // The final texture.
    SDL_Texture *new_texture = NULL;

    // Load image at specified path.
    SDL_Surface *loaded_surface = IMG_Load(path);
    if (loaded_surface == NULL) {
        printf("Unabled to load image %s SDL_Error %s.\n", path,
               SDL_GetError());
        return false;
    }

    SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0xFF));
    new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
    // Get rid of old loaded texture.
    SDL_FreeSurface(loaded_surface);

    return new_texture;


    return true;
}

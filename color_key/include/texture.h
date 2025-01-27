#pragma once

#include "common.h"

typedef struct Texture texture_t;
typedef struct Texture {
    int x, y;
    int w, h;
    SDL_Texture *texture;
} texture_t;

// Functions declarations.
void texture_init(texture_t *t);
void texture_free(texture_t *t);
void texture_render(texture_t *t, int x, int y);
bool texture_load_from_image(texture_t *t, const char *path);

// #IMPORTANT. Global variables.
// Scene textures.
extern texture_t foo_texture;
extern texture_t background_texture;


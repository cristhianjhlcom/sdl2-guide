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
void texture_render(texture_t *t, int x, int y, SDL_Rect *clip);
void texture_set_color(texture_t *t, Uint8 red, Uint8 green, Uint8 blue);
void texture_set_blend_mode(texture_t *t, SDL_BlendMode blending);
void texture_set_alpha(texture_t *t, Uint8 alpha);
bool texture_load_from_image(texture_t *t, const char *path);

// #IMPORTANT. Global variables.
// #IMPORTANT. You must define it on your .c file.
// Scene textures.
extern texture_t sprite_sheet_texture;
extern SDL_Rect sprite_clips[WALKING_ANIMATION_FRAMES];

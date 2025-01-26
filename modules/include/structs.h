#pragma once

#include "common.h"

// Texture wrapper as a struct.
typedef struct Texture texture_t;
typedef struct Texture {
    int x, y;
    int w, h;
    SDL_Texture *texture;
    bool (*load_from_file)(const char *);
} texture_t;

#pragma once

#include "common.h"

// Start up SDL and creates window.
bool init(void);
// Load medias resources.
bool load_media(void);
// Load individuals image texture.
SDL_Texture *load_texture(const char *path);
// Free resources and shuts down SDL.
void cleanup(void);

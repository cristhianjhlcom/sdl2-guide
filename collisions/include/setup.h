#pragma once

#include "common.h"

// Start up SDL and creates window.
bool init(void);
// Load medias resources.
bool load_media(void);
// Box collision detector.
bool check_collision(SDL_Rect a, SDL_Rect b);
// Clean and render main screen.
void render(void);
// Present and update the screen.
void present(void);
// Free resources and shuts down SDL.
void cleanup(void);

extern game_state_t game_game_state;

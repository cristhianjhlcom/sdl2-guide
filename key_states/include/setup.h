#pragma once

#include "common.h"

// Start up SDL and creates window.
bool init(void);
// Load medias resources.
bool load_media(void);
// Clean and render main screen.
void render(void);
// Present and update the screen.
void present(void);
// Free resources and shuts down SDL.
void cleanup(void);

extern game_state_t game_game_state;

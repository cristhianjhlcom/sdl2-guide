#pragma once

#include "common.h"

typedef struct GameState game_state_t;

typedef struct GameState {
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool is_running;
} game_state_t;

extern game_state_t game_state;

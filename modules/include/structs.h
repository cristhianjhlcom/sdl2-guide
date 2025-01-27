#pragma once

#include "common.h"

typedef struct State state_t;

typedef struct State {
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool is_running;
} state_t;

#pragma once

#include <SDL_events.h>

typedef struct Dot dot_t;
typedef struct Dot {
    int posX, posY;
    int velX, velY;
    // Dot's collision box.
    SDL_Rect collider;
} dot_t;

void dot_init(dot_t *d);
void dot_handle_event(dot_t *d, SDL_Event *e);
void dot_move(dot_t *d, SDL_Rect wall);
void dot_render(dot_t *d);

extern dot_t dot_entity;

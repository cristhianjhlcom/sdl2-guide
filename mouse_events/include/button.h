#pragma once

#include "common.h"

typedef enum ButtonSprite {
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_MOUSE_TOTAL = 4,
} ButtonSprite;

typedef struct Button button_t;
typedef struct Button {
    SDL_Point position;
    ButtonSprite current_sprite;
} button_t;

void button_init(button_t *b);
void button_set_position(button_t *b, int x, int y);
void button_handle_event(button_t *b, SDL_Event *e);
void button_render(button_t *b);

extern button_t button_current_sprite;
extern button_t buttons[TOTAL_BUTTONS];

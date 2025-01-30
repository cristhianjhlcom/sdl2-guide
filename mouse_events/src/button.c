#include "common.h"

button_t button_current_sprite;
button_t buttons[TOTAL_BUTTONS];

void button_init(button_t *b) {
    b->position.x = 0;
    b->position.y = 0;
    b->current_sprite = BUTTON_SPRITE_MOUSE_OUT;
}

void button_set_position(button_t *b, int x, int y) {
    b->position.x = x;
    b->position.y = y;
}

void button_handle_event(button_t *b, SDL_Event *e) {
    // If mouse event happens.
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN ||
        e->type == SDL_MOUSEBUTTONUP) {
        // Get mouse position.
        int x, y;
        SDL_GetMouseState(&x, &y);

        // Check if mouse is in button.
        bool inside = true;

        if (x < b->position.x) {
            inside = false;
        } else if (x > b->position.x + BUTTON_WIDTH) {
            inside = false;
        } else if (y < b->position.y) {
            inside = false;
        } else if (y > b->position.y + BUTTON_HEIGHT) {
            inside = false;
        }

        if (!inside) {
            button_current_sprite.current_sprite = BUTTON_SPRITE_MOUSE_OUT;
        } else {
            switch (e->type) {
                case SDL_MOUSEMOTION:
                    button_current_sprite.current_sprite =
                        BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    button_current_sprite.current_sprite =
                        BUTTON_SPRITE_MOUSE_DOWN;
                    break;
                case SDL_MOUSEBUTTONUP:
                    button_current_sprite.current_sprite =
                        BUTTON_SPRITE_MOUSE_UP;
                    break;
                default:
                    break;
            }
        }
    }
}

void button_render(button_t *b) {
    texture_render(&button_sprite_sheet, b->position.x,
                   b->position.y,
                   NULL, 0.0,
                   NULL, SDL_FLIP_NONE);
}

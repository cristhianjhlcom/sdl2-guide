#include "common.h"

// The dimension of the dot.
static const int DOT_WIDTH = 20;
static const int DOT_HEIGHT = 20;
// Maximum axis velocity of the dot.
static const int DOT_VEL = 10;

dot_t dot_entity;

void dot_init(dot_t *d) {
    // Initialize the offsets.
    d->posX = 0;
    d->posY = 0;
    // Set collision box dimensions.
    d->collider.w = DOT_WIDTH;
    d->collider.h = DOT_HEIGHT;
    // Initialize the velocity.
    d->velX = 0;
    d->velY = 0;
}

void dot_handle_event(dot_t *d, SDL_Event *e) {
    switch (e->type) {
        // If a key was pressed.
        case SDL_KEYDOWN:
            if (e->key.repeat == 0) {
                // Adjust the velocity.
                switch (e->key.keysym.sym) {
                    case SDLK_UP:
                        d->velY -= DOT_VEL;
                        break;
                    case SDLK_DOWN:
                        d->velY += DOT_VEL;
                        break;
                    case SDLK_LEFT:
                        d->velX -= DOT_VEL;
                        break;
                    case SDLK_RIGHT:
                        d->velX += DOT_VEL;
                        break;
                }
            }
            break;
        // If a key was released.
        case SDL_KEYUP:
            if (e->key.repeat == 0) {
                switch (e->key.keysym.sym) {
                    case SDLK_UP:
                        d->velY += DOT_VEL;
                        break;
                    case SDLK_DOWN:
                        d->velY -= DOT_VEL;
                        break;
                    case SDLK_LEFT:
                        d->velX += DOT_VEL;
                        break;
                    case SDLK_RIGHT:
                        d->velX -= DOT_VEL;
                        break;
                }
            }
            break;
        default:
            break;
    }
}

void dot_move(dot_t *d, SDL_Rect wall) {
    // Move the dot left or right.
    d->posX += d->velX;
    d->collider.x = d->posX;

    // If the dot went too far to the left or right.
    if ((d->posX < 0) || (d->posX + DOT_WIDTH > SCREEN_WIDTH) || check_collision(d->collider, wall)) {
        // Move back.
        d->posX -= d->velX;
        d->collider.x = d->posX;
    }

    // Move the dot up or down.
    d->posY += d->velY;
    d->collider.y = d->posY;

    // If the dot went too far to the left or right.
    if ((d->posY < 0) || (d->posY + DOT_HEIGHT > SCREEN_HEIGHT) || check_collision(d->collider, wall)) {
        // Move back.
        d->posY -= d->velY;
        d->collider.y = d->posY;
    }
}

void dot_render(dot_t *d) {
    texture_render(&dot_texture, d->posX, d->posY, NULL);
}

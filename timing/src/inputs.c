#include "common.h"

void do_inputs(SDL_Event *e) {
    // Event loop.
    // Handle events on queue.
    // Keep proccesing the event queue until it is empty.
    while (SDL_PollEvent(e)) {
        switch (e->type) {
            // User requests quit the game.
            case SDL_QUIT:
                game_state.is_running = false;
                break;
            default:
                break;
        }
    }
}

void do_arrow_keys(void) {
    // Keep arrow keys pressed to show current texture.
    // When you release the key, the default texture will load.
    /*
    const Uint8 *current_key_states = SDL_GetKeyboardState(NULL);
    if (current_key_states[SDL_SCANCODE_UP]) {
        current_texture = up_texture;
    } else if (current_key_states[SDL_SCANCODE_DOWN]) {
        current_texture = down_texture;
    } else if (current_key_states[SDL_SCANCODE_LEFT]) {
        current_texture = left_texture;
    } else if (current_key_states[SDL_SCANCODE_RIGHT]) {
        current_texture = right_texture;
    } else {
        current_texture = press_texture;
    }
    */
}

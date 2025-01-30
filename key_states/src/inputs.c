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
        }
    }
}

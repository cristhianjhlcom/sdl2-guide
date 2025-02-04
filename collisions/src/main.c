#include "common.h"

game_state_t game_state;

int main(int argc, char *argv[]) {
    memset(&game_state, 0, sizeof(game_state_t));

    if (!init()) {
        printf("App Initialization failed!\n");
        exit(1);
    }
    // THE FRAME PER SECOND PREVENTS.
    // THATS THE DOT MOVE FAST FROM EDGE TO THE OTHER EDGE OF SCREEN.
    // The frame per second timer.
    timer_init(&fps_timer);
    timer_init(&cap_timer);
    timer_init(&timer);
    // Initialize the dot texture.
    texture_init(&dot_texture);

    if (!load_media()) {
        printf("Load media image failed %s\n", SDL_GetError());
        exit(1);
    }

    game_state.is_running = true;

    // SDL Event handle system.
    // - Key press. (SDL_KeyboardEvent)
    // - Mouse motion. (SDL_MouseMotionEvent)
    // - Joy button press. (SDL_JoyButtonEvent)
    SDL_Event event;
    // The dot that will be moving around the screen.
    dot_init(&dot_entity);
    // Set the wall.
    SDL_Rect wall;
    wall.x = 300;
    wall.y = 40;
    wall.w = 40;
    wall.h = 400;

    // Start counting frames per second.
    int counted_frames = 0;

    timer_start(&fps_timer);

    // This is the game loop.
    // The core of any game application.
    while (game_state.is_running) {
        // Start cap timer.
        timer_start(&cap_timer);
        // Calculate and correct fps.
        float avg_fps = counted_frames / (timer_get_ticks(&fps_timer) / 1000.f);
        if (avg_fps > 2000000) {
            avg_fps = 0.0;
        }
        do_inputs(&event, &dot_entity);
        dot_move(&dot_entity, wall);
        render();
        // Blit here.
        // Render Wall.
        SDL_SetRenderDrawColor(game_state.renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawRect(game_state.renderer, &wall);
        // Render Dot.
        dot_render(&dot_entity);
        // texture_render(&fps_text_texture, 0, 0, NULL, 0.0, NULL, SDL_FLIP_NONE);
        present();

        ++counted_frames;

        // If frame finished early.
        int frame_ticks = timer_get_ticks(&cap_timer);
        if (frame_ticks < SCREEN_TICKS_PER_FRAME) {
            // Wait remaining time.
            SDL_Delay(SCREEN_TICKS_PER_FRAME - frame_ticks);
        }
    }

    cleanup();

    return EXIT_SUCCESS;
}

#include "common.h"
#include "constants.h"

bool initialize_window(void);
void proccess_input(void);
void render(void);
void setup(void);
void present(void);
void update(void);
void cleanup(void);

void square_gravity(void);
void square_jump(void);

float vertical_velocity = 0.0;
float gravity = 0.5;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
bool is_running = false;
SDL_Rect square;

int main(void) {
    is_running = initialize_window();

    atexit(cleanup);

    // Setup function should be here because we only need to set properties
    // once.
    setup();

    while (is_running) {
        proccess_input();
        render();
        update();
        present();

        SDL_Delay(16);
    }

    return EXIT_SUCCESS;
}

// Square behavior.
void square_gravity(void) {
    // Imcrements the vertical velocity for the gravity.
    vertical_velocity += gravity;

    // Update the square position.
    square.y += vertical_velocity;

    // Apply simple gravity physics.
    // Add condition that check if the square is on the bottom edge.
    if (square.y >= SCREEN_HEIGHT - square.h) {
        square.y = SCREEN_HEIGHT - square.h;
        // Stops the velocity.
        vertical_velocity = 0;
    }
}

void square_jump(void) {
    // Alows the jump only if the square is on the bottom of screen.
    if (square.y == SCREEN_HEIGHT - square.h) {
        // Initial impulse to the top.
        vertical_velocity = -10;
    }
}

bool initialize_window(void) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Init failed %s.\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("First Game", 100, 100, SCREEN_WIDTH,
                              SCREEN_HEIGHT, 0);
    if (window == NULL) {
        printf("SDL Window Creation failed %s.\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("SDL Renderer Creation failed %s.\n", SDL_GetError());
        return false;
    }

    printf("Game running...\n");
    return true;
}

void proccess_input(void) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            is_running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_LEFT) {
                if (square.x > 0) {
                    square.x -= 10;
                }
            }

            if (event.key.keysym.sym == SDLK_RIGHT) {
                if (square.x < (SCREEN_WIDTH - square.w)) {
                    square.x += 10;
                }
            }

            if (event.key.keysym.sym == SDLK_SPACE) {
                if (square.y > square.h) {
                    square_jump();
                }
            }
            break;
        default:
            break;
        }
    }
}

void setup(void) {
    // Create square element.
    // Set necesary properties.
    square.w = 30;
    square.h = 30;
    square.x = (SCREEN_WIDTH - square.w) / 2;
    square.y = (SCREEN_HEIGHT - square.h) / 2;
}

void render(void) {
    // Prepare the scene.
    // Draw the window with white color.
    // Then clean the window for the next draw.
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
}

void update(void) {
    // Set square red color.
    // Render the square on screen.
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    // SDL_RenderDrawRect - Draw border of rect.
    // SDL_RenderFillRect - Draw filled rect.
    if (SDL_RenderFillRect(renderer, &square) < 0) {
        printf("Render draw rect failed %s.\n", SDL_GetError());
        exit(1);
    }

    square_gravity();
}

void present(void) {
    // Present the scene.
    // Update the screen with and render performance.
    SDL_RenderPresent(renderer);
}

void cleanup(void) {
    printf("Clean up...\n");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

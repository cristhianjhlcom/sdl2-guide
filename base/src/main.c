#include "common.h"

bool initialize_window(void);
void proccess_input(void);
void render(void);
void setup(void);
void present(void);
void update(void);
void cleanup(void);

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
bool is_running = false;

int main(void) {
    is_running = initialize_window();

    atexit(cleanup);

    while (is_running) {
        proccess_input();
        setup();
        render();
        update();
        present();
    }

    return EXIT_SUCCESS;
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
        default:
            break;
        }
    }
}

void setup(void) {
    //
}

void render(void) {
    // Prepare the scene.
    // Draw the window with white color.
    // Then clean the window for the next draw.
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Create rectangle element.
    // Set necesary properties.
    SDL_Rect rectangle;
    rectangle.w = 100;
    rectangle.h = 20;
    rectangle.x = (SCREEN_WIDTH - rectangle.w) / 2;
    rectangle.y = (SCREEN_HEIGHT - rectangle.h) / 2;

    // Set rectangle red color.
    // Render the rectangle on screen.
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    // SDL_RenderDrawRect - Draw border of rect.
    // SDL_RenderFillRect - Draw filled rect.
    if (SDL_RenderFillRect(renderer, &rectangle) < 0) {
        printf("Render draw rect failed %s.\n", SDL_GetError());
        exit(1);
    }
}

void update(void) {
    //
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

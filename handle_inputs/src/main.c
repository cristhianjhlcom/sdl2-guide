#include "common.h"

bool initialize_window(void);
void proccess_input(void);
void render_window(void);
void setup(void);
void present(void);
void update(void);
void cleanup(void);

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
bool is_running = false;
SDL_Color rectangle_color = {0, 255, 0, 255};
SDL_Rect rectangle;

typedef struct Square {
    int x, y;
} square_t;

square_t squares[MAX_SQUARES];
int max_squares = 0;

int main(void) {
    is_running = initialize_window();

    setup();

    atexit(cleanup);

    while (is_running) {
        proccess_input();
        render_window();
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
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_UP) {
                printf("up key pressed.\n");
                rectangle_color.r = 255;
                rectangle_color.g = 0;
                rectangle_color.b = 0;
            }
            if (event.key.keysym.sym == SDLK_LEFT) {
                printf("left key pressed.\n");
                rectangle_color.r = 0;
                rectangle_color.g = 0;
                rectangle_color.b = 0;
            }
            if (event.key.keysym.sym == SDLK_DOWN) {
                printf("down key pressed.\n");
                rectangle_color.r = 0;
                rectangle_color.g = 0;
                rectangle_color.b = 255;
            }
            if (event.key.keysym.sym == SDLK_RIGHT) {
                printf("right key pressed.\n");
                rectangle_color.r = 255;
                rectangle_color.g = 0;
                rectangle_color.b = 255;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                int x = event.button.x;
                int y = event.button.y;

                if (max_squares < MAX_SQUARES) {
                    squares[max_squares].x = x - 5;
                    squares[max_squares].y = y - 5;
                    max_squares++;
                } else {
                    printf("Maximum of squares excedes (%d).\n", MAX_SQUARES);
                }
            }
            break;
        case SDL_MOUSEMOTION:
            rectangle.x = event.motion.x - (rectangle.w / 2);
            // rectangle.y = event.motion.y - (rectangle.h / 2);
            break;
        default:
            break;
        }
    }
}

void setup(void) {
    // Create rectangle element.
    // Set necesary properties.
    rectangle.w = 100;
    rectangle.h = 20;
    rectangle.x = (SCREEN_WIDTH - rectangle.w) / 2;
    rectangle.y = SCREEN_HEIGHT - rectangle.h;
}

void render_window(void) {
    // Prepare the scene.
    // Draw the window with white color.
    // Then clean the window for the next draw.
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
}

void update(void) {
    // Set litle square black color.
    // Render the litle square on screen.
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int idx = 0; idx < MAX_SQUARES; idx++) {
        SDL_Rect s;
        s.x = squares[idx].x;
        s.y = squares[idx].y;
        s.w = 10;
        s.h = 10;

        if (SDL_RenderFillRect(renderer, &s) < 0) {
            printf("Render litle square failed %s.\n", SDL_GetError());
            exit(1);
        }
    }

    // Set rectangle red color.
    // Render the rectangle on screen.
    SDL_SetRenderDrawColor(renderer, rectangle_color.r, rectangle_color.g,
                           rectangle_color.b, rectangle_color.a);
    // SDL_RenderDrawRect - Draw border of rect.
    // SDL_RenderFillRect - Draw filled rect.
    if (SDL_RenderFillRect(renderer, &rectangle) < 0) {
        printf("Render draw rect failed %s.\n", SDL_GetError());
        exit(1);
    }
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

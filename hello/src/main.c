#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(void) {
    // The window will be rendering to.
    SDL_Window *window = NULL;

    // The surface contained by the window.
    SDL_Surface *screen_surface = NULL;

    // Initialize SDL.
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Init SDL failed %s.\n", SDL_GetError());
        exit(1);
    }

    SDL_Rect display_bounds;

    if (SDL_GetDisplayBounds(0, &display_bounds) != 0) {
        SDL_Log("Could not get display bounds %s.\n", SDL_GetError());
        exit(1);
    }

    // int window_x = display_bounds.x + (display_bounds.w - SCREEN_WIDTH) / 2;
    // int window_y = display_bounds.y + (display_bounds.h - SCREEN_HEIGHT) / 2;
    int window_x = display_bounds.x + display_bounds.w;
    int window_y = display_bounds.y + display_bounds.h;

    printf("window x %d window y %d\n", window_x, window_y);

    // Create windows.
    window = SDL_CreateWindow("Game", window_x, window_y, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window creation failed %s.\n", SDL_GetError());
        exit(1);
    }

    // Get window surface.
    // This is not recommended for video games.
    // Use SDL_CreateRenderer instead.
    // - Give more functionality for work with games.
    screen_surface = SDL_GetWindowSurface(window);

    // Fill the surface with white.
    SDL_FillRect(screen_surface, NULL,
                 SDL_MapRGB(screen_surface->format, 0xFF, 0xFF, 0xFF));

    // Update the surface.
    SDL_UpdateWindowSurface(window);

    // Hack window to stay up.
    SDL_Event event;
    bool quit = false;

    while (quit == false) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    // Destroy window.
    SDL_DestroyWindow(window);

    // Quit SDL subsystems.
    SDL_Quit();

    return EXIT_SUCCESS;
}

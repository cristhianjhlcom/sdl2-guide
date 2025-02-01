#include <SDL.h>
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <SDL_timer.h>
#include <SDL_video.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *argv[]) {
    // The window will be rendering to.
    SDL_Window *window = NULL;

    // The surface contained by the window.
    SDL_Surface *screen_surface = NULL;

    // Initialize SDL.
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Init SDL failed %s.\n", SDL_GetError());
        exit(1);
    }

    // Create windows.
    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
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

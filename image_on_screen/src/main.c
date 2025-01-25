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

// The window will be rendering to.
SDL_Window *window = NULL;
// The surface contained by the window.
SDL_Surface *screen_surface = NULL;
// The image we will load and show on screen.
SDL_Surface *hello_world_image = NULL;

bool init(void);
bool load_media(void);
void cleanup(void);

int main(void) {
    if (!init()) {
        printf("App Initialization failed!\n");
        exit(1);
    }

    if (!load_media()) {
        printf("Load image failed!\n");
        exit(1);
    }

    // Take a sources image and copy onto a surface screen.
    SDL_BlitSurface(hello_world_image, NULL, screen_surface, NULL);

    // After we draw the image we have to update the screen.
    // Update the surface.
    // Most of draw system use double buffer (front and back).
    // While we're drawing on front buffer the back buffer is rendering.
    // You don't call this function after every blit.
    // Only after all blits for the current frame are done.
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

    cleanup();

    return EXIT_SUCCESS;
}

bool init(void) {
    // Initialize SDL.
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Init SDL failed %s.\n", SDL_GetError());
        return false;
    }

    SDL_Rect display_bounds;

    if (SDL_GetDisplayBounds(0, &display_bounds) != 0) {
        SDL_Log("Could not get display bounds %s.\n", SDL_GetError());
        return false;
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
        return false;
    }

    // Get window surface.
    // This is not recommended for video games.
    // Use SDL_CreateRenderer instead.
    // - Give more functionality for work with games.
    screen_surface = SDL_GetWindowSurface(window);

    return true;
}

bool load_media(void) {
    const char *path = "graphics/hello_world.bmp";
    // Take a url path and returns and loaded surface.
    hello_world_image = SDL_LoadBMP(path);

    // Must check if the function returns NULL.
    if (hello_world_image == NULL) {
        printf("Load image failed %s - %s.\n", path, SDL_GetError());
        return false;
    }

    return true;
}

void cleanup(void) {
    // #IMPORTANT. Always set your pointers to NULL.
    // #IMPORTANT. Always take care of undefined behaviors.
    // Deallocate surface.
    SDL_FreeSurface(screen_surface);
    hello_world_image = NULL;

    // Destroy window.
    SDL_DestroyWindow(window);
    window = NULL;

    // Quit SDL subsystems.
    SDL_Quit();
}

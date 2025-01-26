#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Start up SDL and creates window.
bool init(void);
// Load medias resources.
bool load_media(void);
// Free resources and shuts down SDL.
void cleanup(void);

// The window will be rendering to.
SDL_Window *window = NULL;
// The window renderer.
SDL_Renderer *renderer = NULL;

int main(void) {
    if (!init()) {
        printf("App Initialization failed!\n");
        exit(1);
    }

    if (!load_media()) {
        printf("Load image failed!\n");
        exit(1);
    }

    // Hack window to stay up.
    bool quit = false;

    // SDL Event handle system.
    // - Key press. (SDL_KeyboardEvent)
    // - Mouse motion. (SDL_MouseMotionEvent)
    // - Joy button press. (SDL_JoyButtonEvent)
    SDL_Event event;

    // This is the game loop.
    // The core of any game application.
    while (quit == false) {
        // Event loop.
        // Handle events on queue.
        // Keep proccesing the event queue until it is empty.
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                // User requests quit the game.
                case SDL_QUIT:
                    quit = true;
                    break;
                default:
                    break;
            }
        }

        // Set clearing white color on every frame.
        // Instead of set once on the init function.
        // Explained later!
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        // Clear screen.
        // Fills the screen we the color that we define on init function
        // - SDL_SetRenderDrawColor
        SDL_RenderClear(renderer);

        // Now we have to user RenderPresent because we are not using surface
        // anymore then update screen.
        SDL_RenderPresent(renderer);
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

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer creation failed %s.\n", SDL_GetError());
        return false;
    }

    // Initialize PNG image resources.
    int image_flags = IMG_INIT_PNG;
    if (!(IMG_Init(image_flags) & image_flags)) {
        printf("SDL_image initalization failed %s.\n", IMG_GetError());
        return false;
    }

    printf("Game Started!\n");
    return true;
}

bool load_media(void) { return true; }

void cleanup(void) {
    // Destroy window.
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;

    // Quit SDL subsystems.
    IMG_Quit();
    SDL_Quit();
}

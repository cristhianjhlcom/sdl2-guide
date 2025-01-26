#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
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

// Start up SDL and creates window.
bool init(void);
// Load medias resources.
bool load_media(void);
// Load individuals image resources.
SDL_Surface *load_surface(const char *path);
// Free resources and shuts down SDL.
void cleanup(void);

// Key press surface constants.
// 0...5
enum key_press_surfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL,
};
// The window will be rendering to.
SDL_Window *window = NULL;
// The surface contained by the window.
SDL_Surface *screen_surface = NULL;
// The images that correspond to a keypress.
SDL_Surface *key_press_surfaces[KEY_PRESS_SURFACE_TOTAL];
// Current displayed image.
SDL_Surface *stretched_surface = NULL;

int main(void) {
    if (!init()) {
        printf("App Initialization failed!\n");
        exit(1);
    }

    if (!load_media()) {
        printf("Load image failed!\n");
        exit(1);
    }

    // After we draw the image we have to update the screen.
    // Update the surface.
    // Most of draw system use double buffer (front and back).
    // While we're drawing on front buffer the back buffer is rendering.
    // You don't call this function after every blit.
    // Only after all blits for the current frame are done.
    SDL_UpdateWindowSurface(window);

    // Hack window to stay up.
    bool quit = false;

    // SDL Event handle system.
    // - Key press. (SDL_KeyboardEvent)
    // - Mouse motion. (SDL_MouseMotionEvent)
    // - Joy button press. (SDL_JoyButtonEvent)
    SDL_Event event;

    // Set default current surface.
    stretched_surface = key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT];

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
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_UP:
                    stretched_surface =
                        key_press_surfaces[KEY_PRESS_SURFACE_UP];
                    break;
                case SDLK_DOWN:
                    stretched_surface =
                        key_press_surfaces[KEY_PRESS_SURFACE_DOWN];
                    break;
                case SDLK_RIGHT:
                    stretched_surface =
                        key_press_surfaces[KEY_PRESS_SURFACE_RIGHT];
                    break;
                case SDLK_LEFT:
                    stretched_surface =
                        key_press_surfaces[KEY_PRESS_SURFACE_LEFT];
                    break;
                default:
                    stretched_surface =
                        key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT];
                    break;
                }
            default:
                break;
            }
        }

        SDL_Rect stretch_rect;
        stretch_rect.x = 0;
        stretch_rect.y = 0;
        stretch_rect.w = SCREEN_WIDTH;
        stretch_rect.h = SCREEN_HEIGHT;
        // After the keys have been handled and the surface has been set we blit
        // the selected surface on the screen. We render it in the back buffer.
        // SDL_BlitSurface(stretched_surface, NULL, screen_surface, NULL);
        SDL_BlitScaled(stretched_surface, NULL, screen_surface, &stretch_rect);
        // Now we set the loaded surface on the front buffer.
        SDL_UpdateWindowSurface(window);
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

    // Initialize PNG image resources.
    int image_flags = IMG_INIT_PNG;
    if (!(IMG_Init(image_flags) & image_flags)) {
        printf("SDL_image initalization failed %s.\n", IMG_GetError());
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
    // Take a sources image and copy onto a surface screen.
    // Load default surfaces.
    key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT] =
        load_surface("graphics/loaded.png");
    if (key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
        printf("Load default image failed.\n");
        return false;
    }

    // Load up surfaces.
    key_press_surfaces[KEY_PRESS_SURFACE_UP] = load_surface("graphics/up.bmp");
    if (key_press_surfaces[KEY_PRESS_SURFACE_UP] == NULL) {
        printf("Load up image failed.\n");
        return false;
    }
    // Load down surfaces.
    key_press_surfaces[KEY_PRESS_SURFACE_DOWN] =
        load_surface("graphics/down.bmp");
    if (key_press_surfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
        printf("Load down image failed.\n");
        return false;
    }
    // Load left surfaces.
    key_press_surfaces[KEY_PRESS_SURFACE_LEFT] =
        load_surface("graphics/left.bmp");
    if (key_press_surfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
        printf("Load left image failed.\n");
        return false;
    }
    // Load right surfaces.
    key_press_surfaces[KEY_PRESS_SURFACE_RIGHT] =
        load_surface("graphics/right.bmp");
    if (key_press_surfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
        printf("Load right image failed.\n");
        return false;
    }
    return true;
}

SDL_Surface *load_surface(const char *path) {
    // The final optimized image.
    SDL_Surface *optimized_surface = NULL;
    // Load image at specified path.
    SDL_Surface *loaded_surface = IMG_Load(path);
    if (loaded_surface == NULL) {
        printf("Unable to load image %s - %s.\n", path, SDL_GetError());
        return NULL;
    }

    // Convert surface to screen format.
    optimized_surface =
        SDL_ConvertSurface(loaded_surface, screen_surface->format, 0);
    if (optimized_surface == NULL) {
        printf("Unable to optimized image %s - %s.\n", path, SDL_GetError());
        return NULL;
    }

    // Get rid of old load surface.
    SDL_FreeSurface(loaded_surface);

    // After convert the image to an optimized one.
    // Return it.
    return optimized_surface;
}

void cleanup(void) {
    // #IMPORTANT. Always set your pointers to NULL.
    // #IMPORTANT. Always take care of undefined behaviors.
    // Deallocate surface.
    SDL_FreeSurface(screen_surface);

    // Destroy window.
    SDL_DestroyWindow(window);
    window = NULL;

    // Quit SDL subsystems.
    SDL_Quit();
}

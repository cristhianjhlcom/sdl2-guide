#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 400

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

static void cleanup(void);

int main(int argc, char *argv[]) {
  bool is_running = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL Init failed %s.\n", SDL_GetError());
    exit(1);
  }

  window = SDL_CreateWindow("First Game", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  if (window == NULL) {
    printf("SDL Window Creation failed %s.\n", SDL_GetError());
    exit(1);
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    printf("SDL Renderer Creation failed %s.\n", SDL_GetError());
    exit(1);
  }

  printf("Game running...\n");

  while (is_running) {
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

    // Present the scene.
    // Update the screen with and render performance.
    SDL_RenderPresent(renderer);
  }

  atexit(cleanup);

  return EXIT_SUCCESS;
}

static void cleanup(void) {
  printf("Clean up the game state...\n");
  SDL_DestroyWindow(window);
  // This code is making the following error:
  // [1]    18059 segmentation fault (core dumped)
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

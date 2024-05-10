#define SDL_MAIN_HANDLED
#include <stdbool.h> 
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "game.h"
#include "const.h"

SDL_Renderer* renderer = NULL;

void cleanup() {
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

int main() {
  // Initialize SDL
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return -1;
  }

  // Create SDL window
  SDL_Window* window = SDL_CreateWindow(
    "Pong", 
    SDL_WINDOWPOS_CENTERED, 
    SDL_WINDOWPOS_CENTERED, 
    SCREEN_WIDTH, 
    SCREEN_HEIGHT, 
    0
  );

  if(!window) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return -1;
  }

  // Create renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
      printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
      return -1;
  }

  initializeGame();

  bool quit = false;
  Uint32 lastFrameTime = SDL_GetTicks(); // Get current time in milliseconds

  // Main loop
  while(!quit) {
    SDL_Event e;

    // Calculate delta time
    Uint32 currentFrameTime = SDL_GetTicks(); // Get current time in milliseconds
    float deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f; // Convert milliseconds to seconds
    lastFrameTime = currentFrameTime;

    // Handle events on queue
    while(SDL_PollEvent(&e) > 0) {
      // User requests quit
      if(e.type == SDL_QUIT) {
        quit = true;
      } else if(e.type == SDL_KEYDOWN) {
        handleKeyPress(e);
      } else if(e.type == SDL_KEYUP) {
        handleKeyRelease(e);
      }
    }

    update(deltaTime);

    // Clear the renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    draw(renderer);

    // Update the screen
    SDL_RenderPresent(renderer);
  }

  cleanup();
}



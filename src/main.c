#define SDL_MAIN_HANDLED
#include <stdbool.h> 
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

// SCREEN
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// PLAYERS
const int PLAYERS_HEIGHT = 120;
const int PLAYERS_WIDTH = 16;
const int PLAYER_DISTANCE_FROM_WALL = 16;
const float PLAYER_SPEED = 10;

SDL_Renderer* renderer = NULL;

struct Ball {
  float x;
  float y;
} ball;

struct Player {
  float x;
  float y;
  bool moveUp;
  bool moveDown;
} p1, p2;

int calcPlayerVerticalPosition () {
  int screenHalf = SCREEN_HEIGHT / 2;
  int playerHeightHalf = PLAYERS_HEIGHT / 2;
  return screenHalf - playerHeightHalf;
}

void initializePlayers() {
  p1.x = PLAYER_DISTANCE_FROM_WALL;
  p1.y = calcPlayerVerticalPosition();

  p2.x = SCREEN_WIDTH - (PLAYER_DISTANCE_FROM_WALL + PLAYERS_WIDTH);
  p2.y = calcPlayerVerticalPosition();
}

void drawPlayers() {
  SDL_Rect player1 = {p1.x, p1.y, PLAYERS_WIDTH, PLAYERS_HEIGHT};
  SDL_Rect player2 = {p2.x, p2.y, PLAYERS_WIDTH, PLAYERS_HEIGHT};

  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set color to red (R,G,B,A)
  SDL_RenderFillRect(renderer, &player1);

  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Set color to blue (R,G,B,A)
  SDL_RenderFillRect(renderer, &player2);
}

void updatePlayersPosition(float deltaTime) {
  const float speed = PLAYER_SPEED * deltaTime * 60;

  if (p1.moveUp && p1.y > 0) {
      p1.y -= speed;
  }
  if (p1.moveDown && p1.y < SCREEN_HEIGHT - PLAYERS_HEIGHT) {
      p1.y += speed;
  }
  if (p2.moveUp && p2.y > 0) {
      p2.y -= speed;
  }
  if (p2.moveDown && p2.y < SCREEN_HEIGHT - PLAYERS_HEIGHT) {
      p2.y += speed;
  }
}

void handleKeyPress(SDL_Event sdlEvent) {
  switch (sdlEvent.key.keysym.sym) {
  case SDLK_w:
      p1.moveUp = true;
      break;

  case SDLK_s:
      p1.moveDown = true;
      break;

  case SDLK_UP:
      p2.moveUp = true;
      break;

  case SDLK_DOWN:
      p2.moveDown = true;
      break;

  default:
      break;
  }
}

void handleKeyRelease(SDL_Event sdlEvent) {
  switch (sdlEvent.key.keysym.sym) {
  case SDLK_w:
      p1.moveUp = false;
      break;

  case SDLK_s:
      p1.moveDown = false;
      break;

  case SDLK_UP:
      p2.moveUp = false;
      break;

  case SDLK_DOWN:
      p2.moveDown = false;
      break;

  default:
      break;
  }
}

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

  initializePlayers();

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

    // Update players position
    updatePlayersPosition(deltaTime);

    // Clear the renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw the players
    drawPlayers();

    // Update the screen
    SDL_RenderPresent(renderer);
  }

  cleanup();
}



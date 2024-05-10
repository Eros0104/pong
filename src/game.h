#include "ball.h"
#include "player.h"
#include "const.h"
#include "utils.h"
#include <stdbool.h>
#include <SDL2/SDL.h>

#ifndef H_GAME
#define H_GAME

void draw(SDL_Renderer* renderer);

void update(float deltaTime);

void initializeGame();

void handleKeyPress(SDL_Event sdlEvent);

void handleKeyRelease(SDL_Event sdlEvent);

#endif
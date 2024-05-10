#include <stdbool.h>

#ifndef PLAYER_H
#define PLAYER_H

#define PLAYERS_HEIGHT 120
#define PLAYERS_WIDTH 16
#define PLAYER_DISTANCE_FROM_WALL 16
#define PLAYER_SPEED 10.0f

struct Player {
  float x;
  float y;
  bool moveUp;
  bool moveDown;
};

#endif
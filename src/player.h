#ifndef PLAYER_H
#define PLAYER_H

const int PLAYERS_HEIGHT = 120;
const int PLAYERS_WIDTH = 16;
const int PLAYER_DISTANCE_FROM_WALL = 16;
const float PLAYER_SPEED = 10;

struct Player {
  float x;
  float y;
  bool moveUp;
  bool moveDown;
};

#endif
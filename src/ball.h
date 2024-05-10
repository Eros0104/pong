#ifndef BALL_H
#define BALL_H

const int BALL_SIZE = 12;
const float BALL_SPEED = 5;

struct Ball {
  float x;
  float y;
  float speedX;
  float speedY;
};

#endif
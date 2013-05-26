#include "timer.h"

struct Brick {
  double h = 20;
  double w = 50;
  double x = 0;
  double y = 0;
  int hp = 1;
};

struct Ball {
  double r = 15;
  double x = 50;
  double y = 300;
  double vx = 4;
  double vy = -5;
};
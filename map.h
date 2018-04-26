#ifndef MAP_H
# define MAP_H

#include "io.h"
#include "snake.h"

#define mapxy(x, y) (m.grid[y][x])

class map{
public:
  char grid[21][80];
  int won;
  int score;
  int speed;
  int special;
  int time;
  int placedSpecial;
  int foodPosx;
  int foodPosy;
  int specFoodx;
  int specFoody;
  snake *Snake;
};

void add_food(map *m);
void add_special_food(map *m);
void delete_special_food(map *m);
#endif

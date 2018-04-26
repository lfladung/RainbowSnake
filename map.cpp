#include <stdio.h>
#include <stdint.h>
#include <endian.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <limits.h>
#include <errno.h>

#include "io.h"

void add_food(map *m){
  bool placed = false;
  srand (time(NULL));
  while(!placed){
    int x = rand() % 78 + 1;
    int y = rand() % 19 + 1;
    if(m->grid[y][x] != '@'){
      m->grid[y][x] = 'o';
      m->foodPosx = x;
      m->foodPosy = y;
      placed = true;
    }
  }
}

void add_special_food(map *m){
  bool placed = false;
  srand (time(NULL));
  while(!placed){
    int x = rand() % 78 + 1;
    int y = rand() % 19 + 1;
    if(m->grid[y][x] != '@' && m->grid[y][x] != 'o'){
      m->grid[y][x] = '$';
      m->specFoodx = x;
      m->specFoody = y;
      placed = true;
      m->placedSpecial = 1;
    }
  }
}

void delete_special_food(map *m){
  m->grid[m->specFoody][m->specFoodx] = ' ';
  m->specFoody = 0;
  m->specFoodx = 0;
  m->special = 0;
  m->placedSpecial = 0;
  m->time = 0;
}

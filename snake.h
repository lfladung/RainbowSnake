#ifndef SNAKE_H
# define SNAKE_H

# include <vector>

#include "map.h"

class map;

typedef struct segment{
int posY;
int posX;
segment *next;
segment *prev;
int color;
}seg_t;

class snake{
  public:
  int length;
  int currentDir;//2 is down, 4 is left, 6 is right, 8 is up
  segment *head;
  segment *tail;
  std::vector<segment *> list;
};

int changeDir(map *m, int dir);
void init_snake(map *m);
void delete_snake(map *m);
void add_seg(map *m, int x, int y, bool isSpecial);

#endif

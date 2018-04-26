#ifndef IO_H
# define IO_H
#include "map.h"
#include "snake.h"

void move(map *m, int dir);
void io_display(map *m);
void io_handle_input(map *m);

#endif

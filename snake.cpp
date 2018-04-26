#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>
#include <vector>

#include "map.h"
#include "snake.h"

int changeDir(map *m, int dir){
  if(dir == 2){
    if(m->Snake->currentDir != 8){
      m->Snake->currentDir = 2;
    }
    return 1;
  }
  else if(dir == 4){
    if(m->Snake->currentDir != 6){
      m->Snake->currentDir = 4;
    }
    return 1;
  }
  else if(dir == 6){
    if(m->Snake->currentDir != 4){
      m->Snake->currentDir = 6;
    }
    return 1;
  }
  else if(dir == 8){
    if(m->Snake->currentDir != 2){
      m->Snake->currentDir = 8;
    }
    return 1;
  }
  return 0;
}

void init_snake(map *m){
  m->Snake = new snake;
  m->Snake->currentDir = 6;
  m->Snake->length = 2;
  m->Snake->head = new segment;
  m->Snake->tail = new segment;
  m->Snake->head->posX = 40;
  m->Snake->head->posY = 10;
  m->Snake->tail->posX = 39;
  m->Snake->tail->posY = 10;
  m->Snake->head->prev = m->Snake->tail;
  m->Snake->tail->next = m->Snake->head;
  m->Snake->head->next = NULL;
  m->Snake->tail->prev = NULL;
  m->Snake->list.push_back(m->Snake->tail);
  m->Snake->list.push_back(m->Snake->head);
}

void add_seg(map *m, int x, int y, bool isSpecial){
  m->score += 5;
  segment *newSeg = new segment;
   newSeg->posX = x;
   newSeg->posY = y;
   newSeg->prev = NULL;
   newSeg->next = m->Snake->tail;
   m->Snake->tail = newSeg;
   m->Snake->tail->next->prev = newSeg;
   m->Snake->list.push_back(newSeg);
   m->Snake->length++;
   m->speed -= 1000;
   if(!isSpecial){
     m->special++;
     add_food(m);
   }
}

void delete_snake(map *m){
   for(int i = 0; i<(int) m->Snake->list.size();i++){
     delete m->Snake->list[i];
  }
  delete m->Snake;
}

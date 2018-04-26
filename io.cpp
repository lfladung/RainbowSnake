#include <unistd.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#include "io.h"
#include "snake.h"
#include "map.h"

void move(map *m, int dir){

  int tailOldx = m->Snake->tail->posX;
  int tailOldy = m->Snake->tail->posY;
  m->Snake->tail->posX = m->Snake->head->posX;
  m->Snake->tail->posY = m->Snake->head->posY;

  //2 is down, 4 is left, 6 is right, 8 is up
  if(dir == 2){
    m->Snake->tail->posY++;
  }
  else if(dir == 4){
    m->Snake->tail->posX--;
  }
  else if(dir == 6){
    m->Snake->tail->posX++;
  }
  else if(dir == 8){
    m->Snake->tail->posY--;
  }
  for(int i = 0;i<m->Snake->length;i++){
    if(m->Snake->list[i]->posY == m->Snake->tail->posY){
      if(m->Snake->list[i]->posX == m->Snake->tail->posX){
        if(m->Snake->list[i] != m->Snake->tail){
          m->won = 1;
        }
      }
    }
  }
  segment *tmp = m->Snake->tail->next;
  m->Snake->tail->next = NULL;
  m->Snake->tail->prev = m->Snake->head;
  m->Snake->head->next = m->Snake->tail;
  m->Snake->head = m->Snake->tail;
  tmp->prev = NULL;
  m->Snake->tail = tmp;


   if(m->grid[m->Snake->head->posY][m->Snake->head->posX] == 'o'){
     m->grid[m->Snake->head->posY][m->Snake->head->posX] = ' ';
     add_seg(m, tailOldx, tailOldy, false);
     add_food(m);
   }
   if(m->grid[m->Snake->head->posY][m->Snake->head->posX] == '$'){
     m->grid[m->Snake->head->posY][m->Snake->head->posX] = ' ';
     add_seg(m, tailOldx, tailOldy, true);
     delete_special_food(m);
     m->score += 15;
   }

}

void io_display(map *m){
  clear();
  srand (time(NULL));
  for(int i = 0;i<m->Snake->length;i++){
    m->grid[m->Snake->list[i]->posY][m->Snake->list[i]->posX] = '@';
  }
  for (int y = 0; y < 21; y++) {
    for (int x = 0; x < 80; x++) {
      int color = rand() % 7 + 1;
      if(m->grid[y][x] == '@'){
          attron(COLOR_PAIR((color)));
      }
      if(m->grid[y][x] == 'o'){
        attron(COLOR_PAIR(2));
      }
      if(m->grid[y][x] == '$'){
        attron(COLOR_PAIR((color)));
      }
      mvaddch(y, x, m->grid[y][x]);
      if(m->grid[y][x] == '@'){
        attroff(COLOR_PAIR((color)));
      }
      if(m->grid[y][x] == '$'){
        attroff(COLOR_PAIR((color)));
      }
      if(m->grid[y][x] == 'o'){
        attroff(COLOR_PAIR((2)));
      }
      mvprintw(21, 0, "Your score: %d", m->score);
      mvprintw(22, 0, "Current speed: %d", m->speed);

      if(m->placedSpecial){
        mvprintw(23, 0, "Ticks left for special: %d", 50-m->time);
      }
    }
  }
  for (int y = 0; y < 21; y++) {
    for (int x = 0; x < 80; x++) {
      if (y == 0 || y == 20 ||
          x == 0 || x == 79) {
            m->grid[y][x] = '#';
      }
      else{
        m->grid[y][x] = ' ';
      }
      if(x == m->foodPosx && m->foodPosy == y){
        m->grid[y][x] = 'o';
      }
      if(x == m->specFoodx && m->specFoody == y && m->specFoody){
        m->grid[y][x] = '$';
      }
    }
  }
  refresh();
}

void io_handle_input(map *m)
{
  int key;

//2 is down, 4 is left, 6 is right, 8 is up
    switch (key = getch()) {
    case '8':
    case KEY_UP:
      changeDir(m, 8);
      break;
    case '6':
    case KEY_RIGHT:
      changeDir(m, 6);
      break;
    case '2':
    case KEY_DOWN:
      changeDir(m, 2);
      break;
    case '4':
    case KEY_LEFT:
      changeDir(m, 4);
      break;
    case 'Q':
      m->won = 1;
      break;
    default:
      mvprintw(0, 0, "Unbound key: %#o ", key);
      }
}

#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <cstdlib>
#include <ncurses.h>
#include <iostream>

#include "io.h"
#include "map.h"
#include "snake.h"

using namespace std;

int main(int argc, char *argv[]){
  initscr();
  raw();
  noecho();
  cbreak();
  scrollok(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  keypad(stdscr, true);
  start_color();
  init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
  init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
  init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
  init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
  init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);
  init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);

  map m;
  memset(&m, 0, sizeof (m));
  m.won = 0;
  m.score = 0;
  m.speed = 100000;
  m.special = 0;
  m.placedSpecial = 0;
  int x,y;
  init_snake(&m);

  for (y = 0; y < 21; y++) {
    for (x = 0; x < 80; x++) {
      if (y == 0 || y == 20 ||
          x == 0 || x == 79) {
        mapxy(x,y) = '#';
      }
      else{
        mapxy(x,y) = ' ';
      }
    }
  }
  add_food(&m);

while(!m.won){
  if(m.special == 5){
    add_special_food(&m);
    m.special = 0;
  }
  if(m.placedSpecial){
    m.time++;
  }
  if(m.time == 50){
    delete_special_food(&m);
  }
  if(m.speed < 30000){
    m.speed = 30000;
  }
  usleep(m.speed);
  if (m.grid[m.Snake->head->posY][m.Snake->head->posX] == '#') {
    m.won = 1;
  }
  io_handle_input(&m);
  io_display(&m);
  move(&m, m.Snake->currentDir);
}
  endwin();
  printf("You lost! Your score was %d", m.score);
  printf("\n");
  delete_snake(&m);
}

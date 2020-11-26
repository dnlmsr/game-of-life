/**
 *   \file main.c
 *   \brief Game of life main program
 *
 *  This is the main c file of conway's game of life
 *
 */
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
  srand(time(NULL));
  int maxX, maxY;

  initscr();
  getmaxyx(stdscr,maxY,maxX);
  curs_set(0);
  cbreak();
  noecho();
  clear();
  for (int i = 0; i<90; ++i)
  {
    int x=(int) rand()%maxX;
    int y=(int) rand()%maxY;
    mvaddch(y,x,'*');
  }
	refresh();
	getch();
	endwin();
  return 0;
}

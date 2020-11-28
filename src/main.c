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

typedef struct
{
  int x, y;
} point;

point getXY(int index, int maxX)
{
  point output;
  output.y=(int)index/maxX;
  output.x=(int)index%maxX;

  return output;
}

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
    point Point=getXY(i, maxX);
    mvaddch(Point.y,Point.x,'*');
  }
	refresh();
	getch();
	endwin();
  return 0;
}

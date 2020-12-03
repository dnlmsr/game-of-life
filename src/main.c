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
#include <string.h>

int maxX, maxY;

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

int getIndex(point Point, int maxX){
  int index = Point.y * maxX + Point.x;
  return index;
}

void initDots(bool dots[maxX][maxY]){
  FILE *fp;
  fp = fopen("./patterns/glider.gol", "r");
  for (int i = 0; i < 3; ++i) {
    char str[maxX];
    fscanf(fp,"%s\n",str);
    for (int j = 0; j < 3; ++j) if(str[j]=='X') dots[j][i]= true;
  }
}

int main(int argc, char *argv[])
{
  srand(time(NULL));

  initscr();

  getmaxyx(stdscr,maxY,maxX);

  curs_set(0);
  cbreak();
  noecho();

  bool dots[maxX][maxY];
  for (int x = 0; x < maxX; ++x) for (int y = 0; y < maxY; ++y) dots[x][y]=0;
  initDots(dots);

  while(true){
    clear();

    bool newDots[maxX][maxY];
    for (int x = 0; x < maxX; ++x) for (int y = 0; y < maxY; ++y) newDots[x][y]=dots[x][y];

    for (int x = 0; x < maxX; ++x) for (int y = 0; y < maxY; ++y) {
        int found = 0;
        for (int x1 = x-1; x1 <= x+1; ++x1) for (int y1 = y-1; y1 <= y+1; ++y1) {
            if (x1 >= 0 && y1>=0 && x1 < maxX && y1 < maxY){
              if (x1!=x || y1!=y){
                if (dots[x1][y1])++found;
              }
            }
          }
        if(dots[x][y]){
          if(found<2 || found>3)newDots[x][y]=false;
          mvaddch(y,x,ACS_BLOCK);
        } else if(found == 3) newDots[x][y]=true;
      }

    for (int x = 0; x < maxX; ++x) for (int y = 0; y < maxY; ++y) dots[x][y]=newDots[x][y];

    refresh();
    if(getch() == 'q') break;
  }

	endwin();
  return 0;
}

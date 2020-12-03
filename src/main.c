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
#include <string.h>

int maxX, maxY;

void initDots(bool dots[maxX][maxY], char filePath[]){
  FILE *fp;
  fp = fopen(filePath, "r");
  int i = 0;
  while (!feof(fp)){
    char str[maxX];
    fscanf(fp,"%s\n",str);
    for (int j = 0; j < (int)sizeof(str); ++j) if(str[j]=='X') dots[j][i]= true;
    ++i;
  }
}

int main(int argc, char *argv[])
{
  initscr();

  getmaxyx(stdscr,maxY,maxX);

  curs_set(0);
  cbreak();
  noecho();

  bool dots[maxX][maxY];
  for (int x = 0; x < maxX; ++x) for (int y = 0; y < maxY; ++y) dots[x][y]=0;
  initDots(dots, argv[1]);

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

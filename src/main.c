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

int MAX_X, MAX_Y;

void initUniverse(bool universe[MAX_X][MAX_Y], char filePath[]){
  FILE *fp;
  fp = fopen(filePath, "r");
  int i = 0;
  while (!feof(fp)){
    char str[MAX_X];
    fscanf(fp,"%s\n",str);
    for (int j = 0; j < (int)sizeof(str); ++j) if(str[j]=='X') universe[j][i]= true;
    ++i;
  }
}

int main(int argc, char *argv[])
{
  initscr();

  getmaxyx(stdscr,MAX_Y,MAX_X);

  curs_set(0);
  cbreak();
  noecho();

  bool universe[MAX_X][MAX_Y];
  for (int x = 0; x < MAX_X; ++x) for (int y = 0; y < MAX_Y; ++y) universe[x][y]=0;
  initUniverse(universe, argv[1]);

  while(true){
    clear();

    bool newUniverse[MAX_X][MAX_Y];
    for (int x = 0; x < MAX_X; ++x) for (int y = 0; y < MAX_Y; ++y) newUniverse[x][y]=universe[x][y];

    for (int x = 0; x < MAX_X; ++x) for (int y = 0; y < MAX_Y; ++y) {
        int found = 0;
        for (int x1 = x-1; x1 <= x+1; ++x1) for (int y1 = y-1; y1 <= y+1; ++y1) {
            if (x1 >= 0 && y1>=0 && x1 < MAX_X && y1 < MAX_Y){
              if (x1!=x || y1!=y){
                if (universe[x1][y1])++found;
              }
            }
          }
        if(universe[x][y]){
          if(found<2 || found>3)newUniverse[x][y]=false;
          mvaddch(y,x,ACS_BLOCK);
        } else if(found == 3) newUniverse[x][y]=true;
      }

    for (int x = 0; x < MAX_X; ++x) for (int y = 0; y < MAX_Y; ++y) universe[x][y]=newUniverse[x][y];

    refresh();
    if(getch() == 'q') break;
  }

	endwin();
  return 0;
}

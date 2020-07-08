#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DELAY 30000

char RandomNumberGenerator(const int nMin, const int nMax, const int  nNumOfNumsToGenerate, const int val)
{
  int nRandomNumber = 0;
  for (int i = 0; i < nNumOfNumsToGenerate; i++)
  {
    nRandomNumber = rand()%(nMax-nMin) + nMin;
  }
  if (nRandomNumber > val) return 'X';
  else return ' ';
}

int check(char spot){
  if (spot == 'X') return 1;
  else return 0;
}

int main(int argc, char *argv[]) {
  if (argc == 1){
    printf("please type a number between 0-9 after program, e.g.\n");
    printf("./game_of_life 3\n");
    return 0;
  }
  else ;
  int x = 0, y = 10;
  int max_y = 0, max_x = 0;
  int next_x = 0;
  int direction = 1;
  int rn;
  initscr();
  
  curs_set(FALSE);
  srand(time(NULL));
  
  getmaxyx(stdscr, max_y, max_x);
  
  char field[max_y][max_x];
  char field_next[max_y][max_x];
  int n = atoi(argv[1]);
  for (int j = 0;j<max_y;j++){
    for (int i = 0;i<max_x;i++){
      field[j][i] = RandomNumberGenerator(0,9,1,n);
      field_next[j][i] = ' ';
    }
  }
  mvprintw(10,10,"A very simple implementation of Conway's Game of Life");
  mvprintw(11,10,"by Christian Johann Sutton");
  mvprintw(12,10,"christian.sutton@gmail.com");
  mvprintw(14,10,"\t\tPress control-c to stop");


  getch();
  while(1) {
    getmaxyx(stdscr, max_y, max_x);

    clear();

    for (int x1=0; x1<max_x;x1++){
      for (int y1=0; y1<max_y;y1++){
        mvprintw(y1,x1,"%c",field[y1][x1]);
        refresh();
      
      }
    }
    for (int x1=0; x1<max_x;x1++){
      for (int y1=0; y1<max_y;y1++){
        int sum = 0;
        int up = y1 - 1;
        int down = y1 + 1;
        int left = x1 - 1;
        int right = x1 + 1;

        if (up < 0) up = max_y - 1;
        if (down > max_y) down = 0;
        if (left < 0) left = max_x - 1;
        if (right > max_x) right = 0;
  
        sum = check(field[up][x1]) +  check(field[down][x1]) + check(field[y1][left]) + check(field[y1][right]);
        sum = check(field[up][right]) + check(field[up][left]) + check(field[down][right]) + check(field[down][left]) + sum;

        if ((field[y1][x1] == 'X') && ((sum == 2) || (sum == 3))) field_next[y1][x1] = 'X';
        else if ((field[y1][x1] == 'X') && ((sum == 1) || (sum == 4))) field_next[y1][x1] = ' ';
        else if ((field[y1][x1] == ' ') && (sum == 3)) field_next[y1][x1] = 'X';
        else field[y1][x1] = ' ';

        }
      }
      usleep(60000);
      for (int j = 0;j<max_y;j++){
        for (int i = 0;i<max_x;i++){
          field[j][i] = field_next[j][i];
          field_next[j][i] = ' ';
        }
      }

    }
  endwin();
  return 0;
}

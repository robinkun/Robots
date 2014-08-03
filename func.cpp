#include <stdio.h>
#include "func.h"

// 範囲内にいるかチェック
int check_in_scope(int size_x, int size_y, int x, int y) {
  if(x >= 0 && x < size_x && y >= 0 && y < size_y)
    return 1;
  else return 0;
}

void disp_level_line(int num) {
  int i;

  printf("+");
  for(i = 0; i < num; i++) printf("-");
  printf("+");
  puts("");
}

void surroundings(int direction, int *x, int *y) {
  switch(direction) {
  case 8: // 
    (*y)--;
    break;
  case 9: //     
    (*y)--; (*x)++;
    break;
  case 6: //  
    (*x)++;
    break;
  case 3: //     
    (*y)++; (*x)++;
    break;
  case 2: //  
    (*y)++;
    break;
  case 1: //     
    (*y)++; (*x)--;
    break;
  case 4: //  
    (*x)--;
    break;
  case 7: //     
    (*x)--; (*y)--;
    break;
  }
}

int min(int num1, int num2) {
  if(num1 <= num2) return num1;
  if(num2 < num1) return num2;
}

int max(int num1, int num2) {
  if(num1 >= num2) return num1;
  if(num2 > num1) return num2;
}

void change_num(int *num1, int *num2) {
  int dummy = *num1;
  *num1 = *num2;
  *num2 = dummy;
}

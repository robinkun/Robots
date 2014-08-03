#ifndef INCLUDED_FUNC_H
#define INCLUDED_FUNC_H

extern int check_in_scope(int size_x, int size_y, int x, int y);
extern void disp_level_line(int num);
extern void surroundings(int direction, int *x, int *y);
extern int min(int num1, int num2);
extern int max(int num1, int num2);
extern void change_num(int *num1, int *num2);

#endif

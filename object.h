#ifndef INCLUDED_OBJECT_H
#define INCLUDED_OBJECT_H
#include "node.h"
#include <stdlib.h>

class object {
public:
  node *root;
  node *point;

  object();
  node *add_obj(int x, int y, int type);
  void move(node *p, int x, int y);
  void move_point_obj(int x, int y);
  void set_point_root();
  int move_point();
  int get_x();
  int get_y();
  int get_type();
  node *get_node();
  void get_data(int num, int *x = NULL, int *y = NULL, int *type = NULL);
  void del_point_obj();
  void del_all();
  void del_loop(node *p);
};

#endif

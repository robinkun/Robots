#ifndef INCLUDED_FIELD_H
#define INCLUDED_FIELD_H
#include "node.h"

class field {
public:
  int size_x, size_y;
  int cur_x, cur_y;
  node **objs;
  node *point;

  field();
  field(int x, int y);
  void make_array();
  node *make_obj(int x, int y, int type);
  void del_obj(node *obj);
  void reg_obj(node *obj);
  void move_obj(node *obj, int x, int y);
  void move_point_obj(int x, int y);
  int del_point_obj();
  void set_point_root(int x, int y);
  int move_point();
  int get_x();
  int get_y();
  int get_type();
  node *get_node();
};

#endif

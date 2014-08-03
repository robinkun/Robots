#ifndef INCLUDED_GAMEOBJ_H
#define INCLUDED_GAMEOBJ_H
#include <stdlib.h>
#include "node.h"

class gameobj {
public:
  int size_x, size_y;
  int point_x, point_y;
  int typenum;
  int ***objnum;
  int *objtotal;
  node **field;
  node *objs;
  node *point;

private:
  node *oadd_obj(int x, int y, int type);
  void freg_obj(node *obj);
  void del_objs_loop(node *p);
public:
  gameobj();
  gameobj(int x, int y, int typenum);
  void init_objnum();
  void init_field();
  void init_objs();
  void add_obj(int x, int y, int type);
  void move_obj(node *obj, int x, int y);
  void move_point_obj(int x, int y);
  void del_obj(node *obj);
  void del_point_obj();
  void del_objs();
  void del_field();
  void del_objnum();
  int  get_objnum(int x, int y, int type);
  int  get_objtotal(int type);
  void fset_point_root(int x, int y);
  void oset_point_root();
  int  fmove_point();
  int  omove_point();
  int  get_x();
  int  get_y();
  int  get_type();
  void oget_data(int num, int *x = NULL, int *y = NULL, int *type = NULL);
  int check_type(int type);
};

#endif

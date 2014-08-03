#include <stdlib.h>
#include "object.h"

object::object() {
  root = new node();
  point = root;
}

node *object::add_obj(int x, int y, int type) {
  node *p;

  for(p = root; p->objn != NULL; p = p->objn);
  p->make_next();
  p->objn->set_num(x, y, type);

  return p->objn;
}

void object::move(node *p, int x, int y) {
  p->x = x;
  p->y = y;
}

void object::move_point_obj(int x, int y) {
  move(point, x, y);
}

void object::del_all() {
  del_loop(root);
}

void object::del_loop(node *p) {
  if(p->objn != NULL) {
    del_loop(p->objn);
  }
  delete p;
}

void object::set_point_root() {
  point = root;
}

int object::move_point() {
  point = point->objn;
  if(point == NULL) {
    point = root->objn;
    return 1;
  }
  return 0;
}

int object::get_x() {
  return point->x;
}

int object::get_y() {
  return point->y;
}

int object::get_type() {
  return point->type;
}

node *object::get_node() {
  return point;
}

void object::get_data(int num, int *x, int *y, int *type) {
  int i;
  node *p;

  for(p = root; p->objn != NULL && num > 0; p = p->objn, num--) {
  }

  if(x != NULL) *x = p->x;
  if(y != NULL) *y = p->y;
  if(type != NULL) *type = p->type;
}

void object::del_point_obj() {
  if(point == NULL) return;
  point->fieldp->fieldn = point->fieldn;
  if(point->fieldn != NULL)
    point->fieldn->fieldp = point->fieldp;
  point->objp->objn = point->objn;
  if(point->objn != NULL)
    point->objn->objp = point->objp;
  point->del_node();
}

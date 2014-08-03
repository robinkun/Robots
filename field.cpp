#include <stdlib.h>
#include <stdio.h>
#include "node.h"
#include "field.h"


field::field() {
}

field::field(int x, int y) {
  size_x = x;
  size_y = y;
  cur_x = 0;
  cur_y = 0;
  make_array();
}

void field::make_array() {
  int i, j;

  objs = new node*[size_y];
  for(i = 0; i < size_y; i++) {
    objs[i] = new node[size_x];
    for(j = 0; j < size_x; j++)
      objs[i][j] = node();
  }
}

node *field::make_obj(int x, int y, int type) {
  node *p, *prev;

  for(p = objs[y][x].fieldn, prev = &objs[y][x]; p != NULL; p = p->fieldn, prev = prev->fieldn) {
    if(p->type > type) break;
  }
  prev->make_nextf();
  prev->fieldn->set_num(x, y, type);

  return prev->fieldn;
}

void field::del_obj(node *obj) {
  if(obj->fieldp != NULL)
    obj->fieldp->fieldn = obj->fieldn;
  if(obj->fieldn != NULL)
    obj->fieldn->fieldp = obj->fieldp;
  if(obj->objp != NULL)
    obj->objp->objn = obj->objn;
  if(obj->objn != NULL)
    obj->objn->objp = obj->objp;
  delete obj;
}

void field::reg_obj(node *obj) {
  node *prev;

  if(obj == NULL) return;
  for(prev = &objs[obj->y][obj->x]; prev->fieldn != NULL; prev = prev->fieldn) {
    if(prev->type > obj->type) break;
  }
  if(obj->fieldp != NULL)
    obj->fieldp->fieldn = obj->fieldn;
  if(obj->fieldn != NULL)
    obj->fieldn->fieldp = obj->fieldp;
  obj->fieldn = prev->fieldn;
  obj->fieldp = prev;

  if(prev->fieldn != NULL)
    prev->fieldn->fieldp = obj;
  prev->fieldn = obj;
}

void field::move_obj(node *obj, int x, int y) {
  obj->x = x;
  obj->y = y;

  reg_obj(obj);
}

int field::del_point_obj() {
  node *p = point;
  point = point->fieldp;

  del_obj(p);
}

void field::move_point_obj(int x, int y) {
  if(this->point->type == -1) {
    puts("Point is root");
  } else move_obj(point, x, y);
}

void field::set_point_root(int x, int y) {
  cur_x = x;
  cur_y = y;
  point = &objs[y][x];
}

int field::move_point() {
  point = point->fieldn;
  if(point == NULL) {
    point = objs[cur_y][cur_x].fieldn;
    return 1;
  }
  return 0;
}

node *field::get_node() {
  return point;
}

int field::get_x() {
  return point->x;
}

int field::get_y() {
  return point->y;
}

int field::get_type() {
  return point->type;
}

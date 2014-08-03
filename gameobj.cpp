#include <stdio.h>
#include <stdlib.h>
#include "gameobj.h"

gameobj::gameobj() {
}

gameobj::gameobj(int x, int y, int typenum) {
  this->size_x = x;
  this->size_y = y;
  this->typenum = typenum;
  init_objnum();
  init_field();
  init_objs();
  point = objs;
}

void gameobj::init_objnum() {
  int i, j, k;

  objtotal = new int[typenum];
  objnum = new int**[size_y];
  for(i = 0; i < typenum; i++) objtotal[i] = 0;
  for(i = 0; i < size_y; i++) {
    objnum[i] = new int*[size_x];
    for(j = 0; j < size_x; j++) {
      objnum[i][j] = new int[typenum];
      for(k = 0; k < typenum; k++) {
        objnum[i][j][k] = 0;
      }
    }
  }
}

void gameobj::init_field() {
  int i, j;

  field = new node*[size_y];
  for(i = 0; i < size_y; i++) {
    field[i] = new node[size_x];
    for(j = 0; j < size_x; j++)
      field[i][j] = node();
  }
}

void gameobj::init_objs() {
  objs = new node();
}

node *gameobj::oadd_obj(int x, int y, int type) {
  node *p;

  for(p = objs; p->objn != NULL; p = p->objn);
  p->make_next();
  p->objn->set_num(x, y, type);

  return p->objn;
}

void gameobj::freg_obj(node *obj) {
  node *prev;

  if(obj == NULL) return;
  for(prev = &field[obj->y][obj->x]; prev->fieldn != NULL; prev = prev->fieldn) {
    if(prev->fieldn->type > obj->type) break;
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

void gameobj::add_obj(int x, int y, int type) {
  if(type <= typenum) {
    freg_obj(oadd_obj(x, y, type));
    objnum[y][x][type]++;
    objtotal[type]++;
  } else {
    puts("type deksugi");
  }
}

void gameobj::move_obj(node *obj, int x, int y) {
  if(x == obj->x && y == obj->y) return;
  objnum[obj->y][obj->x][obj->type]--;
  objnum[y][x][obj->type]++;
  obj->x = x;
  obj->y = y;

  freg_obj(obj);
}

void gameobj::move_point_obj(int x, int y) {
  if(this->point->type == -1) {
    puts("Point is root");
  } else move_obj(point, x, y);
}

void gameobj::del_obj(node *obj) {
  if(check_type(obj->type)) {
    objnum[obj->y][obj->x][obj->type]--;
    objtotal[obj->type]--;
  }
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

void gameobj::del_point_obj() {
  node *p = point;
  point = point->fieldp;

  del_obj(p);
}

void gameobj::del_objs_loop(node *p) {
  if(p->objn != NULL) del_objs_loop(p->objn);
  /*
  if(p->type >= 0 && p->type < typenum) {
    objnum[p->y][p->x][p->type]--;
    objtotal[p->type]--;
  }*/
  del_obj(p);
}

void gameobj::del_objs() {
  del_objs_loop(objs);
}

void gameobj::del_field() {
  int i;

  for(i = 0; i < size_y; i++) {
    delete [] field[i];
  }
  delete [] field;
}

void gameobj::del_objnum() {
  int i, j;

  for(i = 0; i < size_y; i++) {
    for(j = 0; j < size_x; j++) {
      delete [] objnum[i][j];
    }
    delete [] objnum[i];
  }
  delete [] objnum;
  delete [] objtotal;
}

int gameobj::get_objnum(int x, int y, int type) {
  return objnum[y][x][type];
}

int gameobj::get_objtotal(int type) {
  return objtotal[type];
}

void gameobj::fset_point_root(int x, int y) {
  point_x = x;
  point_y = y;
  point = &field[y][x];
}

int gameobj::fmove_point() {
  point = point->fieldn;
  if(point == NULL) {
    point = field[point_y][point_x].fieldn;
    return 1;
  }
  return 0;
}

void gameobj::oset_point_root() {
  point = objs;
}

int gameobj::omove_point() {
  point = point->objn;
  if(point == NULL) {
    point = objs->objn;
    return 1;
  }
  return 0;
}

int gameobj::get_x() {
  return point->x;
}

int gameobj::get_y() {
  return point->y;
}

int gameobj::get_type() {
  return point->type;
}

int gameobj::check_type(int type) {
  if(type < typenum && type >= 0) return 1;
  return 0;
}

void gameobj::oget_data(int num, int *x, int *y, int *type) {
  int i;
  node *p;

  for(p = objs; p->objn != NULL && num > 0; p = p->objn, num--) {
  }

  if(x != NULL) *x = p->x;
  if(y != NULL) *y = p->y;
  if(type != NULL) *type = p->type;
}

#include <stdlib.h>
#include "node.h"

node::node() {
  int x = y = type = -1;
  this->fieldp = NULL;
  this->fieldn = NULL;
  this->objp = NULL;
  this->objn = NULL;
}

void node::set_num(int x, int y, int type) {
  this->x = x;
  this->y = y;
  this->type = type;
}

void node::make_next() {
  this->objn = new node();
  this->objn->objp = this;
}

void node::make_nextf() {
  this->fieldn = new node();
  this->fieldn->fieldp = this;
}

void node::del_node() {
  delete this;
}


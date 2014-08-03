#ifndef INCLUDED_NODE_H
#define INCLUDED_NODE_H

class node {
public:
  int x, y;
  int type;
  node *fieldn;
  node *fieldp;
  node *objn;
  node *objp;

  node();
  void set_num(int x, int y, int type);
  void make_next();
  void make_nextf();
  void del_node();
};

#endif

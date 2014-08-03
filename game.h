#ifndef INCLUDED_GAME_H
#define INCLUDED_GAME_H
#include "gameobj.h"

class game {
public:
  gameobj objs;
  int size_x, size_y;
  int time;
  int cmd;
  int level, score;

  game(int x, int y);
  ~game();

  int  make_objs();
  void disp_data(int x, int y);
  void disp_myfield();
  void disp_status();
  int  command(int key);
  void add_time(int direction);
  void add_score(int robotnum);
  int  check_moveable();

  void move();
  void move_all();
  void move_player();
  void move_robot(int px, int py);
  void move_myrobot();

  void check_collision(int x, int y);
  void check_collision_all();
  int  check_gameover();
  int  check_gameclear();
  int  levelup();

  int  delete_obj(int x, int y, int type);
};

#endif

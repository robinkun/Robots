#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "gameobj.h"
#include "func.h"
#include "getchar.h"
#include "int.h"

game::game(int x, int y) {
  this->size_x = x;
  this->size_y = y;
  this->cmd = 0;
  this->time = 0;
  this->level = 1;
  this->score = 0;
  this->objs = gameobj(size_x, size_y, TYPE_NUM);
}

game::~game() {
  objs.del_objs();
  objs.del_field();
  objs.del_objnum();
}

int game::make_objs() {
  int i, j, r = min(this->level * 5, MAXROBOT);
  int x, y, px, py;
  int **dummy = new int*[size_y];

  objs.del_objs();
  objs.init_objs();

  for(i = 0; i < size_y; i++) {
    dummy[i] = new int[size_x];
    for(j = 0; j < size_x; j++) {
      if(i*size_x+j < r+1)
        dummy[i][j] = ROBOT;
      else
        dummy[i][j] = NOTHING;
    }
  }
  dummy[0][0] = PLAYER;

  for(i = 0; i < size_y; i++) {
    for(j = 0; j < size_x; j++) {
      x = rand() % size_x;
      y = rand() % size_y;
      change_num(&dummy[i][j], &dummy[y][x]);
      if(dummy[y][x] == PLAYER) {
        px = x;
        py = y;
      }
    }
  }

  // プレイヤーを最初のオブジェクトにする
  objs.add_obj(px, py, PLAYER);
  for(i = 0; i < size_y; i++) {
    for(j = 0; j <size_x; j++) {
      if(dummy[i][j] == ROBOT)
        objs.add_obj(j, i, dummy[i][j]);
    }
  }
}

void game::move_all() {
  for(objs.oset_point_root(); objs.omove_point() != 1;)
    move();
}

void game::move() {
  switch(objs.get_type()) {
  case PLAYER:
    move_player();
    break;
  case ROBOT:
    move_myrobot();
    break;
  case SCRAP:
    break;
  }
}

void game::move_player() {
  int x, y;
  
  x = objs.get_x();
  y = objs.get_y();
  if(cmd == '0') {
    x = rand() % size_x;
    y = rand() % size_y;
  }else surroundings(cmd - '0', &x, &y);
  if(check_in_scope(size_x, size_y, x, y)) {
    if(objs.get_objnum(x, y, ROBOT) >= 1 && objs.get_objnum(x, y, SCRAP) >= 1) return;
      objs.move_point_obj(x, y);
  }
}

void game::move_robot(int px, int py) {
  int x, y;

  x = objs.get_x();
  y = objs.get_y();
  if(px > x) x++;
  else if(px < x) x--;
  if(py > y) y++;
  else if(py < y) y--;

  if(check_in_scope(size_x, size_y, x, y)) {
    objs.move_point_obj(x, y);
  }
}

void game::move_myrobot() {
  int x = 5, y = 5;

  objs.oget_data(1, &x, &y);
  move_robot(x, y);
}

void game::check_collision(int x, int y) {
  if(objs.get_objnum(x, y, ROBOT) >= 2 || (objs.get_objnum(x, y, ROBOT) >= 1 && objs.get_objnum(x, y, SCRAP) >= 1)) {
    score += (delete_obj(x, y, ROBOT));
    delete_obj(x, y, SCRAP);
    objs.add_obj(x, y, SCRAP);
  }
}

void game::check_collision_all() {
  int i, j;

  for(i = 0; i < size_y; i++) {
    for(j = 0; j < size_x; j++) {
      check_collision(j, i);
    }
  }
}

int game::check_gameover() {
  int x, y;

  objs.oget_data(1, &x, &y);
  if(objs.get_objnum(x, y, PLAYER) >= 1 && (objs.get_objnum(x, y, ROBOT) >= 1 || objs.get_objnum(x, y, SCRAP) >= 1)) {
    return GAMEOVER;
  }
  return GAMECONTINUE;
}

int game::check_gameclear() {
  if(objs.get_objtotal(ROBOT) <= 0) {
    return GAMECLEAR;
  }
  return GAMECONTINUE;
}

int game::delete_obj(int x, int y, int type) {
  int i = 0;

  for(objs.fset_point_root(x, y); objs.fmove_point() != 1; i++) {
    if(objs.get_type() == type) {
      objs.del_point_obj();
    }
  }
  return i;
}

int game::command(int key) {
  cmd = key;
  switch(key) {
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    add_time(key-'0');
    break;
  case 'q':
    return GAMEEND;
    break;
  }
  return GAMECONTINUE;
}

void game::add_time(int direction) {
  if(check_moveable()) {
    move_all();
    check_collision_all();
    time++;
  }
}

int game::check_moveable() {
  int x, y;

  objs.oget_data(1, &x, &y);
  surroundings(cmd - '0', &x, &y);
  if(check_in_scope(size_x, size_y, x, y)) {
    if(objs.get_objnum(x, y, ROBOT) >= 1 || objs.get_objnum(x, y, SCRAP) >= 1) return 0;
    return 1;
  }
  return 0;
}

int game::levelup() {
  this->score += level * 10;
  this->level++;
}

void game::disp_myfield() {
  int i, j, data;
  
  disp_level_line(this->size_x);
  for(i = 0; i < this->size_y; i++) {
    printf("|");
    for(j = 0; j < this->size_x; j++) {
      this->disp_data(j, i);
    }
    puts("|");
  }
  disp_level_line(this->size_x);
  disp_status();
  puts(":?");
}

void game::disp_status() {
  printf("(level:%d score:%d)", this->level, this->score);
}

void game::disp_data(int x, int y) {
  objs.fset_point_root(x, y);
  if(objs.fmove_point() != 1) {
    switch(objs.get_type()) {
    case NOTHING:
      printf(" ");
      break;
    case PLAYER:
      printf("@");
      break;
    case ROBOT:
      printf("+");
      break;
    case SCRAP:
      printf("*");
      break;
    default:
      printf("%d", objs.get_type());
      break;
    }
  } else {
    printf(" ");
  }
}


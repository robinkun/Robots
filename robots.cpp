#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "int.h"
#include "func.h"
#include "getchar.h"
#define SIZE_X 60
#define SIZE_Y 20

int game_main(game *mygame);

int main(void) {
  int game_status = GAMECONTINUE;
  game *mygame = new game(SIZE_X, SIZE_Y);

  srand((unsigned)time(NULL));
  while(game_status != GAMEEND) {
    mygame->make_objs();
    game_status = game_main(mygame);
  }

  delete mygame;

  return 0;
}

int game_main(game *mygame) {
  int key;
  int game_status = GAMECONTINUE;

  while(game_status == GAMECONTINUE) {
    mygame->disp_myfield();
    key = getChar();
    game_status = mygame->command(key);
    game_status = max(mygame->check_gameover(), game_status);
    game_status = max(mygame->check_gameclear(), game_status);
  }

  if(game_status == GAMEOVER) {
    printf("\nGame over...");
    mygame->disp_status();
    puts("");
    game_status = GAMEEND;
  }else if(game_status == GAMECLEAR) {
    mygame->levelup();
  }

  return game_status;
}

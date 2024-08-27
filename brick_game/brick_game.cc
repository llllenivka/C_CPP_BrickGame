extern "C" {
#include "./tetris/tetris.c"
#include "./tetris/tetris.h"
#include "./tetris/tetris_backend.c"
#include "./tetris/tetris_backend.h"
#include "./tetris/tetris_sm.h"
}

#include "snake/snake.h"

void game() {
  int code = START_GAME;
  while (code != QUIT_GAME) {
    code = show_start_game();
    switch (code) {
      case TETRIS:
        game_loop();
        break;

      case SNAKE:
        s21::GameSnakeInfo GameInfo;
        GameInfo.GameSnake();
        break;
    }
  }
}

int main() {
  settings_ncurses();
  keypad(stdscr, true);
  game();
  endwin();
  return 0;
}
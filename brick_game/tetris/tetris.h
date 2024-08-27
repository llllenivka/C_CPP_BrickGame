#ifndef TETRIS_H
#define TETRIS_H

// #include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../../gui/cli/frontend_term.h"
#include "tetris_backend.h"

void game_loop();
void pause_game(Game_state_t *game_state);

#endif
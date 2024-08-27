#ifndef FRONTEND_TERM_H
#define FRONTEND_TERM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../../brick_game/tetris/tetris_backend.h"

void settings_ncurses();
int show_start_game();
void text_tetris();
void text_snake();
int menu();
void menu_selection(int index_i, int index_j, int game);
int pause_menu();

void print_field(int field[HEIGHT_FIELD][WIDHT_FIELD]);
void drawing_figures(int i, int j);
void drawing_border(int i_start, int i_end, int j_start, int j_end);

void print_level(int level);
void print_score(int score, int record);
void control_hint();

void show_tetris(Game_state_t game_state);
void print_next_figure(Game_state_t game_state);
void show_snake(int field[HEIGHT_FIELD][WIDHT_FIELD], int level, int score,
                int record);

void end_game(int record, int score, int game_state);
void text_game_over();
void text_you_win();

#ifdef __cplusplus
}
#endif

#endif

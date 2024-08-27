#ifndef TETRIS_BACKEND_H
#define TETRIS_BACKEND_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../defines.h"
#include "tetris_sm.h"

typedef struct {
  int f_square[4][4];
  int f_stick[4][4];
  int f_zigzag_r[4][4];
  int f_zigzag_l[4][4];
  int f_corner_r[4][4];
  int f_corner_l[4][4];
  int f_tank[4][4];
} Figures_t;

typedef struct {
  int field[HEIGHT_FIELD][WIDHT_FIELD];
  int figure[4][4];

  Figures_t figure_template;
  Tetris_state state_machine;

  int index_figure_i;
  int index_figure_j;
  int index_born;

  int next_figure;
  int current_color;
  int next_color;

  unsigned int record;
  unsigned int score;
  short int level;
  int speed;
} Game_state_t;

void init_game_state(Game_state_t *game_state);
void tetris_start(Game_state_t *game_state);

void create_templates(Figures_t *figure_templates);
void init_record(Game_state_t *game_state);
void new_record(Game_state_t game_state);

// SPAWN
void new_figure(int result[4][4], Figures_t figures, int current_figure,
                int color);
void copy_figure(int result[4][4], int figures[4][4], int color);

// MOVING
int press_button(Game_state_t *game_state, int button);
int left_move(Game_state_t *game_state);
int right_move(Game_state_t *game_state);
int turn(Game_state_t *game_state);
int rolling_figure(Game_state_t *game_state);
void insert_figure(Game_state_t *game_state);

// SHIFTING
int down_move(Game_state_t *game_state);
int spawn_figure(Game_state_t *game_state, int code);
void figure_fell(Game_state_t *game_state);

// ATTACHING
void attaching(Game_state_t *game_state);
void delete_line(Game_state_t *game_state, int line_index);
void scoring(Game_state_t *game_state, int count_combo);

void spawning(Game_state_t *game_state, int *current_figure);
void moving(Game_state_t *game_state, int user_key);
void shifting(Game_state_t *game_state);
void attaching(Game_state_t *game_state);
void new_level(Game_state_t *game_state);

#endif

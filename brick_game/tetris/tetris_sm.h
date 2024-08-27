#ifndef TETRIS_SM_H
#define TETRIS_SM_H

typedef enum {
  START = 0,
  PAUSE,
  SPAWN,
  MOVING,
  SHIFTING,
  ATTACHING,
  GAMEOVER,
  EXITGAME
} Tetris_state;

#endif
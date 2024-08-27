#ifndef SNAKE_FSM_H
#define SNAKE_FSM_H

namespace s21 {

typedef enum {
  START = 0,
  SPAWNSNAKE,
  SPAWNAPPLE,
  PAUSE,
  MOVING,
  SHIFTING,
  EATING,
  GAMEOVER
} FSM_Snake_t;

}

#endif
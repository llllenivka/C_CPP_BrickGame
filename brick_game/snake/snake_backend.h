#ifndef SNAKE_BACKEND_C
#define SNAKE_BACKEND_C

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <list>

#include "../defines.h"
#include "snake_fsm.h"

namespace s21 {

class GameSnakeInfo {
 public:
  /* Основные параметры */
  int field_[HEIGHT_FIELD][WIDHT_FIELD];
  FSM_Snake_t state_;
  int UserKey;
  int PrevUserKey;
  int speed_;
  unsigned short int level_;
  unsigned short int score_;
  unsigned short int record_;

  /*(first == i, second == j)*/
  std::pair<int, int> index_apple_;

  /* Определение местоположения змеи на поле (first == i, second == j) */
  std::list<std::pair<int, int>> snake_;

  using iterator = std::list<std::pair<int, int>>::iterator;

  GameSnakeInfo();

  void GameSnake();
  void PauseGame();
  void InitNewGame();

  int CheckPressButton();
  void InitRecord();

  void SpawningSnake();
  void SpawningApple();

  void MovingSnake();
  int MovingRight(iterator Head);
  int MovingLeft(iterator Head);
  int MovingUp(iterator Head);
  int MovingDown(iterator Head);
  int MovingForward(iterator Head);
  void Move(std::pair<int, int> NewHead);

  void ShiftingSnake();

  void EatingApple();

  void NewRecord();
};
}  // namespace s21
#endif
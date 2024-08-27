#include "test.h"

TEST(StateShift, Shift_1) {
  s21::GameSnakeInfo Game;
  Game.SpawningSnake();

  Game.ShiftingSnake();

  bool IsSnake = true;

  for (int j = 1; j < 5 && IsSnake; j++) {
    if (Game.field_[HEIGHT_FIELD - 4][j] != 1) IsSnake = false;
  }

  EXPECT_EQ(IsSnake, true);
}

TEST(StateShift, Shift_2) {
  s21::GameSnakeInfo Game;
  Game.SpawningSnake();
  Game.field_[HEIGHT_FIELD - 4][4] = IS_APPLE;

  Game.ShiftingSnake();
  bool IsSnake = true;

  for (int j = 0; j < 4 && IsSnake; j++) {
    if (Game.field_[HEIGHT_FIELD - 4][j] != 1) IsSnake = false;
  }

  EXPECT_EQ(IsSnake, true);
  EXPECT_EQ(Game.state_, s21::EATING);
}

TEST(StateShift, Shift_3) {
  s21::GameSnakeInfo Game;
  Game.SpawningSnake();

  while (Game.state_ != s21::GAMEOVER) Game.ShiftingSnake();
  bool IsSnake = true;

  for (int j = 6; j < 10 && IsSnake; j++) {
    if (Game.field_[HEIGHT_FIELD - 4][j] != 1) IsSnake = false;
  }

  EXPECT_EQ(IsSnake, true);
  EXPECT_EQ(Game.state_, s21::GAMEOVER);
}
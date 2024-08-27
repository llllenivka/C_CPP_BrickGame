#include "test.h"

TEST(StateEat, Eat_1) {
  s21::GameSnakeInfo Game;
  Game.SpawningSnake();

  Game.index_apple_ = {HEIGHT_FIELD - 4, 4};
  Game.state_ = s21::EATING;

  Game.score_ = 4;

  bool IsSnake = true;

  Game.EatingApple();

  for (int j = 0; j < 5; j++) {
    if (Game.field_[HEIGHT_FIELD - 4][j] != 1) IsSnake = false;
  }
  EXPECT_EQ(Game.record_, 5);
  EXPECT_EQ(Game.score_, 5);
  EXPECT_EQ(Game.state_, s21::SPAWNAPPLE);
  EXPECT_EQ(IsSnake, true);
}
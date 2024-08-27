#include "test.h"

TEST(SupFun, SupFun_1) {
  s21::GameSnakeInfo Game;
  Game.SpawningSnake();

  Game.InitNewGame();
  EXPECT_EQ(Game.snake_.empty(), true);
}

TEST(SupFun, SupFun_2) {
  s21::GameSnakeInfo Game;
  Game.UserKey = 0;

  EXPECT_EQ(Game.CheckPressButton(), 1);
}

TEST(SupFun, SupFun_3) {
  s21::GameSnakeInfo Game;
  Game.UserKey = BUTTON_UP;
  Game.PrevUserKey = BUTTON_DOWN;

  EXPECT_EQ(Game.CheckPressButton(), 1);
}

TEST(SupFun, SupFun_4) {
  s21::GameSnakeInfo Game;
  Game.UserKey = BUTTON_LEFT;
  Game.PrevUserKey = BUTTON_RIGHT;

  EXPECT_EQ(Game.CheckPressButton(), 1);
}
#include "test.h"

TEST(StartState, Start_1) {
  s21::GameSnakeInfo Game;

  EXPECT_EQ(Game.state_, s21::START);
  EXPECT_EQ(Game.speed_, 600);
  EXPECT_EQ(Game.PrevUserKey, BUTTON_RIGHT);
}

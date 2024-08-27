#include "test.h"

TEST(StateSpawn, Spawn_1) {
  s21::GameSnakeInfo Game;
  Game.SpawningApple();
  bool IsApple = false;

  for (int i = 0; i < HEIGHT_FIELD && !IsApple; i++) {
    for (int j = 0; j < WIDHT_FIELD && !IsApple; j++) {
      if (Game.field_[i][j] == 11) IsApple = true;
    }
  }

  EXPECT_EQ(IsApple, true);
}

TEST(StateSpawn, Spawn_2) {
  s21::GameSnakeInfo Game;
  Game.SpawningSnake();
  bool IsSnake = true;

  for (int j = 0; j < 4 && IsSnake; j++) {
    if (Game.field_[HEIGHT_FIELD - 4][j] != 1) IsSnake = false;
  }

  EXPECT_EQ(IsSnake, true);
}
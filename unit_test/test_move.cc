#include "test.h"

TEST(StateMove, MoveRight_1) {
  s21::GameSnakeInfo Game;
  Game.SpawningSnake();
  Game.UserKey = BUTTON_RIGHT;

  Game.MovingSnake();

  bool IsSnake = true;

  for (int j = 1; j < 5 && IsSnake; j++) {
    if (Game.field_[HEIGHT_FIELD - 4][j] != 1) IsSnake = false;
  }

  EXPECT_EQ(IsSnake, true);
}

TEST(StateMove, MoveRight_2) {
  s21::GameSnakeInfo Game;
  Game.SpawningSnake();

  auto head = Game.snake_.begin();
  Game.MovingUp(head);
  Game.PrevUserKey = BUTTON_UP;
  head = Game.snake_.begin();
  Game.MovingLeft(head);
  Game.PrevUserKey = BUTTON_LEFT;

  Game.UserKey = BUTTON_RIGHT;
  Game.MovingSnake();

  bool IsSnake = true;

  if (Game.field_[HEIGHT_FIELD - 4][2] != 1 ||
      Game.field_[HEIGHT_FIELD - 4][3] != 1 ||
      Game.field_[HEIGHT_FIELD - 5][3] != 1 ||
      Game.field_[HEIGHT_FIELD - 5][2] != 1)
    IsSnake = false;

  EXPECT_EQ(IsSnake, true);
}

TEST(StateMove, MoveRight_3) {
  s21::GameSnakeInfo Game;
  Game.SpawningSnake();

  Game.field_[HEIGHT_FIELD - 4][4] = IS_APPLE;

  Game.UserKey = BUTTON_RIGHT;
  Game.MovingSnake();

  bool IsSnake = true;

  for (int j = 0; j < 4 && IsSnake; j++) {
    if (Game.field_[HEIGHT_FIELD - 4][j] != 1) IsSnake = false;
  }

  EXPECT_EQ(IsSnake, true);
  EXPECT_EQ(Game.state_, s21::EATING);
}

TEST(StateMove, MoveRight_4) {
  s21::GameSnakeInfo Game;
  Game.SpawningSnake();

  Game.UserKey = BUTTON_RIGHT;
  for (int count = 0; count < 7; count++) Game.MovingSnake();

  bool IsSnake = true;

  for (int j = 6; j < 10 && IsSnake; j++) {
    if (Game.field_[HEIGHT_FIELD - 4][j] != 1) IsSnake = false;
  }

  EXPECT_EQ(IsSnake, true);
  EXPECT_EQ(Game.state_, s21::GAMEOVER);
}

TEST(StateMove, MoveLeft_1) {
  s21::GameSnakeInfo Game;
  Game.SpawningSnake();

  Game.UserKey = BUTTON_LEFT;

  Game.MovingSnake();

  bool IsSnake = true;

  for (int j = 0; j < 4 && IsSnake; j++) {
    if (Game.field_[HEIGHT_FIELD - 4][j] != 1) IsSnake = false;
  }

  EXPECT_EQ(IsSnake, true);
}

TEST(StateMove, MoveLeft_2) {
  s21::GameSnakeInfo Game;
  Game.SpawningSnake();
  Game.UserKey = BUTTON_LEFT;

  auto head = Game.snake_.begin();
  Game.MovingUp(head);
  Game.PrevUserKey = BUTTON_UP;

  for (int count = 0; count < 4; count++) Game.MovingSnake();

  bool IsSnake = true;

  for (int j = 0; j < 4 && IsSnake; j++) {
    if (Game.field_[HEIGHT_FIELD - 5][j] != 1) IsSnake = false;
  }

  EXPECT_EQ(IsSnake, true);
  EXPECT_EQ(Game.state_, s21::GAMEOVER);
}

TEST(StateMove, MoveLeft_3) {
  s21::GameSnakeInfo Game;
  Game.SpawningSnake();
  Game.UserKey = BUTTON_LEFT;

  Game.field_[HEIGHT_FIELD - 5][2] = IS_APPLE;

  auto head = Game.snake_.begin();
  Game.MovingUp(head);
  Game.PrevUserKey = BUTTON_UP;

  Game.MovingSnake();

  bool IsSnake = true;

  for (int j = 1; j < 4 && IsSnake; j++) {
    if (Game.field_[HEIGHT_FIELD - 4][j] != 1) IsSnake = false;
  }
  if (Game.field_[HEIGHT_FIELD - 5][3] != 1) IsSnake = false;

  EXPECT_EQ(IsSnake, true);
  EXPECT_EQ(Game.state_, s21::EATING);
}

TEST(StateMove, MoveLeft_4) {
  s21::GameSnakeInfo Game;
  Game.SpawningSnake();

  Game.MovingSnake();

  bool IsSnake = true;

  for (int j = 0; j < 4 && IsSnake; j++) {
    if (Game.field_[HEIGHT_FIELD - 4][j] != 1) IsSnake = false;
  }

  EXPECT_EQ(IsSnake, true);
}

TEST(StateMove, MoveUp_1) {
  s21::GameSnakeInfo Game;
  Game.SpawningSnake();

  auto head = Game.snake_.begin();
  Game.MovingDown(head);
  Game.PrevUserKey = BUTTON_DOWN;

  Game.UserKey = BUTTON_UP;
  Game.MovingSnake();

  bool IsSnake = true;

  for (int j = 1; j < 4 && IsSnake; j++) {
    if (Game.field_[HEIGHT_FIELD - 4][j] != 1) IsSnake = false;
  }
  if (Game.field_[HEIGHT_FIELD - 3][3] != 1) IsSnake = false;

  EXPECT_EQ(IsSnake, true);
}

TEST(StateMove, MoveUp_2) {
  s21::GameSnakeInfo Game;
  Game.SpawningSnake();

  Game.field_[HEIGHT_FIELD - 5][3] = IS_APPLE;

  Game.UserKey = BUTTON_UP;
  Game.MovingSnake();

  bool IsSnake = true;

  for (int j = 0; j < 4 && IsSnake; j++) {
    if (Game.field_[HEIGHT_FIELD - 4][j] != 1) IsSnake = false;
  }

  EXPECT_EQ(IsSnake, true);
  EXPECT_EQ(Game.state_, s21::EATING);
}

TEST(StateMove, MoveUp_3) {
  s21::GameSnakeInfo Game;
  Game.SpawningSnake();

  Game.UserKey = BUTTON_UP;

  while (Game.state_ != s21::GAMEOVER) {
    Game.MovingSnake();
    Game.PrevUserKey = BUTTON_UP;
  }

  bool IsSnake = true;

  for (int i = 0; i < 4 && IsSnake; i++) {
    if (Game.field_[i][3] != 1) IsSnake = false;
  }

  EXPECT_EQ(IsSnake, true);
  EXPECT_EQ(Game.state_, s21::GAMEOVER);
}

TEST(StateMove, MoveDown_1) {
  s21::GameSnakeInfo Game;
  Game.SpawningSnake();

  Game.field_[HEIGHT_FIELD - 3][3] = IS_APPLE;

  Game.UserKey = BUTTON_DOWN;
  Game.MovingSnake();

  bool IsSnake = true;

  for (int j = 0; j < 4 && IsSnake; j++) {
    if (Game.field_[HEIGHT_FIELD - 4][j] != 1) IsSnake = false;
  }

  EXPECT_EQ(IsSnake, true);
  EXPECT_EQ(Game.state_, s21::EATING);
}

TEST(StateMove, MoveDown_2) {
  s21::GameSnakeInfo Game;
  Game.SpawningSnake();

  auto head = Game.snake_.begin();
  Game.MovingUp(head);
  Game.PrevUserKey = BUTTON_UP;

  Game.UserKey = BUTTON_DOWN;
  Game.MovingSnake();

  bool IsSnake = true;

  for (int j = 1; j < 4 && IsSnake; j++) {
    if (Game.field_[HEIGHT_FIELD - 4][j] != 1) IsSnake = false;
  }
  if (Game.field_[HEIGHT_FIELD - 5][3] != 1) IsSnake = false;

  EXPECT_EQ(IsSnake, true);
}

TEST(StateMove, MoveDown_3) {
  s21::GameSnakeInfo Game;
  Game.SpawningSnake();

  Game.UserKey = BUTTON_DOWN;
  while (Game.state_ != s21::GAMEOVER) Game.MovingSnake();

  bool IsSnake = true;

  for (int i = HEIGHT_FIELD - 1; i > HEIGHT_FIELD - 4 && IsSnake; i--) {
    if (Game.field_[i][3] != 1) IsSnake = false;
  }

  EXPECT_EQ(IsSnake, true);
  EXPECT_EQ(Game.state_, s21::GAMEOVER);
}

TEST(StateMove, MoveForward_1) {
  s21::GameSnakeInfo Game;
  Game.SpawningSnake();

  Game.UserKey = BUTTON_ENT;
  Game.MovingSnake();

  bool IsSnake = true;

  for (int j = 1; j < 5 && IsSnake; j++) {
    if (Game.field_[HEIGHT_FIELD - 4][j] != 1) IsSnake = false;
  }

  EXPECT_EQ(IsSnake, true);
}

TEST(StateMove, MoveForward_2) {
  s21::GameSnakeInfo Game;
  Game.SpawningSnake();

  Game.PrevUserKey = BUTTON_UP;

  Game.UserKey = BUTTON_ENT;
  Game.MovingSnake();

  bool IsSnake = true;

  for (int j = 1; j < 4 && IsSnake; j++) {
    if (Game.field_[HEIGHT_FIELD - 4][j] != 1) IsSnake = false;
  }
  if (Game.field_[HEIGHT_FIELD - 5][3] != 1) IsSnake = false;

  EXPECT_EQ(IsSnake, true);
}

TEST(StateMove, MoveForward_3) {
  s21::GameSnakeInfo Game;
  Game.SpawningSnake();

  Game.PrevUserKey = BUTTON_DOWN;

  Game.UserKey = BUTTON_ENT;
  Game.MovingSnake();

  bool IsSnake = true;

  for (int j = 1; j < 4 && IsSnake; j++) {
    if (Game.field_[HEIGHT_FIELD - 4][j] != 1) IsSnake = false;
  }
  if (Game.field_[HEIGHT_FIELD - 3][3] != 1) IsSnake = false;

  EXPECT_EQ(IsSnake, true);
}

TEST(StateMove, MoveForward_4) {
  s21::GameSnakeInfo Game;
  Game.SpawningSnake();

  auto head = Game.snake_.begin();
  Game.MovingDown(head);
  Game.PrevUserKey = BUTTON_DOWN;

  Game.PrevUserKey = BUTTON_LEFT;

  Game.UserKey = BUTTON_ENT;
  Game.MovingSnake();

  bool IsSnake = true;

  for (int i = HEIGHT_FIELD - 4; i < HEIGHT_FIELD - 2; i++) {
    for (int j = 2; j < 4 && IsSnake; j++) {
      if (Game.field_[HEIGHT_FIELD - 4][j] != 1) IsSnake = false;
    }
  }

  EXPECT_EQ(IsSnake, true);
}
#include "snake.h"

namespace s21 {

void GameSnakeInfo::GameSnake() {
  std::srand(std::time(NULL));
  InitRecord();

  state_ = SPAWNSNAKE;

  SpawningSnake();
  SpawningApple();
  show_snake(field_, level_, score_, record_);

  while (state_ != GAMEOVER) {
    timeout(speed_);
    UserKey = getch();

    if (state_ == SPAWNAPPLE) SpawningApple();
    if (UserKey == BUTTON_PAUSE)
      PauseGame();
    else if (CheckPressButton() == 1 && UserKey != BUTTON_ENT)
      state_ = SHIFTING;
    if (state_ == MOVING) MovingSnake();
    if (state_ == SHIFTING || UserKey == BUTTON_ENT) ShiftingSnake();
    if (state_ == EATING) EatingApple();

    show_snake(field_, level_, score_, record_);
    if (CheckPressButton() == 0) PrevUserKey = UserKey;
  }

  end_game(record_, score_, score_ == IS_WIN_SNAKE ? WIN_GAME : FAIL_GAME);
  NewRecord();
}

void GameSnakeInfo::PauseGame() {
  FSM_Snake_t PrevState = state_;
  state_ = PAUSE;
  timeout(-1);

  if (pause_menu() == CONTINUE_GAME) {
    state_ = PrevState;
    timeout(speed_);
  } else
    state_ = GAMEOVER;
}

}  // namespace s21

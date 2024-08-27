#include "snake_backend.h"

namespace s21 {

GameSnakeInfo::GameSnakeInfo() : snake_() {
  for (int i = 0; i < HEIGHT_FIELD; i++)
    for (int j = 0; j < WIDHT_FIELD; j++) field_[i][j] = 0;

  state_ = START;
  UserKey = 0;
  PrevUserKey = BUTTON_RIGHT;
  speed_ = 600;
  index_apple_ = std::make_pair(0, 0);
  level_ = 0;
  score_ = 0;
  record_ = 0;
}

void GameSnakeInfo::InitRecord() {
  std::fstream file("brick_game/snake/record_score.txt");
  if (file.is_open()) {
    file >> record_;
    file.close();
  } else {
    throw std::runtime_error("File record_score.txt opening error");
  }
}

// Проврека на нажатие кнопок
int GameSnakeInfo::CheckPressButton() {
  int code = 0;
  if (!BUTTON_DEFINED(UserKey))
    code = 1;
  else if ((PRESS_LEFT(UserKey) && PRESS_RIGHT(PrevUserKey)) ||
           (PRESS_LEFT(PrevUserKey) && PRESS_RIGHT(UserKey)))
    code = 1;
  else if ((PRESS_DOWN(UserKey) && PRESS_UP(PrevUserKey)) ||
           (PRESS_DOWN(PrevUserKey) && PRESS_UP(UserKey)))
    code = 1;

  return code;
}

// Змейка на поле
void GameSnakeInfo::SpawningSnake() {
  for (int j = 0; j < 4; j++) {
    field_[HEIGHT_FIELD - 4][j] = 1;
    std::pair<int, int> index = std::make_pair(HEIGHT_FIELD - 4, j);
    snake_.push_front(index);
  }
  state_ = SPAWNAPPLE;
}

// Генерация яблок на поле
void GameSnakeInfo::SpawningApple() {
  do {
    index_apple_.first = rand() % 20;
    index_apple_.second = rand() % 10;
  } while (field_[index_apple_.first][index_apple_.second] == 1);

  field_[index_apple_.first][index_apple_.second] = 11;
  state_ = MOVING;
}

// Передвижение замейки пользователем
void GameSnakeInfo::MovingSnake() {
  int code = 0;

  iterator Head = snake_.begin();

  switch (UserKey) {
    case BUTTON_RIGHT:
    case 0405:
      code = MovingRight(Head);
      break;
    case BUTTON_LEFT:
    case 0404:
      code = MovingLeft(Head);
      break;
    case BUTTON_UP:
    case 0403:
      code = MovingUp(Head);
      break;
    case BUTTON_DOWN:
    case 0402:
      code = MovingDown(Head);
      break;
    case BUTTON_ENT:
      code = MovingForward(Head);
      break;
  }

  if (code == IS_COLLISION)
    state_ = GAMEOVER;
  else if (code == IS_APPLE)
    state_ = EATING;
}

// Проверка на движение вправо
int GameSnakeInfo::MovingRight(iterator Head) {
  int code = 0;

  if (PRESS_LEFT(PrevUserKey)) {
    code = IS_MOVE_BACK;
  } else if (Head->second + 1 == WIDHT_FIELD ||
             field_[Head->first][Head->second + 1] == 1) {
    code = IS_COLLISION;
  } else if (field_[Head->first][Head->second + 1] == 11) {
    code = IS_APPLE;
  } else {
    std::pair<int, int> NewHead = std::make_pair(Head->first, Head->second + 1);
    Move(NewHead);
  }

  return code;
}

// Проверка на движение влево
int GameSnakeInfo::MovingLeft(iterator Head) {
  int code = 0;

  if (PRESS_RIGHT(PrevUserKey)) {
    code = IS_MOVE_BACK;
  } else if (Head->second - 1 == -1 ||
             field_[Head->first][Head->second - 1] == 1) {
    code = IS_COLLISION;
  } else if (field_[Head->first][Head->second - 1] == 11) {
    code = IS_APPLE;
  } else {
    std::pair<int, int> NewHead = std::make_pair(Head->first, Head->second - 1);
    Move(NewHead);
  }

  return code;
}

// Проверка на движение наверх
int GameSnakeInfo::MovingUp(iterator Head) {
  int code = 0;

  if (PRESS_DOWN(PrevUserKey)) {
    code = IS_MOVE_BACK;
  } else if (Head->first - 1 == -1 ||
             field_[Head->first - 1][Head->second] == 1) {
    code = IS_COLLISION;
  } else if (field_[Head->first - 1][Head->second] == 11) {
    code = IS_APPLE;
  } else {
    std::pair<int, int> NewHead = std::make_pair(Head->first - 1, Head->second);
    Move(NewHead);
  }

  return code;
}

// Проверка на движение вниз
int GameSnakeInfo::MovingDown(iterator Head) {
  int code = 0;

  if (PRESS_UP(PrevUserKey)) {
    code = IS_MOVE_BACK;
  } else if (Head->first + 1 == HEIGHT_FIELD ||
             field_[Head->first + 1][Head->second] == 1) {
    code = IS_COLLISION;
  } else if (field_[Head->first + 1][Head->second] == 11) {
    code = IS_APPLE;
  } else {
    std::pair<int, int> NewHead = std::make_pair(Head->first + 1, Head->second);
    Move(NewHead);
  }

  return code;
}

// Вперед
int GameSnakeInfo::MovingForward(iterator Head) {
  int code = 0;

  if (PRESS_RIGHT(PrevUserKey)) {
    code = MovingRight(Head);
  } else if (PRESS_LEFT(PrevUserKey)) {
    code = MovingLeft(Head);
  } else if (PRESS_UP(PrevUserKey)) {
    code = MovingUp(Head);
  } else if (PRESS_DOWN(PrevUserKey)) {
    code = MovingDown(Head);
  }

  return code;
}

// Сдвиг
void GameSnakeInfo::Move(std::pair<int, int> NewHead) {
  auto Tail = snake_.rbegin();
  field_[Tail->first][Tail->second] = 0;
  field_[NewHead.first][NewHead.second] = 1;
  snake_.pop_back();
  snake_.push_front(NewHead);
}

// Передвижение вперед по таймеру
void GameSnakeInfo::ShiftingSnake() {
  int code = 0;
  iterator Head = snake_.begin();

  code = MovingForward(Head);

  if (code == 0)
    state_ = MOVING;
  else if (code == IS_COLLISION)
    state_ = GAMEOVER;
  else if (code == IS_APPLE)
    state_ = EATING;
}

// Поедание яблок и подсчет очков
void GameSnakeInfo::EatingApple() {
  snake_.push_front(index_apple_);
  field_[index_apple_.first][index_apple_.second] = 1;
  score_ += 1;
  if (record_ < score_) record_ = score_;
  if (level_ < 10) {
    int old_level = level_;
    level_ = score_ / 5;
    if (level_ > old_level) speed_ -= 50;
  }
  state_ = (score_ == IS_WIN_SNAKE) ? GAMEOVER : SPAWNAPPLE;
}

// Записываем рекорд в файл
void GameSnakeInfo::NewRecord() {
  std::fstream file("brick_game/snake/record_score.txt");
  if (file.is_open()) {
    file << record_;
  } else {
    throw std::runtime_error("File record_score.txt opening error");
  }
}

void GameSnakeInfo::InitNewGame() {
  for (int i = 0; i < HEIGHT_FIELD; i++)
    for (int j = 0; j < WIDHT_FIELD; j++) field_[i][j] = 0;

  state_ = START;
  UserKey = 0;
  PrevUserKey = BUTTON_RIGHT;
  speed_ = 600;
  index_apple_ = std::make_pair(0, 0);
  level_ = 0;
  score_ = 0;
  snake_.clear();
}

}  // namespace s21

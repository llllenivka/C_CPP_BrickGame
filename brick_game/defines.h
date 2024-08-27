#ifndef DEFINES_H
#define DEFINES_H

// #define NCURSES_ON settings_ncurses()

// Размер игрового поля
#define WIDHT_FIELD 10
#define HEIGHT_FIELD 20

// Размер рамки с учетом масштаба
#define WIDHT_BORDER (WIDHT_FIELD * 4 + 2)
#define HEIGHT_BORDER (HEIGHT_FIELD * 2 + 2)

// Разметки рамки
#define UP_BORDER 0
#define DOWN_BORDER HEIGHT_BORDER - 1
#define LEFT_BORDER 0
#define RIGHT_BORDER WIDHT_BORDER - 1

// Размер рамки с учетом масштаба
#define WIDHT_INFO_WINDOW (WIDHT_BORDER + 30)
#define HEIGHT_INFO_WINDOW HEIGHT_BORDER

#define LEFT_INFO_WINDOW WIDHT_BORDER
#define RIGHT_INFO_WINDOW WIDHT_INFO_WINDOW - 1

// Кнопки управления
#define BUTTON_ENTER 10
#define BUTTON_EXIT 113
#define BUTTON_LEFT 97
#define BUTTON_RIGHT 100
#define BUTTON_DOWN 115
#define BUTTON_UP 119
#define BUTTON_ENT 32
#define BUTTON_PAUSE 112

// Рандомнайзер
#define RANDOM_FIGURE rand() % 7 + 1
#define RANDOM_COLOR rand() % 5 + 1

// Клетки поля
#define EMPTY_CELL 0
#define IS_FIGURE(num) (num > EMPTY_CELL && num < 6)
#define OCCUPIED_CELL(num) (num > 5)

// Меню
#define START_GAME 0
#define TETRIS 1
#define SNAKE 2
#define QUIT_GAME 3
#define CONTINUE_GAME 4

// Ячейки поля в змейке
#define IS_MOVE_BACK 1
#define IS_COLLISION 2
#define IS_APPLE 11

// Выигрышный счет в змейке
#define IS_WIN_SNAKE 196

#define WIN_GAME 1
#define FAIL_GAME 2

// Проверка кнопок
#define PRESS_RIGHT(key) (key == BUTTON_RIGHT || key == 0405)
#define PRESS_LEFT(key) (key == BUTTON_LEFT || key == 0404)
#define PRESS_UP(key) (key == BUTTON_UP || key == 0403)
#define PRESS_DOWN(key) (key == BUTTON_DOWN || key == 0402)

#define BUTTON_DEFINED(key) \
  (PRESS_DOWN(key) || PRESS_UP(key) || PRESS_RIGHT(key) || PRESS_LEFT(key))

#endif
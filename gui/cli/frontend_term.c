#include "frontend_term.h"

// Включение ncurses
void settings_ncurses() {
  initscr();

  curs_set(0);
  noecho();
  start_color();

  // фигуры
  init_pair(1, COLOR_BLACK, COLOR_GREEN);
  init_pair(2, COLOR_BLACK, COLOR_YELLOW);
  init_pair(3, COLOR_BLACK, COLOR_CYAN);
  init_pair(4, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(5, COLOR_BLACK, COLOR_BLUE);

  // яблоко и надпись
  init_pair(11, COLOR_BLACK, COLOR_RED);

  // рамка и задний фон и надписи
  init_pair(12, COLOR_RED, COLOR_BLACK);
  init_pair(13, COLOR_GREEN, COLOR_BLACK);
  init_pair(14, COLOR_BLACK, COLOR_BLACK);
}

// Заставка старта игры
int show_start_game() {
  int empty_field[HEIGHT_FIELD][WIDHT_FIELD] = {0};
  int code = 0;
  attron(COLOR_PAIR(13));
  print_field(empty_field);
  code = menu();
  return code;
}

// Текст для красоты
void text_tetris() {
  attron(COLOR_PAIR(13));
  int i_index = 7;
  int j_index = 3;
  mvprintw(i_index + 0, j_index, "   _____ ____ _____ ______ ____  ____ ");
  mvprintw(i_index + 1, j_index, "  /_  _// __//_  _// __  //_ _/ / __/ ");
  mvprintw(i_index + 2, j_index, "   / / / /_   / / / /_/ /  //  //__  ");
  mvprintw(i_index + 3, j_index, "  / / / __/  / / / _  _/  //  /__ / ");
  mvprintw(i_index + 4, j_index, " / / / /_   / / / // /  _//_  __// ");
  mvprintw(i_index + 5, j_index, "/_/ /___/  /_/ /_//_/  /___//___/ ");
}

void text_snake() {
  attron(COLOR_PAIR(12));
  int i_index = 7;
  int j_index = 3;
  mvprintw(i_index + 0, j_index, "     ____ __   __ ______ __   ___ ____");
  mvprintw(i_index + 1, j_index, "    / __// /  / // __  // / _/  // __/");
  mvprintw(i_index + 2, j_index, "   //__ / /__/ // /_/ // /_/ __// /_ ");
  mvprintw(i_index + 3, j_index, "  /__ // _    // __  //  _  /_ / __/");
  mvprintw(i_index + 4, j_index, "  __/// //_  // / / // / /_  // /_");
  mvprintw(i_index + 5, j_index, "/___//_/  /_//_/ /_//_/   /_//___/");
}

// Меню для начала игры и выхода из игры
int menu() {
  int game_selection = TETRIS;
  text_tetris();

  attron(COLOR_PAIR(13));

  int index_i = 16;
  int index_j = 14;

  mvprintw(index_i + 0, index_j, "===============");
  mvprintw(index_i + 1, index_j, "    M E N U    ");
  mvprintw(index_i + 2, index_j, "===============");

  int user_key = KEY_UP;

  while (user_key != BUTTON_ENTER) {
    if (game_selection == TETRIS) {
      menu_selection(index_i, index_j, TETRIS);
    } else if (game_selection == SNAKE) {
      menu_selection(index_i, index_j, SNAKE);
    } else {
      menu_selection(index_i, index_j, QUIT_GAME);
    }

    refresh();

    user_key = getch();

    if (PRESS_DOWN(user_key) && game_selection != QUIT_GAME) {
      game_selection++;
    } else if (PRESS_UP(user_key) && game_selection != TETRIS) {
      game_selection--;
    }
  }
  return game_selection;
}

void menu_selection(int index_i, int index_j, int game) {
  if (game == TETRIS)
    text_tetris();
  else if (game == SNAKE)
    text_snake();
  else {
    for (int i = 7; i < 7 + 6; i++) {
      for (int j = 3; j < 3 + 38; j++) {
        attron(COLOR_PAIR(13));
        mvaddch(i, j, ' ');
      }
    }
  }
  attron(COLOR_PAIR(13));
  if (game == TETRIS) attron(COLOR_PAIR(1));
  mvprintw(index_i + 4, index_j - 4, "         TETRIS        ");
  attron(COLOR_PAIR(13));
  if (game == SNAKE) attron(COLOR_PAIR(1));
  mvprintw(index_i + 6, index_j - 4, "         SNAKE         ");
  attron(COLOR_PAIR(13));
  if (game == QUIT_GAME) attron(COLOR_PAIR(1));
  mvprintw(index_i + 8, index_j - 4, "       QUIT GAME       ");
}

// Меню паузы для выхода в главное меню или для продолжения игры
int pause_menu() {
  int code = 0;
  int empty_field[HEIGHT_FIELD][WIDHT_FIELD] = {0};

  print_field(empty_field);

  int index_i = 12;
  int index_j = 8;

  attron(COLOR_PAIR(14));

  mvprintw(index_i + 1, index_j, "  ----   P A U S E  ----  ");

  int user_key = KEY_UP;
  int previous_key = KEY_UP;

  while (user_key != BUTTON_ENTER) {
    attron(COLOR_PAIR(13));
    if (PRESS_UP(user_key)) attron(COLOR_PAIR(1));
    mvprintw(index_i + 4, index_j, "         CONTINUE         ");
    attron(COLOR_PAIR(13));
    if (PRESS_DOWN(user_key)) attron(COLOR_PAIR(1));
    mvprintw(index_i + 6, index_j, "           EXIT           ");

    refresh();

    if (PRESS_UP(user_key) || PRESS_DOWN(user_key)) previous_key = user_key;
    user_key = getch();

    if (PRESS_UP(previous_key))
      code = CONTINUE_GAME;
    else if (PRESS_DOWN(previous_key))
      code = QUIT_GAME;
  }
  return code;
}

// Рисовка рамки с определенными параметрами
void drawing_border(int i_start, int i_end, int j_start, int j_end) {
  mvaddch(i_start, j_start, ACS_ULCORNER);
  mvaddch(i_start, j_end, ACS_URCORNER);
  mvaddch(i_end, j_start, ACS_LLCORNER);
  mvaddch(i_end, j_end, ACS_LRCORNER);

  for (int j = j_start + 1; j < j_end; j++) mvaddch(i_start, j, ACS_HLINE);
  for (int j = j_start + 1; j < j_end; j++) mvaddch(i_end, j, ACS_HLINE);
  for (int i = i_start + 1; i < i_end; i++) mvaddch(i, j_start, ACS_VLINE);
  for (int i = i_start + 1; i < i_end; i++) mvaddch(i, j_end, ACS_VLINE);
}

// Вывод игрового поля в терминал
void print_field(int field[HEIGHT_FIELD][WIDHT_FIELD]) {
  /* Очистка поля */
  for (int i = 0; i < HEIGHT_BORDER; i++) {
    for (int j = 0; j < RIGHT_INFO_WINDOW + 1; j++) {
      mvaddch(i, j, ' ' | COLOR_PAIR(14));
    }
  }

  /* Отрисовка рамки */
  attron(COLOR_PAIR(13));
  drawing_border(0, HEIGHT_BORDER - 1, 0, WIDHT_BORDER - 1);
  drawing_border(0, HEIGHT_BORDER - 1, LEFT_INFO_WINDOW, WIDHT_INFO_WINDOW);

  /* Игровое поле */
  for (int i = 0; i < HEIGHT_FIELD; i++) {
    for (int j = 0; j < WIDHT_FIELD; j++) {
      if (IS_FIGURE(field[i][j]) || field[i][j] == IS_APPLE) {
        attron(COLOR_PAIR(field[i][j]));
        drawing_figures(i * 2, j * 4);
      } else if (OCCUPIED_CELL(field[i][j])) {
        attron(COLOR_PAIR(field[i][j] - 5));
        drawing_figures(i * 2, j * 4);
      }
    }
  }

  refresh();
}

// Вставка фигуры с учетом масштаба
void drawing_figures(int i, int j) {
  for (int n = 1; n <= 2; n++) {
    for (int m = 1; m <= 4; m++) {
      mvaddch(i + n, j + m, ' ');
    }
  }
}

// Текущий уровень
void print_level(int level) {
  attron(COLOR_PAIR(13));
  drawing_border(25, 27, 48, 65);
  mvprintw(26, 53, "LEVEL  %d", level);
}

// Вывод рекордного счета и счета пользователя
void print_score(int score, int record) {
  attron(COLOR_PAIR(14));
  mvprintw(15, 46, "R E C O R D  S C O R E");

  attron(COLOR_PAIR(13));
  drawing_border(16, 18, 48, 65);
  mvprintw(17, 50, "%014u", record);

  attron(COLOR_PAIR(14));
  mvprintw(20, 52, "S C O R E");

  attron(COLOR_PAIR(13));
  drawing_border(21, 23, 48, 65);
  mvprintw(22, 50, "%014u", score);
}

// Подсказка управления
void control_hint() {
  attron(COLOR_PAIR(13));
  int index_i = 32;
  int index_j = 45;

  mvaddch(index_i + 1, index_j + 1, 'A');
  mvaddch(index_i - 2, index_j + 4, 'W');
  mvaddch(index_i + 1, index_j + 4, 'S');
  mvaddch(index_i + 1, index_j + 7, 'D');

  for (int i = 0; i < 2; i++) {
    drawing_border(index_i, index_i + 2, index_j, index_j + 2);
    drawing_border(index_i, index_i + 2, index_j + 3, index_j + 5);
    drawing_border(index_i - 3, index_i - 1, index_j + 3, index_j + 5);
    drawing_border(index_i, index_i + 2, index_j + 6, index_j + 8);

    index_j = 47 + 13;
  }

  attron(COLOR_PAIR(14));

  mvprintw(index_i, index_j - 4, "OR");

  attron(COLOR_PAIR(13));

  mvaddch(index_i + 1, index_j + 1, '<');
  mvaddch(index_i - 2, index_j + 4, '^');
  mvaddch(index_i + 1, index_j + 4, 'v');
  mvaddch(index_i + 1, index_j + 7, '>');

  attron(COLOR_PAIR(13));
  drawing_border(index_i + 3, index_i + 5, 45, index_j + 8);
  mvprintw(index_i + 4, 53, "S P A C E");

  attron(COLOR_PAIR(14));
  mvprintw(39, 49, "Press P for pause");
}

// Вывод игры тетрис в терминал
void show_tetris(Game_state_t game_state) {
  print_field(game_state.field);
  print_next_figure(game_state);
  print_score(game_state.score, game_state.record);
  print_level(game_state.level);
  control_hint();
}

// Показ следующей фигуры
void print_next_figure(Game_state_t game_state) {
  int f_next[4][4] = {0};

  attron(COLOR_PAIR(14));
  mvprintw(2, 47, "N E X T  F I G U R E");

  attron(COLOR_PAIR(13));
  drawing_border(3, 12, 48, 65);

  new_figure(f_next, game_state.figure_template, game_state.next_figure,
             game_state.next_color);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (IS_FIGURE(f_next[i][j])) {
        attron(COLOR_PAIR(game_state.next_color));
        drawing_figures(i * 2 + 3, j * 4 + 48);
      }
    }
  }
}

// Доп параметры для змейки
void show_snake(int field[HEIGHT_FIELD][WIDHT_FIELD], int level, int score,
                int record) {
  print_field(field);
  print_level(level);
  print_score(score, record);
  control_hint();
  refresh();
}

void end_game(int record, int score, int game_state) {
  int empty_field[HEIGHT_FIELD][WIDHT_FIELD] = {0};
  print_field(empty_field);

  if (game_state == FAIL_GAME)
    text_game_over();
  else
    text_you_win();

  int index_i = 32;
  int index_j = 10;

  attron(COLOR_PAIR(14));

  drawing_border(index_i, index_i + 2, index_j - 1, index_j + 21);
  mvprintw(index_i + 1, index_j + 1, "RECORD : %010d", record);

  attron(COLOR_PAIR(14));

  drawing_border(index_i + 3, index_i + 5, index_j - 1, index_j + 21);
  mvprintw(index_i + 4, index_j + 1, "SCORE  : %010d", score);

  attron(COLOR_PAIR(14));
  mvprintw(39, index_j - 5, "Press ENTER to exit to the menu");

  refresh();

  while (getch() != BUTTON_ENTER) {
  };
}

void text_game_over() {
  attron(COLOR_PAIR(12));
  int i_index = 4;
  int j_index = 3;

  mvprintw(i_index + 0, j_index, "     _____ ______ _     _ ____ ");
  mvprintw(i_index + 1, j_index, "    /____// __  ///_  _/// __/");
  mvprintw(i_index + 2, j_index, "   //___ / /_/ //  /_/ // /_ ");
  mvprintw(i_index + 3, j_index, "  ///_ // __  // ___  // __/");
  mvprintw(i_index + 4, j_index, " //__/// / / // /  / // /_ ");
  mvprintw(i_index + 5, j_index, "/____//_/ /_//_/  /_//___/");

  i_index += 6;
  j_index += 9;

  mvprintw(i_index + 0, j_index, "     ____ __  __ ____ ______ ");
  mvprintw(i_index + 1, j_index, "    /__ // / / // __// __  /");
  mvprintw(i_index + 2, j_index, "   // /// / / // /_ / /_/ /");
  mvprintw(i_index + 3, j_index, "  // /// /_/ // __// _  _/");
  mvprintw(i_index + 4, j_index, " //_///_  __// /_ / // /");
  mvprintw(i_index + 5, j_index, "/___/  /_/  /___//_//_/");
}

void text_you_win() {
  attron(COLOR_PAIR(13));
  int i_index = 5;
  int j_index = 10;

  mvprintw(i_index + 0, j_index, "    __  __ ____ __  __");
  mvprintw(i_index + 1, j_index, "   / / / //__ // / / /");
  mvprintw(i_index + 2, j_index, "  / /_/ /// /// / / /");
  mvprintw(i_index + 3, j_index, " /___  /// /// / / /");
  mvprintw(i_index + 4, j_index, " ___/ ///_/// /_/ /");
  mvprintw(i_index + 5, j_index, "/____//___//_____/");

  i_index += 6;
  j_index -= 5;

  mvprintw(i_index + 0, j_index, "     __  __  __ ____  __   __");
  mvprintw(i_index + 1, j_index, "    / / / / / //_ _/ / /  / /");
  mvprintw(i_index + 2, j_index, "   / / / / / /  //  / /__/ /");
  mvprintw(i_index + 3, j_index, "  / /_/ /_/ /  //  / _    /");
  mvprintw(i_index + 4, j_index, " /  _//_  _/ _//_ / //_  /");
  mvprintw(i_index + 5, j_index, " /_/   /_/  /___//_/  /_/");
}

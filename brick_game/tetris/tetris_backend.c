#include "tetris_backend.h"

void tetris_start(Game_state_t *game_state) {
  init_record(game_state);
  create_templates(&(game_state->figure_template));
  game_state->speed = 600;
  game_state->next_figure = RANDOM_FIGURE;
  game_state->next_color = RANDOM_COLOR;
  game_state->state_machine = SPAWN;
}

// Инициализируем рекорд очков за все время
void init_record(Game_state_t *game_state) {
  FILE *file = fopen("brick_game/tetris/record_scope.txt", "r");
  if (file == NULL) {
    file = fopen("brick_game/tetris/record_scope.txt", "w");
  }
  fscanf(file, "%u", &(game_state->record));
  fclose(file);
}

void init_game_state(Game_state_t *game_state) {
  for (int i = 0; i < HEIGHT_FIELD; i++) {
    for (int j = 0; j < WIDHT_FIELD; j++) {
      game_state->field[i][j] = 0;
    }
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      game_state->figure[i][j] = 0;
      game_state->figure_template.f_square[i][j] = 0;
      game_state->figure_template.f_stick[i][j] = 0;
      game_state->figure_template.f_zigzag_l[i][j] = 0;
      game_state->figure_template.f_zigzag_r[i][j] = 0;
      game_state->figure_template.f_corner_l[i][j] = 0;
      game_state->figure_template.f_corner_r[i][j] = 0;
      game_state->figure_template.f_tank[i][j] = 0;
    }
  }
  game_state->index_figure_i = 0;
  game_state->index_figure_j = 0;
  game_state->index_born = 0;
  game_state->next_figure = 0;

  game_state->record = 0;
  game_state->score = 0;
  game_state->level = 0;
  game_state->speed = 0;

  game_state->current_color = 0;
  game_state->next_color = 0;

  game_state->state_machine = START;
}

// Создает шаблоны фигур
void create_templates(Figures_t *figures_templates) {
  /* квадрат */
  figures_templates->f_square[1][1] = 1;
  figures_templates->f_square[1][2] = 1;
  figures_templates->f_square[2][1] = 1;
  figures_templates->f_square[2][2] = 1;
  /* палка */
  figures_templates->f_stick[2][0] = 1;
  figures_templates->f_stick[2][1] = 1;
  figures_templates->f_stick[2][2] = 1;
  figures_templates->f_stick[2][3] = 1;
  /* правый зигзаг */
  figures_templates->f_zigzag_r[1][2] = 1;
  figures_templates->f_zigzag_r[1][3] = 1;
  figures_templates->f_zigzag_r[2][1] = 1;
  figures_templates->f_zigzag_r[2][2] = 1;
  /* не правый зигзаг */
  figures_templates->f_zigzag_l[1][0] = 1;
  figures_templates->f_zigzag_l[1][1] = 1;
  figures_templates->f_zigzag_l[2][1] = 1;
  figures_templates->f_zigzag_l[2][2] = 1;
  /* правый угол */
  figures_templates->f_corner_r[1][3] = 1;
  figures_templates->f_corner_r[2][1] = 1;
  figures_templates->f_corner_r[2][2] = 1;
  figures_templates->f_corner_r[2][3] = 1;
  /* левый угол */
  figures_templates->f_corner_l[1][0] = 1;
  figures_templates->f_corner_l[2][0] = 1;
  figures_templates->f_corner_l[2][1] = 1;
  figures_templates->f_corner_l[2][2] = 1;
  /* танк */
  figures_templates->f_tank[1][2] = 1;
  figures_templates->f_tank[2][1] = 1;
  figures_templates->f_tank[2][2] = 1;
  figures_templates->f_tank[2][3] = 1;
}

// Создаем новую фигуру
void spawning(Game_state_t *game_state, int *current_figure) {
  *current_figure = game_state->next_figure;
  game_state->next_figure = RANDOM_FIGURE;
  game_state->current_color = game_state->next_color;
  game_state->next_color = RANDOM_COLOR;

  game_state->index_figure_i = -1;
  game_state->index_figure_j = 3;
  game_state->index_born = 3;

  new_figure(game_state->figure, game_state->figure_template, *current_figure,
             game_state->current_color);

  game_state->state_machine = MOVING;
}

// Генерация фигуры
void new_figure(int result[4][4], Figures_t figures, int current_figure,
                int color) {
  switch (current_figure) {
    case 1:
      copy_figure(result, figures.f_square, color);
      break;
    case 2:
      copy_figure(result, figures.f_stick, color);
      break;
    case 3:
      copy_figure(result, figures.f_zigzag_r, color);
      break;
    case 4:
      copy_figure(result, figures.f_zigzag_l, color);
      break;
    case 5:
      copy_figure(result, figures.f_corner_r, color);
      break;
    case 6:
      copy_figure(result, figures.f_corner_l, color);
      break;
    case 7:
      copy_figure(result, figures.f_tank, color);
      break;
  }
}

void copy_figure(int result[4][4], int figures[4][4], int color) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (IS_FIGURE(figures[i][j]))
        result[i][j] = color;
      else
        result[i][j] = figures[i][j];
    }
  }
}

// Движение фигуры пользователем
void moving(Game_state_t *game_state, int user_key) {
  press_button(game_state, user_key);
  game_state->state_machine = SHIFTING;
}

// Нажатие кнопок
int press_button(Game_state_t *game_state, int button) {
  int code = 0;
  switch (button) {
    case BUTTON_LEFT:
    case 0404:
      code = left_move(game_state);
      break;

    case BUTTON_RIGHT:
    case 0405:
      code = right_move(game_state);
      break;

    case BUTTON_DOWN:
    case 0402:
      code = down_move(game_state);
      break;

    case BUTTON_UP:
    case 0403:
      break;

    case BUTTON_ENT:
      turn(game_state);
      break;
  }
  return code;
}

//  Движение фигуры вниз
int down_move(Game_state_t *game_state) {
  int code = 0;
  for (int i = HEIGHT_FIELD - 1; i >= 0 && code == 0; i--)
    for (int j = 0; j < WIDHT_FIELD && code == 0; j++)
      if (IS_FIGURE(game_state->field[i][j]) &&
          ((i + 1) == HEIGHT_FIELD ||
           OCCUPIED_CELL(game_state->field[i + 1][j])))
        code = 1;

  if (code != 1) {
    for (int i = HEIGHT_FIELD - 1; i >= 0; i--) {
      for (int j = 0; j < WIDHT_FIELD; j++) {
        if (IS_FIGURE(game_state->field[i][j])) {
          game_state->field[i + 1][j] = game_state->field[i][j];
          game_state->field[i][j] = EMPTY_CELL;
        }
      }
    }
  }
  if (code != 1) game_state->index_figure_i++;

  if (game_state->index_born >= 0) code = spawn_figure(game_state, code);

  return code;
}

// Выход новой фигуры из верхней границы
int spawn_figure(Game_state_t *game_state, int code) {
  if (code == 1)
    code = 2;
  else {
    int n = 0;
    for (int j = game_state->index_figure_j; j < game_state->index_figure_j + 4;
         j++) {
      game_state->field[0][j] = game_state->figure[game_state->index_born][n];
      n++;
    }
    game_state->index_born--;
  }
  return code;
}

//  Движение фигуры влево
int left_move(Game_state_t *game_state) {
  int code = 0;
  for (int j = 0; j < WIDHT_FIELD && code == 0; j++)
    for (int i = 0; i < HEIGHT_FIELD && code == 0; i++)
      if (IS_FIGURE(game_state->field[i][j]) &&
          (j == 0 || OCCUPIED_CELL(game_state->field[i][j - 1])))
        code = 1;

  if (code != 1) {
    for (int j = 0; j < WIDHT_FIELD && code == 0; j++) {
      for (int i = 0; i < HEIGHT_FIELD; i++) {
        if (IS_FIGURE(game_state->field[i][j])) {
          game_state->field[i][j - 1] = game_state->field[i][j];
          game_state->field[i][j] = EMPTY_CELL;
        }
      }
    }
  }

  if (code != 1 && game_state->index_figure_j != 0)
    game_state->index_figure_j--;

  return code;
}

//  Движение фигуры вправо
int right_move(Game_state_t *game_state) {
  int code = 0;
  for (int j = WIDHT_FIELD - 1; j >= 0 && code == 0; j--)
    for (int i = 0; i < HEIGHT_FIELD && code == 0; i++)
      if (IS_FIGURE(game_state->field[i][j]) &&
          (j == WIDHT_FIELD - 1 || OCCUPIED_CELL(game_state->field[i][j + 1])))
        code = 1;

  if (code != 1) {
    for (int j = WIDHT_FIELD - 1; j >= 0 && code == 0; j--) {
      for (int i = 0; i < HEIGHT_FIELD; i++) {
        if (IS_FIGURE(game_state->field[i][j])) {
          game_state->field[i][j + 1] = game_state->field[i][j];
          game_state->field[i][j] = EMPTY_CELL;
        }
      }
    }
  }

  if (code != 1 && game_state->index_figure_j < WIDHT_FIELD)
    game_state->index_figure_j++;

  return code;
}

// Вращение
int turn(Game_state_t *game_state) {
  int code = 0;
  rolling_figure(game_state);
  int n = 0;
  for (int i = game_state->index_figure_i - 3;
       i <= game_state->index_figure_i && code == 0; i++) {
    int m = 0;
    for (int j = game_state->index_figure_j;
         j <= game_state->index_figure_j + 3 && code == 0; j++) {
      if (IS_FIGURE(game_state->figure[n][m]) &&
          (OCCUPIED_CELL(game_state->field[i][j]) || i >= HEIGHT_FIELD ||
           j >= WIDHT_FIELD))
        code = 1;
      m++;
    }
    n++;
  }

  if (code == 0) {
    insert_figure(game_state);
  } else {
    for (int count = 1; count <= 3; count++) rolling_figure(game_state);
  }

  return code;
}

// Вставка фигуры в поле
void insert_figure(Game_state_t *game_state) {
  int n = 0;
  for (int i = game_state->index_figure_i - 3; i <= game_state->index_figure_i;
       i++) {
    if (i < 0) {
      n++;
      continue;
    }
    int m = 0;
    for (int j = game_state->index_figure_j;
         j <= game_state->index_figure_j + 3; j++) {
      if (IS_FIGURE(game_state->figure[n][m]))
        game_state->field[i][j] = game_state->figure[n][m];
      else if (IS_FIGURE(game_state->field[i][j]))
        game_state->field[i][j] = EMPTY_CELL;
      m++;
    }
    n++;
  }
}

// Вращение фигуры по часовой стрелке
int rolling_figure(Game_state_t *game_state) {
  int buff[4][4] = {0};
  int n = 0;
  for (int j = 3; j >= 0; j--) {
    int m = 0;
    for (int i = 0; i < 4; i++) {
      buff[i][j] = game_state->figure[n][m];
      m++;
    }
    n++;
  }
  copy_figure(game_state->figure, buff, game_state->current_color);
  return 0;
}

// Спуск вниз
void shifting(Game_state_t *game_state) {
  int result = down_move(game_state);
  if (result == 1) {
    figure_fell(game_state);
    game_state->state_machine = ATTACHING;
  } else if (result == 2) {
    game_state->state_machine = GAMEOVER;
  } else
    game_state->state_machine = MOVING;
}

// Фигура остановилась
void figure_fell(Game_state_t *game_state) {
  int count_square = 0;

  for (int i = 0; i < HEIGHT_FIELD && count_square != 4; i++) {
    for (int j = 0; j < WIDHT_FIELD && count_square != 4; j++) {
      if (IS_FIGURE(game_state->field[i][j])) {
        game_state->field[i][j] += 5;
        count_square++;
      }
    }
  }
}

// Проверка на цельную линию, если линия нашлась, удаляем
void attaching(Game_state_t *game_state) {
  int count_combo = 0;
  for (int i = 0; i < HEIGHT_FIELD && count_combo < 4; i++) {
    int is_combo = 1;

    for (int j = 0; j < WIDHT_FIELD && is_combo; j++) {
      if (game_state->field[i][j] < 6 || game_state->field[i][j] > 10)
        is_combo = 0;
    }

    if (is_combo) {
      delete_line(game_state, i);
      count_combo++;
    }
  }

  if (count_combo > 0) {
    scoring(game_state, count_combo);
    new_level(game_state);
  }

  game_state->state_machine = SPAWN;
}

void scoring(Game_state_t *game_state, int count_combo) {
  switch (count_combo) {
    case 1:
      game_state->score += 100;
      break;
    case 2:
      game_state->score += 300;
      break;
    case 3:
      game_state->score += 700;
      break;
    case 4:
      game_state->score += 1500;
      break;
  }
  if (game_state->record < game_state->score)
    game_state->record = game_state->score;
}

//  Удаление цельной линии и сдвиг вниз
void delete_line(Game_state_t *game_state, int line_index) {
  for (int i = line_index; i != 0; i--) {
    for (int j = 0; j < WIDHT_FIELD; j++) {
      if (i == 0)
        game_state->field[i][j] = 0;
      else
        game_state->field[i][j] = game_state->field[i - 1][j];
    }
  }
}

// UP LEVEL
void new_level(Game_state_t *game_state) {
  if (game_state->level < 10) {
    short int old_level = game_state->level;
    game_state->level = game_state->score / 600;

    while (old_level != game_state->level) {
      game_state->speed -= 50;
      old_level++;
    }
  }
}

// Записываем новый рекорд за все время
void new_record(Game_state_t game_state) {
  FILE *file = fopen("brick_game/tetris/record_scope.txt", "w");
  fprintf(file, "%u", game_state.record);
  fclose(file);
}

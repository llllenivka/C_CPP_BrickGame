#include "tetris.h"

// Игровой процесс
void game_loop() {
  srand(time(NULL));
  Game_state_t game_state;
  init_game_state(&game_state);

  if (game_state.state_machine == START) tetris_start(&game_state);

  int current_figure = 0;
  spawning(&game_state, &current_figure);
  show_tetris(game_state);

  while (game_state.state_machine != GAMEOVER) {
    timeout(game_state.speed);
    int user_key = getch();
    if (user_key == BUTTON_PAUSE && game_state.state_machine != GAMEOVER)
      pause_game(&game_state);

    if (game_state.state_machine == SPAWN)
      spawning(&game_state, &current_figure);
    else if (game_state.state_machine == MOVING)
      moving(&game_state, user_key);

    if (game_state.state_machine == SHIFTING) shifting(&game_state);
    if (game_state.state_machine == ATTACHING) attaching(&game_state);

    show_tetris(game_state);
  }
  timeout(-1);
  end_game(game_state.record, game_state.score, FAIL_GAME);

  new_record(game_state);
}

// Пауза игры
void pause_game(Game_state_t *game_state) {
  Tetris_state current_game_state = game_state->state_machine;
  game_state->state_machine = PAUSE;
  timeout(-1);

  if (pause_menu() == CONTINUE_GAME) {
    game_state->state_machine = current_game_state;
    timeout(game_state->speed);
  } else {
    game_state->state_machine = GAMEOVER;
  }
}
#ifndef BRICKGAMEFRONT_H
#define BRICKGAMEFRONT_H

#include <tetris_square.h>

#include <QFile>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QTextStream>
#include <QVBoxLayout>
#include <iostream>

#include "../../../brick_game/snake/snake_backend.h"

extern "C" {
#include "../../../brick_game/tetris/tetris_backend.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class BrickGameFront;
}
QT_END_NAMESPACE

class BrickGameFront : public QMainWindow {
  Q_OBJECT

 public:
  BrickGameFront(QWidget *parent = nullptr);
  ~BrickGameFront();

 private slots:
  void on_ButtonQuit_clicked();
  void on_ButtonTetrisGame_clicked();
  void on_ButtonSnakeGame_clicked();

 private:
  Ui::BrickGameFront *ui;
  Game_state_t game_state;
  s21::GameSnakeInfo GameState;

  int UserKey = 0;
  int current_figure = 0;
  int Timer = 0;

  QWidget *WidgetField;
  QWidget *WidgetInfoGame;
  QTimer *timer;
  QLabel *ScoreLabel;
  QLabel *LevelLabel;
  QLabel *RecordLabel;
  std::pair<QGraphicsScene *, QGraphicsView *> WindowGame;
  QGraphicsView *ViewNextFigure;
  QGraphicsScene *SceneNextFigure;

  QWidget *PauseWidget;
  QPushButton *ButtonContinue;
  QPushButton *ButtonExit;

  void TETRISGameStart();
  void SNAKEGameStart();
  void InitWidgetsField();
  void InitInfoGame(int score, int level, int record);
  void ShowInfoGame(int score, int level, int record);
  void InitScene();

  void TETRISLoopGame();
  void SNAKEGameLoop();
  void GameOver();
  void PauseMenu();
  void ContinueGame();
  void ExitGame();

  int PressButtonQT(QKeyEvent *user_key);
  void ShowChange(int field[HEIGHT_FIELD][WIDHT_FIELD]);
  void ShowNextFigure();
  void SceneUpdate(QGraphicsScene *Scene);

  void keyPressEvent(QKeyEvent *key) override;
  bool CurrentPressedButtons();
};

class TetrisCotroller {
  friend BrickGameFront;

 private:
  Game_state_t game_state;

  int UserKey = 0;
  int current_figure = 0;
  int Timer = 0;
};

#endif  // BRICKGAMEFRONT_H

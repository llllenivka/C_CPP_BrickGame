#include "brick_game_front.h"

#include <QDebug>
#include <QTimer>

#include "ui_brick_game_front.h"

#define DESKTOP_FIELD_RIGHT 20
#define DESKTOP_FIELD_TOP 26
#define DESKTOP_FIELD_HEIGHT 700
#define DESKTOP_FIELD_WIGTH 350
#define TIMER_DELAY 150

BrickGameFront::BrickGameFront(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::BrickGameFront) {
  ui->setupUi(this);
  setFocusPolicy(Qt::StrongFocus);
  timer = new QTimer(this);
}

BrickGameFront::~BrickGameFront() { delete ui; }

void BrickGameFront::on_ButtonQuit_clicked() {
  qApp->exit();
  delete timer;
}

void BrickGameFront::on_ButtonTetrisGame_clicked() {
  init_game_state(&game_state);

  QFile file(":/record_score_tetris.txt");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    throw std::runtime_error("File record_score.txt opening error");
  } else {
    QTextStream TextFile(&file);
    QString line = TextFile.readLine();
    game_state.record = line.toInt();
    file.close();
  }

  InitWidgetsField();
  InitInfoGame(game_state.score, game_state.level, game_state.record);
  InitScene();

  WidgetField->show();
  WidgetInfoGame->show();

  TETRISGameStart();
}

// Cоздание двух виджетов, где происходит основная игра
void BrickGameFront::InitWidgetsField() {
  WidgetField = new QWidget(this);
  WidgetField->setGeometry(ui->widgetMenu->rect());
  WidgetField->move(ui->widgetMenu->pos());
  WidgetField->setStyleSheet(
      "QWidget { background-color: rgb(251, 249, 250); border-radius: 40px}");

  WidgetInfoGame = new QWidget(WidgetField);
  WidgetInfoGame->setGeometry(DESKTOP_FIELD_RIGHT + DESKTOP_FIELD_WIGTH + 5,
                              DESKTOP_FIELD_TOP + 2, 200,
                              DESKTOP_FIELD_HEIGHT - 3);
  WidgetInfoGame->setStyleSheet(
      "QWidget { background-color:rgb(255, 213, 214); border-radius: 0px; }");
}

// Создание окошек информации об игре (уровень, очки и рекорд)
void BrickGameFront::InitInfoGame(int score, int level, int record) {
  int coordinate_x = 10;
  int coordinate_y = 180;
  int width = 180;
  int height = 40;

  QString StyleForLabel(
      "QLabel { background-color: white; color: rgb(145, 47, 85); border: 3px "
      "solid rgb(145, 47, 85);}");
  QFont FontForLabel("Chalkduster", 11);

  RecordLabel = new QLabel(WidgetInfoGame);
  RecordLabel->move(coordinate_x, coordinate_y);
  RecordLabel->setMinimumSize(width, height);
  RecordLabel->setStyleSheet(StyleForLabel);
  RecordLabel->setFont(FontForLabel);

  ScoreLabel = new QLabel(WidgetInfoGame);
  ScoreLabel->move(coordinate_x, coordinate_y + 50);
  ScoreLabel->setMinimumSize(width, height);
  ScoreLabel->setStyleSheet(StyleForLabel);
  ScoreLabel->setFont(FontForLabel);

  LevelLabel = new QLabel(WidgetInfoGame);
  LevelLabel->move(coordinate_x, coordinate_y + 50 * 2);
  LevelLabel->setMinimumSize(width, height);
  LevelLabel->setStyleSheet(StyleForLabel);
  LevelLabel->setFont(FontForLabel);

  ShowInfoGame(score, level, record);
}

// Информация об игре
void BrickGameFront::ShowInfoGame(int score, int level, int record) {
  ScoreLabel->setText(QString("S C O R E :\n%1").arg(score));
  LevelLabel->setText(QString("L E V E L :\n%1").arg(level));
  RecordLabel->setText(QString("R E C O R D  S C O R E :\n%1").arg(record));
}

// Сцена
void BrickGameFront::InitScene() {
  QGraphicsScene* SceneField = new QGraphicsScene();

  QGraphicsView* ViewField = new QGraphicsView(WidgetField);
  ViewField->setStyleSheet("QGraphicsView { border: 1 px solid red;}");
  ViewField->setGeometry(DESKTOP_FIELD_RIGHT, DESKTOP_FIELD_TOP,
                         DESKTOP_FIELD_WIGTH, DESKTOP_FIELD_HEIGHT);
  ViewField->setScene(SceneField);

  QGraphicsPixmapItem* PictureField = new QGraphicsPixmapItem();
  QPixmap picture(":/img/image/field.png");
  PictureField->setPixmap(picture);
  PictureField->setScale(SCALE_PXMAP);
  SceneField->addItem(PictureField);

  WindowGame = std::make_pair(SceneField, ViewField);
}

// Начало игры
void BrickGameFront::TETRISGameStart() {
  srand(time(NULL));

  ViewNextFigure = new QGraphicsView(WidgetInfoGame);
  ViewNextFigure->setStyleSheet(
      "QGraphicsView { background-color: white; border: 3px solid rgb(145, 47, "
      "85);}");
  ViewNextFigure->setGeometry(23, 15, 150, 150);
  SceneNextFigure = new QGraphicsScene();
  ViewNextFigure->setScene(SceneNextFigure);
  ViewNextFigure->show();

  create_templates(&(game_state.figure_template));

  game_state.speed = 600;
  game_state.next_figure = RANDOM_FIGURE;
  game_state.next_color = RANDOM_COLOR;
  game_state.state_machine = SPAWN;
  UserKey = 0;

  connect(timer, &QTimer::timeout, this, &BrickGameFront::TETRISLoopGame);
  timer->start(game_state.speed);
}

// Цикл игры
void BrickGameFront::TETRISLoopGame() {
  timer->setInterval(game_state.speed);
  if (game_state.state_machine == SPAWN) spawning(&game_state, &current_figure);
  if (game_state.state_machine == MOVING) moving(&game_state, UserKey);
  if (game_state.state_machine == SHIFTING)
    shifting(&game_state);
  else if (game_state.state_machine == ATTACHING)
    attaching(&game_state);
  if (game_state.state_machine == GAMEOVER) {
    QFile file(":/record_score_tetris.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      throw std::runtime_error("File record_score.txt opening error");
    } else {
      QTextStream out(&file);
      out << game_state.record;
      out.flush();
      file.close();
    }
    GameOver();
  } else {
    ShowInfoGame(game_state.score, game_state.level, game_state.record);
    ShowChange(game_state.field);
    ShowNextFigure();
  }

  UserKey = 0;
}

void BrickGameFront::GameOver() {
  disconnect(timer, nullptr, this, nullptr);

  if (ButtonContinue) {
    delete ButtonContinue;
    ButtonContinue = nullptr;
  }

  if (PauseWidget) {
    delete PauseWidget;
    PauseWidget = nullptr;
  }

  if (WindowGame.first) {
    WindowGame.first->clear();
    delete WindowGame.first;
    WindowGame.first = nullptr;
  }

  if (WindowGame.second) {
    delete WindowGame.second;
    WindowGame.second = nullptr;
  }

  if (SceneNextFigure) {
    SceneNextFigure->clear();
    delete SceneNextFigure;
    SceneNextFigure = nullptr;
  }

  if (ViewNextFigure) {
    delete ViewNextFigure;
    ViewNextFigure = nullptr;
  }

  if (WidgetInfoGame) {
    delete WidgetInfoGame;
    WidgetInfoGame = nullptr;
  }

  if (WidgetField) {
    delete WidgetField;
    WidgetField = nullptr;
  }

  GameState.snake_.clear();
}

void BrickGameFront::ShowNextFigure() {
  int NextFigure[4][4] = {
      {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  SceneNextFigure->clear();
  SquareTetris* Squares = new SquareTetris();
  Squares->setScale(SCALE_PXMAP);

  new_figure(NextFigure, game_state.figure_template, game_state.next_figure,
             game_state.next_color);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (NextFigure[i][j] != 0) {
        Squares->AddSquareToWidget(j * SIZE_SQUARE, i * SIZE_SQUARE,
                                   NextFigure[i][j]);
      }
    }
  }

  SceneNextFigure->addItem(Squares);
  ViewNextFigure->show();
}

// Вывод поля на экран
void BrickGameFront::ShowChange(int field[HEIGHT_FIELD][WIDHT_FIELD]) {
  SceneUpdate(WindowGame.first);

  SquareTetris* Squares = new SquareTetris();
  Squares->setScale(SCALE_PXMAP);

  for (int i = 0; i < HEIGHT_FIELD; i++) {
    for (int j = 0; j < WIDHT_FIELD; j++) {
      if (field[i][j] != 0) {
        Squares->AddSquareToWidget(j * SIZE_SQUARE, i * SIZE_SQUARE,
                                   field[i][j]);
      }
    }
  }

  WindowGame.first->addItem(Squares);
  WindowGame.second->show();
}

// Удаление всех items со сцены кроме самого поля
void BrickGameFront::SceneUpdate(QGraphicsScene* Scene) {
  if (Scene->items().size() > 1) {
    QList<QGraphicsItem*> allItems = Scene->items();
    QGraphicsItem* firstItem = allItems.last();
    for (QGraphicsItem* item : allItems) {
      if (item != firstItem) {
        Scene->removeItem(item);
        delete item;
      }
    }
  }
}

// Нажатие клавиш
void BrickGameFront::keyPressEvent(QKeyEvent* key) {
  switch (key->key()) {
    case Qt::Key_Up:
      UserKey = BUTTON_UP;
      break;
    case Qt::Key_Down:
      UserKey = BUTTON_DOWN;
      break;
    case Qt::Key_Left:
      UserKey = BUTTON_LEFT;
      break;
    case Qt::Key_Right:
      UserKey = BUTTON_RIGHT;
      break;
    case Qt::Key_Space:
      UserKey = BUTTON_ENT;
      break;
    case Qt::Key_Escape:
      PauseMenu();
      timer->stop();
      break;
  }
}

void BrickGameFront::PauseMenu() {
  QFont font("Heiti SC", 20);
  PauseWidget = new QWidget(WidgetField);
  PauseWidget->setStyleSheet("QWidget{ background: rgb(251, 249, 250);}");
  PauseWidget->setGeometry(0, 0, 591, 751);
  PauseWidget->show();

  ButtonContinue = new QPushButton(PauseWidget);
  ButtonContinue->setText("C o n t i n u e");
  ButtonContinue->setFont(font);
  ButtonContinue->setStyleSheet(
      "QPushButton { background: rgb(251, 249, 250); color:rgb(145, 47, 85); "
      "border-radius: 10px;} QPushButton:hover{ background:rgb(145, 47, 85);  "
      "color:rgb(251, 249, 250);}");
  ButtonContinue->setGeometry(180, 300, 220, 40);
  ButtonContinue->show();

  ButtonExit = new QPushButton(PauseWidget);
  ButtonExit->setText("E x i t");
  ButtonExit->setFont(font);
  ButtonExit->setStyleSheet(
      "QPushButton { background: rgb(251, 249, 250); color:rgb(145, 47, 85); "
      "border-radius: 10px;} QPushButton:hover{ background:rgb(145, 47, 85);  "
      "color:rgb(251, 249, 250);}");
  ButtonExit->setGeometry(180, 350, 220, 40);
  ButtonExit->show();

  connect(ButtonContinue, &QPushButton::clicked, this,
          &BrickGameFront::ContinueGame);
  connect(ButtonExit, &QPushButton::clicked, this, &BrickGameFront::ExitGame);
}

void BrickGameFront::ContinueGame() {
  delete ButtonContinue;
  ButtonContinue = nullptr;
  delete ButtonExit;
  ButtonExit = nullptr;
  delete PauseWidget;
  PauseWidget = nullptr;
  timer->start();
}

void BrickGameFront::ExitGame() {
  delete ButtonContinue;
  ButtonContinue = nullptr;
  delete ButtonExit;
  ButtonExit = nullptr;
  delete PauseWidget;
  PauseWidget = nullptr;
  GameOver();
}

void BrickGameFront::on_ButtonSnakeGame_clicked() {
  QFile file(":/record_score_snake.txt");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    throw std::runtime_error("File record_score.txt opening error");
  } else {
    QTextStream TextFile(&file);
    QString line = TextFile.readLine();
    game_state.record = line.toInt();
    file.close();
  }

  InitWidgetsField();
  InitInfoGame(GameState.score_, GameState.level_, GameState.record_);
  InitScene();

  WidgetField->show();
  WidgetInfoGame->show();
  SNAKEGameStart();
}

void BrickGameFront::SNAKEGameStart() {
  srand(time(NULL));

  GameState.InitNewGame();

  GameState.SpawningSnake();
  GameState.SpawningApple();

  UserKey = BUTTON_RIGHT;

  ShowChange(GameState.field_);

  connect(timer, &QTimer::timeout, this, &BrickGameFront::SNAKEGameLoop);
  timer->start(GameState.speed_);
}

void BrickGameFront::SNAKEGameLoop() {
  timer->setInterval(GameState.speed_);
  if (UserKey != 0 && CurrentPressedButtons() == true)
    GameState.UserKey = UserKey;

  if (GameState.state_ == s21::SPAWNAPPLE) GameState.SpawningApple();
  if (GameState.state_ == s21::MOVING) GameState.MovingSnake();
  if (GameState.state_ == s21::SHIFTING || GameState.UserKey == BUTTON_ENT)
    GameState.ShiftingSnake();
  if (GameState.state_ == s21::EATING) GameState.EatingApple();
  if (GameState.state_ == s21::GAMEOVER) {
    QFile file(":/record_score_snake.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      throw std::runtime_error("File record_score.txt opening error");
    } else {
      QTextStream out(&file);
      out << GameState.record_;
      out.flush();
      file.close();
    }
    GameState.InitNewGame();
    GameOver();
  } else {
    ShowInfoGame(GameState.score_, GameState.level_, GameState.record_);
    ShowChange(GameState.field_);
  }

  if (GameState.CheckPressButton() == 0)
    GameState.PrevUserKey = GameState.UserKey;
}

// QFile file(filename);
// if (file.open(QIODevice::WriteOnly))
//{
//     QDataStream out(&file);
//     out << number;
//     file.close();
// }

bool BrickGameFront::CurrentPressedButtons() {
  bool code = true;
  if (UserKey == BUTTON_DOWN && GameState.UserKey == BUTTON_UP)
    code = false;
  else if (UserKey == BUTTON_UP && GameState.UserKey == BUTTON_DOWN)
    code = false;
  else if (UserKey == BUTTON_RIGHT && GameState.UserKey == BUTTON_LEFT)
    code = false;
  else if (UserKey == BUTTON_LEFT && GameState.UserKey == BUTTON_RIGHT)
    code = false;
  return code;
}

#include <QApplication>

#include "brick_game_front.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  BrickGameFront w;
  w.show();

  return a.exec();
}

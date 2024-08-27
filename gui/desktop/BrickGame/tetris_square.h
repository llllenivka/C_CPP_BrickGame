#ifndef TETRIS_SQUARE_H
#define TETRIS_SQUARE_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QPixmap>
#include <QWidget>

#define SIZE_SQUARE 34.82
#define SCALE_PXMAP 0.58

class SquareTetris : public QGraphicsItemGroup {
 public:
  void AddSquareToWidget(int x_coordinate, int y_coordinate, int number) {
    QGraphicsPixmapItem *Squares = new QGraphicsPixmapItem();
    Squares->setScale(SCALE_PXMAP);

    if (number > 5 && number < 11) number -= 5;

    if (number == 1) {
      QPixmap picture_square(":/img/image/tetris_2.png");
      Squares->setPixmap(picture_square);
    } else if (number == 2) {
      QPixmap picture_square(":/img/image/tetris_3.png");
      Squares->setPixmap(picture_square);
    } else if (number == 3) {
      QPixmap picture_square(":/img/image/tetris_1.png");
      Squares->setPixmap(picture_square);
    } else if (number == 4) {
      QPixmap picture_square(":/img/image/tetris_4.png");
      Squares->setPixmap(picture_square);
    } else if (number == 5) {
      QPixmap picture_square(":/img/image/tetris_5.png");
      Squares->setPixmap(picture_square);
    } else if (number == 11) {
      QPixmap picture_apple(":/img/image/apple.png");
      Squares->setPixmap(picture_apple);
      Squares->setScale(SCALE_PXMAP * 0.115);
    }

    Squares->setPos(x_coordinate, y_coordinate);
    this->addToGroup(Squares);
  }
};

#endif  // TETRIS_SQUARE_H

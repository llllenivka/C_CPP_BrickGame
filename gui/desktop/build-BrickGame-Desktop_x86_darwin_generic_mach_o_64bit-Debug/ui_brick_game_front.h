/********************************************************************************
** Form generated from reading UI file 'brick_game_front.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BRICK_GAME_FRONT_H
#define UI_BRICK_GAME_FRONT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BrickGameFront
{
public:
    QWidget *MainMenu;
    QWidget *widgetMenu;
    QLabel *NameGame;
    QLabel *TextMenu;
    QLabel *label;
    QPushButton *ButtonTetrisGame;
    QPushButton *ButtonSnakeGame;
    QPushButton *ButtonQuit;
    QLabel *label_2;
    QLabel *BrickGamev2;
    QStatusBar *statusbar;
    QMenuBar *menubar;

    void setupUi(QMainWindow *BrickGameFront)
    {
        if (BrickGameFront->objectName().isEmpty())
            BrickGameFront->setObjectName("BrickGameFront");
        BrickGameFront->resize(714, 927);
        MainMenu = new QWidget(BrickGameFront);
        MainMenu->setObjectName("MainMenu");
        MainMenu->setStyleSheet(QString::fromUtf8("background:rgb(250, 180, 203);"));
        widgetMenu = new QWidget(MainMenu);
        widgetMenu->setObjectName("widgetMenu");
        widgetMenu->setGeometry(QRect(60, 50, 591, 751));
        widgetMenu->setStyleSheet(QString::fromUtf8("QWidget{\n"
"	background: rgb(251, 249, 250);\n"
" border-radius: 40px;}"));
        NameGame = new QLabel(widgetMenu);
        NameGame->setObjectName("NameGame");
        NameGame->setGeometry(QRect(50, 150, 511, 91));
        QFont font;
        font.setFamilies({QString::fromUtf8("Heiti SC")});
        font.setPointSize(92);
        font.setBold(true);
        font.setKerning(true);
        NameGame->setFont(font);
        NameGame->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	background: rgb(251, 249, 250);\n"
"	color:  rgb(145, 47, 85);\n"
"}"));
        NameGame->setAlignment(Qt::AlignCenter);
        TextMenu = new QLabel(widgetMenu);
        TextMenu->setObjectName("TextMenu");
        TextMenu->setGeometry(QRect(100, 330, 411, 41));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Heiti SC")});
        font1.setPointSize(25);
        font1.setBold(true);
        font1.setItalic(false);
        TextMenu->setFont(font1);
        TextMenu->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	background: rgb(251, 249, 250);\n"
"	color:  rgb(86, 85, 86);\n"
"}"));
        TextMenu->setAlignment(Qt::AlignCenter);
        label = new QLabel(widgetMenu);
        label->setObjectName("label");
        label->setGeometry(QRect(100, 400, 411, 221));
        label->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color : rgb(145, 47, 85);\n"
"	background: rgb(252, 250, 253);\n"
"	border: 3px solid rgb(145, 47, 85);\n"
"}"));
        ButtonTetrisGame = new QPushButton(widgetMenu);
        ButtonTetrisGame->setObjectName("ButtonTetrisGame");
        ButtonTetrisGame->setGeometry(QRect(110, 420, 391, 51));
        ButtonTetrisGame->setMaximumSize(QSize(16777215, 16777215));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Heiti SC")});
        font2.setPointSize(27);
        font2.setBold(true);
        font2.setItalic(false);
        ButtonTetrisGame->setFont(font2);
        ButtonTetrisGame->setCursor(QCursor(Qt::PointingHandCursor));
        ButtonTetrisGame->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background: rgb(251, 249, 250);\n"
"	color: rgb(145, 47, 85);\n"
"	border: 3px solid rgb(251, 249, 250);\n"
"	border-radius: 20px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	background: rgb(145, 47, 85);\n"
"	color: rgb(251, 249, 250);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background:qlineargradient(spread:pad, x1:1, y1:0.613636, x2:0.995, y2:0.0170455, stop:0 rgba(128, 42, 76, 255), stop:1 rgba(228, 76, 136, 255));\n"
"	color: rgb(251, 249, 250);\n"
"}\n"
""));
        ButtonSnakeGame = new QPushButton(widgetMenu);
        ButtonSnakeGame->setObjectName("ButtonSnakeGame");
        ButtonSnakeGame->setGeometry(QRect(110, 480, 391, 51));
        ButtonSnakeGame->setMaximumSize(QSize(16777215, 16777215));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Heiti SC")});
        font3.setPointSize(27);
        font3.setBold(true);
        ButtonSnakeGame->setFont(font3);
        ButtonSnakeGame->setCursor(QCursor(Qt::PointingHandCursor));
        ButtonSnakeGame->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background: rgb(251, 249, 250);\n"
"	color: rgb(145, 47, 85);\n"
"	border: 3px solid rgb(251, 249, 250);\n"
"	border-radius: 20px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	background: rgb(145, 47, 85);\n"
"	color: rgb(251, 249, 250);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background:qlineargradient(spread:pad, x1:1, y1:0.613636, x2:0.995, y2:0.0170455, stop:0 rgba(128, 42, 76, 255), stop:1 rgba(228, 76, 136, 255));\n"
"	color: rgb(251, 249, 250);\n"
"}\n"
""));
        ButtonQuit = new QPushButton(widgetMenu);
        ButtonQuit->setObjectName("ButtonQuit");
        ButtonQuit->setGeometry(QRect(110, 540, 391, 51));
        ButtonQuit->setMaximumSize(QSize(16777215, 16777215));
        ButtonQuit->setFont(font3);
        ButtonQuit->setCursor(QCursor(Qt::PointingHandCursor));
        ButtonQuit->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background: rgb(251, 249, 250);\n"
"	color: rgb(145, 47, 85);\n"
"	border: 3px solid rgb(251, 249, 250);\n"
"	border-radius: 20px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	background: rgb(145, 47, 85);\n"
"	color: rgb(251, 249, 250);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background:qlineargradient(spread:pad, x1:1, y1:0.613636, x2:0.995, y2:0.0170455, stop:0 rgba(128, 42, 76, 255), stop:1 rgba(228, 76, 136, 255));\n"
"	color: rgb(251, 249, 250);\n"
"}\n"
""));
        label_2 = new QLabel(MainMenu);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 20, 651, 821));
        label_2->setStyleSheet(QString::fromUtf8("QLabel { background-color: black;\n"
" border: 1px;\n"
"border-radius: 40px; }"));
        BrickGamev2 = new QLabel(MainMenu);
        BrickGamev2->setObjectName("BrickGamev2");
        BrickGamev2->setGeometry(QRect(70, 810, 161, 21));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Heiti SC")});
        font4.setPointSize(18);
        font4.setUnderline(false);
        font4.setStrikeOut(false);
        BrickGamev2->setFont(font4);
        BrickGamev2->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	background: black;\n"
"	color:rgb(251, 249, 250);\n"
"}"));
        BrickGameFront->setCentralWidget(MainMenu);
        label_2->raise();
        widgetMenu->raise();
        BrickGamev2->raise();
        statusbar = new QStatusBar(BrickGameFront);
        statusbar->setObjectName("statusbar");
        statusbar->setStyleSheet(QString::fromUtf8("background: rgb(146, 50, 88);"));
        BrickGameFront->setStatusBar(statusbar);
        menubar = new QMenuBar(BrickGameFront);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 714, 24));
        menubar->setCursor(QCursor(Qt::PointingHandCursor));
        menubar->setStyleSheet(QString::fromUtf8("QMenuBar{\n"
"	background: rgb(146, 50, 88);\n"
"}"));
        BrickGameFront->setMenuBar(menubar);

        retranslateUi(BrickGameFront);

        QMetaObject::connectSlotsByName(BrickGameFront);
    } // setupUi

    void retranslateUi(QMainWindow *BrickGameFront)
    {
        BrickGameFront->setWindowTitle(QCoreApplication::translate("BrickGameFront", "BrickGameFront", nullptr));
        NameGame->setText(QCoreApplication::translate("BrickGameFront", "Brick Game", nullptr));
        TextMenu->setText(QCoreApplication::translate("BrickGameFront", "MENU", nullptr));
        label->setText(QString());
        ButtonTetrisGame->setText(QCoreApplication::translate("BrickGameFront", "t e t r i s", nullptr));
        ButtonSnakeGame->setText(QCoreApplication::translate("BrickGameFront", "s n a k e", nullptr));
        ButtonQuit->setText(QCoreApplication::translate("BrickGameFront", "q u i t", nullptr));
        label_2->setText(QString());
        BrickGamev2->setText(QCoreApplication::translate("BrickGameFront", "BrickGameV2.0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BrickGameFront: public Ui_BrickGameFront {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BRICK_GAME_FRONT_H

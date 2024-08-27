QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../../brick_game/snake/snake_backend.cc \
    ../../../brick_game/tetris/tetris_backend.c \
    main.cpp \
    brick_game_front.cpp

HEADERS += \
    ../../../brick_game/snake/snake_backend.h \
    ../../../brick_game/snake/snake_fsm.h \
    ../../../brick_game/tetris/tetris_backend.h \
    ../../../brick_game/tetris/tetris_sm.h \
    brick_game_front.h \
    tetris_square.h

FORMS += \
    brick_game_front.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES +=

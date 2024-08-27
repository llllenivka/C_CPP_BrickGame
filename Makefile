CC=g++
CFLAGS=-Wall -Werror -Wextra -std=c++17
GTESTFLAGS=-lgtest -lm

BACK_TETRIS=$(wildcard brick_game/tetris/*.c)
BACK_SNAKE=$(wildcard brick_game/snake/*.cc)

BACKEND=$(BACK_TETRIS) $(BACK_SNAKE)
TESTS=unit_test/*.cc
FRONT_TERM=gui/cli/*.c
CONTROLLER=brick_game/*.cc

LAUNCH_TERM_GAME =$(FRONT_TERM) $(BACKEND) $(CONTROLLER)

all: test dist dvi

install: uninstall
	cd gui && cd desktop && cd BrickGame && qmake BrickGame.pro && make && make clean && rm Makefile && mkdir ../../../build && mv BrickGame.app/$(UI_BIN) ../../../build

uninstall:
	rm -rf build

install_term: uninstall_term
	$(CC) $(CFLAGS) $(LAUNCH_TERM_GAME) -o term_game -lncurses
	./term_game

test: clean
	$(CC) $(CFLAGS) brick_game/snake/snake_backend.cc $(TESTS) $(GTESTFLAGS) -o test
	./test

dist: install
	mkdir -p dist
	cp  -R ./build/BrickGame.app ./dist
	cp ./documentation.md ./dist
	cd ./dist && tar cvzf BrickGame.tgz *
	cd ./dist && rm -R BrickGame.app documentation.md
	make clean

dvi:
	open documentation.md

gcov_report: clean
	$(CC) $(CFLAGS) --coverage brick_game/snake/snake_backend.cc $(TESTS) $(GTESTFLAGS) -o coverage
	./coverage
	lcov -t "result" -o res.info  --ignore-errors inconsistent -c -d .
	lcov --remove res.info /c++/13 /usr/local/include/gtest -o filtered_coverage.info
	genhtml -o report filtered_coverage.info
	open report/index.html

uninstall_term:
	rm -rf term_game

clang:
	cp ../materials/linters/.clang-format .
	clang-format -n brick_game/*.cc brick_game/*.h brick_game/tetris/* brick_game/snake/* gui/cli/* gui/desktop/BrickGame/*.cpp  gui/desktop/BrickGame/*.h unit_test/*
	clang-format -i brick_game/*.cc brick_game/*.h brick_game/tetris/* brick_game/snake/* gui/cli/* gui/desktop/BrickGame/*.cpp  gui/desktop/BrickGame/*.h unit_test/*
	rm -rf .clang-format

clean:
	rm -rf term_game test *.gc* coverage report *.info build
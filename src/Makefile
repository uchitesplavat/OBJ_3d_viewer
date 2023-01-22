CC=gcc
CFLAGS=-std=c11 -pedantic -Wall -Wextra -g3
SOURCES=parser.c helpers/helpers.c helpers/affin_transform.c
OBJECTS=$(SOURCES:.c=.o)
OS = $(shell uname)
TEST_FILE_NAME = tests.c

ifeq ($(OS), Darwin)
	TEST_LIBS=-lcheck
else
	TEST_LIBS=-lcheck -lsubunit -pthread -lrt -lm
endif

all: clean gcov_report

install: build
	cd s21_3d_viewer; make

build: s21_3d_viewer.a
	rm -rf s21_3d_viewer
	mkdir s21_3d_viewer
	cd s21_3d_viewer; cmake ../../src

uninstall:
	rm -rf s21_3d_viewer

exec:
ifeq ($(OS), Darwin)
	cd s21_3d_viewer/viewer_test.app/Contents/MacOS; ./viewer_test
else
	cd s21_3d_viewer; ./viewer_test
endif


dist: build
	tar --totals -cvf s21_3d_viewer.tar s21_3d_viewer

s21_3d_viewer.a: clean $(OBJECTS)
	ar -rcs s21_3d_viewer.a $(OBJECTS)
	rm -f *.o

tests: $(TEST_FILE_NAME) s21_3d_viewer.a
	$(CC) $(CFLAGS) $(TEST_FILE_NAME) $(SOURCES) -o test $(TEST_LIBS) -L. --coverage
	./test

lint:
	sh linter.sh

gcov_report: tests
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
ifeq ($(OS), Darwin)
	open report/index.html
else
	xdg-open ./report/index.html
endif

dvi:
	cp pics/viewer.pdf .
	xdg-open ./viewer.pdf

clean:
	rm -rf *.o *.a *.so *.gcda *.gcno *.gch *.pdf *.tar rep.info *.html *.css test.info test.dSYM report

# install lcov:
# 	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
# 	brew install lcov

check: tests

ifeq ($(OS), Darwin)
	leaks --atExit -- ./test
else
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test
endif
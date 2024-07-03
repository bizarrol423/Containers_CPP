CC=g++
CFLAGS=-std=c++17#-Wall -Werror -Wextra 
LIBS=-lgtest
LEAKS= leaks --atExit -- ./tests
OPEN=open report/index.html

OS=$(shell uname -s)
ifeq ($(OS), Linux)
	LIBS+= -lpthread
	LEAKS=valgrind ./tests
	OPEN=
endif

all: clean test gcov_report

clean:
	@rm -rf *.o tests .clang-format *.gch *.info *.dSYM
	@rm -rf test_report list/*.gch *.gcda *.gcno report/

test: test_build
	./tests

gcov_report: clean
	@$(CC) -std=c++17 --coverage tests.cc -o test_report $(LIBS) -g
	./test_report
	lcov --ignore-errors mismatch -t "test" -o test.info --no-external -c -d .
	genhtml -o report/ test.info
	$(OPEN)

clang:
	@cp ../materials/linters/.clang-format .
	@clang-format -i *.h *.cc implementations/*
	@clang-format -n *.h *.cc implementations/*

leaks: test_build
	@$(LEAKS)

check:
	@cppcheck --language=c++ *.h *.cc implementations/*

test_build: clean tests.o
	@$(CC) $(CFLAGS) -o tests tests.cc $(LIBS) -g

tests.o:
	@$(CC) $(CFLAGS) -c tests.cc $(LIBS) -g

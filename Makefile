CC=gcc
CFLAGS= -std=c++17 -pedantic -Wall -Werror -Wextra
TARGET = s21_containers_test

# Директория для тестов
TEST_DIR=./test/
TEST_FILES=$(wildcard $(TEST_DIR)*.cc)
OUT_TEST=$(TEST_DIR)$(TARGET)
OS := $(shell uname -s)

# Флаги для линукса отдельно
ifeq ($(OS),Linux)
	OPEN_CMD = xdg-open
	TEST_LIBS = -lgtest -pthread -lstdc++ -lsubunit -lrt -lm
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
	TEST_LIBS =-ld64 -lgtest -pthread -lstdc++
endif

SRC = test/*.cc
INCLUDES = -I./src

all: clean $(TARGET)

$(TARGET): clean $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(INCLUDES) -o $(OUT_TEST) $(TEST_LIBS)

test: rebuild
	${OUT_TEST}
	
%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@

gcov_report: clean
	$(CC) $(CFLAGS) --coverage -o $(TEST_DIR)gtest_test $(TEST_FILES) $(TEST_LIBS)
	chmod +x $(TEST_DIR)gtest_test
	$(TEST_DIR)gtest_test
	lcov --capture --directory . --rc branch_coverage=0 --output-file $(TEST_DIR)coverage.info \
		--ignore-errors=mismatch,inconsistent \
		--exclude '*/test/*' --exclude '*/usr/*'
	genhtml $(TEST_DIR)coverage.info --output-directory $(TEST_DIR)coverage_report --rc branch_coverage=0
	$(OPEN_CMD) $(TEST_DIR)coverage_report/index.html

valgrind: rebuild
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=leaks_log.txt $(OUT_TEST)
	echo --- Valgrind summary --- && cat leaks_log.txt | grep 'total heap usage' && cat leaks_log.txt | grep 'ERROR SUMMARY'

clean: clean_test
	rm -rf *.o */*.o $(TARGET) */$(TARGET) *.out *.dSYM report debug test.out leaks_log.txt

clean_test:
	rm -rf $(TEST_DIR)*.gc* $(TEST_DIR)*.info $(TEST_DIR)gtest_test $(TEST_DIR)coverage_report $(TEST_DIR)*.out $(TEST_DIR)*.out.* $(TEST_DIR)gtest_test.dSYM/ $(TEST_DIR)*.gcda

rebuild: clean $(TARGET)

##
## EPITECH PROJECT, 2026
## Makefile
## File description:
## Makefile.
##

NAME = corewar
TEST_NAME = unit_tests

CC = clang
CFLAGS = -Wall -Wextra -Werror -Iinclude
CRITERION = $(shell pkg-config --libs criterion)
CRITERION_FLAGS = $(shell pkg-config --cflags criterion)
TEST_CFLAGS = $(CFLAGS) $(CRITERION_FLAGS) --coverage

SRC = $(shell find ./src/ -name '*.c')
TEST_SRC = $(shell find ./tests/ -name '*.c')
TESTED_SRC = $(filter-out ./src/main.c,$(SRC))
TEST_BUILD = $(CC) $(TEST_CFLAGS) -o $(TEST_NAME)
TEST_INPUTS = $(TESTED_SRC) $(TEST_SRC)

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

$(TEST_NAME):
	$(TEST_BUILD) $(TEST_INPUTS) $(CRITERION)

clean:
	rm -f $(shell find . -name '*.o')
	rm -f $(shell find . -name '*.gcno')
	rm -f $(shell find . -name '*.gcda')
	rm -f $(shell find . -name '*.gcov')
	rm -f $(shell find . -name '*.c~')
	rm -f $(shell find . -name '*.h~')
	rm -f $(shell find . -name '*#*')
	rm -f $(shell find . -name '*.pch')
	rm -f $(shell find . -name '*.out')
	rm -f $(shell find . -name '*~')
	rm -f $(shell find . -name '.DS_Store')

fclean: clean
	rm -f $(shell find . -name '$(NAME)')
	rm -f $(shell find . -name '$(TEST_NAME)')

re: fclean all

tests_run: fclean $(TEST_NAME)
	./$(TEST_NAME)

epiclang:
	epiclang -Iinclude $(CRITERION_FLAGS) $(SRC) $(TEST_SRC) $(CRITERION)

.PHONY: all clean fclean re tests_run epiclang

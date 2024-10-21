NAME = main

CC = clang
VERSION = -std=c89
FLAGS =
WARNINGS = -Wall -Wextra -Werror -pedantic -pedantic-errors -Wpedantic -Wno-gnu-label-as-value -Wno-unused-function

INPUT = object.c vm.c $(NAME).c
OUTPUT = a.out

all: compile

compile:
	$(CC) $(OPT) $(VERSION) $(FLAGS) $(WARNINGS) -o $(OUTPUT) $(INPUT) && ./$(OUTPUT)

clean:
	$(RM) -f $(OUTPUT) *.dSYM

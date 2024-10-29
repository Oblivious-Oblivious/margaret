NAME = main

CC = clang
VERSION = -Og -std=c89
FLAGS = -g -fsanitize=address
WARNINGS = -Wall -Wextra -Werror -pedantic -pedantic-errors -Wpedantic -Wno-gnu-label-as-value -Wno-unused-function -Wno-gnu-statement-expression-from-macro-expansion

SRC = object.c vm.c scanner.c ../libs/EmeraldsReadline/export/libreadline.a ../libs/EmeraldsReadline/export/libcurses.a ../libs/EmeraldsReadline/export/libhistory.a
INPUT = $(SRC) $(NAME).c
SPECINPUT = $(SRC) $(NAME).spec.c
OUTPUT = a.out
SPECOUTPUT = spec

all: compile

compile:
	$(CC) $(OPT) $(VERSION) $(FLAGS) $(WARNINGS) -o $(OUTPUT) $(INPUT) && ./$(OUTPUT)

test:
	$(CC) $(OPT) -std=c99 $(FLAGS) $(WARNINGS) -o spec $(SPECINPUT) && ./$(SPECOUTPUT)

clean:
	$(RM) -r $(OUTPUT) spec *.dSYM

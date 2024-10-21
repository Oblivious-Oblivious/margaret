NAME = main

CC = clang
VERSION = -std=c89
FLAGS =
WARNINGS = -Wall -Wextra -Werror -pedantic -pedantic-errors -Wpedantic -Wno-gnu-label-as-value -Wno-unused-function

INPUT = object.c vm.c scanner.c $(NAME).c ../libs/EmeraldsReadline/export/libreadline.a ../libs/EmeraldsReadline/export/libcurses.a ../libs/EmeraldsReadline/export/libhistory.a
OUTPUT = a.out

all: compile

compile:
	$(CC) $(OPT) $(VERSION) $(FLAGS) $(WARNINGS) -o $(OUTPUT) $(INPUT) && ./$(OUTPUT) -i

clean:
	$(RM) -f $(OUTPUT) *.dSYM

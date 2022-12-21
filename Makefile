NAME = margaret
TEST = spec_helper

CC = clang
OPT = -O2
VERSION = -std=c99

FLAGS = -Wall -Wextra -Werror -pedantic -pedantic-errors -Wpedantic
WARNINGS = -Wno-unused-function -Wno-strict-prototypes
HEADERS =
LIBS = libs/readline/libreadline.dylib libs/boehm_gc/libgc.a

SRC = src/**/*.c
INPUT = $(SRC) $(NAME).c
OUTPUT = $(NAME)

TESTINPUT = spec/$(TEST).c $(SRC)
TESTOUTPUT = spec/$(TEST)

all: compiler

compiler:
	$(CC) $(OPT) $(VERSION) $(HEADERS) $(FLAGS) $(WARNINGS) $(REMOVE_WARN) $(LIBS) -o $(OUTPUT) $(INPUT)
	@echo
	./$(OUTPUT) examples/test.marg

test:
	$(CC) $(OPT) $(VERSION) $(HEADERS) $(FLAGS) $(WARNINGS) $(LIBS) -o $(TESTOUTPUT) $(TESTINPUT)
	@echo
	./$(TESTOUTPUT)

clean:
	$(RM) -r $(OUTPUT) $(TESTOUTPUT)

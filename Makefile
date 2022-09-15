NAME = margaret
TEST = spec_helper

CC = clang
OPT = -O2
VERSION = -std=c99

FLAGS = -Wall -Wextra -Werror -pedantic -pedantic-errors -Wpedantic
WARNINGS = -Wno-unused-function
HEADERS =
LIBS =

SRC = src/**/*.c
INPUT = $(NAME).c
OUTPUT = $(NAME)

TESTINPUT = spec/$(TEST).c $(SRC)
TESTOUTPUT = spec/$(TEST)

# all: compiler
all: run

run:
	ruby margaret.rb examples/test.marg

# compiler:
# 	$(CC) $(OPT) $(VERSION) $(HEADERS) $(FLAGS) $(WARNINGS) $(REMOVE_WARN) $(LIBS) -o $(OUTPUT) $(INPUT)
# 	@echo
# 	./$(OUTPUT)

test:
	$(CC) $(OPT) $(VERSION) $(HEADERS) $(FLAGS) $(WARNINGS) $(LIBS) -o $(TESTOUTPUT) $(TESTINPUT)
	@echo
	./$(TESTOUTPUT)

rtest:
	ruby spec/spec_helper.rb

clean:
	$(RM) -r $(OUTPUT) $(TESTOUTPUT)

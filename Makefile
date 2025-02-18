CC = gcc
LIBS = -lm
CC_FLAGS = -Wall -Wpedantic -Werror $(LIBS)
EXE = finanz

all: dev

build: main.c 
	$(CC) $(CC_FLAGS) -o $(EXE) main.c -g

dev: build
	@./$(EXE)

release: main.c 
	$(CC) $(CC_FLAGS) -o $(EXE) main.c -O2

test: core.c tests/*
	$(CC) $(CC_FLAGS) -o test tests/tests_main.c -g
	@./test


clean:
	rm $(EXE)
	rm test

.PHONY: build dev release clean all test
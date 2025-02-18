CC = gcc
CC_FLAGS = -Wall -Wpedantic -Werror
EXE = finanz

all: dev

build: main.c 
	$(CC) $(CC_FLAGS) -o $(EXE) main.c -g

dev: build
	@./$(EXE)

release: main.c 
	$(CC) $(CC_FLAGS) -o $(EXE) main.c -O2

clean:
	rm $(EXE)
	rm test*

.PHONY: build dev release clean all
CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic -O2 -Iinclude -Imock
SRC     := $(wildcard src/*.c) $(wildcard mock/*.c)
BIN     := build/temp_monitor

all: $(BIN)

$(BIN): $(SRC)
	@mkdir -p build
	$(CC) $(CFLAGS) $(SRC) -o $(BIN)

run: all
	./$(BIN)

clean:
	rm -rf build

.PHONY: all run clean

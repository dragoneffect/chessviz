CC = gcc
CFLAGS = -Wall -Werror
OBJ = $(CC) -c $< -o $@ $(CFLAGS)

.PHONY: clean test

default: bin/chessviz bin/chessviz_test

bin/chessviz: build/src/main.o build/src/board_print_plain.o build/src/conversion.o build/src/board.o
	mkdir -p bin
	$(CC) $^ -o $@ $(CFLAGS)

build/src/main.o: src/main.c
	mkdir -p build
	mkdir -p build/src
	$(OBJ)

build/src/board_print_plain.o: src/board_print_plain.c src/board_print_plain.h
	$(OBJ)

build/src/board.o: src/board.c src/board.h
	$(OBJ)

build/src/conversion.o: src/conversion.c src/conversion.h
	$(OBJ)

bin/chessviz_test: build/test/main.o build/src/board_print_plain.o build/src/conversion.o build/src/board.o
	$(CC) $^ -o $@ $(CFLAGS)

build/test/main.o: test/main.c thirdparty/ctest.h src/board.h src/board_print_plain.h src/conversion.h
	mkdir -p build/test
	$(OBJ) -I thirdparty -I src

clean:
	rm -rf build bin

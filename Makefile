all: build/prog

build/prog: build/main.o build/board.o build/board_print_plain.o build/conversion.o
	gcc -Wall -Werror build/main.o build/board.o build/board_print_plain.o build/conversion.o -o build/prog

build/main.o: src/main.c
	gcc -Wall -Werror -c src/main.c -o build/main.o

build/board.o: src/board.c
	gcc -Wall -Werror -c src/board.c -o build/board.o

build/board_print_plain.o: src/board_print_plain.c
	gcc -Wall -Werror -c src/board_print_plain.c -o build/board_print_plain.o

build/conversion.o: src/conversion.c
	gcc -Wall -Werror -c src/conversion.c -o build/conversion.o

clean:
	rm -rf build/*.o

TARGET = bin/prog
CC = gcc
CFLAGS = -Wall -Werror

.PHONY: clean all default

default: bin build $(TARGET)
all: default

OBJECTS = $(patsubst src/%.c, build/%.o, $(wildcard src/*.c))

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall -o $@

bin:
	mkdir bin
build:
	mkdir build

clean:
	-rm -rf build/*.o
	-rm -f $(TARGET)

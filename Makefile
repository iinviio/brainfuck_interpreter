
CC = gcc

all: brainfuck clean

%.o: %.c ./src/header.h
	$(CC) -c -o $@ $<

brainfuck: ./src/main.o ./src/input_parser.o ./src/string_parser.o ./src/help.o ./src/syntax_checker.o
	$(CC) -o brainfuck ./src/main.o ./src/input_parser.o ./src/string_parser.o ./src/help.o ./src/syntax_checker.o

clean:
	rm ./src/*.o

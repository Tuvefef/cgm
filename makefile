CC = gcc
SRC = src/test.c 
BIN = src/cgmtest

all:
	$(CC) $(SRC) -o $(BIN) -lm -O3

run:
	./$(BIN)

clean:
	rm $(BIN)
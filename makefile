CC = gcc
SRC = src/main.c 
BIN = src/cgmb

all:
	$(CC) $(SRC) -o $(BIN) -lm

run:
	./$(BIN)

clean:
	rm $(BIN)
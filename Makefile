CC = gcc
SRC_DIR = src
INC_DIR = include

SRC = $(SRC_DIR)/*.c
OUT = sudoku

build: $(SRC)
	$(CC) $(SRC) -o $(OUT) -I $(INC_DIR) -lm

clean:
	rm -f *.o $(OUT)

rebuild: clean build
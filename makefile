CC=g++
SRC=*.cpp
BIN=remote
FLAGS=-w -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system -lsfml-audio


all:
	$(CC) $(SRC) -o $(BIN) $(FLAGS)

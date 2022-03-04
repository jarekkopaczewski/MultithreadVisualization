all: main

main: main.o
	g++ -o main main.o -lncurses

main.o: main.cpp
	g++ -c main.cpp 
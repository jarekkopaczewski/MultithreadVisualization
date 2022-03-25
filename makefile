all: main

main: main.o
	g++ -o main main.o -lncurses -pthread

main.o: main.cpp
	g++ -c main.cpp 

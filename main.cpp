#include <ncurses.h>

int main()
{	
	initscr();			            
	printw("Hello World !!!");	    
	refresh();			            
	getch();			            
	endwin();			            
	return 0;
}

// #include <iostream>
// #include "Punkt.cpp"
// using namespace std;

// int main()
// {
//     Punkt pkt = Punkt(1, 2);
//     pkt.wyswietl();
//     return 0;
// }
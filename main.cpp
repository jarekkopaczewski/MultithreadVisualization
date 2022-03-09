#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include "Point.h"
using namespace std;

#define DELAY 30000

void printBoard(int max_x, int max_y)
{
	for (int y = 1; y <= max_y; y++)
	{
		mvprintw(1, y, "#");
		mvprintw(max_x, y, "#");
	}

	for (int x = 1; x < max_x; x++)
	{
		mvprintw(x, 1, "#");
		mvprintw(x, max_y, "#");
	}
}

void printPoints(vector<Point *> points)
{
	for (Point *point : points)
	{
		mvprintw(point->x, point->y, "o");
		point->calcCords();
	}
}

int main(int argc, char *argv[])
{
	int max_x = 30;
	int max_y = 80;
	vector<Point *> points;
	for (int i = 0; i < 5; i++)
		points.push_back(new Point(max_x, max_y / 2, Direction::N, max_x, max_y));

	initscr();
	noecho();
	curs_set(FALSE);

	while (1)
	{
		clear();
		printBoard(max_x, max_y);
		printPoints(points);
		refresh();
		usleep(DELAY);
	}
	endwin();
	return 0;
}
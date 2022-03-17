#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include "Point.cpp"
using namespace std;

#define DELAY 30000

void printBoard(int max_x, int max_y)
{
	for (int y = 0; y <= max_y; y++)
	{
		mvprintw(0, y, "#");
		mvprintw(max_x, y, "#");
	}

	for (int x = 0; x < max_x; x++)
	{
		mvprintw(x, 0, "#");
		mvprintw(x, max_y, "#");
	}
}

void printPoints(vector<Point *> points)
{
	srand(time(NULL));
	for (Point *point : points)
	{
		point->refresh();
		mvprintw(point->x, point->y, "o");
	}
}

int main(int argc, char *argv[])
{
	int max_x = 15;
	int max_y = 30;
	vector<Point *> points;
	for (int i = 0; i < 10; i++)
		points.push_back(new Point(max_x / 2, max_y / 2, Direction::S, max_x, max_y));

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
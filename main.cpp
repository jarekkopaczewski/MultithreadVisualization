#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include <thread>
#include <algorithm>
#include "Point.cpp"
#include "Printer.cpp"
#include "Block.cpp"
using namespace std;

#define DELAY 100000
vector<Point *> points;
vector<thread> threads;

void pointThreadRun(Point *point)
{
	point->run();
	points.erase(find(points.begin(), points.end(), point));
	pthread_exit(0);
}

void blockThreadRun(Block *block)
{
	block->run();
	pthread_exit(0);
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	char symbolCounter = 'a';
	int max_x = 20;
	int max_y = 40;
	Printer *printer = new Printer(max_x, max_y);
	Block *block = new Block(5, 5, 10, 5, max_x, max_y);
	thread blockThread(blockThreadRun, block);

	initscr();
	cbreak();
	noecho();
	curs_set(0);
	nodelay(stdscr, TRUE);

	int input = 0;
	do
	{
		if (points.size() < 5)
		{
			Point *point = new Point(max_x - 1, max_y / 2, Generator::randomBottomDirection(7, 0), max_x, max_y, (rand() % 5 + 2), symbolCounter);
			threads.push_back(thread(pointThreadRun, point));
			points.push_back(point);
			symbolCounter++;
		}

		clear();
		printer->printFrame(points, block);
		mvprintw(0, 0, "%i", threads.size());
		refresh();
		usleep(DELAY);

		input = getch();
	} while (input != 'q');

	endwin();
	return 0;
}
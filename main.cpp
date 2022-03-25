#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include <pthread.h>
#include "Point.cpp"
#include "Printer.cpp"
#include "Block.cpp"
using namespace std;

#define DELAY 100000

int main(int argc, char *argv[])
{
	srand(time(NULL));
	int max_x = 20;
	int max_y = 40;
	Printer *printer = new Printer(max_x, max_y);
	vector<Point *> points;
	Block *block = new Block(5, 5, 10, 5, max_x, max_y);

	for (int i = 0; i < 10; i++)
		points.push_back(new Point(max_x / 2, max_y / 2, Generator::randomBottomDirection(7, 0), max_x, max_y, 50000));

	initscr();
	noecho();
	curs_set(FALSE);

	pthread_t ptid[5];

	for (int i = 0; i < 5; i++)
		pthread_create(&ptid[i], NULL, &Point::run_helper, points[i]);

	while (1)
	{
		block->refresh();
		clear();
		printer->printFrame(points, block);
		refresh();
		usleep(DELAY);
	}

	endwin();
	return 0;
}

void refreshBlock(Block *block)
{
}
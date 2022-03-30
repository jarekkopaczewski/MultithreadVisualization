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
vector<thread *> threads;
int numberOfThreads = 0;

void pointThreadRun(Point *point, int threadId)
{
	thread *currentThread = threads[threadId];
	point->run();
	points.erase(find(points.begin(), points.end(), point));
	threads.erase(find(threads.begin(), threads.end(), currentThread));
	numberOfThreads--;
	pthread_exit(0);
}

void blockThreadRun(Block *block, int *status)
{
	block->run(status);
	pthread_exit(0);
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	char symbolCounter = 'a';
	int max_x = 20, max_y = 40;
	int *status;
	Printer *printer = new Printer(max_x, max_y);
	Block *block = new Block(5, 5, 10, 5, max_x, max_y);

	initscr();
	cbreak();
	noecho();
	curs_set(0);
	nodelay(stdscr, TRUE);

	start_color();
	init_pair(0, COLOR_GREEN, COLOR_BLACK);
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_GREEN, COLOR_WHITE);
	init_pair(6, COLOR_YELLOW, COLOR_RED);
	init_pair(7, COLOR_BLUE, COLOR_CYAN);
	init_pair(8, COLOR_MAGENTA, COLOR_BLUE);
	init_pair(9, COLOR_CYAN, COLOR_MAGENTA);
	init_pair(10, COLOR_WHITE, COLOR_BLACK);
	init_pair(11, COLOR_RED, COLOR_BLACK);

	if (has_colors() == FALSE)
	{
		endwin();
		cout << " No color support, program ends";
		return 0;
	}

	int input = 0;
	status = &input;
	thread blockThread(blockThreadRun, block, status);
	do
	{
		if (points.size() < 5)
		{
			Point *point = new Point(max_x - 1, max_y / 2, Generator::randomBottomDirection(7, 0), max_x, max_y, (rand() % 5 + 2), symbolCounter, (rand() % 9 + 0));
			threads.push_back(new thread(pointThreadRun, point, numberOfThreads));
			points.push_back(point);
			symbolCounter++;
			numberOfThreads++;
		}

		clear();
		printer->printFrame(points, block);
		refresh();
		usleep(DELAY);
		input = getch();
		status = &input;
	} while (*status != 'q');

	endwin();
	blockThread.join();
	return 0;
}
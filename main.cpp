#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include <thread>
#include <algorithm>
#include <mutex>
#include <shared_mutex>
#include "Printer.cpp"
#include "BlockPoint.cpp"
using namespace std;

// Pilki beda wpadaly do prostokata i zatrzymywac sie ( ruszac sie z  prostokatem ), jak wpadna 3 to odblokowuja sie i zaczynaja ruszac sie ponowanie.
// Po opuszczeniu prostokąt zaczyna po jakimś czasie znowu zbierać piłki.

// Zmienna wyswietlajaca sredni czas przebywania kulek w prostokacie.
// Wyliczanie tylko jak gina kulki

#define DELAY 100000
#define GENERATOR_DELAY 2500000
vector<Point *> points;
vector<thread *> threads;
Block *block;
int numberOfThreads = 0;
mutex pointLocker;
shared_ptr<condition_variable> con{make_shared<condition_variable>()};

void pointThreadRun(Point *, int, bool &);
void blockThreadRun(Block *, bool &);
void generatorRun(int, int, bool &);
void iniColors();
void checkColision(bool &);

int main(int argc, char *argv[])
{
	srand(time(NULL));
	int max_x = 20, max_y = 40;
	bool status;
	int input = 0;
	Printer *printer = new Printer(max_x, max_y);
	block = new Block(5, 5, 10, 5, max_x, max_y, ref(pointLocker), con);

	initscr();
	cbreak();

	noecho();
	curs_set(0);
	nodelay(stdscr, TRUE);

	start_color();

	iniColors();

	if (has_colors() == FALSE)
	{
		delete printer;
		delete block;
		endwin();
		return 0;
	}

	// watek bloku
	thread blockThread(blockThreadRun, block, ref(status));
	// watek generujacy watki pilek
	thread generatorThread(generatorRun, max_x, max_y, ref(status));

	do
	{
		// wyswietlanie elementow symulacji
		clear();
		printer->printFrame(points, block);
		refresh();
		usleep(DELAY);

		// wczytywanie znaku
		input = getch();
		if (input == 'q')
			status = true;

	} while (!status);

	// wlaczenie join na uruchomionych watkach
	generatorThread.join();

	for (thread *t : threads)
		t->join();

	blockThread.join();

	// czyszczenie pamieci
	threads.clear();
	points.clear();
	delete printer;
	delete block;

	// koniec
	endwin();
	return 0;
}

void pointThreadRun(Point *point, int threadId, bool &status)
{
	thread *currentThread = threads[threadId];
	point->run(status);
	points.erase(find(points.begin(), points.end(), point));
	threads.erase(find(threads.begin(), threads.end(), currentThread));
	numberOfThreads--;
}

void blockThreadRun(Block *block, bool &status)
{
	block->run(status);
}

void generatorRun(int max_x, int max_y, bool &status)
{
	char symbolCounter = 'a';
	while (!status)
	{
		Point *point = new Point(max_x - 1, max_y / 2, Generator::randomBottomDirection(7, 0), max_x, max_y, (rand() % 7 + 4), symbolCounter, (rand() % 9 + 0), block, ref(pointLocker), con);
		threads.push_back(new thread(pointThreadRun, point, numberOfThreads, ref(status)));
		points.push_back(point);
		symbolCounter++;
		numberOfThreads++;
		usleep(GENERATOR_DELAY);
	}
}

void iniColors()
{
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
}

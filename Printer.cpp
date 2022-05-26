#include "Printer.h"

Printer::Printer(int max_x, int max_y)
{
    this->max_x = max_x;
    this->max_y = max_y;
}

void Printer::printFrame(vector<Point *> points, Block *block, int avg)
{
    printBoard();
    printBlock(block);
    printPoints(points);
    mvprintw(0, this->max_y + 2, "Sredni czas w bloku[ms]: %i", avg);
}

void Printer::printBoard()
{
    wattron(stdscr, COLOR_PAIR(10));
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
    wattroff(stdscr, COLOR_PAIR(10));
}

void Printer::printBlock(Block *block)
{
    if (block->stop)
        wattron(stdscr, COLOR_PAIR(11));
    else
        wattron(stdscr, COLOR_PAIR(9));

    for (int y = block->y; y <= (block->y + block->width); y++)
    {
        mvprintw(block->x, y, "@");
        mvprintw(block->x + block->height, y, "@");
    }

    for (int x = block->x; x < (block->x + block->height); x++)
    {
        mvprintw(x, block->y, "@");
        mvprintw(x, block->y + block->width, "@");
    }
    if (block->stop)
        wattroff(stdscr, COLOR_PAIR(11));
    else
        wattroff(stdscr, COLOR_PAIR(9));
}

void Printer::printPoints(vector<Point *> points)
{
    for (Point *point : points)
    {
        wattron(stdscr, COLOR_PAIR(point->color));
        mvprintw(point->x, point->y, "%c", point->symbol);
        wattroff(stdscr, COLOR_PAIR(point->color));
    }
}
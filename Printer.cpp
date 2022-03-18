#include "Printer.h"

Printer::Printer(int max_x, int max_y)
{
    this->max_x = max_x;
    this->max_y = max_y;
}

void Printer::printFrame(vector<Point *> points, Block *block)
{
    printBoard();
    printBlock(block);
    printPoints(points);
}

void Printer::printBoard()
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

void Printer::printBlock(Block *block)
{
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
}

void Printer::printPoints(vector<Point *> points)
{
    for (Point *point : points)
        mvprintw(point->x, point->y, "o");
}
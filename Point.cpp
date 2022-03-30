#include "Point.h"
#include "Generator.cpp"
#include <iostream>
using namespace std;

Point::Point() {}

Point::~Point() {}

Point::Point(int x, int y, Direction dir, int max_x, int max_y, int delay, char symbol, int color)
{
    this->x = x;
    this->y = y;
    this->dir = dir;
    this->max_x = max_x;
    this->max_y = max_y;
    this->bounce = 0;
    this->delay = delay;
    this->symbol = symbol;
    this->color = color;
}

void Point::run()
{
    while (bounce != 5)
    {
        this->checkColision();
        this->calcCords();
        usleep(50000 * delay);
    }
}

void Point::checkColision()
{
    if (x == max_x - 1) // dol
    {
        dir = Generator::randomBottomDirection(2, 0);
        bounce++;
    }
    else if (y == 1) // lewa sciana
    {
        dir = Generator::randomDirection(3, 1);
        bounce++;
    }
    else if (y == max_y - 1) // prawa sciana
    {
        dir = Generator::randomDirection(3, 5);
        bounce++;
    }
    else if (x == 1)
    {
        dir = Generator::randomDirection(3, 3);
        bounce++;
    }
}

void Point::calcCords()
{
    switch (dir)
    {
    case N:
        x--;
        break;
    case NE:
        x--;
        y++;
        break;
    case E:
        y++;
        break;
    case ES:
        y++;
        x++;
        break;
    case S:
        x++;
        break;
    case SW:
        x++;
        y--;
        break;
    case W:
        y--;
        break;
    case NW:
        x--;
        y--;
        break;
    default:
        break;
    }
}
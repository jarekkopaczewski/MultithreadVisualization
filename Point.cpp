#include "Point.h"
#include "Generator.cpp"
#include <iostream>
using namespace std;

Point::Point()
{
}

Point::~Point()
{
}

Point::Point(int x, int y, Direction dir, int max_x, int max_y)
{
    this->x = x;
    this->y = y;
    this->dir = dir;
    this->max_x = max_x;
    this->max_y = max_y;
}

void Point::refresh()
{
    this->checkColision();
    this->calcCords();
}

void Point::checkColision()
{
    // dol
    if (x == max_x - 1)
        dir = Generator::randomBottomDirection(2, 0);
    // lewa sciana
    else if (y == 1)
        dir = Generator::randomDirection(3, 1);
    // prawa sciana
    else if (y == max_y - 1)
        dir = Generator::randomDirection(3, 5);
    // gora
    else if (x == 1)
        dir = Generator::randomDirection(3, 3);
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
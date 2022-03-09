#include "Point.h"
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

void Point::calcCords()
{
    x--;
    y--;
}
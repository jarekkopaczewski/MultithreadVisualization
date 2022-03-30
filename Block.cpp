#include "Block.h"

Block::Block(int x, int y, int width, int height, int max_x, int max_y)
{
    this->x = x;
    this->y = y;
    this->height = height;
    this->width = width;
    this->max_y = max_y;
    this->max_x = max_x;
    this->delay = 3;
    this->counter = 0;
    this->dir = Direction::N;
}

void Block::run(int *status)
{
    while (*status != 'q')
    {
        this->checkColision();
        this->calcCords();
        usleep(100000 * delay);
    }
}

void Block::calcCords()
{
    switch (dir)
    {
    case Direction::N:
        x--;
        break;
    case Direction::S:
        x++;
        break;
    default:
        break;
    }
}

void Block::checkColision()
{
    if (x + height == max_x - 1)
    {
        dir = Direction::N;
        delay = (rand() % 10 + 2);
    }
    else if (x == 1)
    {
        dir = Direction::S;
        delay = (rand() % 10 + 2);
    }
}
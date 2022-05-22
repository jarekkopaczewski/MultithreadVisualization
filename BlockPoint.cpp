#include "BlockPoint.h"
#include "Generator.cpp"
#include <iostream>
#include <condition_variable>
#include <shared_mutex>
using namespace std;

condition_variable con2;
bool ready = false;

Point::~Point() {}

Point::Point(int x, int y, Direction dir, int max_x, int max_y, int delay, char symbol, int color, Block *block, mutex &pointBlock, shared_ptr<condition_variable> con) : pointBlock(pointBlock), con(con)
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
    this->stop = false;
    this->block = block;
}

void Point::run(bool &status)
{
    while (bounce <= 5)
    {
        if (status)
            break;

        usleep(50000 * delay);

        if (!this->block->stop)
            this->checkBlockColision();

        this->checkColision();
        this->calcCords();
    }
}

void Point::checkBlockColision()
{
    if (this->x > this->block->x &&
        this->x < (this->block->x + this->block->height) &&
        this->y > this->block->y &&
        this->y < (this->block->y + this->block->width))
    {
        this->block->points.insert(this);
        unique_lock<mutex> locker(pointBlock);
        con2.wait(locker, []
                  { return ready; });
        locker.unlock();
    }
}

bool Point::stillWait()
{
    return this->block->points.size() >= 3;
}

void Point::checkColision()
{
    if (x == max_x - 1) // bottom
    {
        dir = Generator::randomBottomDirection(2, 0);
        bounce++;
    }
    else if (y == 1) // left border
    {
        dir = Generator::randomDirection(3, 1);
        bounce++;
    }
    else if (y == max_y - 1) // right border
    {
        dir = Generator::randomDirection(3, 5);
        bounce++;
    }
    else if (x == 1) // top
    {
        dir = Generator::randomDirection(3, 3);
        bounce++;
    }
}

void Point::moveUp()
{
    x--;
}

void Point::moveDown()
{
    x++;
}

void Point::lockPoint()
{
    stop = true;
}

void Point::unlockPoint()
{
    stop = false;
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

// Block class
Block::Block(int x, int y, int width, int height, int max_x, int max_y, mutex &pointBlock, shared_ptr<condition_variable> con) : pointBlock(pointBlock), con(con)
{
    this->x = x;
    this->y = y;
    this->height = height;
    this->width = width;
    this->max_y = max_y;
    this->max_x = max_x;
    this->delay = 3;
    this->counter = 0;
    this->stop = false;
    this->dir = Direction::N;
}

void Block::run(bool &status)
{
    unique_lock<mutex> locker(pointBlock);
    while (!status)
    {
        this->checkColision();
        this->calcCords();

        if (this->points.size() >= 3)
        {
            locker.unlock();
            ready = true;
            con2.notify_all();
            this->points.clear();

            this->stop = true;

            for (int i = 0; i < 5; i++)
            {
                usleep(100000 * delay);
                this->checkColision();
                this->calcCords();
            }

            locker.lock();
            this->stop = false;
            ready = false;
        }

        usleep(100000 * delay);
    }

    ready = true;
    con2.notify_all();
    locker.unlock();
}

void Block::calcCords()
{
    switch (dir)
    {
    case Direction::N:
        x--;
        for (Point *point : points)
            point->moveUp();
        break;
    case Direction::S:
        x++;
        for (Point *point : points)
            point->moveDown();
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
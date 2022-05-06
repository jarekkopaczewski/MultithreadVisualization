#pragma once
#include <set>

class Block
{
public:
    int x;
    int y;
    int height;
    int width;
    int max_x;
    int max_y;
    int delay;
    int counter;
    bool stop;
    Direction dir;
    set<Point *> points;
    Block(int x, int y, int width, int height, int max_x, int max_y);
    void calcCords();
    void checkColision();
    void run(bool &status);
};
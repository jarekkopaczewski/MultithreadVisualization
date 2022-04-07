#pragma once

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
    Direction dir;
    Block(int x, int y, int width, int height, int max_x, int max_y);
    void calcCords();
    void checkColision();
    void run(bool &status);
};
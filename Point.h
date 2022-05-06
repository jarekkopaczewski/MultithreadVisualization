#pragma once

enum Direction
{
    N = 0,
    NE = 1,
    E = 2,
    ES = 3,
    S = 4,
    SW = 5,
    W = 6,
    NW = 7
};

class Point
{
private:
    int max_x;
    int max_y;
    int delay;
    Direction dir;
    ~Point();
    void checkColision();
    void calcCords();

public:
    int x;
    int y;
    char symbol;
    int color;
    int bounce;
    bool stop;
    Point();
    Point(int x, int y, Direction dir, int max_x, int max_y, int delay, char symbol, int color);
    void run(bool &status);
    void moveUp();
    void moveDown();
};
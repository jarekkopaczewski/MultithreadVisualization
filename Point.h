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
    Direction dir;
    ~Point();
    void checkColision();
    void calcCords();

public:
    int x;
    int y;
    Point();
    Point(int x, int y, Direction dir, int max_x, int max_y);
    void refresh();
};
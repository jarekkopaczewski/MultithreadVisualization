#pragma once

enum Direction
{
    N,
    NE,
    E,
    ES,
    S,
    SW,
    W,
    NW
};

class Point
{
    private:
        int max_x;
        int max_y;
        Direction dir;
        ~Point();
    public:
        int x; 
        int y;
        Point();
        Point(int x, int y, Direction dir, int max_x, int max_y);
        void calcCords();
};
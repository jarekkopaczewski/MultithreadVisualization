#pragma once
#include <atomic>
#include <mutex>
#include <set>
#include <condition_variable>
using namespace std;

class Block;
class Point;

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

// Block
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
    shared_ptr<condition_variable> con;
    mutex &pointBlock;
    Block(int x, int y, int width, int height, int max_x, int max_y, mutex &pointBlock, shared_ptr<condition_variable> con);
    void calcCords();
    void checkColision();
    void run(bool &status);
};

// Point
class Point
{
private:
    int max_x;
    int max_y;
    int delay;
    atomic<bool> stop;
    Direction dir;
    ~Point();
    void checkColision();
    void checkBlockColision();
    void calcCords();
    bool stillWait();

public:
    Block *block;
    mutex &pointBlock;
    shared_ptr<condition_variable> con;
    atomic<int> x;
    atomic<int> y;
    char symbol;
    int color;
    int bounce;
    Point(int x, int y, Direction dir, int max_x, int max_y, int delay, char symbol, int color, Block *block, mutex &pointBlock, shared_ptr<condition_variable> con);
    void run(bool &status);
    void moveUp();
    void moveDown();
    void lockPoint();
    void unlockPoint();
};
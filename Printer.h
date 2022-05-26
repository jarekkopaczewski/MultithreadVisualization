#include <vector>
#include "BlockPoint.h"

class Printer
{
private:
    int max_x;
    int max_y;
    void printPoints(vector<Point *> points);
    void printBoard();
    void printBlock(Block *block);

public:
    Printer(int max_x, int max_y);
    void printFrame(vector<Point *> points, Block *block, int avg);
};
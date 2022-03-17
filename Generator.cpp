#include "Generator.h"
#include <stdlib.h>
#include <time.h>

Direction Generator::randomDirection(int size, int begin)
{
    int dir = (rand() % size + begin);
    return (Direction)dir;
}

Direction Generator::randomBottomDirection(int size, int begin)
{
    int dir = (rand() % size + begin);
    int temp = (rand() % 2 + 0);
    if (temp == 0)
        return (Direction)dir;

    else
        return (Direction)7;
}
#pragma once
#include "Point.h"

class Generator
{
public:
    static Direction randomDirection(int size, int begin);
    static Direction randomBottomDirection(int size, int begin);
};
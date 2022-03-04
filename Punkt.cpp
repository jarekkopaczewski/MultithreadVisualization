#include "Punkt.h"
#include <iostream>
using namespace std;

Punkt::Punkt(int x, int y)
{
    this->x = x;
    this->y = y;
}

Punkt::~Punkt()
{

}

void Punkt::wyswietl()
{
    cout << this->x << ", " << this->y << endl;
}
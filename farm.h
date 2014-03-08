#ifndef FARM_H_INCLUDED
#define FARM_H_INCLUDED

#include "main.h"

class CFarm
{
public:
    int x, y, ID,
        zasieg;

    CFarm(int x, int y)
        : x(x), y(y)
    {
        ID = 202;
        zasieg = 4; // zasieg N pol uprawnych
    }
};

extern vector <CFarm> v_farm;

void renderFarm();
CFarm& getFarm(int, int);


#endif // FARM_H_INCLUDED

#ifndef HOUSE_H_INCLUDED
#define HOUSE_H_INCLUDED

#include "main.h"

class CHouse
{
public:
    int x, y, ID;

    int ludzie;
    int jedz_zboze, jedz_naczynia;

    int awans, maxAwans;

    CHouse(int x, int y)
        : x(x), y(y)
    {
        ID = 100;
        maxAwans = rand()%50;
        awans = maxAwans;
    }
};

extern vector <CHouse> v_house;

void renderHouse();
CHouse& getHouse(int, int);


#endif // HOUSE_H_INCLUDED

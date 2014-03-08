#ifndef CORNFIELD_H_INCLUDED
#define CORNFIELD_H_INCLUDED

#include "main.h"

class CCornfield
{
public:
    int x, y, ID;
    float time;

    CCornfield(int x, int y)
        : x(x), y(y)
    {
        ID = 203;
        time = 0;
    }

    void render(int,int, int,int);
};

extern vector <CCornfield> v_cornfield;

void createCornfield();
CCornfield& getCornfield(int, int);


#endif // CORNFIELD_H_INCLUDED

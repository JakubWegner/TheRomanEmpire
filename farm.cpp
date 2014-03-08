#include "farm.h"
#include "map.h"
#include "cornfield.h"

vector <CFarm> v_farm;

CFarm& getFarm(int x, int y)
{
    for(int i = 0; i < v_farm.size(); ++i)
    {
        if(x == v_farm[i].x && y == v_farm[i].y)
            return v_farm[i];
    }
}

void renderFarm()
{
    for(int i = 0; i < v_farm.size(); ++i)
    {
        for(int x = v_farm[i].x-v_farm[i].zasieg/2-1; x <= v_farm[i].x+v_farm[i].zasieg/2; ++x)
            for(int y = v_farm[i].y-v_farm[i].zasieg/2-1; y <= v_farm[i].y+v_farm[i].zasieg/2; ++y)
            {
                if(!pause)
                    getCornfield(x,y).time += ( rand()%5 )/2;
            }
    }
}

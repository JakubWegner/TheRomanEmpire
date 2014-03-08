#include "house.h"
#include "map.h"
#include "particle.h"

vector <CHouse> v_house;

CHouse& getHouse(int x, int y)
{
    for(int i = 0; i < v_house.size(); ++i)
    {
        if(x == v_house[i].x && y == v_house[i].y)
            return v_house[i];
    }
}

void renderHouse()
{
    for(int i = 0; i < v_house.size(); ++i)
    {
        // pod wplywem dojscia do wody: 2lvl -> 3lvl
        if(v_house[i].ID == 102 || v_house[i].ID == 103)
        {
            bool jestDojscie = false;
            for(int x = v_house[i].x-3; x <= v_house[i].x+3; ++x)
                for(int y = v_house[i].y-3; y <= v_house[i].y+3; ++y)
                {
                    if(map[y][x] == 201) // studnia
                        jestDojscie = true;
                }

            if(jestDojscie && !pause)
            {
                if(v_house[i].awans >= 0)
                    v_house[i].awans--;

                if(v_house[i].awans <= 0)
                {
                    int los = rand()%100;
                    if(los <= 50) map[v_house[i].y][v_house[i].x] = v_house[i].ID = 104;
                    else map[v_house[i].y][v_house[i].x] = v_house[i].ID = 105;

                    for(int i = 0; i < 30; ++i)
                        v_pHouseLvl.push_back(CParticle(v_house[i].x, v_house[i].y));

                    v_house[i].awans = v_house[i].maxAwans;
                }
            }
        }
    }
}

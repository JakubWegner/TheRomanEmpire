#include "people_settler.h"
#include "house.h"

vector <CPeople_settler> p_settler;

CPeople_settler::CPeople_settler(int px, int py, int cx, int cy)
{
    type = "settler";

    this->px = px;
    this->py = py;

    x = (px-py)*TILE_W/2;
    y = (px+py)*TILE_H/2;

    celX = cx;
    celY = cy;

    isLive = true;
}

void CPeople_settler::update()
{
    int tx = screen2iso_x((x+25),(y+25));
    int ty = screen2iso_y((x+25),(y+25));


    int tx2 = screen2iso_x((x+15),(y+25));
    int tx3 = screen2iso_x((x+35),(y+25));

    int ty2 = screen2iso_y((x+25),(y+15));
    int ty3 = screen2iso_y((x+25),(y+35));

    if(celY > ty)
    {
        kierunek = 4;
    }
    else if(celY < ty)
    {
        kierunek = 1;
    }
    else if(celX > tx)
    {
        kierunek = 3;
    }
    else if(celX < tx)
    {
        kierunek = 2;
    }

    if(celY >= ty2 && celY <= ty3 && celX >= tx2 && celX <= tx3)
    {
        if(map[celY][celX] == 100 || map[celY][celX] == 101)
        {
            int ktoryNamiot = rand()%2+1;
            map[celY][celX] = getHouse(celX, celY).ID = 101+ktoryNamiot;
            player.populacja++;
            isLive = false;
        }
        else
        {
            bool isFind = false;
            for(int i = 0; i < MAP_W; ++i)
            {
                for(int j = 0; j < MAP_H; ++j)
                {
                    if(map[j][i] == 100)
                    {
                        celX = i; celY = j;
                        map[j][i] = 101;
                        isFind = true;
                        break;
                    }
                }
            }
            if(!isFind)
            {
                kierunek = 4;
            }
        }
    }
}

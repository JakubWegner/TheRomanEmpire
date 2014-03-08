#include "player.h"

CPlayer player;

CPlayer::CPlayer()
{
    denary = 5000;
    populacja = 0;
    dzien = 1; miesiac = 1; rok = -200;
    wskOpinia = 100;
    nazwaMiasta = "Rzym";
}

void CPlayer::render()
{
    if(!pause)
        dzien += 0.005;
    if(dzien >= 31)
    {
        dzien = 1; miesiac++;
    }

    if(miesiac >= 13)
    {
        miesiac = 1; rok++;
    }
}

#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "main.h"

class CPlayer
{
public:
    int denary, populacja,
        dzien, miesiac, rok;
    int wskOpinia; // od 100 do -100

    string nazwaMiasta;

    CPlayer();
    void render();
};

extern CPlayer player;



#endif // PLAYER_H_INCLUDED

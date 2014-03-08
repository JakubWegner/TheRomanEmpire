#ifndef PEOPLE_H_INCLUDED
#define PEOPLE_H_INCLUDED

#include "main.h"
#include "map.h"
#include "player.h"

class CPeople
{
public:

    float x, y;
    int kierunek, frame;
    string type, cel;
    bool isLive;

    void render();
    virtual void update() = 0;
};

// ladowanie w pliku people_manager
extern ALLEGRO_BITMAP* IMG_pSettler;
extern ALLEGRO_BITMAP* IMG_pNormal;


#endif // PEOPLE_H_INCLUDED

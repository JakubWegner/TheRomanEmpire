#ifndef INTRO_H_INCLUDED
#define INTRO_H_INCLUDED

#include "main.h"
#include "input.h"

class CCircle
{
public:
    float x,y, w,h;
    ALLEGRO_COLOR col;
    CCircle(float,float, float,float, ALLEGRO_COLOR);
};

extern vector <CCircle> kola;

void createIntro();
void renderIntro(int&);



#endif // INTRO_H_INCLUDED

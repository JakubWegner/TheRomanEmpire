#ifndef PEOPLE_SETTLER_H_INCLUDED
#define PEOPLE_SETTLER_H_INCLUDED

#include "people.h"

/*
    Kolonizator - szuka wolnych domow i w nich zamieszkuje,
                  jezeli wskaznik imigracje-emigracje > 0,
                  inaczej wyprowadza sie z miasta lub mysli
                  nad ta decyzja.
*/

class CPeople_settler
    : public CPeople
{
public:

    CPeople_settler(int, int, int, int);
    void update();

    int celX, celY;
    int px, py;
};

extern vector <CPeople_settler> p_settler;


#endif // PEOPLE_SETTLER_H_INCLUDED

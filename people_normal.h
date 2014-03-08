#ifndef PEOPLE_NORMAL_H_INCLUDED
#define PEOPLE_NORMAL_H_INCLUDED

#include "people.h"

/*
    Normalny - po wybudowaniu budynku,
               walesa sie po miescie,
               robiac sztuczny tlum ;)
*/

class CPeople_normal
    : public CPeople
{
public:

    CPeople_normal(int, int, int);
    void update();
    int zmKi;
};

extern vector <CPeople_normal> p_normal;



#endif // PEOPLE_NORMAL_H_INCLUDED

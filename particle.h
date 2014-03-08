#ifndef PARTICLE_H_INCLUDED
#define PARTICLE_H_INCLUDED

#include "main.h"

class CParticle
{
public:
    float x, y, alpha;

    CParticle(int, int);
};

extern vector <CParticle> v_pHouseLvl;

void createParticle();
void renderParticle();


#endif // PARTICLE_H_INCLUDED

#include "particle.h"
#include "map.h"

vector <CParticle> v_pHouseLvl;

CParticle::CParticle(int txx, int tyy)
{
    x = (txx-tyy)*TILE_W/2 + map_x;
    y = (txx+tyy)*TILE_H/2 + map_y;

    x += TILE_W/2;
    y += TILE_H/2;

    x += rand()%100-50;
    y += rand()%50-25;

    alpha = 255;
}


ALLEGRO_BITMAP* IMG_particle[1];

void createParticle()
{
    IMG_particle[0] = loadBmp("media/particle.png");
}

void renderParticle()
{
    for(int i = 0; i < v_pHouseLvl.size(); ++i)
    {
        al_draw_tinted_scaled_bitmap(IMG_particle[0], al_map_rgba(255,255,255,v_pHouseLvl[i].alpha),
                                     0,0, getBmpW(IMG_particle[0]), getBmpH(IMG_particle[0]),
                                     v_pHouseLvl[i].x, v_pHouseLvl[i].y, 10,10, 0);

        if(!pause)
            v_pHouseLvl[i].alpha -= 1;
        //v_pHouseLvl[i].y--;

        if(v_pHouseLvl[i].alpha <= 0)
            v_pHouseLvl.erase(v_pHouseLvl.begin()+i);
    }
}

#include "people_manager.h"

ALLEGRO_BITMAP* IMG_pSettler,
              * IMG_pNormal;

void createPeople()
{
    IMG_pSettler = loadBmp("media/human1.png");
    IMG_pNormal = loadBmp("media/human2.png");
}

void renderPeople()
{
    for(int i = 0; i < p_settler.size(); ++i)
    {
        p_settler[i].render();
        p_settler[i].update();

        if(!p_settler[i].isLive)
            p_settler.erase(p_settler.begin() + i);
    }

    for(int i = 0; i < p_normal.size(); ++i)
    {
        p_normal[i].render();
        p_normal[i].update();

        if(!p_normal[i].isLive)
            p_normal.erase(p_normal.begin() + i);
    }
}

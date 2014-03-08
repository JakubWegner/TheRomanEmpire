#include "cornfield.h"
#include "map.h"

vector <CCornfield> v_cornfield;

CCornfield& getCornfield(int x, int y)
{
    for(int i = 0; i < v_cornfield.size(); ++i)
    {
        if(x == v_cornfield[i].x && y == v_cornfield[i].y)
            return v_cornfield[i];
    }

    CCornfield field(0,0);
    return field;
}

ALLEGRO_BITMAP* IMG_cornfiled[5];
void createCornfield()
{
    IMG_cornfiled[0] = loadBmp("media/corn/1.png");
    IMG_cornfiled[1] = loadBmp("media/corn/2.png");
    IMG_cornfiled[2] = loadBmp("media/corn/3.png");
    IMG_cornfiled[3] = loadBmp("media/corn/4.png");
    IMG_cornfiled[4] = loadBmp("media/corn/5.png");
}

int jakDlugo = 300;
void CCornfield::render(int posX,int posY, int zoomX,int zoomY)
{
    if(time <= jakDlugo/2)
        al_draw_scaled_bitmap(IMG_cornfiled[0], 0,0,150,100, posX-50, posY-75, zoomX+100, zoomY+100, 0);
    else if(time > jakDlugo/2 && time <= jakDlugo*2)
        al_draw_scaled_bitmap(IMG_cornfiled[1], 0,0,150,100, posX-50, posY-75, zoomX+100, zoomY+100, 0);
    else if(time > jakDlugo*2 && time <= jakDlugo*3)
        al_draw_scaled_bitmap(IMG_cornfiled[2], 0,0,150,100, posX-50, posY-75, zoomX+100, zoomY+100, 0);
    else if(time > jakDlugo*3 && time <= jakDlugo*4)
        al_draw_scaled_bitmap(IMG_cornfiled[3], 0,0,150,100, posX-50, posY-75, zoomX+100, zoomY+100, 0);
    else
        al_draw_scaled_bitmap(IMG_cornfiled[4], 0,0,150,100, posX-50, posY-75, zoomX+100, zoomY+100, 0);
}

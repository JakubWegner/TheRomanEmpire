#include "people.h"

/*
    KIERUNEK

    1 - prawy gorny rog
    2 - lewy gorny rog
    3 - prawy dolny rog
    4 - lewy dolny rog

*/

void CPeople::render()
{
    frame++;
    if(frame > 30)
        frame = 0;

    if(kierunek == 0)
    {
        if(type == "settler")
            al_draw_bitmap_region(IMG_pSettler, 0,0, 50,50, x+map_x,y+map_y, 0);

        if(type == "normal")
            al_draw_bitmap_region(IMG_pNormal, 0,50, 50,50, x+map_x,y+map_y, 0);
    }
    else if(kierunek == 1)
    {
        if(!pause) {
            y -= 0.5;
            x += 1.0;
        }

        if(type == "settler")
            al_draw_bitmap_region(IMG_pSettler, 0,0, 50,50, x+map_x,y+map_y, 0);

        if(type == "normal")
        {
            if(frame <= 15)
                al_draw_bitmap_region(IMG_pNormal, 0,0, 50,50, x+map_x,y+map_y, ALLEGRO_FLIP_HORIZONTAL);
            else
                al_draw_bitmap_region(IMG_pNormal, 50,0, 50,50, x+map_x,y+map_y, ALLEGRO_FLIP_HORIZONTAL);
        }
    }
    else if(kierunek == 2)
    {
        if(!pause) {
            y -= 0.5;
            x -= 1.0;
        }

        if(type == "settler")
            al_draw_bitmap_region(IMG_pSettler, 0,0, 50,50, x+map_x,y+map_y, ALLEGRO_FLIP_HORIZONTAL);

        if(type == "normal")
        {
            if(frame <= 15)
                al_draw_bitmap_region(IMG_pNormal, 0,0, 50,50, x+map_x,y+map_y, 0);
            else
                al_draw_bitmap_region(IMG_pNormal, 50,0, 50,50, x+map_x,y+map_y, 0);
        }
    }
    else if(kierunek == 3)
    {
        if(!pause) {
            y += 0.5;
            x += 1.0;
        }

        if(type == "settler")
            al_draw_bitmap_region(IMG_pSettler, 50,0, 50,50, x+map_x,y+map_y, 0);

        if(type == "normal")
        {
            if(frame <= 15)
                al_draw_bitmap_region(IMG_pNormal, 0,50, 50,50, x+map_x,y+map_y, 0);
            else
                al_draw_bitmap_region(IMG_pNormal, 50,50, 50,50, x+map_x,y+map_y, 0);
        }
    }
    else if(kierunek == 4)
    {
        if(!pause) {
            y += 0.5;
            x -= 1.0;
        }

        if(type == "settler")
            al_draw_bitmap_region(IMG_pSettler, 50,0, 50,50, x+map_x,y+map_y, ALLEGRO_FLIP_HORIZONTAL);

        if(type == "normal")
        {
            if(frame <= 15)
                al_draw_bitmap_region(IMG_pNormal, 0,50, 50,50, x+map_x,y+map_y, ALLEGRO_FLIP_HORIZONTAL);
            else
                al_draw_bitmap_region(IMG_pNormal, 50,50, 50,50, x+map_x,y+map_y, ALLEGRO_FLIP_HORIZONTAL);
        }
    }
    else
    {
        if(type == "settler")
            al_draw_bitmap_region(IMG_pSettler, 50,0, 50,50, x+map_x,y+map_y, ALLEGRO_FLIP_HORIZONTAL);
        if(type == "normal")
            al_draw_bitmap_region(IMG_pNormal, 0,50, 50,50, x+map_x,y+map_y, ALLEGRO_FLIP_HORIZONTAL);
    }

    int tx = screen2iso_x((x+25),(y+25));
    int ty = screen2iso_y((x+25),(y+25));
    if(tx >= MAP_W || ty >= MAP_H)
        isLive = false;
}

#include "people_normal.h"

vector <CPeople_normal> p_normal;

CPeople_normal::CPeople_normal(int px, int py, int kier)
{
    type = "normal";

    x = (px-py)*TILE_W/2;
    y = (px+py)*TILE_H/2;

    isLive = true;

    kierunek = kier;
    zmKi = 0;
}

void CPeople_normal::update()
{
    if(zmKi >= 0)
        zmKi--;

    //cout << "\nZmKi: " << zmKi << ", kier: " << kierunek;

    if(kierunek == 1)
    {
        if(map[screen2iso_y(x+25, y+25)][screen2iso_x(x+25, y+25)] != 50)
        {
            if(map[screen2iso_y(x-30, y)][screen2iso_x(x-30, y)] == 50 && zmKi <= 0) {
                kierunek = 2; zmKi = 40;
            }

            if(map[screen2iso_y(x+30, y+60)][screen2iso_x(x+30, y+60)] == 50 && zmKi <= 0) {
                kierunek = 3; zmKi = 40;
            }

            if(map[screen2iso_y(x-30, y+60)][screen2iso_x(x-30, y+60)] == 50 && zmKi <= 0) {
                kierunek = 4; zmKi = 40;
            }
        }
    }

    if(kierunek == 2)
    {
        //map[screen2iso_y(x+45, y)][screen2iso_x(x+50, y)] = -1;

        if(map[screen2iso_y(x+25, y+25)][screen2iso_x(x+25, y+25)] != 50)
        {
           if(map[screen2iso_y(x-50, y+60)][screen2iso_x(x-50, y+60)] == 50 && zmKi <= 0) {
                kierunek = 4; zmKi = 40;
            }

            if(map[screen2iso_y(x+50, y)][screen2iso_x(x+50, y)] == 50 && zmKi <= 0) {
                kierunek = 1; zmKi = 40;
            }

            /*if(map[screen2iso_y(x-26, y-14)][screen2iso_x(x-26, y-14)] == 50 && zmKi <= 0) {
                kierunek = 3; zmKi = 40;
            }*/
        }
    }

    /*if(kierunek == 2)
    {
        int tx = screen2iso_x(x,y-50);
        int ty = screen2iso_y(x,y-50);

        int tx2 = screen2iso_x(x,y-25);
        int ty2 = screen2iso_y(x,y-25);

        if(map[ty][tx] != 50)
        {
            if(map[ty2-1][tx2] == 50)
                kierunek = 1;
            else if(map[ty2+1][tx2] == 50)
                kierunek = 4;
            else if(map[ty2][tx2+1] == 50)
                kierunek = 3;
           // else
           //     kierunek = 0;
        }

        //map[ty][tx] = 10;
    }
    if(kierunek == 3)
    {
        int tx = screen2iso_x(x,y+50);
        int ty = screen2iso_y(x,y+50);

        int tx2 = screen2iso_x(x,y+25);
        int ty2 = screen2iso_y(x,y+25);

        if(map[ty][tx] != 50)
        {
            if(map[ty2-1][tx2] == 50)
                kierunek = 1;
            else if(map[ty2+1][tx2] == 50)
                kierunek = 4;
            else if(map[ty2][tx2-1] == 50)
                kierunek = 2;
           // else
           //     kierunek = 0;
        }

        //map[ty][tx] = -1;
    }
    if(kierunek == 4)
    {
        int tx = screen2iso_x(x+50,y);
        int ty = screen2iso_y(x+50,y);

        int tx2 = screen2iso_x(x+25,y);
        int ty2 = screen2iso_y(x+25,y);

        /*if(map[ty][tx] != 50)
        {
            if(map[ty2][tx2-1] == 50)
                kierunek = 2;
            else if(map[ty2][tx2+1] == 50)
                kierunek = 3;
            else if(map[ty2-1][tx2] == 50)
                kierunek = 1;
           // else
           //     kierunek = 0;
        }*/

        //map[ty][tx] = -1;
    //}
}

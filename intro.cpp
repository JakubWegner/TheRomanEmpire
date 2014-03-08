#include "intro.h"

ALLEGRO_FONT* fontintro;
ALLEGRO_BITMAP* IMG_seaIcon,* IMG_ekran1;

vector <CCircle> kola;

CCircle::CCircle(float x, float y, float w, float h, ALLEGRO_COLOR c)
    : x(x), y(y), w(w), h(h), col(c)
{
}

void createIntro()
{
    fontintro = al_load_font("media/font.ttf", 30, 0);
    IMG_seaIcon = loadBmp("media/seaIcon.png");
    IMG_ekran1 = loadBmp("media/ekran1.png");

    //kola.push_back(CCircle(50,50, 200,200, al_map_rgb(255,255,255)));

}

float times = 0, speed = 1, speed2 = 0;
int napisX = 770, obrazekX = -10;
int ekran = 0;

extern CMouse mouse;
void renderIntro(int &gameState)
{
    if(ekran == 0)
    {
        times++;
        if(times == 60) kola.push_back(CCircle(1024/2-400, 768/2-400-100, 200,200, al_map_rgb(0,0,0)));
        if(times == 60) kola.push_back(CCircle(1024/2+400, 768/2-400-100, 200,200, al_map_rgb(0,0,0)));
        if(times == 60) kola.push_back(CCircle(1024/2-400, 768/2+400-100, 200,200, al_map_rgb(0,0,0)));
        if(times == 60) kola.push_back(CCircle(1024/2+400, 768/2+400-100, 200,200, al_map_rgb(0,0,0)));

        for(int i = 0; i < kola.size(); ++i)
        {
            //if(times < 50+60)
            if(times < 50+60)
            {
                if(kola[i].x > 1024/2)
                    kola[i].x-=speed;
                else
                    kola[i].x+=speed;

                if(kola[i].y > 768/2)
                    kola[i].y-=speed;
                else
                    kola[i].y+=speed;

                if(kola[i].w > 30)
                    kola[i].w-=speed/2;

                speed += 0.05;
            }
            else
            {
                /*if(speed > 0) {
                    speed -= 0.09;
                    kola[i].x += cos(speed);
                }*/

                //kola[i].x += 2*cos(speed2);
                //kola[i].y += 2*sin(speed2);

                speed += 0.005;

                if(napisX >= 1024/2-al_get_text_width(fontintro, "SeaMonster131 prezentuje...")/2)
                    napisX-=speed-2;

                if(obrazekX < 768/2-120)
                    obrazekX += speed/5;
                else
                {
                    if(speed2 >= 350)
                    {
                        kola[i].w += speed;
                        if(kola[i].w >= 500)
                        {
                            ekran = 1;
                            speed = 0;
                        }
                    }
                    else
                        speed2++;
                }

                al_draw_bitmap(IMG_seaIcon, 1024/2-55, obrazekX, 0);

                al_draw_text(fontintro, al_map_rgb(0,0,0), napisX, 768-200, 0, "SeaMonster131 prezentuje...");
            }

            al_draw_filled_circle(kola[i].x, kola[i].y, kola[i].w, kola[i].col);
        }
    }
    else if(ekran == 1)
    {
        al_draw_scaled_bitmap(IMG_ekran1, 0,0, getBmpW(IMG_ekran1),getBmpH(IMG_ekran1), 0,0, 1024,768, 0);

        int alpha = 355*cos(speed);
        if(alpha > 255)
            alpha = 255;
        if(alpha < 0)
            alpha = 0;

        al_draw_text(fontintro, al_map_rgba(0,0,0, alpha), 15,768-30, 0, "Kliknij myszka, by przejsc dalej");

        speed+=0.06;

        if(mouse.Press(1) || mouse.Press(2))
            gameState = 0;
    }
}

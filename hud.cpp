#include "hud.h"
#include "map.h"

ALLEGRO_BITMAP* IMG_hud[4];
ALLEGRO_BITMAP* IMG_buildMenu[2];


ALLEGRO_BITMAP* IMG_kategoriaBud[8];
ALLEGRO_BITMAP* IMG_hudPause;

ALLEGRO_BITMAP* IMG_cir,
              * IMG_shovel,
              * IMG_window;

ALLEGRO_FONT* fonthud;

void createHud()
{

    IMG_hud[0] = loadBmp("media/hud1.png");
    IMG_hud[1] = loadBmp("media/minimap.png");
    IMG_hud[2] = loadBmp("media/hud3.png");
    IMG_hud[3] = loadBmp("media/hud4.png");

    IMG_buildMenu[0] = loadBmp("media/hud_buildMenu.png");
    IMG_buildMenu[1] = loadBmp("media/hud_buildMenu_click.png");


    IMG_kategoriaBud[0] = loadBmp("media/kat1.png");
    IMG_kategoriaBud[1] = loadBmp("media/kat2.png");
    IMG_kategoriaBud[2] = loadBmp("media/kat3.png");
    IMG_kategoriaBud[3] = loadBmp("media/kat4.png");
    IMG_kategoriaBud[4] = loadBmp("media/kat5.png");
    IMG_kategoriaBud[5] = loadBmp("media/kat6.png");
    IMG_kategoriaBud[6] = loadBmp("media/kat7.png");
    IMG_kategoriaBud[7] = loadBmp("media/kat8.png");

    IMG_cir = loadBmp("media/kat.png");
    IMG_shovel = loadBmp("media/shovel.png");
    IMG_window = loadBmp("media/window.png");

    IMG_hudPause = loadBmp("media/hud_pause.png");

    fonthud = al_load_font("media/font.ttf", 16, 0);
}


bool keyPause_click = false, pause = false,
     mouse2click = false;
int menuCx, menuCy,
    alpha;
int wysMenu = -1;
int scalX, scalY;
string textWindow[5];
void renderHud(CMouse mouse, CKeyboard key)
{
    if(key.Press(ALLEGRO_KEY_P) && !keyPause_click)
    {
        pause = !pause;
        keyPause_click = true;
    }
    if(!key.Press(ALLEGRO_KEY_P) && keyPause_click)
        keyPause_click = false;
    if(pause)
        al_draw_bitmap(IMG_hudPause, WIN_W/2-getBmpW(IMG_hudPause)/2, 50, 0);

    //al_draw_bitmap(IMG_hud[3], WIN_W-getBmpW(IMG_hud[3]), 0, ALLEGRO_FLIP_HORIZONTAL);

    al_draw_scaled_bitmap(IMG_minimap, 0,0, MAP_W,MAP_H, WIN_W-200+25,53, 150,170, 0);
    al_draw_scaled_bitmap(IMG_hud[1], 0,0, 234,256,  WIN_W-200,0, 200,220, 0);
    al_draw_text(fonthud, al_map_rgb(0,0,0), WIN_W-100,35, ALLEGRO_ALIGN_CENTER, player.nazwaMiasta.c_str());

    if(mouse.Press(2) && !mouse2click && !mouseClick)
    {
        if(wysunieteMenu == -1)
        {
            wysunieteMenu = 1; wysMenu = -1;
            alpha = 0;
            //menuCx = mouse.getX();
            //menuCy = mouse.getY();
            menuCx = WIN_W/2;
            menuCy = WIN_H/2;

            // TODO - zeby menu bylo cale na oknie, a nie troche poza
        }
        else
            wysunieteMenu = -1;

        mouse2click = true;
    }
    if(!mouse.Press(2) && mouse2click)
        mouse2click = false;

    if(wysunieteMenu != -1) // menu
    {
        if(alpha < 230)
            alpha += 15;

        //al_draw_circle(menuCx, menuCy, 110, al_map_rgba(200,200,200, alpha), 3);
        al_draw_circle(menuCx, menuCy, 110, al_map_rgba(50,50,50, 50), 3);
        //al_draw_tinted_scaled_bitmap(IMG_cir, al_map_rgba(255,255,255,alpha), 0,0, 150,150, menuCx-250/2, menuCy-250/2, 250,250, 0);

        al_draw_tinted_bitmap(IMG_kategoriaBud[0], al_map_rgba(255,255,255,alpha), menuCx-95/2, menuCy-110-91/2, 0);
        al_draw_tinted_bitmap(IMG_kategoriaBud[1], al_map_rgba(255,255,255,alpha), menuCx+80-95/2, menuCy-80-91/2, 0);
        al_draw_tinted_bitmap(IMG_kategoriaBud[2], al_map_rgba(255,255,255,alpha), menuCx+110-95/2, menuCy-91/2, 0);
        al_draw_tinted_bitmap(IMG_kategoriaBud[3], al_map_rgba(255,255,255,alpha), menuCx+80-95/2, menuCy+80-91/2, 0);
        al_draw_tinted_bitmap(IMG_kategoriaBud[4], al_map_rgba(255,255,255,alpha), menuCx-95/2, menuCy+110-91/2, 0);
        al_draw_tinted_bitmap(IMG_kategoriaBud[5], al_map_rgba(255,255,255,alpha), menuCx-80-95/2, menuCy+80-91/2, 0);
        al_draw_tinted_bitmap(IMG_kategoriaBud[6], al_map_rgba(255,255,255,alpha), menuCx-110-95/2, menuCy-91/2, 0);
        al_draw_tinted_bitmap(IMG_kategoriaBud[7], al_map_rgba(255,255,255,alpha), menuCx-80-95/2, menuCy-80-91/2, 0);

        if( pow(mouse.getX()-(menuCx), 2)+pow(mouse.getY()-(menuCy-110), 2) <= pow(78/2, 2) )
        {
            al_draw_filled_circle(menuCx, menuCy-110, 76/2, al_map_rgba(50,50,50, 30));

            if(mouse.Press(1) && !mouseClick) {
                wysMenu = 1;
                scalX = scalY = 0;
                mouseClick = true;
            }
        }
        else if( pow(mouse.getX()-(menuCx+80), 2)+pow(mouse.getY()-(menuCy-80), 2) <= pow(78/2, 2) )
        {
            al_draw_filled_circle(menuCx+80, menuCy-80, 76/2, al_map_rgba(50,50,50, 30));

            if(mouse.Press(1) && !mouseClick) {
                wysMenu = 2;
                scalX = scalY = 0;
                mouseClick = true;
            }
        }
        else if( pow(mouse.getX()-(menuCx+110), 2)+pow(mouse.getY()-(menuCy), 2) <= pow(78/2, 2) )
        {
            al_draw_filled_circle(menuCx+110, menuCy, 76/2, al_map_rgba(50,50,50, 30));

            if(mouse.Press(1) && !mouseClick) {
                wysMenu = 3;
                scalX = scalY = 0;
                mouseClick = true;
            }
        }
        else if( pow(mouse.getX()-(menuCx+80), 2)+pow(mouse.getY()-(menuCy+80), 2) <= pow(78/2, 2) )
        {
            al_draw_filled_circle(menuCx+80, menuCy+80, 76/2, al_map_rgba(50,50,50, 30));

            if(mouse.Press(1) && !mouseClick) {
                wysMenu = 4;
                scalX = scalY = 0;
                mouseClick = true;
            }
        }
        else if( pow(mouse.getX()-(menuCx), 2)+pow(mouse.getY()-(menuCy+110), 2) <= pow(78/2, 2) )
        {
            al_draw_filled_circle(menuCx, menuCy+110, 76/2, al_map_rgba(50,50,50, 30));

            if(mouse.Press(1) && !mouseClick) {
                wysMenu = 5;
                scalX = scalY = 0;
                mouseClick = true;
            }
        }
        else if( pow(mouse.getX()-(menuCx-80), 2)+pow(mouse.getY()-(menuCy+80), 2) <= pow(78/2, 2) )
        {
            al_draw_filled_circle(menuCx-80, menuCy+80, 76/2, al_map_rgba(50,50,50, 30));

            if(mouse.Press(1) && !mouseClick) {
                wysMenu = 6;
                scalX = scalY = 0;
                mouseClick = true;
            }
        }
        else if( pow(mouse.getX()-(menuCx-110), 2)+pow(mouse.getY()-(menuCy), 2) <= pow(78/2, 2) )
        {
            al_draw_filled_circle(menuCx-110, menuCy, 76/2, al_map_rgba(50,50,50, 30));

            if(mouse.Press(1) && !mouseClick) {
                wysMenu = 7;
                scalX = scalY = 0;
                mouseClick = true;
            }
        }
        else if( pow(mouse.getX()-(menuCx-80), 2)+pow(mouse.getY()-(menuCy-80), 2) <= pow(78/2, 2) )
        {
            al_draw_filled_circle(menuCx-80, menuCy-80, 76/2, al_map_rgba(50,50,50, 30));

            if(mouse.Press(1) && !mouseClick) {
                wysMenu = 8;
                scalX = scalY = 0;
                mouseClick = true;
            }
        }
        else
        {
            if(wysMenu == -1)
            {
                if(mouse.Press(1))
                    wysunieteMenu = -1;
            }
        }


        if(wysMenu != -1)
        {
            if(scalX < 100)
                scalX += 15;
            else
                scalX = 100;
            if(scalY < 100)
                scalY += 15;
            else
                scalY = 100;

            al_draw_circle(menuCx, menuCy, 210, al_map_rgba(50,50,50, 50), 2);

            al_draw_scaled_bitmap(IMG_window, 0,0, 302,145, WIN_W/2-500/2, WIN_H-getBmpH(IMG_window), 500,145, 0);

            if(textWindow[0] == "")
                textWindow[0] = "Tablica z informacjami.";

            al_draw_text(fonthud, al_map_rgb(0,0,0), WIN_W/2-450/2, WIN_H-130, 0, textWindow[0].c_str());
            al_draw_text(fonthud, al_map_rgb(0,0,0), WIN_W/2+450/2, WIN_H-130, 2, textWindow[1].c_str());

            al_draw_text(fonthud, al_map_rgb(0,0,0), WIN_W/2-460/2, WIN_H-100, 0, textWindow[2].c_str());
            al_draw_text(fonthud, al_map_rgb(0,0,0), WIN_W/2-460/2, WIN_H-80, 0, textWindow[3].c_str());
            al_draw_text(fonthud, al_map_rgb(0,0,0), WIN_W/2-460/2, WIN_H-60, 0, textWindow[4].c_str());

            textWindow[0] = textWindow[1] = textWindow[2] = textWindow[3] = textWindow[4] = "";
        }

        if(wysMenu == 1)
        {
            al_draw_scaled_bitmap(IMG_cir, 0,0, 95,91, menuCx-120/2, menuCy-210-110/2, scalX+20,scalY+10, 0);
            al_draw_scaled_bitmap(IMG_house[0], 0,0, 100,50, menuCx-90/2, menuCy-210-40/2, scalX-10,scalY/2-10, 0);

            if( pow(mouse.getX()-(menuCx-2), 2)+pow(mouse.getY()-(menuCy-2-210), 2) <= pow(90/2, 2) )
            {
                al_draw_filled_circle(menuCx-2, menuCy-2-210, 90/2, al_map_rgba(50,50,50, 30));

                textWindow[0] = "Dom";
                textWindow[1] = "0 Dn";
                textWindow[2] = "Zbuduj domy, by ludzie mogli przyjsc i osiedlic sie";
                textWindow[3] = "w Twoim miescie!";

                if(mouse.Press(1)) {
                    activeID = 100;
                    wysunieteMenu = -1;
                    mouseClick = true;
                }
            }
        }
        if(wysMenu == 2)
        {
            al_draw_scaled_bitmap(IMG_cir, 0,0, 95,91, menuCx-120/2, menuCy-210-110/2, scalX+20,scalY+10, 0);
            al_draw_scaled_bitmap(IMG_shovel, 0,0, 100,50, menuCx-90/2, menuCy-210-40/2, scalX-10,scalY/2-10, 0);

            al_draw_scaled_bitmap(IMG_cir, 0,0, 95,91, menuCx+150-120/2, menuCy-150-110/2, scalX+20,scalY+10, 0);
            al_draw_scaled_bitmap(IMG_road[0], 0,0, 100,50, menuCx+150-90/2, menuCy-150-40/2, scalX-10,scalY/2-10, 0);

            if( pow(mouse.getX()-(menuCx-2), 2)+pow(mouse.getY()-(menuCy-2-210), 2) <= pow(90/2, 2) )
            {
                al_draw_filled_circle(menuCx-2, menuCy-2-210, 90/2, al_map_rgba(50,50,50, 30));

                textWindow[0] = "Wyczysc teren";
                textWindow[1] = "2 Dn";
                textWindow[2] = "Zlec robotnikom wyczyszczenie terenu pod przyszle";
                textWindow[3] = "budowle lub usun istniejace.";

                if(mouse.Press(1)) {
                    activeID = 0;
                    wysunieteMenu = -1;
                    mouseClick = true;
                }
            }
            if( pow(mouse.getX()-(menuCx-2+150), 2)+pow(mouse.getY()-(menuCy-2-150), 2) <= pow(90/2, 2) )
            {
                al_draw_filled_circle(menuCx-2+150, menuCy-2-150, 90/2, al_map_rgba(50,50,50, 30));

                textWindow[0] = "Droga";
                textWindow[1] = "5 Dn";
                textWindow[2] = "Wszystkie drogi prowadza do Rzymu!";
                textWindow[3] = "Bez drogi zaden budynek nie bedzie funkcjonowac,";
                textWindow[4] = "a ludzie beda niezadowoleni.";

                if(mouse.Press(1)) {
                    activeID = 50;
                    wysunieteMenu = -1;
                    mouseClick = true;
                }
            }
        }
        if(wysMenu == 3)
        {
            al_draw_scaled_bitmap(IMG_cir, 0,0, 95,91, menuCx-120/2, menuCy-210-110/2, scalX+20,scalY+10, 0);
            al_draw_scaled_bitmap(IMG_building[0], 0,0, 100,50, menuCx-90/2, menuCy-210-40/2, scalX-10,scalY/2-10, 0);

            al_draw_scaled_bitmap(IMG_cir, 0,0, 95,91, menuCx+150-120/2, menuCy-150-110/2, scalX+20,scalY+10, 0);
            al_draw_scaled_bitmap(IMG_building[1], 0,0, 100,50, menuCx+150-90/2, menuCy-150-40/2, scalX-10,scalY/2-10, 0);

            if( pow(mouse.getX()-(menuCx-2), 2)+pow(mouse.getY()-(menuCy-2-210), 2) <= pow(90/2, 2) )
            {
                al_draw_filled_circle(menuCx-2, menuCy-2-210, 90/2, al_map_rgba(50,50,50, 30));

                textWindow[0] = "Prefektura";
                textWindow[1] = "50 Dn";
                textWindow[2] = "Prefektura zapewni porzadek w Twoim miescie,";
                textWindow[3] = "ugasi pozary, a takze zlapie zloczyncow!";

                if(mouse.Press(1)) {
                    activeID = 200;
                    wysunieteMenu = -1;
                    mouseClick = true;
                }
            }
            if( pow(mouse.getX()-(menuCx-2+150), 2)+pow(mouse.getY()-(menuCy-2-150), 2) <= pow(90/2, 2) )
            {
                al_draw_filled_circle(menuCx-2+150, menuCy-2-150, 90/2, al_map_rgba(50,50,50, 30));

                textWindow[0] = "Studnia";
                textWindow[1] = "25 Dn";
                textWindow[2] = "Studnia zapewnia biezaca wode okolicznym";
                textWindow[3] = "mieszkancom, lecz brzydko wyglada.";

                if(mouse.Press(1)) {
                    activeID = 201;
                    wysunieteMenu = -1;
                    mouseClick = true;
                }
            }
        }
        /// ...........................................
        if(wysMenu == 8)
        {
            al_draw_scaled_bitmap(IMG_cir, 0,0, 95,91, menuCx-120/2, menuCy-210-110/2, scalX+20,scalY+10, 0);
            al_draw_scaled_bitmap(IMG_building[2], 0,0, 100,50, menuCx-90/2, menuCy-210-40/2, scalX-10,scalY/2-10, 0);

            if( pow(mouse.getX()-(menuCx-2), 2)+pow(mouse.getY()-(menuCy-2-210), 2) <= pow(90/2, 2) )
            {
                al_draw_filled_circle(menuCx-2, menuCy-2-210, 90/2, al_map_rgba(50,50,50, 30));

                textWindow[0] = "Farma zboza";
                textWindow[1] = "123.123.210 Dn";
                textWindow[2] = "Zbuduj domy, by ludzie mogli przyjsc i osiedlic sie";
                textWindow[3] = "w Twoim miescie!";
                textWindow[4] = "asdsadasdsadsadsadsadsad";

                if(mouse.Press(1)) {
                    activeID = 202;
                    wysunieteMenu = -1;
                    mouseClick = true;
                }
            }
        }
    }
}


/*bool keyPause_click = false; bool pause = false;*/
int Min = 0, Max = 0;
void renderHud2(CMouse mouse, CKeyboard key)
{
    //al_draw_bitmap(IMG_hud[1], 1024-getBmpW(IMG_hud[1]), 0, 0); // mapa
    al_draw_bitmap(IMG_hud[0], 1024-getBmpW(IMG_hud[0]), getBmpH(IMG_hud[1]), 0); // panel boczny
    //al_draw_bitmap(IMG_hud[2], 1024-getBmpW(IMG_hud[2]), 768-getBmpH(IMG_hud[2])+3, 0); // doradcy i mapa
    for(int i = 0; i < 3; ++i) al_draw_bitmap(IMG_hud[3], i*getBmpW(IMG_hud[3]),0, 0); // kasa, populacja, rok

    al_draw_scaled_bitmap(IMG_minimap, 0,0, MAP_W,MAP_H, WIN_W-200+25,53, 150,170, 0);
    al_draw_scaled_bitmap(IMG_hud[1], 0,0, 234,256,  WIN_W-200,0, 200,220, 0);
    al_draw_text(fonthud, al_map_rgb(0,0,0), WIN_W-100,35, ALLEGRO_ALIGN_CENTER, player.nazwaMiasta.c_str());

    al_draw_textf(fonthud, al_map_rgb(255,255,255), 20, 15, 0,"Dn %d", player.denary);
    al_draw_textf(fonthud, al_map_rgb(255,255,255), getBmpW(IMG_hud[3])+20, 15, 0,"Pop %d", player.populacja);
    if(player.rok < 0)
    {
        int rok = player.rok * -1;
        al_draw_textf(fonthud, al_map_rgb(255,255,255), 2*getBmpW(IMG_hud[3])+20, 15, 0,"%d.%d.%d pne", player.dzien, player.miesiac, rok);
    }
    else
    {
        al_draw_textf(fonthud, al_map_rgb(255,255,255), 2*getBmpW(IMG_hud[3])+20, 15, 0,"%d.%d.%d ne", player.dzien, player.miesiac, player.rok);
    }

    if(mouse.getX() >= 1024-getBmpW(IMG_hud[0]) && mouse.getY() >= getBmpH(IMG_hud[1]) && mouse.getY() <= getBmpH(IMG_hud[1])+getBmpH(IMG_hud[0]))
    {
        // wybieranie opcji z panelu bocznego
        for(int i = 0; i < 13; ++i)
        {
            if(mouse.getY() >= getBmpH(IMG_hud[1])+10+i*34 && mouse.getY() <= getBmpH(IMG_hud[1])+10+i*34+30+i/1.2)
            {
                al_draw_filled_rectangle(1024-getBmpW(IMG_hud[0]),getBmpH(IMG_hud[1])+10+i*34, 1024-9,getBmpH(IMG_hud[1])+10+i*34+30+i/1.2, al_map_rgba(0,0,0, 100));
                if(mouse.Press(1))
                {
                    wysunieteMenu = i;
                    break;
                }
            }
        }
    }

    // wybieranie konkretnych budynkow
    if(wysunieteMenu >= 0)
    {
        if(wysunieteMenu == 0) { Min = 0; Max = 3; }
        if(wysunieteMenu == 1) { Min = 4; Max = 4; }
        if(wysunieteMenu == 2) { Min = 5; Max = 5; }
        if(wysunieteMenu == 3) { Min = 6; Max = 6; }
        if(wysunieteMenu == 4) { Min = 7; Max = 10; }
        if(wysunieteMenu == 5) { Min = 11; Max = 12; }
        if(wysunieteMenu == 6) { Min = 13; Max = 13; }
        if(wysunieteMenu == 7) { Min = 14; Max = 16; }
        if(wysunieteMenu == 8) { Min = 17; Max = 18; }
        if(wysunieteMenu == 9) { Min = 19; Max = 19; }
        if(wysunieteMenu == 10) { Min = 20; Max = 20; }
        if(wysunieteMenu == 11) { Min = 21; Max = 21; }
        if(wysunieteMenu == 12) { Min = 22; Max = 26; }

        int a = 0;
        for(int i = Min; i <= Max; ++i)
        {
            if(mouse.getX() >= 1024-288-getBmpW(IMG_hud[0]) && mouse.getX() <= 1024-52 &&
               mouse.getY() >= getBmpH(IMG_hud[1])+10+wysunieteMenu*34.7+a*23 &&
               mouse.getY() <= getBmpH(IMG_hud[1])+10+wysunieteMenu*34.7+a*23+23)
            {
                al_draw_bitmap(IMG_buildMenu[1], 1024-288-getBmpW(IMG_hud[0]), getBmpH(IMG_hud[1])+10+wysunieteMenu*34.7+a*23, 0);

                al_draw_text(fonthud, al_map_rgb(255,255,255), 1024-280-getBmpW(IMG_hud[0]), getBmpH(IMG_hud[1])+13+wysunieteMenu*34.7+a*23, 0, opisID[i].c_str());

                if(mouse.Press(1) && !pause && !mouseClick)
                {
                    if(i == 0) { /* zapis gry */ }
                    if(i == 1) { /* wczytaj gre */ }
                    if(i == 2) { /* ustawienia */ }
                    if(i == 3) { /* wyjscie */ exit(0); }

                    if(i == 4) { /* zbuduj dom */   activeID = 100; }

                    if(i == 5) { /* wyczysc pole */ activeID = 0; }

                    if(i == 6) { /* zbuduj droge */ activeID = 50; }

                    if(i == 7) { /* studnia */ activeID = 201; }
                    if(i == 8) { /* fontanna */ }
                    if(i == 9) { /* rezerwuar */ }
                    if(i == 10) { /* adwedukt */ }

                    if(i == 11) { /* laznia */ }
                    if(i == 12) { /* szpital */ }

                    if(i == 13) { /* swiatynia wenus */ }

                    if(i == 14) { /* szkola */ }
                    if(i == 15) { /* szkola aktorow */ }
                    if(i == 16) { /* szkola gladiatorow */ }

                    if(i == 17) { /* teatr */ }
                    if(i == 18) { /* koloseum */ }

                    if(i == 19) { /* senat */ }

                    if(i == 20) { /* dom inzyniera */ }

                    if(i == 21) { /* prefektura */ activeID = 200; }

                    if(i == 22) { /* uprawa pola */ activeID = 202; }
                    if(i == 23) { /* pole zboza */ activeID = 203; }
                    if(i == 24) { /*      owocow */ }
                    if(i == 25) { /* stragan */ }
                    if(i == 26) { /* spichlerz */ }

                    wysunieteMenu = -1;
                    mouseClick = true;
                    break;
                }
            }
            else
            {
                al_draw_bitmap(IMG_buildMenu[0], 1024-288-getBmpW(IMG_hud[0]), getBmpH(IMG_hud[1])+10+wysunieteMenu*34.7+a*23, 0);

                al_draw_text(fonthud, al_map_rgb(255,255,255), 1024-280-getBmpW(IMG_hud[0]), getBmpH(IMG_hud[1])+13+wysunieteMenu*34.7+a*23, 0, opisID[i].c_str());
                if(mouse.Press(1) && mouse.getX() < 1024-52 && !pause)
                {
                    bool moznaZamknac = true;
                    int b = 0;
                    for(int j = Min; j <= Max; ++j)
                    {
                        if(mouse.getX() >= 1024-288-getBmpW(IMG_hud[0]) && mouse.getX() <= 1024-52 &&
                           mouse.getY() >= getBmpH(IMG_hud[1])+10+wysunieteMenu*34.7+b*23 &&
                           mouse.getY() <= getBmpH(IMG_hud[1])+10+wysunieteMenu*34.7+b*23+23)
                        {
                            moznaZamknac = false;
                            break;
                        }

                        b++;
                    }

                    if(moznaZamknac)
                    {
                        activeID = -1; wysunieteMenu = -1;
                    }
                }
            }
            ++a;
        }
    }

    if(key.Press(ALLEGRO_KEY_P) && !keyPause_click)
    {
        pause = !pause;
        keyPause_click = true;
    }
    if(!key.Press(ALLEGRO_KEY_P) && keyPause_click)
        keyPause_click = false;
    if(pause)
        al_draw_bitmap(IMG_hudPause, WIN_W/2-getBmpW(IMG_hudPause)/2, 50, 0);
}

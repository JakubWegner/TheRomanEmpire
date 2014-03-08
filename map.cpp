#include "people_settler.h"
#include "people_normal.h"
#include "house.h"
#include "cornfield.h"
#include "farm.h"

int map[500][500];
//int mapWidocznosc[500][500];
int mapKolizje[500][500];
int MAP_W = 35, MAP_H = 35,
    TILE_W = 100, TILE_H = 50;
int startX, startY;
int startX2, startY2;

int zoomX = 100, zoomY = 50;

int coIleOsadnik[2] = { 0, 40 };
int coIleLudz[2] = { 0, 10 };

vector <CPoint> pkt; // do pkt przy czyszczeniu terenu

void updateMap(int, int),
     generateMap();

int iso2screen_x(int x, int y)
{
    return ( (x-y)*TILE_W/2 ) ;
}
int iso2screen_y(int x, int y)
{
    return ( (x+y)*TILE_H/2 ) ;
}

int screen2iso_x(int x, int y)
{
    x /= 2;
    return ( (y+x)/TILE_H );
}
int screen2iso_y(int x, int y)
{
    x /= 2;
    return ( (y-x)/TILE_H );
}


ALLEGRO_BITMAP* IMG_grass[5];
ALLEGRO_BITMAP* IMG_corn[1];
ALLEGRO_BITMAP* IMG_rock[2];
ALLEGRO_BITMAP* IMG_tree[4];
ALLEGRO_BITMAP* IMG_house[5];
ALLEGRO_BITMAP* IMG_road[5];
ALLEGRO_BITMAP* IMG_building[3];
/*
    [0] prefekttura
    [1] studnia
    [2] farma
*/

ALLEGRO_BITMAP* IMG_minimap;

ALLEGRO_BITMAP* IMG_green,* IMG_red,* IMG_green_border;

int tx, ty;
int map_x = (1024/2-TILE_W/2), map_y = (768/2-MAP_H/2*TILE_H);
void createMap(ALLEGRO_DISPLAY* dis)
{
    IMG_grass[0] = loadBmp("media/grass1.png");
    IMG_grass[1] = loadBmp("media/grass2.png");
    IMG_grass[2] = loadBmp("media/grass3.png");
    IMG_grass[3] = loadBmp("media/grass4.png");
    IMG_grass[4] = loadBmp("media/grass5.png");

    IMG_corn[0] = loadBmp("media/corn1.png");

    IMG_rock[0] = loadBmp("media/rock1.png");
    IMG_rock[1] = loadBmp("media/rock2.png");

    IMG_tree[0] = loadBmp("media/tree1.png");
    IMG_tree[1] = loadBmp("media/tree2.png");
    IMG_tree[2] = loadBmp("media/tree3.png");
    IMG_tree[3] = loadBmp("media/tree4.png");

    IMG_house[0] = loadBmp("media/house/1.png");
    IMG_house[1] = loadBmp("media/house/2.png");
    IMG_house[2] = loadBmp("media/house/2_2.png");
    IMG_house[3] = loadBmp("media/house/3.png");
    IMG_house[4] = loadBmp("media/house/3_2.png");

    IMG_road[0] = loadBmp("media/road1.png");
    IMG_road[1] = loadBmp("media/road2.png");
    IMG_road[2] = loadBmp("media/road3.png");
    IMG_road[3] = loadBmp("media/road4.png");
    IMG_road[4] = loadBmp("media/road5.png");

    IMG_building[0] = loadBmp("media/b_prefektura.png");
    IMG_building[1] = loadBmp("media/b_studnia.png");
    IMG_building[2] = loadBmp("media/b_farma.png");

    IMG_green = loadBmp("media/green.png");
    IMG_green_border = loadBmp("media/green_border.png");
    IMG_red = loadBmp("media/red.png");

    IMG_minimap = al_create_bitmap(MAP_W, MAP_H);

    generateMap();
}

int posX, posY;
void renderMap(CMouse mouse, CKeyboard key)
{
    for(int x = 0; x < MAP_W; ++x)
    {
        for(int y = 0; y < MAP_H; ++y)
        {
            // ograniczanie wyswietlania mapy
            int x2 = 1024/2, y2 = 768/2;

            x2 -= map_x+TILE_W/2;
            y2 -= map_y;

            int mtx = screen2iso_x(x2,y2);
            int mty = screen2iso_y(x2,y2);

            if(x >= mtx-1024/TILE_W-3 && x <= mtx+1024/TILE_W+3 &&
               y >= mty-768/TILE_H-3 && y <= mty+768/TILE_H+3)
            {
                // podswietlenie na mini-mapie
                //mapWidocznosc[y][x] = 1;

                // wyswietlanie mapy
                posX = (x-y)*TILE_W/2 + map_x;
                posY = (x+y)*TILE_H/2 + map_y;

                // grass
                for(int i = 0; i < 5; ++i)
                    if(map[y][x] == i) al_draw_scaled_bitmap(IMG_grass[i], 0,0,100,50, posX, posY, zoomX, zoomY, 0);
                // rock
                for(int i = 0; i < 2; ++i)
                    if(map[y][x] == 5+i) al_draw_scaled_bitmap(IMG_rock[i], 0,0,100,50, posX, posY, zoomX, zoomY, 0);
                // corn
                for(int i = 0; i < 1; ++i)
                    if(map[y][x] == 9) al_draw_scaled_bitmap(IMG_corn[0], 0,0,100,50, posX, posY, zoomX, zoomY, 0);
                // tree
                for(int i = 10; i < 14; ++i)
                    if(map[y][x] == i) al_draw_scaled_bitmap(IMG_tree[i-10], 0,0,100,50, posX, posY, zoomX, zoomY, 0);

                if(map[y][x] == 50) // droga
                {
                    if(map[y][x-1] != 50 && map[y-1][x] != 50 && map[y][x+1] != 50 && map[y+1][x] != 50)
                        al_draw_scaled_bitmap(IMG_road[0], 0,0,100,50, posX, posY, zoomX, zoomY, 0);
                    if(map[y-1][x] == 50 || map[y+1][x] == 50)
                        al_draw_scaled_bitmap(IMG_road[0], 0,0,100,50, posX, posY, zoomX, zoomY, 0);
                    if(map[y][x-1] == 50 || map[y][x+1] == 50)
                        al_draw_scaled_bitmap(IMG_road[0], 0,0,100,50, posX, posY, zoomX, zoomY, ALLEGRO_FLIP_HORIZONTAL);

                    if(map[y+1][x] == 50 && map[y][x+1] == 50)
                        al_draw_scaled_bitmap(IMG_road[3], 0,0,100,50, posX, posY, zoomX, zoomY, 0);
                    if(map[y-1][x] == 50 && map[y][x-1] == 50)
                        al_draw_scaled_bitmap(IMG_road[3], 0,0,100,50, posX, posY, zoomX, zoomY, ALLEGRO_FLIP_VERTICAL);
                    if(map[y+1][x] == 50 && map[y][x-1] == 50)
                        al_draw_scaled_bitmap(IMG_road[4], 0,0,100,50, posX, posY, zoomX, zoomY, 0);
                    if(map[y-1][x] == 50 && map[y][x+1] == 50)
                        al_draw_scaled_bitmap(IMG_road[4], 0,0,100,50, posX, posY, zoomX, zoomY, ALLEGRO_FLIP_HORIZONTAL);

                    if(map[y-1][x] == 50 && map[y+1][x] == 50 && map[y][x+1] == 50)
                        al_draw_scaled_bitmap(IMG_road[2], 0,0,100,50, posX, posY, zoomX, zoomY, 0);
                    if(map[y][x-1] == 50 && map[y+1][x] == 50 && map[y][x+1] == 50)
                        al_draw_scaled_bitmap(IMG_road[2], 0,0,100,50, posX, posY, zoomX, zoomY, ALLEGRO_FLIP_HORIZONTAL);
                    if(map[y][x-1] == 50 && map[y-1][x] == 50 && map[y][x+1] == 50)
                        al_draw_scaled_bitmap(IMG_road[2], 0,0,100,50, posX, posY, zoomX, zoomY, ALLEGRO_FLIP_VERTICAL);
                    if(map[y+1][x] == 50 && map[y-1][x] == 50 && map[y][x-1] == 50)
                        al_draw_scaled_bitmap(IMG_road[2], 0,0,100,50, posX, posY, zoomX, zoomY, ALLEGRO_FLIP_HORIZONTAL | ALLEGRO_FLIP_VERTICAL);

                    if(map[y][x-1] == 50 && map[y-1][x] == 50 && map[y][x+1] == 50 && map[y+1][x] == 50)
                        al_draw_scaled_bitmap(IMG_road[1], 0,0,100,50, posX, posY, zoomX, zoomY, 0);
                }

                if(map[y][x] == 200) // prefektura
                    al_draw_scaled_bitmap(IMG_building[0], 0,0,100,50, posX, posY, zoomX, zoomY, 0);
                if(map[y][x] == 201) // studnia
                    al_draw_scaled_bitmap(IMG_building[1], 0,0,100,50, posX, posY, zoomX, zoomY, 0);
                if(map[y][x] == 202) { // farma
                    al_draw_scaled_bitmap(IMG_grass[0], 0,0,100,50, posX, posY, zoomX, zoomY, 0);
                    al_draw_scaled_bitmap(IMG_building[2], 0,0,150,100, posX-50, posY-75, zoomX+100, zoomY+100, 0);
                }
                if(map[y][x] == 203) { // pole zboza
                    al_draw_scaled_bitmap(IMG_corn[0], 0,0,100,50, posX, posY, zoomX, zoomY, 0);
                    getCornfield(x,y).render(posX,posY, zoomX,zoomY);
                }

                // domy:
                    // 1 lvl
                if(map[y][x] == 100 || map[y][x] == 101)
                        al_draw_scaled_bitmap(IMG_house[0], 0,0,100,50, posX, posY, zoomX, zoomY, 0);
                    // 2 lvl
                if(map[y][x] == 102)
                        al_draw_scaled_bitmap(IMG_house[1], 0,0,100,50, posX, posY, zoomX, zoomY, 0);
                if(map[y][x] == 103)
                        al_draw_scaled_bitmap(IMG_house[2], 0,0,100,50, posX, posY, zoomX, zoomY, 0);
                    // 3 lvl
                if(map[y][x] == 104)
                        al_draw_scaled_bitmap(IMG_house[3], 0,0,100,50, posX, posY, zoomX, zoomY, 0);
                if(map[y][x] == 105)
                        al_draw_scaled_bitmap(IMG_house[4], 0,0,100,50, posX, posY, zoomX, zoomY, 0);

            } // END ograniczanie widoku
            //else
            //    mapWidocznosc[y][x] = 0;

            if(map[y][x] == 100 && coIleOsadnik[0] <= 0)
            {
                p_settler.push_back(CPeople_settler(startX2,startY2, x,y));
                map[y][x] = 101;
                getHouse(x, y).ID = 101;
                coIleOsadnik[0] = coIleOsadnik[1] + ( rand()%30 );
            }

            /*if(map[y][x] >= 200 && coIleLudz[0] <= 0)
            {
                int losuj = rand()%100;
                if(losuj <= 50)
                {
                    p_normal.push_back(CPeople_normal(x, y, 1));
                    coIleLudz[0] = coIleLudz[1] + ( rand()%30 );
                }
            }*/
        }
    }

    if(coIleOsadnik[0] >= 0) coIleOsadnik[0]--;
    if(coIleLudz[0] >= 0) coIleLudz[0]--;

    bool rysujNaZielono = false;
    if(activeID != -1)
    {
        int x = mouse.getX(), y = mouse.getY();

        x -= map_x+TILE_W/2;
        y -= map_y;

        tx = screen2iso_x(x,y);
        ty = screen2iso_y(x,y);

        cout << "\nMap ID: " << map[ty][tx];


        int posX = (tx-ty)*TILE_W/2 + map_x;
        int posY = (tx+ty)*TILE_H/2 + map_y;
        if(tx >= 0 && tx < MAP_W && ty >= 0 && ty < MAP_H)
        {
            if(activeID != 0)
            {
                if(mapKolizje[ty][tx] == 0)
                {
                    if(activeID >= 200 && activeID != 202 && activeID != 203)
                    {
                        if(map[ty-1][tx] == 50 || map[ty+1][tx] == 50 || map[ty][tx-1] == 50 || map[ty][tx+1] == 50)
                            rysujNaZielono = true;
                        else
                            rysujNaZielono = false;
                    }
                    else
                        rysujNaZielono = true;
                }
                else
                    rysujNaZielono = false;

                if(activeID == 202) // farma 2x2
                {
                    if( mapKolizje[ty][tx] == 0 && mapKolizje[ty][tx-1] == 0 &&
                        mapKolizje[ty-1][tx-1] == 0 && mapKolizje[ty-1][tx] == 0 )
                       {
                           if(map[ty][tx] == 9 || map[ty-1][tx] == 9 || map[ty][tx-1] == 9 || map[ty-1][tx-1] == 9)
                                rysujNaZielono = true;
                            else
                                rysujNaZielono = false;
                       }
                    else
                        rysujNaZielono = false;
                }
                if(activeID == 203) // pole zboza
                {
                    if( mapKolizje[ty][tx] == 0)
                    {
                        if(map[ty][tx] == 9)
                            rysujNaZielono = true;
                        else
                            rysujNaZielono = false;
                    }
                    else
                        rysujNaZielono = false;
                }


                if(rysujNaZielono)
                {
                    al_draw_tinted_scaled_bitmap(IMG_green, al_map_rgba(0,100,0,20), 0,0,100,50,  posX, posY, zoomX, zoomY, 0);
                    if(activeID >= 200)
                    {
                        if(activeID == 202) { // farma 2x2
                            al_draw_tinted_scaled_bitmap(IMG_green, al_map_rgba(0,100,0,20), 0,0,100,50,  posX-50, posY-25, zoomX, zoomY, 0);
                            al_draw_tinted_scaled_bitmap(IMG_green, al_map_rgba(0,100,0,20), 0,0,100,50,  posX, posY-50, zoomX, zoomY, 0);
                            al_draw_tinted_scaled_bitmap(IMG_green, al_map_rgba(0,100,0,20), 0,0,100,50,  posX+50, posY-25, zoomX, zoomY, 0);
                            al_draw_tinted_scaled_bitmap(IMG_building[2], al_map_rgba(200,200,200,100), 0,0, 150,100, posX-50, posY-75, zoomX+100, zoomY+100, 0);
                        }
                        else
                            al_draw_tinted_scaled_bitmap(IMG_building[activeID-200], al_map_rgba(200,200,200,100), 0,0, 100,50, posX, posY, zoomX, zoomY, 0);
                    }
                }
                else
                {
                    al_draw_tinted_scaled_bitmap(IMG_red, al_map_rgba(100,0,0,20), 0,0,100,50, posX, posY, zoomX,zoomY, 0);
                    if(activeID == 202) { // farma 2x2
                        al_draw_tinted_scaled_bitmap(IMG_red, al_map_rgba(100,0,0,20), 0,0,100,50,  posX-50, posY-25, zoomX, zoomY, 0);
                        al_draw_tinted_scaled_bitmap(IMG_red, al_map_rgba(100,0,0,20), 0,0,100,50,  posX, posY-50, zoomX, zoomY, 0);
                        al_draw_tinted_scaled_bitmap(IMG_red, al_map_rgba(100,0,0,20), 0,0,100,50,  posX+50, posY-25, zoomX, zoomY, 0);
                    }
                }
            }
            else
                al_draw_tinted_scaled_bitmap(IMG_green_border, al_map_rgba(0,100,0,20), 0,0,100,50, posX, posY, zoomX, zoomY, 0);
        }
    }

    if(mouse.Press(1) && mouse.getX() < 1024-52 && wysunieteMenu == -1 && !mouseClick && activeID != -1 && !pause)
    {
        int x = mouse.getX(), y = mouse.getY();

        x -= map_x+TILE_W/2;
        y -= map_y;

        tx = screen2iso_x(x,y);
        ty = screen2iso_y(x,y);

        if(tx >= 0 && tx < MAP_W && ty >= 0 && ty < MAP_H)
        {
            if(activeID == 0)
            {
                if(map[ty][tx] != 9 && map[ty][tx] != 5 && map[ty][tx] != 6)
                {
                    bool takiSamPkt = false;

                    for(int i = 0; i < pkt.size(); ++i)
                    {
                        if(tx == pkt[i].x && ty == pkt[i].y)
                        {
                            takiSamPkt = true;
                            break;
                        }
                    }

                    if(!takiSamPkt)
                    {
                        int innatrawa = rand()%100;
                        if(innatrawa <= 60)
                        {
                            int los = rand()%2+1;
                            map[ty][tx] = los;
                            mapKolizje[ty][tx] = 0;
                        }
                        else {
                            map[ty][tx] = 0;
                            mapKolizje[ty][tx] = 0;
                        }

                        pkt.push_back(CPoint(tx, ty));

                        if(map[ty][tx] == 202) { // farma 2x2
                            mapKolizje[ty][tx-1] = 0;
                            mapKolizje[ty-1][tx-1] = 0;
                            mapKolizje[ty-1][tx] = 0;
                        }

                        /*if(map[ty][tx] == 100)
                            v_house.erase(v_house.begin()+getHouse(tx,ty));
                        if(map[ty][tx] == 202)
                            v_farm.push_back(CFarm(tx, ty));
                        if(map[ty][tx] == 203)
                            v_cornfield.push_back(CCornfield(tx, ty));*/
                    }
                }
            }
            else
            {
                /*if(map[ty][tx] <= 2 || map[ty][tx] == 9)
                {
                    if(activeID >= 200)
                    {
                        if(map[ty][tx+1] == 50) { // prawy rog
                            if(map[ty-1][tx+1] != 50 && map[ty+1][tx+1] != 50)
                                p_normal.push_back(CPeople_normal(tx+1, ty, 3));
                            else if(map[ty-1][tx+1] != 50)
                                p_normal.push_back(CPeople_normal(tx+1, ty, 4));
                            else if(map[ty+1][tx+1] != 50)
                                p_normal.push_back(CPeople_normal(tx+1, ty, 1));
                            else if(map[ty-1][tx+1] == 50 && map[ty+1][tx+1] == 50)
                                p_normal.push_back(CPeople_normal(tx+1, ty, 4));

                            map[ty][tx] = activeID;
                        }
                        else if(map[ty][tx-1] == 50) { // lewy rog
                            if(map[ty-1][tx-1] != 50 && map[ty+1][tx-1] != 50)
                                p_normal.push_back(CPeople_normal(tx-1, ty, 2));
                            else if(map[ty-1][tx-1] != 50 && map[ty+1][tx-1] == 50)
                                p_normal.push_back(CPeople_normal(tx-1, ty, 4));
                            else if(map[ty-1][tx-1] == 50 && map[ty+1][tx-1] == 50)
                                p_normal.push_back(CPeople_normal(tx-1, ty, 1));
                            else if(map[ty-1][tx-1] == 50 && map[ty+1][tx-1] == 50)
                                p_normal.push_back(CPeople_normal(tx-1, ty, 4));

                            map[ty][tx] = activeID;
                        }
                        else if(map[ty-1][tx] == 50) { // gorny rog
                            if(map[ty-1][tx-1] != 50 && map[ty-1][tx+1] != 50)
                                p_normal.push_back(CPeople_normal(tx, ty-1, 1));
                            else if(map[ty-1][tx-1] != 50 && map[ty-1][tx+1] == 50)
                                p_normal.push_back(CPeople_normal(tx, ty-1, 3));
                            else if(map[ty-1][tx-1] == 50 && map[ty-1][tx+1] != 50)
                                p_normal.push_back(CPeople_normal(tx, ty-1, 2));
                            else if(map[ty-1][tx-1] == 50 && map[ty-1][tx+1] == 50)
                                p_normal.push_back(CPeople_normal(tx, ty-1, 2));

                            map[ty][tx] = activeID;
                        }
                        else if(map[ty+1][tx] == 50) { // dolny rog
                            if(map[ty+1][tx-1] != 50 && map[ty+1][tx+1] != 50)
                                p_normal.push_back(CPeople_normal(tx, ty+1, 1));
                            else if(map[ty+1][tx-1] != 50 && map[ty+1][tx+1] == 50)
                                p_normal.push_back(CPeople_normal(tx, ty+1, 3));
                            else if(map[ty+1][tx-1] == 50 && map[ty+1][tx+1] != 50)
                                p_normal.push_back(CPeople_normal(tx, ty+1, 2));
                            else if(map[ty+1][tx-1] == 50 && map[ty+1][tx+1] == 50)
                                p_normal.push_back(CPeople_normal(tx, ty+1, 2));

                            map[ty][tx] = activeID;
                        }
                    }
                    else
                    {
                        map[ty][tx] = activeID;

                        if(activeID == 100)
                            v_house.push_back(CHouse(tx, ty));
                    }
                }*/

                if(rysujNaZielono)
                {
                    map[ty][tx] = activeID;
                    mapKolizje[ty][tx] = 1;
                    if(activeID == 202) { // farma 2x2
                        mapKolizje[ty][tx-1] = 1;
                        mapKolizje[ty-1][tx-1] = 1;
                        mapKolizje[ty-1][tx] = 1;
                    }

                    if(activeID == 100)
                        v_house.push_back(CHouse(tx, ty));
                    if(activeID == 202)
                        v_farm.push_back(CFarm(tx, ty));
                    if(activeID == 203)
                        v_cornfield.push_back(CCornfield(tx, ty));
                }
            }
        }
    }
    if(!mouse.Press(1) && pkt.size() > 0)
        pkt.clear();

    if(mouse.Press(2)) {
        if(activeID != -1)
        {
            activeID = -1;
            mouseClick = true;
            mouse2click = true;
        }
    }

    if(wysunieteMenu == -1)
    {
        if(mouse.getX() <= 20 || key.Press(ALLEGRO_KEY_LEFT))
            map_x += 7;
        if(mouse.getX() >= 1004 || key.Press(ALLEGRO_KEY_RIGHT))
            map_x -= 7;
        if(mouse.getY() <= 20 || key.Press(ALLEGRO_KEY_UP))
            map_y += 7;
        if(mouse.getY() >= 748 || key.Press(ALLEGRO_KEY_DOWN))
            map_y -= 7;
    }
}

void updateMap(int x, int y)
{
}

int ilKam = 0, ilZbo = 0;
void generateMap()
{
    for(int x = 0; x < MAP_W; ++x)
    {
        for(int y = 0; y < MAP_H; ++y)
        {
            int drzewo = rand()%100;
            if(drzewo <= 5) // tree
            {
                int los = rand()%4;
                map[y][x] = los+10;
                mapKolizje[y][x] = 1;
            }
            else if(drzewo > 5 && drzewo <= 7 && ilKam < MAP_W/5) // rock
            {
                int los = rand()%2;
                map[y][x] = los+5;
                mapKolizje[y][x] = 1;
                ilKam++;
            }
            else if(drzewo > 20 && drzewo <= 25 && ilZbo <= MAP_W/30 && x > 2 && y > 2) // corn
            {
                //int los = rand()%2;
                map[y][x] = 9;
                mapKolizje[y][x] = 0;
                ilZbo++;
            }
            else
            {
                int innatrawa = rand()%100;
                if(innatrawa <= 30)
                {
                    int los = rand()%4+1;
                    map[y][x] = los;
                    mapKolizje[y][x] = 0;
                }
            }
        }
    }

    if(ilZbo <= 0)
    {
        int x = rand()%MAP_W;
        int y = rand()%MAP_H;
        map[y][x] = 9;
        mapKolizje[y][x] = 0;
    }

    for(int i = 0; i < 8; ++i)
        for(int x = 0; x < MAP_W; ++x)
        {
            for(int y = 0; y < MAP_H; ++y)
            {
                if(map[y][x] >= 10) // tree
                {
                    int drzewo = rand()%100;
                    if(drzewo <= 50)
                    {
                        int los = rand()%4;
                        int kier = rand()%101;
                        if(kier <= 25 && y > 0 && map[y-1][x] != 9) {
                            map[y-1][x] = los+10;
                            mapKolizje[y-1][x] = 1;
                        }
                        if(kier > 25 && kier <= 50 && y < MAP_H && map[y+1][x] != 9) {
                            map[y+1][x] = los+10;
                            mapKolizje[y+1][x] = 1;
                        }
                        if(kier > 50 && kier <= 75 && x > 0 && map[y][x-1] != 9) {
                            map[y][x-1] = los+10;
                            mapKolizje[y][x-1] = 1;
                        }
                        if(kier > 75 && x < MAP_W && map[y][x+1] != 9) {
                            map[y][x+1] = los+10;
                            mapKolizje[y][x+1] = 1;
                        }
                    }
                }

                if(map[y][x] == 5 || map[y][x] == 6) // rock
                {
                    int drzewo = rand()%100;
                    if(drzewo <= 40)
                    {
                        int los = rand()%2;
                        int kier = rand()%101;
                        if(kier <= 25 && y > 0 && map[y-1][x] != 9) {
                            map[y-1][x] = los+5;
                            mapKolizje[y-1][x] = 1;
                        }
                        if(kier > 25 && kier <= 50 && y < MAP_H && map[y+1][x] != 9) {
                            map[y+1][x] = los+5;
                            mapKolizje[y+1][x] = 1;
                        }
                        if(kier > 50 && kier <= 75 && x > 0 && map[y][x-1] != 9) {
                            map[y][x-1] = los+5;
                            mapKolizje[y][x-1] = 1;
                        }
                        if(kier > 75 && x < MAP_W && map[y][x+1] != 9) {
                            map[y][x+1] = los+5;
                            mapKolizje[y][x+1] = 1;
                        }
                    }
                }

                if(map[y][x] == 9) // corn
                {
                    int drzewo = rand()%100;
                    if(drzewo <= 90)
                    {
                        //int los = rand()%2;
                        int kier = rand()%151;
                        if(kier <= 25 && y > 0) {
                            map[y-1][x] = 9;
                            mapKolizje[y-1][x] = 0;
                        }
                        if(kier > 25 && kier <= 50 && y < MAP_H) {
                            map[y+1][x] = 9;
                            mapKolizje[y+1][x] = 0;
                        }
                        if(kier > 50 && kier <= 75 && x > 0) {
                            map[y][x-1] = 9;
                            mapKolizje[y][x-1] = 0;
                        }
                        if(kier > 75 && x < MAP_W) {
                            map[y][x+1] = 9;
                            mapKolizje[y][x+1] = 0;
                        }
                    }
                }
            }
        }

    startX = rand()%MAP_W/2+MAP_W/4, startY = 0;
    map[startY][startX] = 50;

    startX2 = startX;
    startY2 = startY;

    while(1)
    {
        int los = rand()%100;
        if(los <= 80)
        {
            map[startY+1][startX] = 50;
            mapKolizje[startY+1][startX] = 1;
            startY++;
        }
        else
        {
            int kier = rand()%51;
            if(kier <= 25 && startX > 0)
            {
                map[startY][startX-1] = 50;
                map[startY][startX-2] = 50;
                mapKolizje[startY][startX-1] = 1;
                mapKolizje[startY][startX-2] = 1;
                startX-=2;
            }
            if(kier > 25 && startX < MAP_W)
            {
                map[startY][startX+1] = 50;
                map[startY][startX+2] = 50;
                mapKolizje[startY][startX+1] = 1;
                mapKolizje[startY][startX+2] = 1;
                startX+=2;
            }
        }

        if(startX == MAP_W || startY == MAP_H)
            break;
    }
}

void updateMiniMap()
{
    al_set_target_bitmap(IMG_minimap);

    int a = 255;

    for(int x = 0; x < MAP_W; ++x)
    {
        for(int y = 0; y < MAP_H; ++y)
        {
            /*if(mapWidocznosc[y][x] == 1)
                a = 190;
            else
                a = 255;*/

            if(map[y][x] < 5) al_draw_pixel(x,y, al_map_rgba(150,190,20,a));
            if(map[y][x] == 5 || map[y][x] == 6) al_draw_pixel(x,y, al_map_rgba(200,200,200,a));
            if(map[y][x] == 9) al_draw_pixel(x,y, al_map_rgba(255,240,0,a));
            if(map[y][x] >= 10 && map[y][x] < 14) al_draw_pixel(x,y, al_map_rgba(130,160,20,a));

            if(map[y][x] == 50) al_draw_pixel(x,y, al_map_rgba(240,230,180,a));

            if(map[y][x] >= 200) al_draw_pixel(x,y, al_map_rgba(185,120,90,a));

            if(map[y][x] >= 100 && map[y][x] < 200) al_draw_pixel(x,y, al_map_rgba(140,120,200,a));

        }
    }

    al_set_target_backbuffer(al_get_current_display());
}

#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "main.h"
#include "input.h"
#include "point.h"

extern int map[500][500];
extern int TILE_W, TILE_H, map_x, map_y, MAP_W, MAP_H;

int screen2iso_x(int,int), screen2iso_y(int,int);
int iso2screen_x(int,int), iso2screen_y(int,int);

extern int zoomX, zoomY;

void createMap(ALLEGRO_DISPLAY*), renderMap(CMouse, CKeyboard),
     updateMiniMap();

extern ALLEGRO_BITMAP* IMG_grass[5];
extern ALLEGRO_BITMAP* IMG_corn[1];
extern ALLEGRO_BITMAP* IMG_rock[2];
extern ALLEGRO_BITMAP* IMG_tree[4];
extern ALLEGRO_BITMAP* IMG_house[5];
extern ALLEGRO_BITMAP* IMG_road[5];
extern ALLEGRO_BITMAP* IMG_building[3];

extern ALLEGRO_BITMAP* IMG_minimap;

#endif // MAP_H_INCLUDED

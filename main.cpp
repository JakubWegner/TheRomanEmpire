#include "main.h"
#include "input.h"
#include "logger.h"
#include "map.h"
#include "hud.h"
#include "people_manager.h"
#include "intro.h"
#include "house.h"
#include "particle.h"
#include "farm.h"
#include "cornfield.h"

CKeyboard key;
CMouse mouse;

const
int     WIN_W = 1024, WIN_H = 768,
        WIN_FPS = 60;
string  WIN_NAME = "The Roman Empire";

void updateFPS(bool);

ALLEGRO_FONT* font;

enum gameMode { gm_gameplay = 0, gm_menu = 1, gm_intro = 2 } GameMode;
int i_GameMode;

bool mouseClick;

int activeID = -1, wysunieteMenu = -1;
string opisID[] = {  ///   4, 1, 1, 1, 4, 2, 1, 3, 2, 1, 1, 1, 5
    "Zapisz gre", "Wczytaj gre", "Ustawienia", "Wyjscie",
    "Zbuduj dom [ Dn  0 ]",
    "Wyczysc pole [ Dn  2 ]",
    "Zbuduj droge [ Dn  2 ]",
    "Studnia [ Dn  10 ]", "Fontanna [ Dn  50 ]", "Rezerwuar [ Dn  550 ]", "Adwedukt [ Dn  25 ]",
    "Laznia [ Dn  300 ]", "Szpital [ Dn  600 ]",
    "Swiatynia Wenus [ Dn  400 ]",
    "Szkola [ Dn  500 ]", "Szkola aktorow [ Dn  400 ]", "Szkola gladiatorow [ Dn  500 ]",
    "Teatr [ Dn  800 ]", "Koloseum [ Dn  50.000 ]",
    "Senat [ Dn  1.500 ]",
    "Dom inzyniera [ Dn  50 ]",
    "Prefektura [ Dn  50 ]",
    "Uprawa [ Dn  200 ]", "Pole zboza [ Dn  50 ]", "Pole owocow [ Dn  50 ]", "Stragan [ Dn  150 ]", "Spichlerz [ Dn  400 ]"
};

int main(int argc, char * argv[])
{
    logger.start("log.txt");
    #ifndef _DEBUG
        logger << "Mode: Debug.\n";
    #endif

    logger << "Load: Allegro5";
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_TIMER *timer;
    ALLEGRO_KEYBOARD_STATE klawiatura;
    ALLEGRO_MOUSE_STATE myszka;
    ALLEGRO_EVENT ev;

    srand(time(0));

    al_init();
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_audio();
    al_init_acodec_addon();

    logger << "Start: Allegro5";

    al_set_app_name(WIN_NAME.c_str());
    timer = al_create_timer(1.0 / WIN_FPS);

    //al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
    display = al_create_display(WIN_W,WIN_H);

    event_queue = al_create_event_queue();

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_start_timer(timer);


    ALLEGRO_FONT* font = al_load_font("media/font.ttf", 20, 0);
    if(!font)
        return 69;

    createMap(display);
    createHud();
    createPeople();
    createIntro();
    createParticle();
    updateMiniMap();
    createCornfield();

    logger << "Start: Application";

    GameMode = gm_gameplay;


    i_GameMode = GameMode;
    mouseClick = false;

    while(1)
    {
        al_wait_for_event(event_queue, &ev);
        al_get_keyboard_state(&klawiatura);
        al_get_mouse_state(&myszka);

        key.Get(klawiatura);
        mouse.Get(myszka);


        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            al_clear_to_color(al_map_rgb(255,255,255));

            updateFPS(0);

            int(GameMode) = i_GameMode;

            if(GameMode == gm_intro)
            {
                renderIntro(i_GameMode);
            }
            if(GameMode == gm_gameplay)
            {
                renderMap(mouse, key);
                updateMiniMap();
                renderHouse(); // update
                renderParticle();
                renderPeople();
                renderHud2(mouse, key);
                renderFarm();

                player.render();
            }

            al_flip_display();

            zoomX = mouse.getZ()*2+100;
            zoomY = mouse.getZ()*2+50;

            TILE_W = zoomX; TILE_H = zoomY;

            if((key.Press(ALLEGRO_KEY_LCTRL) || key.Press(ALLEGRO_KEY_RCTRL)) && key.Press(ALLEGRO_KEY_PAD_0))
            {
                if(zoomX > 100 || zoomX < 100)
                    zoomX = 100;
                if(zoomY > 50 || zoomY < 50)
                    zoomY = 50;
            }


            if(mouseClick && !mouse.Press(1))
                mouseClick = false;

            if(key.Press(ALLEGRO_KEY_ESCAPE))
                break;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;

        //al_rest(0.001);
    }

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}


int _time(clock());
int cfps(0), FPS(0);
int amount = 0;

void updateFPS(bool write)
{
    if(_time+1000<clock())
    {
        _time = clock();
        FPS = cfps;
        cfps = 0;
    }
    cfps++;

    if(write)
    {
        amount++;
        if(amount >= 100)
        {
            cout << "\n#FPS: " << FPS;
            amount = 0;
        }
    }
}


#include "iostream"
#include <QtCore>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <QString>
#include <QDebug>

#include <nlohmann/json.hpp>

#include <allegro5/allegro_image.h>

using namespace std;

#define GAMEPATH "C:/Users/PICHAU/Documents/QtProjects/GameTestAllegro/"

int main()
{

    int ScreenWidth = 1024;
    int ScreenHeight = 740;
    const float FPS = 60.0;

    enum Direction { DOWN = 0, LEFT = 1, RIGHT = 2, UP = 3 };

    int dir = DOWN;

    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_native_dialog_addon();
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();

    string playerSpriteSheet = ((string)GAMEPATH + "player.png");

    ALLEGRO_BITMAP *player = al_load_bitmap( playerSpriteSheet.c_str()  );

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);

    al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE); /*ALLEGRO_FULLSCREEN | ALLEGRO_NOFRAME | ALLEGRO_OPENGL*/

    ALLEGRO_KEYBOARD_STATE keyState;

    ALLEGRO_DISPLAY *display = al_create_display(ScreenWidth,ScreenHeight);
    ALLEGRO_FONT *font = al_load_ttf_font( "COMICATE.TTF", 64, 0 );

    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_start_timer(timer);

    al_set_window_title(display, "HelloWorld2");

    bool done = false, draw = true, active = false;
    float x = 10.0f, y = 10.0f, moveSpeed = 5.0f;
    int sourceX = 0, sourceY = 0;

    while (!done) {

        ALLEGRO_EVENT events;

        al_wait_for_event(event_queue, &events);

        if(events.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(events.keyboard.keycode)
            {
                case ALLEGRO_KEY_ESCAPE:
                    done = true;
            }
        }
        else if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            done = true;
        else if(events.type == ALLEGRO_EVENT_TIMER)
        {
            active = true;

            al_get_keyboard_state(&keyState);

            if(al_key_down(&keyState, ALLEGRO_KEY_DOWN))
            {
                y += moveSpeed;
                dir = DOWN;
            }
            else if(al_key_down(&keyState, ALLEGRO_KEY_UP))
            {
                y -= moveSpeed;
                dir = UP;
            }
            else if(al_key_down(&keyState, ALLEGRO_KEY_LEFT))
            {
                x -= moveSpeed;
                dir = LEFT;
            }
            else if(al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
            {
                x += moveSpeed;
                dir = RIGHT;
            }
            else
            {
                active = false;
            }

            if(active)
            {
                sourceX += al_get_bitmap_width(player) / 3;
//                sourceY += al_get_bitmap_height(player) / 3;
            }
            else
            {
                sourceX = 53;
            }

            if(sourceX >= al_get_bitmap_width(player))
                sourceX = 0;

            sourceY = dir;

            draw = true;
        }

        if(draw)
        {

            al_draw_bitmap_region(player, sourceX,
                                  sourceY * al_get_bitmap_height(player)/4, 53, 53, x, y, NULL );

            draw = false;

            //al_draw_filled_circle(x, y, 30.0, playerColor);

//            al_draw_bitmap(player, x, y, NULL);

            al_flip_display();

            al_clear_to_color(al_map_rgb(0, 0, 0));

        }

    }


    al_destroy_display(display);
    al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_bitmap(player);
    al_destroy_event_queue(event_queue);

    return 0;
}

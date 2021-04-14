
#include "iostream"
#include <QtCore>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <QString>
#include <QDebug>

#include <allegro5/allegro_image.h>

using namespace std;

#define GAMEPATH "C:/Users/PICHAU/Documents/QtProjects/GameTestAllegro/"

int main()
{

    int ScreenWidth = 1024;
    int ScreenHeight = 740;
    const float FPS = 60.0;

    enum Direction { UP, DOWN, LEFT, RIGHT };

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

    ALLEGRO_BITMAP *player = al_load_bitmap( &playerSpriteSheet[0] );

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

    al_set_window_title(display, "Oi");

    float points[8] = {0, 0, 400, 100, 50, 200, (float)ScreenWidth, (float)ScreenHeight};

    ALLEGRO_COLOR electricBlue = al_map_rgb(44, 117, 255);
    ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
    ALLEGRO_COLOR playerColor = electricBlue;

    bool done = false, draw = true;
    int x = 10, y = 10;
    int moveSpeed = 5;

    al_hide_mouse_cursor(display);

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
        else if(events.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            x = events.mouse.x;
            y = events.mouse.y;
        }
        else if(events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if(events.mouse.button & 1)
                playerColor = electricBlue;
            else if(events.mouse.button & 2)
                playerColor = yellow;
        }


//        if(events.type == ALLEGRO_EVENT_KEY_DOWN)
//        {
//            switch(events.keyboard.keycode)
//            {
//                case ALLEGRO_KEY_DOWN:
//                    dir = DOWN;
//                    break;
//                case ALLEGRO_KEY_UP:
//                    dir = UP;
//                    break;
//                case ALLEGRO_KEY_LEFT:
//                    dir = LEFT;
//                    break;
//                case ALLEGRO_KEY_RIGHT:
//                    dir = RIGHT;
//                    break;
//                case ALLEGRO_KEY_ESCAPE:
//                    done = true;
//                    break;
//            }
//        }



        if(events.type == ALLEGRO_EVENT_TIMER)
        {
            al_get_keyboard_state(&keyState);

            if(al_key_down(&keyState, ALLEGRO_KEY_UP))
                y -= moveSpeed;
            else if(al_key_down(&keyState, ALLEGRO_KEY_DOWN))
                y += moveSpeed;
            else if(al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
                x += moveSpeed;
            else if(al_key_down(&keyState, ALLEGRO_KEY_LEFT))
                x -= moveSpeed;



//            switch(dir)
//            {
//                case DOWN:
//                    y += moveSpeed;
//                    break;
//                case UP:
//                    y -= moveSpeed;
//                    break;
//                case LEFT:
//                    x -= moveSpeed;
//                    break;
//                case RIGHT:
//                    x += moveSpeed;
//                    break;
//            }

            draw = true;
        }

        if(draw)
        {
            draw = false;

            al_draw_filled_circle(x, y, 30.0, playerColor);

            al_flip_display();

            al_clear_to_color(al_map_rgb(0, 0, 0));

        }

        al_draw_bitmap(player, x, y, NULL);



//        int value = al_show_native_message_box(display, "NULL", "Display Settings",
//                                   "Could not initialize", NULL,
//                                   ALLEGRO_MESSAGEBOX_YES_NO | ALLEGRO_MESSAGEBOX_QUESTION);



//        char message[] = "Herro Wold";



//        string addValue = (string)message /*+ " " +  QString::number(value).toStdString()*/;

//        char* msg = &addValue[0];

//        qDebug() << msg;

//        al_clear_to_color(al_map_rgb(100, 120, 150));
//        al_draw_text(font, al_map_rgb(125, 125, 125), ScreenWidth/2 ,ScreenHeight/2 , ALLEGRO_ALIGN_CENTRE, msg);

//        al_draw_triangle(10, 10, 20, 10, 15, 50, al_map_rgb(255, 0, 0), 1.0);


//        al_draw_rounded_rectangle(10, 10, 100, 100, 5, 5, al_map_rgb(0, 255, 0), 30);

//        al_draw_rectangle(400, 400, 450, 500, al_map_rgb(255, 98, 100), 9.0);

////        al_draw_circle

//        al_draw_arc(10, ScreenHeight - 100, 10, 0, 4.0, al_map_rgb(255, 0, 0), 2.0);
//        al_draw_line(100, 500, 300, 500, electricBlue, 6.0);
//        al_draw_pixel(520, 520, electricBlue);

//        al_draw_spline(points, electricBlue, 1.0);



    }


    al_destroy_display(display);
    al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_bitmap(player);
    al_destroy_event_queue(event_queue);

    return 0;
}

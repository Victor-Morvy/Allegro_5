
#include "iostream"
#include <QtCore>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
#include <allegro5/mouse.h>
#include <QString>
#include <QDebug>

#include <sstream>

#include <nlohmann/json.hpp>

#include <allegro5/allegro_image.h>

using namespace std;

#define GAMEPATH "C:/Users/PICHAU/Documents/QtProjects/GameTestAllegro/"
enum dimension{
    WIDTH = 1280,
    HEIGHT = 762
};

int main()
{
    al_init();

    ALLEGRO_DISPLAY *display = al_create_display(WIDTH, HEIGHT);

    const float FPS = 60.0f;

    bool done = false, draw = true, active = false;
    float x = 10.0f, y = 10.0f, moveSpeed = 5.0f;

    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();

    std::stringstream path;
    path << GAMEPATH << "player.png";

    ALLEGRO_BITMAP *image = al_load_bitmap(path.str().c_str());
    al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));

    ALLEGRO_KEYBOARD_STATE keyState;

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_start_timer(timer);

    al_set_window_title(display, "HelloWorld2");

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
            }
            else if(al_key_down(&keyState, ALLEGRO_KEY_UP))
            {
                y -= moveSpeed;
            }

            if(al_key_down(&keyState, ALLEGRO_KEY_LEFT))
            {
                x -= moveSpeed;
            }
            else if(al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
            {
                x += moveSpeed;
            }
            else
                active = false;

            draw = true;
        }

        if(draw)
        {
            al_draw_bitmap(image, x, y, NULL);
            al_flip_display();
            al_clear_to_color(al_map_rgb(255, 255, 255));

        }

    }


    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_bitmap(image);
    al_destroy_event_queue(event_queue);

    return 0;
}

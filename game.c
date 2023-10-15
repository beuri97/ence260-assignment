#include "system.h"
#include "battleship.h"
#include "pacer.h"
#include "led.h"
#include "tinygl.h"
#include "navswitch.h"
#include "ir_start.h"
#include "../fonts/font5x7_1.h"
#include "missile.h" // change

#define PACER_RATE 500
#define MESSAGE_RATE 10

int main (void)
{
    system_init ();
    led_init();
    navswitch_init();
    pacer_init(PACER_RATE);
    led_set(LED1, 1);
    uint8_t number_of_ships = 3;
    bool end = false;

    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_draw_message("Choose ship positions", tinygl_point (0, 0), 1);
    bool keep_going = false;
    while(!keep_going) {
        navswitch_update();
        if(navswitch_push_event_p(NAVSWITCH_PUSH)) {
            keep_going = true;
        pacer_wait();
        tinygl_update();
    }
    ship_init(PACER_RATE);
    uint8_t position = ir_start_init();
    if(position == 1) {
        led_set(LED1, 1);
        missile_init(PACER_RATE);
    }
    while(number_of_ships > 0 || end == false) {
        //display ships (not sure how)
        led_set(LED1, 0);
        uint8_t col = 0;
        uint8_t row = 0;

        while(col == 0) {
            col = receiveDone();
        }
        while(row == 0) {
            row = receiveDone();
        }
        bool hit; //= collisionCheck(col, row);
        if(hit) {
            number_of_ships--;
        }
        led_set(LED1, 1);
        missile_init(PACER_RATE);
        }
    }
}
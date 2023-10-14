#include "system.h"
#include "battleship.h"
#include "pacer.h"
#include "led.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"

#define PACER_RATE 500
#define MESSAGE_RATE 10

int main (void)
{
    system_init ();
    led_init();
    led_set(LED1, 1);

    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_draw_message("Choose ship positions", tinygl_point (0, 0), 1);
    pacer_init(PACER_RATE);
    ship_init(PACER_RATE);
    led_set(LED1, 0);
    while (1)
    {
        
    }
}

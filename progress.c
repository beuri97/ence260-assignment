/** @file   show.c
    @author HanByeol Yang(hya62), Blake W. Manson(bwm206)
    @date   15 October 2023
    @brief  handles LED1(Blue LED) and led-Matrix
*/

#include "system.h"
#include "led.h"
#include "pacer.h"
#include "display.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "progress.h"

#define PACER_RATE 500
#define MESSAGE_RATE 25

/**
 * @brief trigger function to setup to show message on led-matrix
*/
void instruction_set(message_t message) {
    
    switch (message)
    {
    case WELCOME:
        tinygl_text("WELCOME! Please push any button to start positioning ships!\0");
        while(1) {
            pacer_wait();
            tinygl_update();
        }

        break;
    
    default:
        break;
    }

}


/**
 * @brief turn off led1(BLUE LED)
*/
void led1_off(void)
{
    led_set(LED1, 0);
}

/**
 * @brief turn on led1(BLUE LED)
*/
void led1_on(void)
{
    led_set(LED1, 1);
}

/**
 * @brief initialise LED1(BLUE LED) and LED-matrix
*/
void led_interface_init(void)
{
    pacer_init(PACER_RATE);
    led_init();
    tinygl_init(PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
}
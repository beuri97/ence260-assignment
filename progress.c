/** @file   show.c
    @author HanByeol Yang(hya62), Blake W. Manson(bwm206)
    @date   15 October 2023
    @brief  handles LED1(Blue LED) and led-Matrix
*/
#include <avr/io.h>

#include "battleship.h"
#include "system.h"
#include "led.h"
#include "pacer.h"
#include "display.h"
#include "tinygl.h"
#include "../fonts/font5x5_1.h"
#include "progress.h"

#define PACER_RATE 500
#define MESSAGE_RATE 25


/**
 * @brief execute row movement of object
 * 
 * @param prev Starting point of the previous row of objects
 * @param curr Starting point of current row of object
 * @param col column location of object
 */
void move_in_row(uint8_t prev, uint8_t curr, uint8_t col)
{
    display_pixel_set(col, prev, 0);
    display_pixel_set(col, curr, 1);
}

/**
 * @brief check pixel in led-matrix is on
 * 
 * @param col matrix column
 * @param row matrix row
 * @return true if pixel is on,
 * @return false if pixel is off
 */
bool collision_check(uint8_t col, uint8_t row)
{
    return display_pixel_get(col, row);
}

/**
 * @brief show object on led-matrix to control/move object using navswitch
 * 
 * @param object the object being moved
 */
void object_control(object_t* object)
{
    bool done = 0;
    while(!done){
        pacer_wait();
        done = positioning(object);
        display_update();
        }

}

/**
 * @brief draw or remove ship into led-matrix
 * 
 * @param ship structure of ship that has start row, col and size information
 * @param val led status value 1 for led on 0 for other
*/
void draw_object(object_t* object, bool val)
{
    for(uint8_t i = object->row; i < (object->row + object->size+1); i++) {
        display_pixel_set(object->col, i, val);
    }
}

/**
 * @brief initilaise a start point of the ship to set its position
 * 
 * @param ship ship object informations to be initialise
 */
void ship_initialise_start_point(object_t* ship) {

    while(1) {
        if((ship->row + ship->size >= LEDMAT_ROWS_NUM))
        {
            ship->col++;
            ship->row = 0;
        } else if(display_pixel_get(ship->col, ship->row + ship->size) || display_pixel_get(ship->col, ship->row)) {
            ship->row++;
        } else {
            break;
        }
    }    
}

/**
 * @brief Initial game setup
*/
void ship_init(void)
{
    
    // indicate player can control their funkits
    led1_on();

    for(uint8_t i=0; i < TOTAL_NUM_SHIP; i++){     
        object_t ship = {.size = SHIP[i], .col=2, .row=1};

        // need to prevent ship's collision at the beginning of initialisation
        ship_initialise_start_point(&ship);
        draw_object(&ship, 1);
        object_control(&ship);
        //save ship information
        store_ship(i, ship);
    }
    
    // clear display to hide your ship position to opponent
    display_clear();
    display_update();

    // indicate players cannot control their funkits
    led1_off();
}

/**
 * @brief trigger function to setup to show message on led-matrix
 * 
 * @param message the message type to be sent
*/
void instruction_set(message_t message)
{
  
    switch (message)
    {
        case WELCOME:
            tinygl_text("Push any button to start!");
            bool stop = false;
            while(!stop) {
                pacer_wait();
                tinygl_update();
                stop = any_push();
            }
            display_clear();
            display_update();

            break;
        case PLAYER_TURN:
            tinygl_text("Fire your missile");
            led1_on();
            stop = false;
            while(!stop) {
                pacer_wait();
                tinygl_update();
                stop = any_push();
            }
            display_clear();
            display_update();

            break;

        case OPPONENT_TURN:
            led1_off();
            tinygl_text("Prepare for impact");
            stop = false;
            while(!stop) {
                pacer_wait();
                tinygl_update();
                stop = any_push();
            }
            display_clear();
            display_update();
            break;

        case WIN:
            tinygl_text("You win\0");

            //loop will execute arround 5 seconds
            while (1) {
                pacer_wait();
                tinygl_update();
                stop = any_push();
            }
            display_clear();
            display_update();
            break;
       
        case LOSE:
            led1_off();
            tinygl_text("You Lose!\0");

            while (1) {
                pacer_wait();
                tinygl_update();
                stop = any_push();
            }

            display_clear();
            display_update();
            break;

        case BOOM:
            TCNT1 = 0;
            uint16_t count = 0;
            led1_on();
            while(TCNT1 < 14062){
                if(++count  == 2344){
                    PORTC ^= BIT(2);
                    count = 0;
                }
            }
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
    tinygl_font_set (&font5x5_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
}
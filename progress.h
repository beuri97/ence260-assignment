/** @file   show.h
    @author HanByeol Yang(hya62), Blake W. Manson(bwm206)
    @date   15 October 2023
    @brief  handles LED1 and led-Matrix
*/
#ifndef PROGRESS_H
#define PROGRESS_H

#include <stdint.h>
#include <stdbool.h>

#include "object.h"


typedef enum {
    WELCOME,
    PLAYER_TURN,
    OPPONENT_TURN,
    WIN,
    LOSE,
    BOOM
} message_t;


bool check_game_over(void);

void object_show(void);

/**
 * @brief execute row movement of object
 * 
 * @param prev Starting point of the previous row of objects
 * @param curr Starting point of current row of object
 * @param col column location of object
 */
void move_in_row(uint8_t prev, uint8_t curr, uint8_t col);

/**
 * @brief check pixel in led-metrix is on
 * 
 * @param col matrix column
 * @param row matrix row
 * @return true if pixel is on,
 * @return false if pixel is off
 */
bool collision_check(uint8_t col, uint8_t row);

/**
 * @brief show object on led-matrix to control/move object using navswitch
 * 
 */
void object_control(object_t* object);

/**
 * @brief draw or remove ship into led-matriex
 * @param ship structure of ship that has start row, col and size information
 * @param val led status value 1 for led on 0 for other
*/
void draw_object(object_t* object, bool val);

/*Initial game setup*/
void ship_init(void);

/**
 * @brief turn on led1(BLUE LED)
*/
void led1_on(void);

/**
 * @brief turn off led1(BLUE LED)
*/
void led1_off(void);


/**
 * @brief trigger function to setup to show message on led-matrix
*/
void instruction_set(message_t message);

/**
 * @brief initialise LED1 and LED-matrix
*/
void led_interface_init(void);


#endif /*PROGRESS_H*/

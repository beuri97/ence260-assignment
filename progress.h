/** @file   show.c
    @author HanByeol Yang(hya62), Blake W. Manson(bwm206)
    @date   15 October 2023
    @brief  handles LED1 and led-Matrix
*/
#ifndef PROGRESS_H
#define PROGRESS_H

#include <stdint.h>


typedef enum {
    WELCOME,
    PLAYER_TURN,
    OPPONENT_TURN,
    WIN,
    LOOSE
} message_t;

/**
 * @brief initialise LED1 and LED-matrix
*/
void led_interface_init(void);

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
void insturction_set(message_t message);


#endif /*PROGRESS_H*/

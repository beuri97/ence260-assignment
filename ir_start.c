#include "system.h"
#include "pacer.h"
#include "ir_uart.h"

#define PACER_RATE 500

/**
 * Send and reveive setup state of each player, and set turn order of the game
*/
static uint8_t turnOrder = 1;

/**
 * @brief send the turn order to the other player
 * 
 * @param order the turn position for the player
*/
void sendDone(char order)
{
    ir_uart_putc(order);
}

/**
 * @brief receive the enemy player's turn order
 * 
 * @return returns the value of the enemy's turn position
*/
uint8_t receiveDone(void)
{
    uint8_t done = 0xFF;
    if (ir_uart_read_ready_p()){
        done = ir_uart_getc();
    }

    return done;
}

/**
 * @brief check if the player has finished setup, waits for other player to finish, then sets turn order
 * 
 * @return the turn position for the player
*/
uint8_t ir_start_init(void)
{
    ir_uart_init();
    uint8_t enemyStatus = receiveDone();

    if (enemyStatus != 0xFF) {
        turnOrder = 2;
        sendDone(1);
    } else {
        turnOrder = 1;
        sendDone(turnOrder);
    }
    return turnOrder;
}
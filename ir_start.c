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
    char doneChar = 0;
    if (ir_uart_read_ready_p()){
        doneChar = ir_uart_getc();
    }
    uint8_t done = (int)(doneChar);
    return done;
}

/**
 * @brief get the order position for the player
 * 
 * @return the order position for the player
*/
uint8_t getOrder(void)
{
    return turnOrder;
}

/**
 * @brief check if the player has finished setup, waits for other player to finish, then sets turn order
*/
void ir_start_init(void)
{
    bool bothReady = false;
    sendDone(turnOrder);
    while(enemyStatus!= 0){
        uint8_t enemyStatus = receiveDone();
    }
    if(enemyStatus == 1){
        turnOrder = 2;
        sendDone(2);
        bothReady = true;
    }
    if(enemyStatus == 2){
        bothReady = true;
    }
}
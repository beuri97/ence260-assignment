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
uint8_t reveiveDone(void)
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
 * 
 * @param finished 0 if the player is still setting up, 1 if done
*/
void ir_start_init(bool finished)
{
    while(!finished){
        uint8_t enemyStatus = revieveDone();

        if(enemyStatus == 1){
            turnOrder = 2;
        }
    }

    while(finished){
        sendDone(turnOrder);
        uint8_t enemyStatus = revieveDone();

        if(enemyStatus != 0){
            break;
        }
    }
}
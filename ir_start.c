#include "ir_uart.h"

/**
 * @brief send the turn order to the other player
 * 
 * @param order the turn position for the player
*/
void send(char order)
{
    ir_uart_putc(order);
}

/**
 * @brief receive the enemy player's turn order
 * 
 * @return returns the value of the enemy's turn position
*/
uint8_t receive(void)
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
void ir_init(void)
{
    ir_uart_init();
}

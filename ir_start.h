#ifndef IR_START_H
#define IR_START_H

#include <stdint.h>

/**
 * @brief send the turn order to the other player
 * 
 * @param order the turn position for the player
*/
void send(char order);

/**
 * @brief receive the enemy player's turn order
 * 
 * @return returns the value of the enemy's turn position
*/
uint8_t receive(void);

/**
 * @brief check if the player has finished setup, waits for other player to finish, then sets turn order
 * 
 * @return the turn position for the player
*/
void ir_init(void);

#endif //IR_START_H
#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <stdint.h>
#include <stdbool.h>

#include "object.h"

/*Store ship info into static array ships*/
void store_ship(uint8_t index, object_t ship);

void show_ships(void);

bool check_ship_hit(uint8_t missile_col, uint8_t missile_row);

bool positioning(object_t* object);

void control_interface_init(void);

/*Check if any navswitch buttons is pushed*/
bool any_push(void);

#endif //BATTLESHIP_H
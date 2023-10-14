#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <stdint.h>
#include <stdbool.h>

#include "object.h"


void ship_init(uint16_t rate);
bool positioning(object_t* object);
void draw_ship(object_t* ship, bool val);

#endif //BATTLESHIP_H
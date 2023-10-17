#ifndef MISSILE_H
#define MISSILE_H

#include "object.h"

object_t* missile_init(void);
void missile_shoot(object_t* missile);

#endif //MISSILE_H
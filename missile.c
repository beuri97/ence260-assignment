#include <stdlib.h>
#include <stdbool.h>

#include "missile.h"


void missile_init(object_t* missile)
{

    missile->row = 4;
    missile->col = 2;
    missile->size = MISSILE;
    missile->destroy=false;

}
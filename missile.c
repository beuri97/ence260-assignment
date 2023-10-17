#include <stdlib.h>
#include <stdbool.h>

#include "missile.h"
#include "progress.h"
#include "ir_start.h"


 object_t* missile_init(void)
{

    object_t* missile = malloc(sizeof(object_t));
    missile->row = 3;
    missile->col = 2;
    missile->size = MISSILE;
    missile->destroy=false;
    
    return missile;
}

void missile_shoot(object_t* missile)
{
    uint8_t send = ((missile->col) << 4) | (missile->row);

    sendDone(send);
    free(missile);
}
#include <stdlib.h>
#include <stdbool.h>

#include "missile.h"
#include "progress.h"
#include "ir_start.h"


void missile_init(object_t* missile)
{

    missile->row = 3;
    missile->col = 2;
    missile->size = MISSILE;
    missile->destroy=false;
    
}

void missile_shoot(void)
{
    object_t* missile = malloc(sizeof(object_t));
    missile_init(missile);
    draw_object(missile, 1);
    object_control(missile);

    //sendDone(missile->col);
    //sendDone(missile->row);

    free(missile);
}
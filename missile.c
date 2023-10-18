#include <stdlib.h>
#include <stdbool.h>

#include "missile.h"
#include "progress.h"
#include "ir_start.h"

/**
 * @brief create missile object to shoot
 * 
 * @return pointer to memory for missile object
*/
object_t* missile_init(void)
{
    object_t* missile = malloc(sizeof(object_t));
    missile->row = 3;
    missile->col = 2;
    missile->size = MISSILE;
    missile->destroy=false;
    
    return missile;
}
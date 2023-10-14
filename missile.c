#include "missile.h"
#include "navswitch.h"
#include "system.h"
#include "display.h"
#include "pacer.h"
#include "battleship.h"
#include "object.h"
#include "ir_start.h"


void missile_init(uint16_t rate)
{
    pacer_init(rate);
    navswitch_init();
    display_init();
    bool done = 0;
    object_t* missile = malloc(sizeof(object_t));
    missile->size = MISSILE;
    missile->col = 2;
    missile->row = 3;
    draw_ship(missile, 1);
    while(!done) {
        pacer_wait();
        done = positioning(missile);
        display_update();
    }
    sendDone(missile->col);
    sendDone(missile->row);
    free(missile);
    display_clear();
    display_update();
}
#include <avr/io.h>

#include "battleship.h"
#include "ledmat.h"
#include "navswitch.h"
#include "pacer.h"
#include "system.h"




uint8_t ship_initialise_start_point(uint8_t* col, uint8_t ship) {

}


/**
    Bitmap to display battleship postion to matrix-LED
*/ 
uint8_t ship_position[5] = {0x07, 0x33, 0x17, 0x00, 0x00};


bool collision_check(size_t col, uint8_t target) {
        
    if(target & (1<<7) || (ship_position[col] & target) ) {
        return 0;
    } else {
        return 1;
    }
}

bool ship_positioning(uint8_t ship, size_t col, size_t size) {

    navswitch_init();

    if(navswitch_push_event_p(NAVSWITCH_PUSH)) {
        return 1;
    } else if(navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        if(collision_check(ship_position[col], (ship << 1))) {
            ship_position[col] ^= ship;
            ship <<= 1;
            ship_position[col] |= ship;
        }
    } else if(navswitch_push_event_p(NAVSWITCH_NORTH)) {
        if(((ship >> 1) >= size) || collision_check(ship_position[col], (ship >> 1))) {
            ship_position[col] ^= ship;
            ship >>= 1;
            ship_position[col] |= ship;
        }
    } else if(navswitch_push_event_p(NAVSWITCH_WEST)) {
        if (col!=0 && collision_check(ship_position[col-1], ship_position[col])) {
            ship_position[col] ^= ship;
            col--;
            ship_position[col] |= ship;
        }

    } else if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        if(col != 4 && collision_check(ship_position[col+1], ship_position[col])){
            ship_position[col] ^= ship;
            col++;
            ship_position[col] |= ship;
        }
    }

    return 0;
 }

/**
    initialise and function to ship postioning
*/
void ship_init(void) {

    pacer_init(500);
    for(size_t i=0; i<3; i++){
        size_t col = 4;
        bool done = 0;
        // need to prevent ship's collision at the beginning of initialisation
        uint8_t unit = ship_initialise_start_point(&col, SHIP[i]);
        ship_position[col] |= unit;

        size_t led_col = 0;
        while(!done){
            pacer_wait();
            done = ship_positioning(unit, col, SHIP[i]);
            ledmat_display_column(ship_position[led_col], led_col);
            (led_col==LEDMAT_COLS_NUM-1) ? led_col = 0 : led_col++;
        }
    }

    DDRC |= (1<<2);
    PORTC |= (1 << 2);
}


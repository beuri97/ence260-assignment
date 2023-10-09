#include <avr/io.h>

#include "battleship.h"
#include "ledmat.h"
#include "navswitch.h"
#include "pacer.h"
#include "system.h"
#include "display.h"


/**
    Bitmap to display battleship postion to matrix-LED
*/ 
static uint8_t ship_position[5] = {0x00, 0x00, 0x00, 0x00, 0x00};

/**
 * @brief find the start point of the ship to set its position
 * 
 * @param col led_matrix column 0 to 4 inclusive and start from 4
 * @param ship initiall ship size
 * @return uint8_t returns 7-bits number that represent ship and its postion in the located column
 */
uint8_t ship_initialise_start_point(uint8_t* col, uint8_t ship) {

    char shift = 0;
    while(1) {
        //shift back and move to next column
        if((ship<<(shift))&(1<<(7))) {
            *col--;
            ship >>= shift;
            //reset shift to prevent number of bits are exceeding over 7
            shift = 0;
        } else if(ship_position[*col] & ship) {
            ship <<= ++shift;
        } else {
            break;
        }
    }

    return ship;

}


/**
 * @brief check if ship is collide with others when set the ship's position
 * 
 * @param col led_matrix column 0 to 4 inclusive
 * @param target current ship status
 * @return true if no collision event happens
 * @return false when collision event happens
 */
bool collision_check(size_t col, uint8_t target) {
        
    if(target & (1<<7) || (ship_position[col] & target) ) {
        return 0;
    } else {
        return 1;
    }
}

/**
 * @brief function about bitwise operation to change ship position
 * 
 * @param ship current ship status (include its current position)
 * @param col current ship postion in column
 * @param size current ship size
 * @return true when NAVSWITCH_PUSH push event is happen - represent ship positioning setup is finish
 * @return false otherwise
 */
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
 * @brief initiallize battleship setup - aka. initiallising game
 * 
 */
void ship_init(void) {

    pacer_init(500);
    ledmat_init();

    for(size_t i=0; i<3; i++){
        size_t col = 4;
        bool done = 0;
        // need to prevent ship's collision at the beginning of initialisation
        uint8_t unit = ship_initialise_start_point(&col, SHIP[i]);
        ship_position[col] |= unit;

        size_t led_col = 0;
        while(!done){
            pacer_wait();
            display_update();
            done = ship_positioning(unit, col, SHIP[i]);
            ledmat_display_column(ship_position[led_col], led_col);
            (led_col > LEDMAT_COLS_NUM-1) ? led_col = 0 : led_col++;
        }
    }

    DDRC |= (1<<2);
    PORTC |= (1 << 2);
}


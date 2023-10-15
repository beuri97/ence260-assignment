#include "battleship.h"
#include "navswitch.h"
#include "system.h"
#include "display.h"
#include "pacer.h"
#include "pio.h"
#include "button.h"

#define TOTAL_NUM_SHIP 3


/**
 * @brief an array of ship_t which save ships status and its position
 */
static object_t ships[TOTAL_NUM_SHIP];


/**
 * @brief draw or remove ship into led-matriex
 * @param ship structure of ship that has start row, col and size information
 * @param val led status value 1 for led on 0 for other
*/
void draw_ship(object_t* ship, bool val)
{
    for(uint8_t i = ship->row; i < (ship->row + ship->size+1); i++) {
        display_pixel_set(ship->col, i, val);
    }
}

/**
 * @brief initilaise a start point of the ship to set its position
 * @param ship ship object informations to be initialise
 */
void ship_initialise_start_point(object_t* ship) {

    while(1) {
        if((ship->row + ship->size >= LEDMAT_ROWS_NUM))
        {
            ship->col++;
            ship->row = 0;
        } else if(display_pixel_get(ship->col, ship->row + ship->size) || display_pixel_get(ship->col, ship->row)) {
            ship->row++;
        } else {
            break;
        }
    }    
}

/**
 * @brief ship shifting to initialise ships' position. Ship will not move if ship is going out of bound of led-matirx or
 * other ship is blocking its way.
 * 
 * @param ship structure of ship that has row, col, and its size
 * @return true when NAVSWITCH_PUSH push event is happen - represent ship position init is finish
 * @return false otherwise
 */
bool positioning(object_t* object) 
{
    int8_t check_point = 0;
    navswitch_update();
    if(navswitch_push_event_p(NAVSWITCH_PUSH)) {
        // finish setup ship location
        return 1;
    
    } else if(navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        check_point = (object->row + object->size +1);

        // move ship to left 
        if (check_point < LEDMAT_ROWS_NUM && !(display_pixel_get(object->col, check_point))) {
            display_pixel_set(object->col, object->row, 0);
            display_pixel_set(object->col, check_point, 1);
            object->row++;
            }


    } else if(navswitch_push_event_p(NAVSWITCH_NORTH)) {
        check_point = (object->row -1);

        // move to right
        if (check_point >= 0 && !(display_pixel_get(object->col, check_point))) {
            display_pixel_set(object->col, check_point, 1);
            display_pixel_set(object->col, object->row + object->size, 0);
            object->row--;
        }

    } else if(navswitch_push_event_p(NAVSWITCH_WEST)) {
        check_point = object->col -1;

        // move to up
        if (check_point >= 0 && 
           (display_pixel_get(check_point, (object->row + object->size)) == 0 && display_pixel_get(check_point, object->row) == 0)) {
            draw_ship(object, 0);
            object->col--;
            draw_ship(object, 1);
        }
        

    } else if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        check_point = object->col +1;

        //move to down
        if (check_point < LEDMAT_COLS_NUM && 
           (display_pixel_get(check_point, (object->row + object->size)) == 0 && display_pixel_get(check_point, object->row) == 0)) {
            draw_ship(object,0);
            object->col++;
            draw_ship(object,1);
        }
    }



    return 0;
 }


void control_interface_init(void)
{
    navswitch_init();
    button_init();


}

/**
 * @brief initiallize battleship setup - aka. initiallising game
 * 
 */
/*This function will move to module show*/
void ship_init(uint16_t rate) 
{

    pacer_init(rate);
    display_init();

    for(uint8_t i=0; i < TOTAL_NUM_SHIP; i++){     
        bool done = 0;
        object_t ship = {.size = SHIP[i], .col=2, .row=1};
        // need to prevent ship's collision at the beginning of initialisation
        ship_initialise_start_point(&ship);
        draw_ship(&ship, 1);

        while(!done){
            pacer_wait();
            done = positioning(&ship);
            display_update();
        }
        ships[i] = ship;
    }
    
    // clear display to hide your ship position to opponent
    display_clear();
    display_update();
}
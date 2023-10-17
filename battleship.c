#include "progress.h"
#include "battleship.h"
#include "navswitch.h"
#include "system.h"
#include "display.h"
#include "button.h"


/**
 * @brief an array of ship_t which save ships status and its position
*/
static object_t ships[TOTAL_NUM_SHIP];


bool check_all_ship_destroyed(void) 
{
    for(int8_t i=0; i< TOTAL_NUM_SHIP; i++) {
        if(ships[i].destroy == false) {
            return false;
        }
    }

    return true;
}


/**
 * @brief Store ship info into static array ships
*/
void store_ship(uint8_t index, object_t ship)
{
    ships[index] = ship;
}

/**
 * @brief Display all ships onto the LED matrix
*/
void show_ships(void)
{
    for(uint8_t i = 0; i < TOTAL_NUM_SHIP; i++) {
        object_t ship = ships[i];
        if(!ship.destroy) {
            draw_object(&ship, 1);
        }
    }
}

/**
 * @brief Check if a ship was hit by a missile. If yes, remove the ship from the matrix.
 * 
 * @param missile_col the column location of the missile fired
 * @param missile_row the row location of the missile fired
 * @return true if a ship is hit ||
 * @return false otherwise
*/
bool check_ship_hit(uint8_t missile_col, uint8_t missile_row)
{
    for(uint8_t i = 0; i < TOTAL_NUM_SHIP; i++) {
        if(missile_col == ships[i].col && (BIT(missile_row) & (0xF | BIT(ships[i].size) << ships[i].row))) {
            draw_object(&(ships[i]), 0);
            ships[i].destroy = true;
            return true;
        }
    }
    return false;
}

/**
 * @brief ship shifting to initialise ships' position. Ship will not move if ship is going out of bound of led-matirx or
 * other ship is blocking its way.
 * 
 * @param ship structure of ship that has row, col, and its size
 * @return true when NAVSWITCH_PUSH push event is happen - represent ship position init is finish || 
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
        if (check_point < LEDMAT_ROWS_NUM && !(collision_check(object->col, check_point))) {
            move_in_row(object->row, check_point, object->col);
            (object->row)++;
            }


    } else if(navswitch_push_event_p(NAVSWITCH_NORTH)) {
        check_point = (object->row -1);

        // move to right
        if (check_point >= 0 && !(collision_check(object->col, check_point))) {
            move_in_row(object->row+object->size, check_point, object->col);
            (object->row)--;
        }

    } else if(navswitch_push_event_p(NAVSWITCH_WEST)) {
        check_point = object->col -1;

        // move to up
        if (check_point >= 0 && 
           (collision_check(check_point, (object->row + object->size)) == 0 && collision_check(check_point, object->row) == 0)) {
            draw_object(object, 0);
            object->col--;
            draw_object(object, 1);
        }
        

    } else if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        check_point = object->col +1;

        //move to down
        if (check_point < LEDMAT_COLS_NUM && 
           (collision_check(check_point, (object->row + object->size)) == 0 && collision_check(check_point, object->row) == 0)) {
            draw_object(object,0);
            object->col++;
            draw_object(object,1);
        }
    }



    return 0;
 }

/**
 * @brief Check if any navswitch buttons is pushed'
*/
bool any_push(void)
{
    navswitch_update();
    return navswitch_push_event_p(NAVSWITCH_PUSH) || navswitch_push_event_p(NAVSWITCH_NORTH) || navswitch_push_event_p(NAVSWITCH_SOUTH) ||
            navswitch_push_event_p(NAVSWITCH_EAST) || navswitch_push_event_p(NAVSWITCH_WEST);
}

void control_interface_init(void)
{
    navswitch_init();
    button_init();
}
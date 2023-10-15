#include <stdlib.h>

#include "system.h"
#include "led.h"
#include "ir_start.h"
#include "../fonts/font5x7_1.h"
#include "object.h"
#include "missile.h"
#include "battleship.h"
#include "progress.h"

int main (void)
{
    system_init ();
    led_interface_init();
    control_interface_init();
    uint8_t number_of_ships = 3;
    bool finish = false;

    // I need this while loop
    while(1) {
    
    if(!finish) {
        instruction_set(WELCOME);
        ship_init();
        finish = true;
    }

    }
    uint8_t position = ir_start_init();
    if(position == 1) {
        instruction_set(PLAYER_TURN);
        object_t* missile = malloc(sizeof(object_t));
        missile_init(missile);
        draw_object(missile, 1);
        object_control(missile);

        //free missile
        free(missile);
    }
    while(number_of_ships > 0) {
        //display ships (not sure how)
        led_set(LED1, 0);
        uint8_t col = 0;
        uint8_t row = 0;

        while(col == 0) {
            col = receiveDone();
        }
        while(row == 0) {
            row = receiveDone();
        }
        bool hit; //= collisionCheck(col, row);
        if(hit) {
            number_of_ships--;
        }
        led_set(LED1, 1);
        //missile_init();
    }
}

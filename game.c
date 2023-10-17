#include <stdlib.h>

#include "system.h"
#include "led.h"
#include "ir_start.h"
#include "../fonts/font5x7_1.h"
#include "object.h"
#include "missile.h"
#include "battleship.h"
#include "progress.h"
#include "display.h"

int main (void)
{
    system_init ();
    led_interface_init();
    control_interface_init();
    uint8_t current_ship_number = 3;
    bool finish = false;

    // I need this while loop
    while(!finish) {
    
    if(!finish) {
        instruction_set(WELCOME);
        ship_init();
        finish = true;
    }

    }
    
    uint8_t position = ir_start_init();
    if(position == 1) {
        instruction_set(PLAYER_TURN);
        led_set(LED1, 1);
        missile_shoot();
        display_clear();
    }
    while(current_ship_number > 0) {
        show_ships();
        led_set(LED1, 0);
        uint8_t col = 0;
        uint8_t row = 0;

        while(col == 0) {
            display_update();
            col = receiveDone();
        }
        while(row == 0) {
            display_update();
            row = receiveDone();
        }
        bool hit = check_ship_hit(col, row);
        if(hit) {
            current_ship_number = current_ship_number - 1;
        }
        uint8_t finished = recieveDone();
        if(finished == 1) {
            break;
        }
        led_set(LED1, 1);
        missile_shoot();
        display_clear();
    }
    if(current_ship_number == 0) {
        sendDone(1);
        instruction_set(LOSE);
    } else {
        instruction_set(WIN);
    }
}

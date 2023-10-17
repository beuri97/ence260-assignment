#include <stdlib.h>

#include "system.h"
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
    bool finish = false;
    uint8_t turn = 0;

    // I need this while loop
    while(1) {
    
    if(!finish) {
        instruction_set(WELCOME);
        ship_init();
        finish = true;
        turn = ir_start_init();
        bool ready = receiveDone();
        while(!ready) {
            ready = receiveDone();
        }
    }

    if(turn == 1) {
        instruction_set(PLAYER_TURN);
        object_t* missile = missile_init();
        object_control(missile);
        missile_shoot(missile);
        display_clear();
        display_update();
        turn++;
    } else if (turn == 2){
        show_ships();
        instruction_set(OPPONENT_TURN);
        uint8_t get = 0;
        uint8_t col = 0;
        uint8_t row = 0;

        while(!get) {
            
            get = receiveDone();
            object_show();
            if(get) {
                row = get & 0xF;
                col = get >> 4;
                display_clear();
                display_update();
                bool hit = check_ship_hit(col, row);
                if(hit) {
                    instruction_set(BOOM);
                }
                if(check_game_over()) {
                    sendDone(1);
                }
                turn--;
            }
        }
    

        uint8_t finished = receiveDone();
        if(finished == 1 || check_game_over()) {
            if(check_game_over()) {
                instruction_set(LOSE);
            } else {
                instruction_set(WIN);
            }

        }

    }
   
    }
}

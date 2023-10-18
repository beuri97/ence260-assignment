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
            bool ready = (receiveDone() == 0xFF) ? 0 : 1;
            while(!ready) {
                ready = (receiveDone() == 0xFF) ? 0 : 1;
            }
        }

        if(turn == 1) {
            instruction_set(PLAYER_TURN);
            object_t* missile = missile_control();
            uint8_t send = ((missile->col) << 4) | (missile->row);
            sendDone(send);
            display_clear();
            display_update();
            free_missile(missile);
            turn++;

        } else if (turn == 2){
            instruction_set(OPPONENT_TURN);
            bool hit = missile_impact(&receiveDone);
            if(hit) {
                instruction_set(BOOM);
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

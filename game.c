#include "system.h"
#include "ir_start.h"
#include "../fonts/font5x7_1.h"
#include "object.h"
#include "battleship.h"
#include "progress.h"

/**
 * @brief main function to run program - Described sequence of the program.
*/
int main (void)
{
    system_init ();
    ir_init();
    led_interface_init();
    control_interface_init();
    bool finish_setup = false;
    uint8_t turn = 0;
    uint8_t game_over = 0;
    
    while(1) {
    
        if(!finish_setup) {
            instruction_set(WELCOME);
            ship_init();
            finish_setup = true;
            instruction_set(CHOOSE_ORDER);
            turn = choose_order();
        }

        if(turn == 1) {
            instruction_set(PLAYER_TURN);
            object_t* missile = missile_control();
            uint8_t coordinates = ((missile->col) << 4) | (missile->row);
            send(coordinates);
            free_missile(missile);
            turn++;
            game_over = receive();
            while(game_over == 0xFF) {
                game_over = receive();
            }

        } else if (turn == 2){
            instruction_set(OPPONENT_TURN);
            missile_impact(&receive);   
            turn--;  
            if(check_game_over()) {
                game_over = 1;
            } else {
                game_over = 0;
            }
            send(game_over);
        }

        if(game_over == 1) {
            if(check_game_over()) {
                instruction_set(LOSE);
                finish_setup = false;
            } else {
                instruction_set(WIN);
                finish_setup = false;
            }
        }
    }
}

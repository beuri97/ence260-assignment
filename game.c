#include "system.h"
#include "battleship.h"
#include "led.h"

int main (void)
{
    system_init ();
    led_init();
    led_set(LED1, 1);
    ship_init();
    led_set(LED1, 0);

    while (1)
    {

        break;

    }
}

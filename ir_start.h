#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

void sendDone(char order);
uint8_t receiveDone(void);
uint8_t getOrder(void);
void ir_start_init(void);
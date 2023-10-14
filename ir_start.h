#ifndef IR_START_H
#define IR_START_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

void sendDone(char order);
uint8_t receiveDone(void);
uint8_t getOrder(void);
uint8_t ir_start_init(void);

#endif //IR_START_H
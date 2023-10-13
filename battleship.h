#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>



#define LARGE 3
#define MEDIUM 2
#define SMALL 1
#define SHIP (uint8_t[]){LARGE, MEDIUM, SMALL}

typedef struct {
    uint8_t size;
    uint8_t col;
    uint8_t row;
    bool destroy;
} ship_t;

void ship_init(uint16_t rate);
bool positioning(void);
bool collision_check(size_t col, uint8_t target);

#endif //BATTLESHIP_H
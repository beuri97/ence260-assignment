#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>


#define LARGE 0b1111
#define MEDIUM 0b111
#define SMALL 0b11
#define SHIP (uint8_t[]){LARGE, MEDIUM, SMALL}

void ship_init(void);
bool positioning(void);
bool collision_check(size_t col, uint8_t target);
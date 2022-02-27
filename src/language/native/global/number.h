#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <stdlib.h>

#include "primitive.h"

typedef struct number_s {
    char type;
    mug_primitive *primitive;
} number;

void add(number *left_side, number *right_side);
void subtract(number *left_side, number *right_side);
void multiply(number *left_side, number *right_side);
void divide(number *left_side, number *right_side);

#endif
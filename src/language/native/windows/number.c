#include <stdio.h>
#include <stdlib.h>

#include "number.h"

void add(number *left_side, number *right_side) {
    if(left_side == 0x00 || right_side == 0x00) {
        return;
    }

    if(left_side->type > 0x05 || right_side->type > 0x05) {
        return;
    }

    mug_primitive left_primitive = *left_side->primitive;
    mug_primitive right_primitive = *right_side->primitive;

    switch (left_side->type) {
        case 0x00:
            left_primitive.mug_byte->value += right_primitive.mug_byte->value;
            break;
        case 0x01:
            left_primitive.mug_short->value += right_primitive.mug_short->value;
            break;
        case 0x02:
            left_primitive.mug_int->value += right_primitive.mug_int->value;
            break;
        case 0x03:
            left_primitive.mug_long->value += right_primitive.mug_long->value;
            break;
        case 0x05:
            left_primitive.mug_float->value += right_primitive.mug_float->value;
            break;
        case 0x06:
            left_primitive.mug_double->value += right_primitive.mug_double->value;
            break;
        default:
            break;
    }
}

void subtract(number *left_side, number *right_side) {
    if(left_side == 0x00 || right_side == 0x00) {
        return;
    }

    if(left_side->type > 0x05 || right_side->type > 0x05) {
        return;
    }

    mug_primitive left_primitive = *left_side->primitive;
    mug_primitive right_primitive = *right_side->primitive;

    switch (left_side->type) {
        case 0x00:
            left_primitive.mug_byte->value -= right_primitive.mug_byte->value;
            break;
        case 0x01:
            left_primitive.mug_short->value -= right_primitive.mug_short->value;
            break;
        case 0x02:
            left_primitive.mug_int->value -= right_primitive.mug_int->value;
            break;
        case 0x03:
            left_primitive.mug_long->value -= right_primitive.mug_long->value;
            break;
        case 0x05:
            left_primitive.mug_float->value -= right_primitive.mug_float->value;
            break;
        case 0x06:
            left_primitive.mug_double->value -= right_primitive.mug_double->value;
            break;
        default:
            break;
    }
}

void multiply(number *left_side, number *right_side) {
    if(left_side == 0x00 || right_side == 0x00) {
        return;
    }

    if(left_side->type > 0x05 || right_side->type > 0x05) {
        return;
    }

    mug_primitive left_primitive = *left_side->primitive;
    mug_primitive right_primitive = *right_side->primitive;

    switch (left_side->type) {
        case 0x00:
            left_primitive.mug_byte->value *= right_primitive.mug_byte->value;
            break;
        case 0x01:
            left_primitive.mug_short->value *= right_primitive.mug_short->value;
            break;
        case 0x02:
            left_primitive.mug_int->value *= right_primitive.mug_int->value;
            break;
        case 0x03:
            left_primitive.mug_long->value *= right_primitive.mug_long->value;
            break;
        case 0x05:
            left_primitive.mug_float->value *= right_primitive.mug_float->value;
            break;
        case 0x06:
            left_primitive.mug_double->value *= right_primitive.mug_double->value;
            break;
        default:
            break;
    }
}

void divide(number *left_side, number *right_side) {
    if(left_side == 0x00 || right_side == 0x00) {
        return;
    }

    if(left_side->type > 0x05 || right_side->type > 0x05) {
        return;
    }

    mug_primitive left_primitive = *left_side->primitive;
    mug_primitive right_primitive = *right_side->primitive;

    switch (left_side->type) {
        case 0x00:
            left_primitive.mug_byte->value /= right_primitive.mug_byte->value;
            break;
        case 0x01:
            left_primitive.mug_short->value /= right_primitive.mug_short->value;
            break;
        case 0x02:
            left_primitive.mug_int->value /= right_primitive.mug_int->value;
            break;
        case 0x03:
            left_primitive.mug_long->value /= right_primitive.mug_long->value;
            break;
        case 0x05:
            left_primitive.mug_float->value /= right_primitive.mug_float->value;
            break;
        case 0x06:
            left_primitive.mug_double->value /= right_primitive.mug_double->value;
            break;
        default:
            break;
    }
}
/**
 * Copyright 2022 Daniel Fiala
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>

#include "number.h"

void add(number *left_side, number *right_side)
{
    if (left_side == 0x00 || right_side == 0x00)
    {
        return;
    }

    if (left_side->type > 0x05 || right_side->type > 0x05)
    {
        return;
    }

    mug_primitive left_primitive = *left_side->primitive;
    mug_primitive right_primitive = *right_side->primitive;

    switch (left_side->type)
    {
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

void subtract(number *left_side, number *right_side)
{
    if (left_side == 0x00 || right_side == 0x00)
    {
        return;
    }

    if (left_side->type > 0x05 || right_side->type > 0x05)
    {
        return;
    }

    mug_primitive left_primitive = *left_side->primitive;
    mug_primitive right_primitive = *right_side->primitive;

    switch (left_side->type)
    {
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

void multiply(number *left_side, number *right_side)
{
    if (left_side == 0x00 || right_side == 0x00)
    {
        return;
    }

    if (left_side->type > 0x05 || right_side->type > 0x05)
    {
        return;
    }

    mug_primitive left_primitive = *left_side->primitive;
    mug_primitive right_primitive = *right_side->primitive;

    switch (left_side->type)
    {
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

void divide(number *left_side, number *right_side)
{
    if (left_side == 0x00 || right_side == 0x00)
    {
        return;
    }

    if (left_side->type > 0x05 || right_side->type > 0x05)
    {
        return;
    }

    mug_primitive left_primitive = *left_side->primitive;
    mug_primitive right_primitive = *right_side->primitive;

    switch (left_side->type)
    {
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
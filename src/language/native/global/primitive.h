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

#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <string.h>
#include <stdlib.h>

#include "conversion.h"

typedef enum primitive_type_e primitive_type;

typedef struct byte_s mug_byte;
typedef struct short_s mug_short;
typedef struct int_s mug_int;
typedef struct long_s mug_long;
typedef struct float_s mug_float;
typedef struct double_s mug_double;
typedef struct string_s mug_string;
typedef struct boolean_s mug_boolean;

enum primitive_type_e
{
    BYTE,
    SHORT,
    INT,
    LONG,
    FLOAT,
    DOUBLE,
    STRING,
    BOOL
};

typedef union primitive_u
{
    mug_byte *mug_byte;
    mug_short *mug_short;
    mug_int *mug_int;
    mug_long *mug_long;
    mug_float *mug_float;
    mug_double *mug_double;
    mug_string *mug_string;
    mug_boolean *mug_boolean;
} mug_primitive;

struct byte_s
{
    char value;
};

struct short_s
{
    short value;
};

struct int_s
{
    int value;
};

struct long_s
{
    long value;
};

struct float_s
{
    float value;
};

struct double_s
{
    double value;
};

struct string_s
{
    char *value;
};

struct boolean_s
{
    char value;
};

#define PROCESS_PRIMITIVE(conversion_name, result, left_side, left_side_type, right_side, right_side_type, operator)     \
    result->mug_##conversion_name = malloc(sizeof(mug_##conversion_name));                                               \
    if (result->mug_##conversion_name == 0x00 || convert_primitive(right_side, right_side_type, left_side_type) == 0x01) \
    {                                                                                                                    \
        return 0x00;                                                                                                     \
    }                                                                                                                    \
                                                                                                                         \
    mug_##conversion_name *_result = result->mug_##conversion_name;                                                      \
    mug_##conversion_name *_left_side = left_side->mug_##conversion_name;                                                \
    mug_##conversion_name *_right_side = right_side->mug_##conversion_name;                                              \
                                                                                                                         \
    _result->value = _left_side->value operator _right_side->value;                                                      \
    break;

#define PROCESS_OPERATION(left_side, left_side_type, right_side, right_side_type, operator)                  \
    mug_primitive *result = malloc(sizeof(mug_primitive));                                                   \
    if (result == 0x00)                                                                                      \
    {                                                                                                        \
        return 0x00;                                                                                         \
    }                                                                                                        \
                                                                                                             \
    switch (left_side_type)                                                                                  \
    {                                                                                                        \
    case 0x00:                                                                                               \
    {                                                                                                        \
        PROCESS_PRIMITIVE(byte, result, left_side, left_side_type, right_side, right_side_type, operator);   \
        break;                                                                                               \
    }                                                                                                        \
                                                                                                             \
    case 0x01:                                                                                               \
    {                                                                                                        \
        PROCESS_PRIMITIVE(short, result, left_side, left_side_type, right_side, right_side_type, operator);  \
        break;                                                                                               \
    }                                                                                                        \
                                                                                                             \
    case 0x02:                                                                                               \
    {                                                                                                        \
        PROCESS_PRIMITIVE(int, result, left_side, left_side_type, right_side, right_side_type, operator);    \
        break;                                                                                               \
    }                                                                                                        \
                                                                                                             \
    case 0x03:                                                                                               \
    {                                                                                                        \
        PROCESS_PRIMITIVE(long, result, left_side, left_side_type, right_side, right_side_type, operator);   \
        break;                                                                                               \
    }                                                                                                        \
                                                                                                             \
    case 0x04:                                                                                               \
    {                                                                                                        \
        PROCESS_PRIMITIVE(float, result, left_side, left_side_type, right_side, right_side_type, operator);  \
        break;                                                                                               \
    }                                                                                                        \
                                                                                                             \
    case 0x05:                                                                                               \
    {                                                                                                        \
        PROCESS_PRIMITIVE(double, result, left_side, left_side_type, right_side, right_side_type, operator); \
        break;                                                                                               \
    }                                                                                                        \
                                                                                                             \
    default:                                                                                                 \
        break;                                                                                               \
    }                                                                                                        \
                                                                                                             \
    return result;

#define CONVERT_PRIMITIVE(conversion_name, primitive, original, conversion_type)                          \
    if (primitive == 0x00)                                                                                \
    {                                                                                                     \
        return 0x00;                                                                                      \
    }                                                                                                     \
                                                                                                          \
    switch (conversion_type)                                                                              \
    {                                                                                                     \
    case 0x00:                                                                                            \
    {                                                                                                     \
        primitive->mug_byte = malloc(sizeof(mug_byte));                                                   \
        if (primitive->mug_byte == 0x00 || check_##conversion_name##_conversion(original->value, 0x00))   \
        {                                                                                                 \
            return 0x00;                                                                                  \
        }                                                                                                 \
                                                                                                          \
        primitive->mug_byte->value = original->value;                                                     \
        break;                                                                                            \
    }                                                                                                     \
    case 0x01:                                                                                            \
    {                                                                                                     \
        primitive->mug_short = malloc(sizeof(mug_short));                                                 \
        if (primitive->mug_short == 0x00 || check_##conversion_name##_conversion(original->value, 0x01))  \
        {                                                                                                 \
            return 0x00;                                                                                  \
        }                                                                                                 \
                                                                                                          \
        primitive->mug_short->value = original->value;                                                    \
        break;                                                                                            \
    }                                                                                                     \
                                                                                                          \
    case 0x02:                                                                                            \
    {                                                                                                     \
        primitive->mug_int = malloc(sizeof(mug_int));                                                     \
        if (primitive->mug_int == 0x00 || check_##conversion_name##_conversion(original->value, 0x02))    \
        {                                                                                                 \
            return 0x00;                                                                                  \
        }                                                                                                 \
                                                                                                          \
        primitive->mug_int->value = original->value;                                                      \
        break;                                                                                            \
    }                                                                                                     \
                                                                                                          \
    case 0x03:                                                                                            \
    {                                                                                                     \
        primitive->mug_long = malloc(sizeof(mug_long));                                                   \
        if (primitive->mug_long == 0x00 || check_##conversion_name##_conversion(original->value, 0x03))   \
        {                                                                                                 \
            return 0x00;                                                                                  \
        }                                                                                                 \
                                                                                                          \
        primitive->mug_long->value = original->value;                                                     \
        break;                                                                                            \
    }                                                                                                     \
                                                                                                          \
    case 0x04:                                                                                            \
    {                                                                                                     \
        primitive->mug_float = malloc(sizeof(mug_float));                                                 \
        if (primitive->mug_float == 0x00 || check_##conversion_name##_conversion(original->value, 0x04))  \
        {                                                                                                 \
            return 0x00;                                                                                  \
        }                                                                                                 \
                                                                                                          \
        primitive->mug_float->value = original->value;                                                    \
        break;                                                                                            \
    }                                                                                                     \
                                                                                                          \
    case 0x05:                                                                                            \
    {                                                                                                     \
        primitive->mug_double = malloc(sizeof(mug_double));                                               \
        if (primitive->mug_double == 0x00 || check_##conversion_name##_conversion(original->value, 0x05)) \
        {                                                                                                 \
            return 0x00;                                                                                  \
        }                                                                                                 \
                                                                                                          \
        primitive->mug_double->value = original->value;                                                   \
        break;                                                                                            \
    }                                                                                                     \
                                                                                                          \
    case 0x06:                                                                                            \
    {                                                                                                     \
        return 0x00;                                                                                      \
    }                                                                                                     \
                                                                                                          \
    case 0x07:                                                                                            \
    {                                                                                                     \
        primitive->mug_boolean = malloc(sizeof(mug_boolean));                                             \
        if (primitive->mug_boolean == 0x00)                                                               \
        {                                                                                                 \
            return 0x00;                                                                                  \
        }                                                                                                 \
                                                                                                          \
        if (original->value == 0x00)                                                                      \
        {                                                                                                 \
            primitive->mug_boolean->value = 0x00;                                                         \
        }                                                                                                 \
        else if (original->value == 0x01)                                                                 \
        {                                                                                                 \
            primitive->mug_boolean->value = 0x01;                                                         \
        }                                                                                                 \
        else                                                                                              \
        {                                                                                                 \
            return 0x00;                                                                                  \
        }                                                                                                 \
                                                                                                          \
        break;                                                                                            \
    }                                                                                                     \
    default:                                                                                              \
        break;                                                                                            \
    }                                                                                                     \
                                                                                                          \
    free(original);

char create_primitive(mug_primitive *primitive, char *data);
char *get_name(primitive_type type);

char convert_primitive(mug_primitive *primitive, primitive_type type, primitive_type conversion_type);

mug_primitive *sum_primitive(mug_primitive *left_side, char left_side_type, mug_primitive *right_side, char right_side_type);
mug_primitive *subtract_primitive(mug_primitive *left_side, char left_side_type, mug_primitive *right_side, char right_side_type);
mug_primitive *multiply_primitive(mug_primitive *left_side, char left_side_type, mug_primitive *right_side, char right_side_type);
mug_primitive *divide_primitive(mug_primitive *left_side, char left_side_type, mug_primitive *right_side, char right_side_type);

#endif
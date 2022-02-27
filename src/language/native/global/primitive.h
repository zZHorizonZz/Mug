#ifndef PRIMITIVE_H
#define PRIMITIVE_H

typedef union primitive_u {
    mug_byte mug_byte;
    mug_short mug_short;
    mug_int mug_int;
    mug_long mug_long;
    mug_float mug_float;
    mug_double mug_double;
    mug_string mug_string;
    mug_boolean mug_boolean;
} mug_primitive;

typedef struct byte_s {
    char value;
} mug_byte;

typedef struct short_s {
    short value;
} mug_short;

typedef struct int_s {
    int value;
} mug_int;

typedef struct long_s {
    long value;
} mug_long;

typedef struct float_s {
    float value;
} mug_float;

typedef struct double_s {
    double value;
} mug_double;

typedef struct string_s {
    char *value;
} mug_string;

typedef struct boolean_s {
    char value;
} mug_boolean;

#endif
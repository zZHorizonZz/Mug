#ifndef PRIMITIVE_H
#define PRIMITIVE_H

typedef struct byte_s mug_byte;
typedef struct short_s mug_short;
typedef struct int_s mug_int;
typedef struct long_s mug_long;
typedef struct float_s mug_float;
typedef struct double_s mug_double;
typedef struct string_s mug_string;
typedef struct boolean_s mug_boolean;

typedef union primitive_u {
    mug_byte *mug_byte;
    mug_short *mug_short;
    mug_int *mug_int;
    mug_long *mug_long;
    mug_float *mug_float;
    mug_double *mug_double;
    mug_string *mug_string;
    mug_boolean *mug_boolean;
} mug_primitive;

struct byte_s {
    char value;
};

struct short_s {
    short value;
};

struct int_s {
    int value;
};

struct long_s {
    long value;
};

struct float_s {
    float value;
};

struct double_s {
    double value;
};

struct string_s {
    char *value;
};

struct boolean_s {
    char value;
};

#endif
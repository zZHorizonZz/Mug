#ifndef BUFFER_H
#define BUFFER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct buffer_s
{
    char *buffer;

    int length;
    int write_index;
    int read_index;
} buffer;

typedef union float_int
{
    float _float;
    int _int;
} float_int;

typedef union double_long
{
    double _double;
    long _long;
} double_long;

void write_byte(buffer *buffer, char value);
void set_byte(buffer *buffer, int index, char value);
void write_short(buffer *buffer, short value);
void set_short(buffer *buffer, int index, short value);
void write_int(buffer *buffer, int value);
void set_int(buffer *buffer, int index, int value);
void write_long(buffer *buffer, long value);
void set_long(buffer *buffer, int index, long value);
void write_float(buffer *buffer, float value);
void set_float(buffer *buffer, int index, float value);
void write_double(buffer *buffer, double value);
void set_double(buffer *buffer, int index, double value);
void write_string(buffer *buffer, char *value);
void set_string(buffer *buffer, int index, char *value);

#endif
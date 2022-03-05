#include "buffer.h"

void write_byte(buffer *buffer, char value)
{
    set_byte(buffer, buffer->write_index, value);
    buffer->write_index++;
}

void set_byte(buffer *buffer, int index, char value)
{
    if (buffer->buffer == 0x00)
    {
        buffer->buffer = malloc(sizeof(char));
    }
    else if (index >= buffer->length)
    {
        char *tmp = realloc(buffer->buffer, buffer->length + sizeof(char));
        buffer->buffer = tmp;
    }

    buffer->buffer[index] = value;
    buffer->length += sizeof(char);
}

void write_short(buffer *buffer, short value)
{
    set_short(buffer, buffer->write_index, value);
    buffer->write_index += 2;
}

void set_short(buffer *buffer, int index, short value)
{
    if (buffer->buffer == 0x00)
    {
        buffer->buffer = malloc(sizeof(short));
    }
    else if (index + 0x01 >= buffer->length)
    {
        char *tmp = realloc(buffer->buffer, buffer->length + sizeof(short));
        buffer->buffer = tmp;
    }

    buffer->buffer[index] = value & 0xff;
    buffer->buffer[index + 1] = (value >> 0x08) & 0xff;
    buffer->length += sizeof(short);
}

void write_int(buffer *buffer, int value)
{
    set_int(buffer, buffer->write_index, value);
    buffer->write_index += 4;
}

void set_int(buffer *buffer, int index, int value)
{
    if (buffer->buffer == 0x00)
    {
        buffer->buffer = malloc(sizeof(int));
    }
    else if (index + 0x03 >= buffer->length)
    {
        char *tmp = realloc(buffer->buffer, buffer->length + sizeof(int));
        buffer->buffer = tmp;
    }

    for (size_t i = 0; i < sizeof(int); i++)
    {
        buffer->buffer[index + i] = (value >> i * sizeof(int)) & 0xff;
    }

    buffer->length += sizeof(int);
}

void write_long(buffer *buffer, long value)
{
    set_long(buffer, buffer->write_index, value);
    buffer->write_index += 8;
}

void set_long(buffer *buffer, int index, long value)
{
    if (buffer->buffer == 0x00)
    {
        buffer->buffer = malloc(sizeof(long));
    }
    else if (index + 0x07 >= buffer->length)
    {
        char *tmp = realloc(buffer->buffer, buffer->length + sizeof(long));
        buffer->buffer = tmp;
    }

    for (size_t i = 0; i < sizeof(long); i++)
    {
        buffer->buffer[index + i] = (value >> i * sizeof(long)) & 0xff;
    }

    buffer->length += sizeof(long);
}

void write_float(buffer *buffer, float value)
{
    set_float(buffer, buffer->write_index, value);
}

void set_float(buffer *buffer, int index, float value)
{
    float_int conversion = {value};
    write_int(buffer, conversion._int);
}

void write_double(buffer *buffer, double value)
{
    set_double(buffer, buffer->write_index, value);
}

void set_double(buffer *buffer, int index, double value)
{
    double_long conversion = {value};
    write_long(buffer, conversion._long);
}

void write_string(buffer *buffer, char *value)
{
    set_string(buffer, buffer->write_index, value);
    buffer->write_index += strlen(value);
}

void set_string(buffer *buffer, int index, char *value)
{
    if (buffer->buffer == 0x00)
    {
        buffer->buffer = malloc(strlen(value));
    }
    else if (index + 0x07 >= buffer->length)
    {
        char *tmp = realloc(buffer->buffer, buffer->length + strlen(value));
        buffer->buffer = tmp;
    }

    for (size_t i = 0; i < strlen(value); i++)
    {
        buffer->buffer[index + i] = value[i];
    }

    buffer->length += strlen(value);
}
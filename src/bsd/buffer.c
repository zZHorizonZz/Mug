#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct buffer {
    char *buffer;
    
    int length;
    int write_index;
    int read_index;
} buffer;

typedef union float_int {
    float _float;
    int _int;
} float_int;

typedef union double_long {
    double _double;
    long _long;
} double_long;

void write_byte(buffer *buffer, char value);
void write_byte(buffer *buffer, int index, char value);
void write_short(buffer *buffer, short value);
void write_short(buffer *buffer, int index, short value);
void write_int(buffer *buffer, int value);
void write_int(buffer *buffer, int index, int value);
void write_long(buffer *buffer, long value);
void write_long(buffer *buffer, int index, long value);
void write_float(buffer *buffer, float value);
void write_float(buffer *buffer, int index, float value);
void write_double(buffer *buffer, double value);
void write_double(buffer *buffer, int index, double value);
void write_string(buffer *buffer, char *value);
void write_string(buffer *buffer, int index, char *value);

void write_byte(buffer *buffer, char value) {
    write_byte(buffer, buffer->length, value);
}

void write_byte(buffer *buffer, int index, char value) {
    if(buffer->buffer == 0x00) {
        buffer->buffer = malloc(sizeof(char));
    } else if(index >= buffer->length) {
        char *tmp = realloc(buffer->buffer, buffer->length + sizeof(char));
        buffer->length += sizeof(char);
    
        free(buffer->buffer);
        buffer->buffer = tmp;
    }

    buffer->buffer[index] = value;
}

void write_short(buffer *buffer, short value) {
    write_short(buffer, buffer->length, value);    
}

void write_short(buffer *buffer, int index, short value) {
    if(buffer->buffer == 0x00) {
        buffer->buffer = malloc(sizeof(short));
    } else if(index + 0x01 >= buffer->length) {
        char *tmp = realloc(buffer->buffer, buffer->length + sizeof(short));
        buffer->length += sizeof(short);
    
        free(buffer->buffer);
        buffer->buffer = tmp;
    }

    buffer->buffer[index] = value & 0xff;
    buffer->buffer[index + 1] = (value >> 0x08) & 0xff;
}

void write_int(buffer *buffer, int value) {
    write_int(buffer, buffer->length, value);
}

void write_int(buffer *buffer, int index, int value) {
    if(buffer->buffer == 0x00) {
        buffer->buffer = malloc(sizeof(int));
    } else if(index + 0x03 >= buffer->length) {
        char *tmp = realloc(buffer->buffer, buffer->length + sizeof(int));
        buffer->length += sizeof(int);
    
        free(buffer->buffer);
        buffer->buffer = tmp;
    }

    for (size_t i = 0; i < sizeof(int); i++) {
        buffer->buffer[index + i] = (value >> i * sizeof(int)) & 0xff;
    }
}

void write_long(buffer *buffer, long value) {
    write_long(buffer, buffer->length, value);
}

void write_long(buffer *buffer, int index, long value) {
    if(buffer->buffer == 0x00) {
        buffer->buffer = malloc(sizeof(long));
    } else if(index + 0x07 >= buffer->length) {
        char *tmp = realloc(buffer->buffer, buffer->length + sizeof(long));
        buffer->length += sizeof(long);
    
        free(buffer->buffer);
        buffer->buffer = tmp;
    }

    for (size_t i = 0; i < sizeof(long); i++) {
        buffer->buffer[index + i] = (value >> i * sizeof(long)) & 0xff;
    }
}

void write_float(buffer *buffer, float value) {
    write_float(buffer, buffer->length, value);
}

void write_float(buffer *buffer, int index, float value) {
    float_int conversion = { value };
    write_int(buffer, conversion._int);    
}

void write_double(buffer *buffer, double value) {
    write_double(buffer, buffer->length, value);
}

void write_double(buffer *buffer, int index, double value) {
    double_long conversion = { value };
    write_double(buffer, conversion._double);    
}

void write_string(buffer *buffer, char *value) {
    write_string(buffer, buffer->length, value);
}

void write_string(buffer *buffer, int index, char *value) {
    if(buffer->buffer == 0x00) {
        buffer->buffer = malloc(strlen(value));
    } else if(index + 0x07 >= buffer->length) {
        char *tmp = realloc(buffer->buffer, buffer->length + strlen(value));
        buffer->length += strlen(value);
    
        free(buffer->buffer);
        buffer->buffer = tmp;
    }

    for (size_t i = 0; i < strlen(value); i++) {
        buffer->buffer[index + i] = value[i];
    }
}
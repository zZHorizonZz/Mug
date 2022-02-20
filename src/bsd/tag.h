#ifndef TAG_H
#define TAG_H

#include <stdlib.h>
#include <stdio.h>

typedef struct list_tag_s list_tag;
typedef struct single_type_list_tag_s single_type_list_tag;
typedef struct mapped_list_tag_s mapped_list_tag;
typedef struct byte_tag_s byte_tag;
typedef struct short_tag_s short_tag;
typedef struct int_tag_s int_tag;
typedef struct long_tag_s long_tag;
typedef struct float_tag_s float_tag;
typedef struct double_tag_s double_tag;
typedef struct string_tag_s string_tag;
typedef struct boolean_tag_s boolean_tag;

typedef union tag_u {
    list_tag *list_tag;
    single_type_list_tag *single_type_list_tag;
    mapped_list_tag *mapped_list_tag;
    byte_tag *byte_tag;
    short_tag *short_tag;
    int_tag *int_tag;
    long_tag *long_tag;
    float_tag *float_tag;
    double_tag *double_tag;
    string_tag *string_tag;
    boolean_tag *boolean_tag;
} tag;

struct list_tag_s {
    tag **list;
    int list_size; 
};

struct single_type_list_tag_s {
    char type;
    tag **list;
    int list_size;
};

struct mapped_list_tag_s {
    char **mapping;
    tag **list;
    int list_size;
};

struct byte_tag_s {
    char value;
};

struct short_tag_s {
    short value;
};

struct int_tag_s {
    int value;
};

struct long_tag_s {
    long value;
};

struct float_tag_s {
    float value;
};

struct double_tag_s {
    double value;
};

struct string_tag_s {
    char *value;
};

struct boolean_tag_s {
    char value;
};

void create_list_tag(tag *tag);
void create_single_type_list_tag(tag *tag, char type);
void create_mapped_list_tag(tag *tag);
void create_byte_tag(tag *tag, char value);
void create_short_tag(tag *tag, short value);
void create_int_tag(tag *tag, int value);
void create_long_tag(tag *tag, long value);
void create_float_tag(tag *tag, float value);
void create_double_tag(tag *tag, double value);
void create_string_tag(tag *tag, char *value);
void create_boolean_tag(tag *tag, char value);

int size_of_mappings(tag *tag);

void create_list_tag(tag *tag) {
    list_tag *list = calloc(2, sizeof(tag));

    tag->list_tag = list;
}

void create_single_type_list_tag(tag *tag, char type) {
    single_type_list_tag *list = calloc(3, sizeof(tag));
    list->type = type;

    tag->single_type_list_tag = list;
}

void create_mapped_list_tag(tag *tag) {
    mapped_list_tag *list = calloc(3, sizeof(tag));

    tag->mapped_list_tag = list;
}

void create_byte_tag(tag *tag, char value) {
    byte_tag *byte_tag = calloc(1, sizeof(tag));
    byte_tag->value = value;

    tag->byte_tag = byte_tag;
}

void create_short_tag(tag *tag, short value) {
    short_tag *short_tag = calloc(1, sizeof(tag));
    short_tag->value = value;

    tag->short_tag = short_tag;
}

void create_int_tag(tag *tag, int value) {
    int_tag *int_tag = calloc(1, sizeof(tag));
    int_tag->value = value;
    
    tag->int_tag = int_tag;
}

void create_long_tag(tag *tag, long value) {
    long_tag *long_tag = calloc(1, sizeof(tag));
    long_tag->value = value;

    tag->long_tag = long_tag;
}

void create_float_tag(tag *tag, float value) {
    float_tag *float_tag = calloc(1, sizeof(tag));
    float_tag->value = value;

    tag->float_tag = float_tag;
}

void create_double_tag(tag *tag, double value) {
    double_tag *double_tag = calloc(1, sizeof(tag));
    double_tag->value = value;

    tag->double_tag = double_tag;
}

void create_string_tag(tag *tag, char *value) {
    string_tag *string_tag = calloc(1, sizeof(tag));
    string_tag->value = value;

    tag->string_tag = string_tag;
}

void create_boolean_tag(tag *tag, char value) {
    boolean_tag *boolean_tag = calloc(1, sizeof(tag));
    boolean_tag->value = value;

    tag->boolean_tag = boolean_tag;
}

#endif
#ifndef TAG_H
#define TAG_H

#include <stdlib.h>
#include <stdio.h>

typedef struct compound_s compound;
typedef union tag_u tag;

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

struct compound_s {
    char type;
    tag *tag;
};

union tag_u {
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
};

struct list_tag_s {
    compound **list;
    int list_size; 
};

struct single_type_list_tag_s {
    char type;
    compound **list;
    int list_size;
};

struct mapped_list_tag_s {
    char **mapping;
    compound **list;
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

compound *create_empty_compound();

void create_list_tag(compound *compound);
void create_single_type_list_tag(compound *compound, char type);
void create_mapped_list_tag(compound *compound);
void create_byte_tag(compound *compound, char value);
void create_short_tag(compound *compound, short value);
void create_int_tag(compound *compound, int value);
void create_long_tag(compound *compound, long value);
void create_float_tag(compound *compound, float value);
void create_double_tag(compound *compound, double value);
void create_string_tag(compound *compound, char *value);
void create_boolean_tag(compound *compound, char value);

void free_compound(compound *compound);
void free_tag(tag *tag, char type);

int is_primitive(compound *compound);
int is_list(compound *compound);

#endif
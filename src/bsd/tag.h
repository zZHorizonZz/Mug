#ifndef TAG_H
#define TAG_H

#include <stdlib.h>
#include <stdio.h>

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

typedef struct compound_s {
    char type;
    tag *tag;
} compound;

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

int is_primitive(compound *compound);
int is_list(compound *compound);

compound *create_empty_compound() {
    compound *compound = malloc(sizeof(struct compound_s));
    tag *tag = malloc(sizeof(tag));
    if(compound == 0x00 || tag == 0x00) {
        return 0x00;
    }

    compound->tag = tag;
    return compound;
}

void create_list_tag(compound *compound) {
    list_tag *list = calloc(2, sizeof(union tag_u));

    compound->tag->list_tag = list;
    compound->type = 0x01;
}

void create_single_type_list_tag(compound *compound, char type) {
    single_type_list_tag *list = calloc(3, sizeof(union tag_u));
    if(list == 0x00) {
        return 0x00;
    }

    list->type = type;

    compound->tag->single_type_list_tag = list;
    compound->type = 0x02;
}

void create_mapped_list_tag(compound *compound) {
    mapped_list_tag *list = calloc(3, sizeof(union tag_u));
    if(list == 0x00) {
        return 0x00;
    }

    compound->tag->mapped_list_tag = list;
    compound->type = 0x03;
}

void create_byte_tag(compound *compound, char value) {
    byte_tag *tag = calloc(1, sizeof(union tag_u));
    if(tag == 0x00) {
        return 0x00;
    }

    tag->value = value;

    compound->tag->byte_tag = tag;
    compound->type = 0x04;
}

void create_short_tag(compound *compound, short value) {
    short_tag *tag = calloc(1, sizeof(union tag_u));
    if(tag == 0x00) {
        return 0x00;
    }

    tag->value = value;

    compound->tag->short_tag = tag;
    compound->type = 0x05;
}

void create_int_tag(compound *compound, int value) {
    int_tag *tag = calloc(1, sizeof(union tag_u));
    if(tag == 0x00) {
        return 0x00;
    }

    tag->value = value;
    
    compound->tag->int_tag = tag;
    compound->type = 0x06;
}

void create_long_tag(compound *compound, long value) {
    long_tag *tag = calloc(1, sizeof(union tag_u));
    if(tag == 0x00) {
        return 0x00;
    }

    tag->value = value;

    compound->tag->long_tag = tag;
    compound->type = 0x07;
}

void create_float_tag(compound *compound, float value) {
    float_tag *tag = calloc(1, sizeof(union tag_u));
    if(tag == 0x00) {
        return 0x00;
    }

    tag->value = value;

    compound->tag->float_tag = tag;
    compound->type = 0x08;
}

void create_double_tag(compound *compound, double value) {
    double_tag *tag = calloc(1, sizeof(union tag_u));
    if(tag == 0x00) {
        return 0x00;
    }

    tag->value = value;

    compound->tag->double_tag = tag;
    compound->type = 0x09;
}

void create_string_tag(compound *compound, char *value) {
    string_tag *tag = calloc(1, sizeof(union tag_u));
    if(tag == 0x00) {
        return 0x00;
    }

    tag->value = value;

    compound->tag->string_tag = tag;
    compound->type = 0x0A;
}

void create_boolean_tag(compound *compound, char value) {
    boolean_tag *tag = calloc(1, sizeof(union tag_u));
    if(tag == 0x00) {
        return 0x00;
    }

    tag->value = value;

    compound->tag->boolean_tag = tag;
    compound->type = 0x0B;
}

int is_primitive(compound *compound) {
    return compound->type > 0x03;
}

int is_list(compound *compound) {
    return compound->type < 0x04;
}

#endif
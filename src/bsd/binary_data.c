#include <stdlib.h>
#include <stdio.h>

#include "buffer.c"

typedef union tag {
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

typedef struct list_tag {
    tag *list;
    int list_size; 
} list_tag;

typedef struct single_type_list_tag {
    char type;
    tag *list;
    int list_size;
} single_type_list_tag;

typedef struct mapped_list_tag {
    char **mapping;
    tag *list;
    int list_size;
} mapped_list_tag;

typedef struct byte_tag {
    char value;
} byte_tag;

typedef struct short_tag {
    short value;
} short_tag;

typedef struct int_tag {
    int value;
} int_tag;

typedef struct long_tag {
    long value;
} long_tag;

typedef struct float_tag {
    float value;
} float_tag;

typedef struct double_tag {
    double value;
} double_tag;

typedef struct string_tag {
    char *value;
} string_tag;

typedef struct boolean_tag {
    char value;
} boolean_tag;

tag *create_list_tag();
tag *create_single_type_list_tag(char type);
tag *create_mapped_list_tag();
tag *create_byte_tag(char value);
tag *create_short_tag(short value);
tag *create_int_tag(int value);
tag *create_long_tag(long value);
tag *create_float_tag(float value);
tag *create_double_tag(double value);
tag *create_string_tag(char *value);
tag *create_boolean_tag(char value);

int add_value_to_list(tag *list_tag, tag tag);
int add_value_to_list(list_tag *list_tag, tag tag);
int add_value_to_single_type_list(tag *list_tag, tag tag);
int add_value_to_single_type_list(single_type_list_tag *list_tag, tag tag);
int add_value_to_mapped_list(tag *list_tag, tag tag);
int add_value_to_mapped_list(mapped_list_tag *mapped_list_tag, char *name, tag tag);
int verify_type(int type, tag tag);

void write_list(char *destination, int size, tag *tag);
void write_list(char *destination, int size, list_tag *tag);
void write_single_type_list(char *destination, int size, tag *tag);
void write_single_type_list(char *destination, int size, single_type_list_tag *tag);
void write_mapped_list(char *destination, int size, tag *tag);
void write_mapped_list(char *destination, int size, mapped_list_tag *tag);

char *create_binary(tag *tag);

tag *create_list_tag() {
    tag tag;
    list_tag list = { 0x00, 0x00 };

    tag.list_tag = &list;

    return &tag;
}

tag *create_single_type_list_tag(char type) {
    tag tag;
    single_type_list_tag list = { type, 0x00, 0x00 };

    tag.single_type_list_tag = &list;

    return &tag;
}

tag *create_mapped_list_tag() {
    tag tag;
    mapped_list_tag list = { 0x00, 0x00, 0x00 };

    tag.mapped_list_tag = &list;

    return &list;
}

tag *create_byte_tag(char value) {
    tag tag;
    byte_tag byte_tag = { value };

    tag.byte_tag = &byte_tag;

    return &tag;
}

tag *create_short_tag(short value) {
    tag tag;
    short_tag short_tag = { value };
    tag.short_tag = &short_tag;

    return &tag;
}

tag *create_int_tag(int value) {
    tag tag;
    int_tag int_tag = { value };
    tag.int_tag = &int_tag;

    return &tag;
}

tag *create_long_tag(long value) {
    tag tag;
    long_tag long_tag = { value };
    tag.long_tag = &long_tag;

    return &tag;
}

tag *create_float_tag(float value) {
    tag tag;
    float_tag float_tag = { value };
    tag.float_tag = &float_tag;

    return &tag;
}

tag *create_double_tag(double value) {
    tag tag;
    double_tag double_tag = { value };
    tag.double_tag = &double_tag;

    return &tag;
}

tag *create_string_tag(char *value) {
    tag tag;
    string_tag string_tag = { value };
    tag.string_tag = &string_tag;

    return &tag;
}

tag *create_boolean_tag(char value) {
    tag tag;
    boolean_tag boolean_tag = { value };
    tag.boolean_tag = &boolean_tag;

    return &tag;
}

int add_value_to_list(tag *list_tag, tag tag) {
    return add_value_to_list(list_tag->list_tag, tag);
}

int add_value_to_list(list_tag *list_tag, tag tag) {
    if(list_tag->list == 0x00) {
        list_tag->list = malloc(++list_tag->list_size * sizeof(union tag));
    } else {
        union tag *tmp = realloc(list_tag->list, ++list_tag->list_size * sizeof(union tag));
        free(list_tag->list);
        
        list_tag->list = tmp;
    }

    if(list_tag->list != 0x00) {
        list_tag->list[list_tag->list_size - 0x01] = tag;
        return 0x01;
    } else {
        return 0x00;
    }
}

int add_value_to_single_type_list(tag *list_tag, tag tag) {
    return add_value_to_single_type_list(list_tag->single_type_list_tag, tag);
}

int add_value_to_single_type_list(single_type_list_tag *list_tag, tag tag) {
    if(verify_type(list_tag->type, tag) != 0x01) {
        return 0x00;
    }

    if(list_tag->list == 0x00) {
        list_tag->list = malloc(++list_tag->list_size * sizeof(union tag));
    } else {
        union tag *tmp = realloc(list_tag->list, ++list_tag->list_size * sizeof(union tag));
        free(list_tag->list);
        
        list_tag->list = tmp;
    }

    if(list_tag->list != 0x00) {
        list_tag->list[list_tag->list_size - 0x01] = tag;
        return 0x01;
    } else {
        return 0x00;
    }
}

int add_value_to_mapped_list(tag *list, char *name, tag tag) {
    return add_value_to_mapped_list(list->mapped_list_tag, name, tag);
}

int add_value_to_mapped_list(mapped_list_tag *mapped_list_tag, char *name, tag tag) {
    if(mapped_list_tag->list == 0x00) {
        mapped_list_tag->mapping = malloc(++mapped_list_tag->list_size * sizeof(char*));
        mapped_list_tag->list = malloc(mapped_list_tag->list_size * sizeof(union tag));
    } else {
        char **tmp_mapping = realloc(mapped_list_tag->mapping, ++mapped_list_tag->list_size * sizeof(char*));
        union tag *tmp_list = realloc(mapped_list_tag->list, mapped_list_tag->list_size * sizeof(union tag));

        free(mapped_list_tag->mapping);
        free(mapped_list_tag->list);

        mapped_list_tag->mapping = tmp_mapping;
        mapped_list_tag->list = tmp_list;
    }

    if(mapped_list_tag->list != 0x00) {
        mapped_list_tag->mapping[mapped_list_tag->list_size - 1] = name;
        mapped_list_tag->list[mapped_list_tag->list_size - 1] = tag;
        return 0x01;
    } else {
        return 0x00;
    }
}

int verify_type(int type, tag tag) {
    switch (type) {
        case 0x00:
            if(tag.list_tag != 0x00) {
                return 0x01;
            }

            break;
        case 0x01:
            if(tag.single_type_list_tag != 0x00) {
                return 0x01;
            }

            break;
        case 0x02:
            if(tag.mapped_list_tag != 0x00) {
                return 0x01;
            }

            break;
        case 0x03:
            if(tag.byte_tag != 0x00) {
                return 0x01;
            }

            break;
        case 0x04:
            if(tag.short_tag != 0x00) {
                return 0x01;
            }

            break;
        case 0x05:
            if(tag.int_tag != 0x00) {
                return 0x01;
            }

            break;
        case 0x06:
            if(tag.long_tag != 0x00) {
                return 0x01;
            }

            break;
        case 0x07:
            if(tag.float_tag != 0x00) {
                return 0x01;
            }

            break;
        case 0x08:
            if(tag.double_tag != 0x00) {
                return 0x01;
            }

            break;
        case 0x09:
            if(tag.string_tag != 0x00) {
                return 0x01;
            }

            break;
        case 0x0A:
            if(tag.boolean_tag != 0x00) {
                return 0x01;
            }

            break;

        default:
            break;
    }

    return 0;
}

void write_list(char *destination, int size, tag *tag);
void write_list(char *destination, int size, list_tag *tag);
void write_single_type_list(char *destination, int size, tag *tag);
void write_single_type_list(char *destination, int size, single_type_list_tag *tag);
void write_mapped_list(char *destination, int size, tag *tag);
void write_mapped_list(char *destination, int size, mapped_list_tag *tag);

char *create_binary(tag *tag) {

}

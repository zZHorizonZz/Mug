#include <stdlib.h>
#include <stdio.h>

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

int add_value_to_list(list_tag *list_tag, tag tag) {
    if(list_tag->list == 0x00) {
        list_tag = malloc(++list_tag->list_size * sizeof(union tag));
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

int add_value_to_single_type_list(single_type_list_tag *list_tag, tag tag) {
    if(verify_type(list_tag->type, tag) != 0x01) {
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

#include <stdlib.h>
#include <stdio.h>

#include "buffer.c"
#include "tag.h"

int add_value_to_list_tag(tag *list_tag, tag tag);
int add_value_to_list(list_tag *list_tag, tag tag);
int add_value_to_single_type_list_tag(tag *list_tag, tag tag);
int add_value_to_single_type_list(single_type_list_tag *list_tag, tag tag);
int add_value_to_mapped_list_tag(tag *list_tag, char *name, tag tag);
int add_value_to_mapped_list(mapped_list_tag *mapped_list_tag, char *name, tag tag);
int verify_type(int type, tag tag);
char get_type(tag *tag);

int write_list(buffer *buffer, list_tag *list);
int write_list_tag(buffer *buffer, tag *tag);
int write_single_type_list_tag(buffer *buffer, tag *tag);
int write_single_type_list(buffer *buffer, single_type_list_tag *tag);
int write_mapped_list_tag(buffer *buffer, tag *tag);
int write_mapped_list(buffer *buffer, mapped_list_tag *tag);

void write_tag(buffer *buffer, tag *tag);

char *create_binary(tag *tag);

int add_value_to_list_tag(tag *list_tag, tag tag) {
    return add_value_to_list(list_tag->list_tag, tag);
}

int add_value_to_list(list_tag *list_tag, tag tag) {
    if(list_tag->list == 0x00) {
        list_tag->list = malloc(++list_tag->list_size * sizeof(union tag_u));
    } else {
        union tag_u *tmp = realloc(list_tag->list, ++list_tag->list_size * sizeof(union tag_u));
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

int add_value_to_single_type_list_tag(tag *list_tag, tag tag) {
    return add_value_to_single_type_list(list_tag->single_type_list_tag, tag);
}

int add_value_to_single_type_list(single_type_list_tag *list_tag, tag tag) {
    if(verify_type(list_tag->type, tag) != 0x01) {
        return 0x00;
    }

    if(list_tag->list == 0x00) {
        list_tag->list = malloc(++list_tag->list_size * sizeof(union tag_u));
    } else {
        union tag_u *tmp = realloc(list_tag->list, ++list_tag->list_size * sizeof(union tag_u));
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

int add_value_to_mapped_list_tag(tag *list, char *name, tag tag) {
    return add_value_to_mapped_list(list->mapped_list_tag, name, tag);
}

int add_value_to_mapped_list(mapped_list_tag *mapped_list_tag, char *name, tag tag) {
    if(mapped_list_tag->list == 0x00) {
        mapped_list_tag->mapping = malloc(++mapped_list_tag->list_size * sizeof(char*));
        mapped_list_tag->list = malloc(mapped_list_tag->list_size * sizeof(union tag_u));
    } else {
        char **tmp_mapping = realloc(mapped_list_tag->mapping, ++mapped_list_tag->list_size * sizeof(char*));
        union tag_u *tmp_list = realloc(mapped_list_tag->list, mapped_list_tag->list_size * sizeof(union tag_u));

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

char get_type(tag *tag) {
    if(tag->list_tag != 0x00) {
        return 0x01;
    } else if(tag->single_type_list_tag != 0x00) {
        return 0x02;
    } else if(tag->mapped_list_tag != 0x00) {
        return 0x03;
    } else if(tag->byte_tag != 0x00) {
        return 0x04;
    } else if(tag->short_tag != 0x00) {
        return 0x05;
    } else if(tag->int_tag != 0x00) {
        return 0x06;
    } else if(tag->long_tag != 0x00) {
        return 0x07;
    } else if(tag->float_tag != 0x00) {
        return 0x08;
    } else if(tag->double_tag != 0x00) {
        return 0x09;
    } else if(tag->string_tag != 0x00) {
        return 0x0A;
    } else if(tag->boolean_tag != 0x00) {
        return 0x0B;
    }
}

int write_list(buffer *buffer, list_tag *list) {
    tag tag;
    tag.list_tag = list;
    return write_list_tag(buffer, &tag);
}

int write_list_tag(buffer *buffer, tag *tag) {
    list_tag *list = tag->list_tag;
    if(buffer == 0x00 || list == 0x00) {
        return 0x00;
    }

    write_int(buffer, list->list_size);
    for (size_t i = 0; i < list->list_size; i++) {
        union tag *element = list->list[i];
        write_byte(buffer, get_type(tag));
        write_tag(buffer, element);
    }

    return 0x01;
}

int write_single_type_list(buffer *buffer, single_type_list_tag *list) {
    tag tag;
    tag.single_type_list_tag = list;
    return write_single_type_list_tag(buffer, &tag);
}

int write_single_type_list_tag(buffer *buffer, tag *tag) {
    single_type_list_tag *list = tag->list_tag;
    if(buffer == 0x00 || list == 0x00) {
        return 0x00;
    }

    write_int(buffer, list->list_size);
    write_byte(buffer, list->type);

    for (size_t i = 0; i < list->list_size; i++) {
        union tag *element = list->list[i];
        write_tag(buffer, element);
    }

    return 0x01;
}

int write_mapped_list(buffer *buffer, mapped_list_tag *list) {
    tag tag;
    tag.mapped_list_tag = list;
    return write_mapped_list_tag(buffer, &tag);
}

int write_mapped_list_tag(buffer *buffer, tag *tag) {
    mapped_list_tag *list = tag->list_tag;
    if(buffer == 0x00 || list == 0x00) {
        return 0x00;
    }

    write_int(buffer, list->list_size);

    for (size_t i = 0; i < list->list_size; i++) {
        union tag *element = list->list[i];
        write_byte(buffer, get_type(tag));
        write_string(buffer, list->mapping[i]);
        write_tag(buffer, element);
    }

    return 0x01;
}

void write_tag(buffer *buffer, tag *tag) {
    switch (get_type(tag)) {
    case 0x01:
        write_list_tag(buffer, tag);
        break;
    case 0x02:
        break;    
    case 0x03:
        break;
    case 0x04:
        write_byte(buffer, tag->byte_tag->value);
        break;
    case 0x05:
        write_short(buffer, tag->short_tag->value);
        break;
    case 0x06:
        write_int(buffer, tag->int_tag->value);
        break;
    case 0x07:
        write_long(buffer, tag->long_tag->value);
        break;
    case 0x08:
        write_float(buffer, tag->float_tag->value);
        break;
    case 0x09:
        write_double(buffer, tag->double_tag->value);
        break;
    case 0x0A:
        write_int(buffer, strlen(tag->string_tag->value));
        write_string(buffer, tag->string_tag->value);
        break;
    case 0x0B:
        write_byte(buffer, tag->boolean_tag->value);
        break;    
    default:
        break;
    }
}

char *create_binary(tag *tag) {

}

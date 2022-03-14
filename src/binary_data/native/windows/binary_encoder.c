#include <stdlib.h>
#include <stdio.h>

#include "binary_encoder.h"

int add_value_to_list_tag(compound *list_tag, compound *compound)
{
    return add_value_to_list(list_tag->tag->list_tag, compound);
}

int add_value_to_list(list_tag *list_tag, compound *compound)
{
    if (list_tag->list_size == 0x00)
    {
        list_tag->list = malloc(++list_tag->list_size * sizeof(struct compound_s));
    }
    else
    {
        struct compound_s **tmp = realloc(list_tag->list, ++list_tag->list_size * sizeof(struct compound_s));

        list_tag->list = tmp;
    }

    if (list_tag->list != 0x00)
    {
        list_tag->list[list_tag->list_size - 0x01] = compound;
        return 0x01;
    }
    else
    {
        return 0x00;
    }
}

int add_value_to_single_type_list_tag(compound *list_tag, compound *compound)
{
    return add_value_to_single_type_list(list_tag->tag->single_type_list_tag, compound);
}

int add_value_to_single_type_list(single_type_list_tag *list_tag, compound *compound)
{
    if (list_tag->type == compound->type)
    {
        return 0x00;
    }

    if (list_tag->list_size == 0x00)
    {
        list_tag->list = malloc(++list_tag->list_size * sizeof(struct compound_s));
    }
    else
    {
        struct compound_s **tmp = realloc(list_tag->list, ++list_tag->list_size * sizeof(struct compound_s));

        list_tag->list = tmp;
    }

    if (list_tag->list != 0x00)
    {
        list_tag->list[list_tag->list_size - 0x01] = compound;
        return 0x01;
    }
    else
    {
        return 0x00;
    }
}

int add_value_to_mapped_list_tag(compound *list, char *name, compound *compound)
{
    return add_value_to_mapped_list(list->tag->mapped_list_tag, name, compound);
}

int add_value_to_mapped_list(mapped_list_tag *mapped_list_tag, char *name, compound *compound)
{
    if (mapped_list_tag->list_size == 0x00)
    {
        mapped_list_tag->mapping = malloc(++mapped_list_tag->list_size * sizeof(char *));
        mapped_list_tag->list = malloc(mapped_list_tag->list_size * sizeof(struct compound_s));
    }
    else
    {
        int size = mapped_list_tag->list_size;
        char **tmp_mapping = realloc(mapped_list_tag->mapping, ++mapped_list_tag->list_size * sizeof(char *));
        struct compound_s **tmp_list = realloc(mapped_list_tag->list, mapped_list_tag->list_size * sizeof(struct compound_s));

        mapped_list_tag->mapping = tmp_mapping;
        mapped_list_tag->list = tmp_list;
    }

    if (mapped_list_tag->list != 0x00)
    {
        mapped_list_tag->mapping[mapped_list_tag->list_size - 1] = name;
        mapped_list_tag->list[mapped_list_tag->list_size - 1] = compound;
        return 0x01;
    }
    else
    {
        return 0x00;
    }
}

int write_list_tag(buffer *buffer, compound *compound)
{
    list_tag *list = compound->tag->list_tag;
    if (buffer == 0x00 || list == 0x00)
    {
        return 0x00;
    }

    write_int(buffer, list->list_size);
    for (size_t i = 0; i < list->list_size; i++)
    {
        struct compound_s *element;
        element = list->list[i];
        write_byte(buffer, compound->type);
        write_tag(buffer, element);
    }

    return 0x01;
}

int write_single_type_list_tag(buffer *buffer, compound *compound)
{
    single_type_list_tag *list = compound->tag->single_type_list_tag;
    if (buffer == 0x00 || list == 0x00)
    {
        return 0x00;
    }

    write_int(buffer, list->list_size);
    write_byte(buffer, list->type);

    for (size_t i = 0; i < list->list_size; i++)
    {
        struct compound_s *element;
        element = list->list[i];
        write_tag(buffer, element);
    }

    return 0x01;
}

int write_mapped_list_tag(buffer *buffer, compound *compound)
{
    mapped_list_tag *list = compound->tag->mapped_list_tag;
    if (buffer == 0x00 || list == 0x00)
    {
        return 0x00;
    }

    write_int(buffer, list->list_size);

    for (size_t i = 0; i < list->list_size; i++)
    {
        struct compound_s *element;
        element = list->list[i];
        write_byte(buffer, compound->type);
        write_string(buffer, list->mapping[i]);
        write_tag(buffer, element);
    }

    return 0x01;
}

void write_tag(buffer *buffer, compound *compound)
{
    switch (compound->type)
    {
    case 0x01:
        write_list_tag(buffer, compound);
        break;
    case 0x02:
        write_single_type_list_tag(buffer, compound);
        break;
    case 0x03:
        write_mapped_list_tag(buffer, compound);
        break;
    case 0x04:
        write_byte(buffer, compound->tag->byte_tag->value);
        break;
    case 0x05:
        write_short(buffer, compound->tag->short_tag->value);
        break;
    case 0x06:
        write_int(buffer, compound->tag->int_tag->value);
        break;
    case 0x07:
        write_long(buffer, compound->tag->long_tag->value);
        break;
    case 0x08:
        write_float(buffer, compound->tag->float_tag->value);
        break;
    case 0x09:
        write_double(buffer, compound->tag->double_tag->value);
        break;
    case 0x0A:
        write_int(buffer, strlen(compound->tag->string_tag->value));
        write_string(buffer, compound->tag->string_tag->value);
        break;
    case 0x0B:
        write_byte(buffer, compound->tag->boolean_tag->value);
        break;
    default:
        break;
    }
}

char *create_binary(compound *compound)
{
    buffer *buffer = malloc(sizeof(struct buffer_s));

    write_byte(buffer, compound->type);
    write_tag(buffer, compound);

    return buffer->buffer;
}

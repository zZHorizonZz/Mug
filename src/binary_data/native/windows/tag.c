#include "tag.h"

compound *create_empty_compound()
{
    compound *compound = malloc(sizeof(struct compound_s));
    tag *tag = malloc(sizeof(union tag_u));
    if (compound == 0x00 || tag == 0x00)
    {
        return 0x00;
    }

    compound->tag = tag;
    return compound;
}

void create_list_tag(compound *compound)
{
    list_tag *list = malloc(sizeof(union tag_u));

    if (list == 0x00)
    {
        return;
    }

    list->list = 0x00;
    list->list_size = 0x00;
    compound->tag->list_tag = list;
    compound->type = 0x01;
}

void create_single_type_list_tag(compound *compound, char type)
{
    single_type_list_tag *list = malloc(sizeof(union tag_u));
    if (list == 0x00)
    {
        return;
    }

    list->list = 0x00;
    list->list_size = 0x00;
    list->type = type;

    compound->tag->single_type_list_tag = list;
    compound->type = 0x02;
}

void create_mapped_list_tag(compound *compound)
{
    mapped_list_tag *list = malloc(sizeof(union tag_u));
    if (list == 0x00)
    {
        return;
    }

    list->list = 0x00;
    list->mapping = 0x00;
    list->list_size = 0x00;

    compound->tag->mapped_list_tag = list;
    compound->type = 0x03;
}

void create_byte_tag(compound *compound, char value)
{
    byte_tag *tag = malloc(sizeof(union tag_u));
    if (tag == 0x00)
    {
        return;
    }

    tag->value = value;

    compound->tag->byte_tag = tag;
    compound->type = 0x04;
}

void create_short_tag(compound *compound, short value)
{
    short_tag *tag = malloc(sizeof(union tag_u));
    if (tag == 0x00)
    {
        return;
    }

    tag->value = value;

    compound->tag->short_tag = tag;
    compound->type = 0x05;
}

void create_int_tag(compound *compound, int value)
{
    int_tag *tag = malloc(sizeof(union tag_u));
    if (tag == 0x00)
    {
        return;
    }

    tag->value = value;

    compound->tag->int_tag = tag;
    compound->type = 0x06;
}

void create_long_tag(compound *compound, long value)
{
    long_tag *tag = malloc(sizeof(union tag_u));
    if (tag == 0x00)
    {
        return;
    }

    tag->value = value;

    compound->tag->long_tag = tag;
    compound->type = 0x07;
}

void create_float_tag(compound *compound, float value)
{
    float_tag *tag = malloc(sizeof(union tag_u));
    if (tag == 0x00)
    {
        return;
    }

    tag->value = value;

    compound->tag->float_tag = tag;
    compound->type = 0x08;
}

void create_double_tag(compound *compound, double value)
{
    double_tag *tag = malloc(sizeof(union tag_u));
    if (tag == 0x00)
    {
        return;
    }

    tag->value = value;

    compound->tag->double_tag = tag;
    compound->type = 0x09;
}

void create_string_tag(compound *compound, char *value)
{
    string_tag *tag = malloc(sizeof(union tag_u));
    if (tag == 0x00)
    {
        return;
    }

    tag->value = value;

    compound->tag->string_tag = tag;
    compound->type = 0x0A;
}

void create_boolean_tag(compound *compound, char value)
{
    boolean_tag *tag = malloc(sizeof(union tag_u));
    if (tag == 0x00)
    {
        return;
    }

    tag->value = value;

    compound->tag->boolean_tag = tag;
    compound->type = 0x0B;
}

void free_compound(compound *compound)
{
    if (compound == 0x00)
    {
        return;
    }

    if (is_primitive(compound))
    {
        if (compound->tag != 0x00)
        {
            tag *tag = compound->tag;
            free_tag(tag, compound->type);
        }
    }
    else if (is_list(compound))
    {
        struct compound_s **list;
        int size;

        switch (compound->type)
        {
        case 0x01:
            size = compound->tag->list_tag->list_size;
            list = compound->tag->list_tag->list;
            break;
        case 0x02:
            size = compound->tag->single_type_list_tag->list_size;
            list = compound->tag->single_type_list_tag->list;
            break;
        case 0x03:
            size = compound->tag->mapped_list_tag->list_size;
            list = compound->tag->mapped_list_tag->list;

            for (size_t i = 0; i < size; i++)
            {
                char *mapping = compound->tag->mapped_list_tag->mapping[i];
                free(mapping);
            }

            break;
        default:
            break;
        }

        if (list != 0x00)
        {
            for (size_t i = 0; i < size; i++)
            {
                struct compound_s *element = list[i];
                free_compound(element);
            }

            free(list);
        }

        free(compound->tag);
    }

    free(compound);
}

void free_tag(tag *tag, char type)
{
    switch (type)
    {
    case 0x04:
        free(tag->byte_tag);
        break;
    case 0x05:
        free(tag->short_tag);
        break;
    case 0x06:
        free(tag->int_tag);
        break;
    case 0x07:
        free(tag->long_tag);
        break;
    case 0x08:
        free(tag->float_tag);
        break;
    case 0x09:
        free(tag->double_tag);
        break;
    case 0x0A:
        free(tag->string_tag->value);
        free(tag->string_tag);
        break;
    case 0x0B:
        free(tag->boolean_tag);
        break;
    default:
        break;
    }

    free(tag);
}

int is_primitive(compound *compound)
{
    return compound->type > 0x03;
}

int is_list(compound *compound)
{
    return compound->type < 0x04;
}
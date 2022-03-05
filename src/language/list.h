#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "object.h"

/*
 * Structure list is representation of array of objects.
 * We can set its initial capacity and flags of the list.
 * List of flags:
 *      Read-Only: This flag is used to list which should be in read only mode.
 *      Expandable: This flag set list to state where it can be expanded.
 *      Write-Only:
 *
 */
struct list
{
    int size;
    int last_index;

    int flags;

    struct object *object;
};

struct list create_list(int initial_capacity, int flags);
struct list expand_list(struct list *list, int offset);
void add(struct list *list, struct object obj);
void set(struct list *list, struct object obj, int index);
struct object get(struct list *list, int index);
char is_readonly(struct list *list);
void set_readonly(struct list *list);
char is_expandable(struct list *list);
void set_expandable(struct list *list);
char has_flag(struct list *list, int flag);
void set_flag(struct list *list, int flag);

struct list create_list(int initial_capacity, int flags)
{
    struct object *objects = (struct object *)malloc(initial_capacity * sizeof(struct object));

    for (int i = 0; i < initial_capacity; i++)
    {
        struct object _object = {0x00};
        objects[i] = _object;
    }

    struct list _list;

    _list.last_index = 0x00;
    _list.size = initial_capacity;
    _list.object = objects;
    _list.flags = flags;

    return _list;
}

struct list expand_list(struct list *list, int offset)
{
    int original_size = list->size;
    struct object *objects = (struct object *)malloc(original_size + offset * sizeof(struct object));
    for (int i = 0; i < original_size + offset; i++)
    {
        if (i < original_size)
        {
            objects[i] = list->object[i];
        }
        else
        {
            struct object _object = {0x00};
            objects[i] = _object;
        }
    }

    free(list->object);

    list->object = objects;
    list->size = original_size + offset;

    return *list;
}

void add(struct list *list, struct object obj)
{
    if (is_readonly(list) == 0x01)
    {
        return;
    }

    if (list->last_index >= list->size)
    {
        expand_list(list, 1);
    }

    list->object[list->last_index++] = obj;
}

void set(struct list *list, struct object obj, int index)
{
    if (is_readonly(list) == 0x01)
    {
        return;
    }

    if (index >= list->size)
    {
        return;
    }

    list->object[index] = obj;
}

struct object get(struct list *list, int index)
{
    if (index > list->size)
    {
        struct object _object = {0x00};
        return _object;
    }

    return list->object[index];
}

int index_of(struct list *list, struct object obj)
{
    if (list->size < 1)
    {
        return -1;
    }

    for (int i = 0; i < list->size; i++)
    {
        if (equals(list->object[i], obj))
        {
            return i;
        }
    }

    return -1;
}

void clear(struct list *list)
{
    // memfree(list.object);
}

char is_readonly(struct list *list)
{
    return has_flag(list, 0x00) == 0x01;
}

void set_readonly(struct list *list)
{
    set_flag(list, 0x00);
}

char is_expandable(struct list *list)
{
    return has_flag(list, 0x01);
}

void set_expandable(struct list *list)
{
    set_flag(list, 0x01);
}

char has_flag(struct list *list, int flag)
{
    if ((list->flags & 1 << flag) != 0)
    {
        return 1;
    }

    return 0;
}

void set_flag(struct list *list, int flag)
{
    list->flags = list->flags | 1 << flag;
}

#endif
#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct object_s
{
    char *value;
} object;

object empty_object = {0x00};

object *new_object(char *value);
int equals(object *original, object *equal);

#endif
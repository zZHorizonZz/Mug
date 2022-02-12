#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <stdlib.h>

struct object {
    char* value;
};

struct object new_object(char* value) {
    struct object obj;
    obj.value = value;
    return obj;
}

struct object empty_object = { 0x00 };

int equals(struct object original, struct object equal) 
{
    int valid = 0;
    if(original.value == equal.value) {
        valid = 1;
    }

    return valid;
}

#endif
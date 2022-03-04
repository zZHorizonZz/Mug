#include <stdio.h>
#include <stdlib.h>

#include "object.h"

object *new_object(char* value) {
    object *obj = malloc(sizeof(struct object_s));
    obj->value = value;
    return obj;
}

int equals(object *original, object *equal) {
    int valid = 0;
    if(original->value == equal->value) {
        valid = 1;
    }

    return valid;
}
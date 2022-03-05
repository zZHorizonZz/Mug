#include <stdlib.h>
#include <stdio.h>

#include "body.h"

typedef struct method_s
{
    char *name;
    body *body;
} method;

void evaluate_method(token_iterator *iterator)
{
}
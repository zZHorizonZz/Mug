#include <stdlib.h>
#include <stdio.h>

#include "expression.h"

typedef struct body_s {
    size_t length;
    expression **expression;
} body;
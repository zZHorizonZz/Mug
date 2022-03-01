#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "number.h"
#include "token.h"

typedef struct expression_s {
    char type;

    value_expression *value_expression;
    operator_expression *operator_expression;
    reference_expression *reference_expression;
    arithmetic_expression *arithmetic_expression;
} expression;

typedef struct value_expression_s {
    
} value_expression;

typedef struct operator_expression_s {

} operator_expression;

typedef struct reference_expression_s {

} reference_expression;

typedef struct arithmetic_expression_s {
    char type;

    number *left_side;
    number *right_side;
} arithmetic_expression;

void evaluate_token_block(expression *expression, token *block) {

}

#endif
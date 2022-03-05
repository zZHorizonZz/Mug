#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "number.h"
#include "token.h"

typedef struct value_expression_s value_expression;
typedef struct operator_expression_s operator_expression;
typedef struct reference_expression_s reference_expression;
typedef struct arithmetic_expression_s arithmetic_expression;

typedef struct expression_s
{
    char type;

    value_expression *value_expression;
    operator_expression *operator_expression;
    reference_expression *reference_expression;
    arithmetic_expression *arithmetic_expression;
} expression;

struct value_expression_s
{
    char t;
};

struct operator_expression_s
{
    char t;
};

struct reference_expression_s
{
    char t;
};

struct arithmetic_expression_s
{
    char type;

    number *left_side;
    number *right_side;
};

token_iterator *split_token_iterator(token_iterator *iterator, char type);
void evaluate_token_block(expression *expression, token_iterator *iterator);

#endif
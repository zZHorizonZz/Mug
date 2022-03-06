/**
 * Copyright 2022 Daniel Fiala
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
    char type;
    mug_primitive *primitive;
};

struct operator_expression_s
{
    char operator;
};

struct reference_expression_s
{
    char *reference;
};

struct arithmetic_expression_s
{
    operator_expression *operator;
    expression *left_side;
    expression *right_side;
};

token_iterator *split_token_iterator(token_iterator *iterator, char type);
void evaluate_token_block(expression *expression, token_iterator *iterator);

#endif
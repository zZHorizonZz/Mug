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

#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <stdlib.h>

#include "storage.h"
#include "primitive.h"
#include "token.h"

//
// ─── STRUCTURE ──────────────────────────────────────────────────────────────────
//

typedef struct mug_object_s mug_object;
typedef struct mug_foundation_s mug_foundation;
typedef struct mug_method_s mug_method;

typedef struct body_s body;

typedef union block_u block;
typedef struct field_block_s field_block;
typedef struct expression_blocks_s expression_block;
typedef struct statement_block_s statement_block;

typedef union expression_u expression;
typedef struct value_expression_s value_expression;
typedef struct operator_expression_s operator_expression;
typedef struct reference_expression_s reference_expression;

struct mug_object_s
{
    char *value;
};

struct mug_foundation_s
{
    char *location;
    char *name;

    size_t method_count;
    size_t field_count;

    mug_method **method;
};

struct mug_method_s
{
    char *name;
    body *body;
};

struct body_s
{
    size_t length;

    char *body_type;
    set *body_block;
};

union block_u
{
    field_block *field_block;
    expression_block *expression_block;
    statement_block *statement_block;
};

struct field_block_s
{
    char *type;
    char *name;

    char initializer_type;
    expression *initializer;
};

struct expression_block_s
{
    char expression_type;
    expression *expression;
};

struct statement_blocks_s
{
    char *t;
};

union expression_u
{
    value_expression *value_expression;
    operator_expression *operator_expression;
    reference_expression *reference_expression;
};

struct value_expression_s
{
    char type;
    mug_primitive *primitive;
};

struct operator_expression_s
{
    char operator;

    char left_side_type;
    char right_side_type;

    union expression_u *left_side;
    union expression_u *right_side;
};

struct reference_expression_s
{
    char *reference;
};

//
// ─── OBJECT ─────────────────────────────────────────────────────────────────────
//

mug_object empty_object = {0x00};

mug_object *new_object(char *value);
int equals(mug_object *original, mug_object *equal);

//
// ─── FOUNDATION ─────────────────────────────────────────────────────────────────
//

mug_object *find_foundation(char *location, char *name);
int register_foundation(mug_object *foundation);
int remove_foundation(char *location, char *name);

//
// ─── METHOD ─────────────────────────────────────────────────────────────────────
//

void parse_method(mug_method *method, set *token_set);
void execute_method(mug_method *method);

//
// ─── BODY ───────────────────────────────────────────────────────────────────────
//

void parse_body(body *body, set *token_set);
void execute_body(body *body);

//
// ─── BLOCK ──────────────────────────────────────────────────────────────────────
//

void parse_block(block *block, set *token_set);
void execute_block(block *block);
void execute_field_block(field_block *field_block);

//
// ─── EXPRESSION ─────────────────────────────────────────────────────────────────
//

void parse_token_block(expression *expression, set *token_set);
void parse_operator_expression(expression *operator_expression, set *token_set);
void parse_value_expression(expression *value_expression, set *token_set);
void execute_expression(expression *expression);
void execute_value_expression(value_expression *expression);
int execute_operator_expression(operator_expression *expression);

#endif
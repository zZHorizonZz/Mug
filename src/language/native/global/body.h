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

#include <stdlib.h>
#include <stdio.h>

#include "expression.h"

typedef struct body_s
{
    size_t length;
    expression **expression;
} body;

typedef union block_s
{
    field_block *field_block;
    expression_block *expression_block;
    statement_block *statement_block;
} block;

typedef struct field_block_s
{
    // todo add object type;
    char *name;
    expression *initializer;
} field_block;

typedef struct expression_block_s
{
    expression *expression;
} expression_block;

typedef struct statement_blocks_s
{
    char *t;
} statement_block;

void evaluate_body(body *body, token_iterator *iterator);
void add_expression(body *body, expression *expression);

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

#ifndef BLOCK_H
#define BLOCK_H

#include <stdlib.h>
#include <stdio.h>

#include "expression.h"
#include "storage.h"

typedef union block_u block;
typedef struct field_block_s field_block;
typedef struct expression_blocks_s expression_block;
typedef struct statement_block_s statement_block;

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
    expression *initializer;
};

struct expression_block_s
{
    expression *expression;
};

struct statement_blocks_s
{
    char *t;
};

void parse_block(set *block_set, block *block, set *token_set);

#endif
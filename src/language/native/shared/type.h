// Copyright 2022 Daniel Fiala
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef TYPE_H
#define TYPE_H

#include "storage.h"
#include "primitive.h"
#include "token.h"

typedef struct mug_program_s mug_program;
typedef struct mug_machine_s mug_machine;
typedef struct mug_environment_s mug_environment;

typedef enum field_type_e field_type;
typedef enum advanced_primitive_e advanced_primitive;

typedef struct mug_structure_s mug_structure;
typedef struct mug_foundation_s mug_foundation;
typedef struct mug_method_s mug_method;
typedef struct mug_field_s mug_field;

typedef struct body_s body;

typedef struct block_s block;
typedef struct field_block_s field_block;
typedef struct expression_block_s expression_block;
typedef struct statement_block_s statement_block;
typedef struct return_block_s return_block;

typedef struct expression_s expression;
typedef struct value_expression_s value_expression;
typedef struct operator_expression_s operator_expression;
typedef struct reference_expression_s reference_expression;

struct mug_program_s
{
    char *path;
    char *name;
};

struct mug_machine_s
{
    char os_type;
    char *os_name;

    char metadata;

    mug_environment *environment;
};

struct mug_environment_s
{
    mug_program *program;

    set *native_foundations;
    set *native_structures;
};

enum field_type_e
{
    BASIC_PRIMITIVE,
    ADVANCED_PRIMITIVE
};

enum advanced_primitive_e
{
    FOUNDATION,
    STRUCTURE
};

struct mug_structure_s
{
    mug_foundation *foundation;

    mug_primitive *primitive;
    mug_field **fields;
};

struct mug_foundation_s
{
    const char *location;
    const char *name;

    unsigned char metadata;
    unsigned char type;

    size_t method_count;
    size_t field_count;

    mug_method **method;
};

struct mug_method_s
{
    char *name;
    body *body;
};

struct mug_field_s
{
    mug_foundation *type;

    char *name;
    mug_structure *value;
};

struct body_s
{
    set *declared_fields;
    set *body_block;
};

struct block_s
{
    char type;

    field_block *field_block;
    expression_block *expression_block;
    statement_block *statement_block;
};

struct field_block_s
{
    mug_foundation *type;
    char *name;

    char initializer_type;
    expression *initializer;
};

struct return_block_s
{
    char *type;

    char expression_type;
    expression *expression;
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

struct expression_s
{
    char type;

    value_expression *value_expression;
    operator_expression *operator_expression;
    reference_expression *reference_expression;
};

struct value_expression_s
{
    mug_structure *value;
};

struct operator_expression_s
{
    char operator;

    char left_side_type;
    char right_side_type;

    expression *left_side;
    expression *right_side;
};

struct reference_expression_s
{
    char *reference;
};

#endif
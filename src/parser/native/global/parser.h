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

#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "object.h"

static const char *EXPRESSION = "VALUE_EXPRESSION|OPERATOR_EXPRESSION|REFERENCE_EXPRESSION";
static const char *VALUE_EXPRESSION = "<PRIMITIVE>";
static const char *OPERATOR_EXPRESSION = "(EXPRESSION)<OPERATOR>(EXPRESSION)";
static const char *REFERENCE_EXPRESSION = "<IDENTIFIER>?()?";
static const char *DECLARED_FIELD_BLOCK = "<IDENTIFIER> <IDENTIFIER> = (EXPRESSION)";
static const char *FIELD_BLOCK = "<IDENTIFIER> = (EXPRESSION)";
static const char *RETURN_BLOCK = "'return' ?(EXPRESSION)?";

typedef struct pattern_s pattern;

struct pattern_s
{
    size_t length;
    char *pattern;
};

// char parse_block(block *block, set *token_set);

char is_mathing(const char *rule, set *token_set);
pattern *compile_pattern(const char *rule);

char is_expression(set *token_set);
char is_value_expression(set *token_set);
char is_operator_expression(set *token_set);
char is_reference_expression(set *token_set);
char is_declared_field_block(set *token_set);
char is_field_block(set *token_set);
char is_return_block(set *token_set);

#endif
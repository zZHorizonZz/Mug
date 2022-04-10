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

#ifndef PATTERN_H
#define PATTERN_H

#include "storage.h"
#include "token.h"

#define OPTIONAL_CHARACTER '?'
#define SPECIFIC_TOKEN_CHARACTER '\''
#define EXPRESSION_CHARACTER_START '('
#define EXPRESSION_CHARACTER_END ')'
#define TOKEN_CHARACTER_START '<'
#define TOKEN_CHARACTER_END '>'

typedef struct pattern_s pattern;

struct pattern_s
{
    size_t length;
    unsigned char *pattern;
};

pattern *compile_pattern(const char *rule);
void expand_pattern(pattern *pattern, const char rule);
unsigned char parse_token_type(const char *input);
unsigned char parse_expression_type(const char *input);
token *parse_specific_token_type(const char *input);

#endif
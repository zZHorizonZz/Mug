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

#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <string.h>

#include "token.h"
#include "binary_encoder.h"

typedef struct lexer_s lexer;

struct lexer_s
{
    char *content;

    int content_length;
    int last_index;
    int last_token_index;

    token *current_token;
    token **tokens;
};

char *create_token_binary(lexer *lexer);

void add_binary_header(compound *binary);
void add_binary_content(compound *binary, lexer *lexer);

void parse_content(lexer *lexer, char *content);
void parse_next_token(lexer *lexer);
void next_token(lexer *lexer, token *token, int offset);
void next_string_token(lexer *lexer);

#define MAX_LENGTH 1

#endif
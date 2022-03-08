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

#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>
#include <string.h>

typedef struct token_s
{
    char type;
    char identifier;

    char *data;
} token;

typedef struct token_iterator_s
{
    size_t length;

    int index;
    token *current_token;

    token **array;
} token_iterator;

static const char *SEPARATOR[16] = {".", ",", "(", ")", "{", "}", ";", "\""};
static const char *KEYWORD[16] = {"repository", "structure", "void", "native", "if", "else", "elseif", "while"};
static const char *OPERATOR[16] = {"+", "-", "*", "/", "<<", ">>", "|", "&", "^"};
static const char *BLANK[16] = {"//"};
static const char *IGNORE[16] = {" ", "\n", "\r", "\t"};

void parse_token_letter(token *token, char letter);
void parse_token(token *token, char *content);

token_iterator *create_iterator(size_t length, token **array);
int resize_iterator(token_iterator *iterator, int start, int end);

int iterator_next(token_iterator *iterator);
int iterator_previous(token_iterator *iterator);
int iterator_has_next(token_iterator *iterator);
void free_iterator(token_iterator *iterator);

int is_separator(char letter);
int is_operator(char letter);
int is_ignore(char letter);
int is_constant(char *content);

#endif
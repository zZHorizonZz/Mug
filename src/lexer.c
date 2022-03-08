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

#include <stdio.h>
#include <string.h>

#include "token.h"
#include "binary_encoder.h"

#define MAX_LENGTH 1

typedef struct lexer_s
{
    char *content;

    int content_length;
    int last_index;
    int last_token_index;

    token *current_token;
    token **tokens;
} lexer;

char *create_token_binary(lexer *lexer);

void add_binary_header(compound *binary);
void add_binary_content(compound *binary, lexer *lexer);

void parse_content(lexer *lexer, char *content);
void parse_next_token(lexer *lexer);
void next_token(lexer *lexer, token *token, int offset);
void next_string_token(lexer *lexer);

char *create_token_binary(lexer *lexer)
{
    compound *binary = calloc(2, sizeof(struct compound_s));
    tag *tag = malloc(sizeof(tag));

    binary->tag = tag;
    create_mapped_list_tag(binary);

    add_binary_header(binary);
    add_binary_content(binary, lexer);

    char *binary_data = create_binary(binary);

    free_compound(binary);

    return binary_data;
}

void add_binary_header(compound *binary)
{
    printf("Binary header....");
    compound *header = create_empty_compound();
    compound *name = create_empty_compound();
    compound *author = create_empty_compound();

    create_mapped_list_tag(header);
    create_string_tag(name, "test");
    create_string_tag(author, "Horizon");
    add_value_to_mapped_list_tag(header, "name", name);
    add_value_to_mapped_list_tag(header, "author", author);
    add_value_to_mapped_list_tag(binary, "header", header);
}

void add_binary_content(compound *binary, lexer *lexer)
{
    compound *content = create_empty_compound();

    create_single_type_list_tag(content, 0x04);

    size_t offset = 0x00;
    for (size_t i = 0; i < lexer->last_token_index; i++)
    {
        token *token = lexer->tokens[i];

        compound *type = create_empty_compound();
        compound *identifier = create_empty_compound();

        create_byte_tag(type, token->type);
        create_byte_tag(identifier, token->identifier);

        add_value_to_single_type_list_tag(content, type);
        add_value_to_single_type_list_tag(content, identifier);

        if (token->data != 0x00)
        {
            compound *data = create_empty_compound();

            create_string_tag(data, token->data);
            add_value_to_single_type_list_tag(content, data);
        }
    }

    add_value_to_mapped_list_tag(binary, "content", content);
}

void parse_content(lexer *lexer, char *content)
{
    lexer->content = content;
    lexer->content_length = strlen(content);
    lexer->last_index = 0x00;

    if (lexer->tokens == 0x00)
    {
        lexer->tokens = malloc(sizeof(token));
    }

    int max_depth = 128;
    int current_depth = 0;

    while (lexer->last_index != lexer->content_length && current_depth <= max_depth)
    {
        parse_next_token(lexer);
        current_depth++;
    }
}

void parse_next_token(lexer *lexer)
{
    token *token = malloc(sizeof(struct token_s));

    token->data = 0x00;
    token->type = 0x00;
    token->identifier = 0x00;

    int size = 0;
    int offset = 0;
    char *text = 0x00;
    int current_index = lexer->last_index;

    for (size_t i = lexer->last_index; i < lexer->content_length; i++)
    {
        char current_letter = lexer->content[i];
        offset++;

        if (is_ignore(current_letter))
        {
            if (i == lexer->content_length - 1)
            {
                lexer->last_index = lexer->content_length;
                return;
            }

            if (size > 0)
            {
                break;
            }
            else
            {
                continue;
            }
        }

        if (size > 0 && is_separator(current_letter) == 0x01)
        {
            offset--;
            break;
        }

        char *tmp;

        if (text == 0x00)
        {
            tmp = malloc((++size) + 0x01);
        }
        else
        {
            tmp = realloc(text, (++size) + 0x01);
        }

        if (tmp != 0x00)
        {
            text = tmp;
            text[size - 1] = current_letter;
            text[size] = 0x00;
        }
        else
        {
            printf("\n[ERROR] Null pointer exception. (Temporary text is null)\n");
            exit(0x01);
            return;
        }

        char *token_data = malloc(strlen(text) + 1);
        if(token_data == 0x00) {
            printf("\n[ERROR] Null pointer exception. (Token data are null)\n");
            exit(0x01);
            return;
        }

        parse_token(token, strcpy(token_data, text));

        if (token->type == 0x01 && token->identifier == 0x07)
        {
            int string_start = i;
            lexer->last_index = i + 1;
            next_string_token(lexer);
            i += lexer->last_index - string_start;
            return;
        }

        if (token->type != 0x00)
        {
            break;
        }
    }

    if (size == 0x00)
    {
        return;
    }

    next_token(lexer, token, offset);

    if (text != 0x00)
    {
        free(text);
    }
}

void next_token(lexer *lexer, token *token, int offset)
{
    struct token_s **tmp;

    if (lexer->tokens == 0x00)
    {
        tmp = malloc(sizeof(struct token_s));
    }
    else
    {
        tmp = realloc(lexer->tokens, (lexer->last_token_index + 1) * sizeof(struct token_s));
    }

    if (tmp != 0x00)
    {
        tmp[lexer->last_token_index++] = token;
        lexer->tokens = tmp;
    }
    else
    {
        printf("\n[ERROR] Null pointer exception. (Temporary token array is null.)\n");
        return;
    }

    lexer->current_token = token;
    lexer->last_index += offset;
}

void next_string_token(lexer *lexer)
{
    token *token = malloc(sizeof(token));
    char *current_text = malloc(sizeof(char));

    int offset = 0;
    int current_index = lexer->last_index;
    for (size_t i = 0; i < lexer->content_length; i++)
    {
        offset = i;

        if (lexer->content[lexer->last_index + i] == '"')
        {
            break;
        }

        char *tmp = realloc(current_text, (i + 1) * sizeof(char));

        if (tmp != 0x00)
        {
            current_text = tmp;
            tmp[i] = lexer->content[lexer->last_index + i];
            current_text = strcpy(current_text, tmp);
        }
    }

    char *data = malloc(strlen(current_text));
    
    token->data = strcpy(data, current_text);
    token->type = 0x05;
    token->identifier = 0x06;

    next_token(lexer, token, offset);

    free(current_text);
}

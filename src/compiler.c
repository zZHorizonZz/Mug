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

#include "lexer.c"
#include "storage.h"
#include "structure.h"
#include "parser.h"

struct binary
{
    char *name;
    char *author;
};

int compile_file(char *path, char *name);
int create_binary_file(int *path, char *name, char *binary, int binary_size);

int compile_file(char *path, char *name)
{
    printf("[Compiler] Compiling file %s/%s.\n", path, name);
    FILE *fp = fopen("D:\\program.str", "r");

    if (fp == 0x00)
    {
        printf("Error: could not open file %s", "D:\\program.str");
        return 1;
    }

    char buffer[256];
    lexer *lexer = malloc(sizeof(struct lexer_s));
    lexer->tokens = 0x00;
    lexer->current_token = 0x00;
    lexer->last_token_index = 0x00;

    printf("[Compiler] Evaluating content...");
    while (fgets(buffer, 256, fp))
    {
        parse_content(lexer, buffer);
        free(buffer);
    }

    printf(" [Done]\n");

    for (size_t i = 0; i < lexer->last_token_index; i++)
    {
        token *token = lexer->tokens[i];
        if (token->type != 0x00)
        {
            switch (token->type)
            {
            case 0x01:
                printf("[TOKEN] Separator token of type '%s'.\n", SEPARATOR[token->identifier]);
                break;
            case 0x02:
                printf("[TOKEN] Keyword token of type '%s'.\n", KEYWORD[token->identifier]);
                break;
            case 0x03:
                printf("[TOKEN] Operator token of type '%s'.\n", OPERATOR[token->identifier]);
                break;
            case 0x05:
                printf("[TOKEN] Primitive token of type '%s'.\n", token->data);
                break;
            default:
                break;
            }
        }
        else
        {
            printf("[TOKEN] Identifier token '%s'.\n", token->data);
        }
    }

    token **tokens = calloc(lexer->last_token_index - 1, sizeof(token *));
    for (size_t i = 0; i < lexer->last_token_index - 1; i++)
    {
        tokens[i] = lexer->tokens[i];
    }

    set *token_set = create_set(lexer->last_token_index - 1, (void **)tokens);
    mug_method *method = new_method();

    printf("[Method] Parsing method ...");
    //parse_method(method, token_set);
    printf(" %s [Done] \n", method->name);
    printf("[Method] Executing method %s", method->name);
    execute_method(method);
    printf(" [Done] \n");

    fclose(fp);

    printf("[Compiler] Creating token binary... ");
    // char *binary = create_token_binary(lexer);
    printf(" [Done]");

    // create_binary_file(0x00, 0x00, binary, lexer->last_token_index * 0x02);

    free(lexer->content);
    free(lexer->tokens);
    free(lexer->current_token);
    free(lexer);
}

int create_binary_file(int *path, char *name, char *binary, int binary_size)
{
    FILE *file;

    if ((file = fopen("D:\\program.mug", "wb")) == 0x00)
    {
        printf("Error! opening file");
        exit(1);
    }

    fwrite(binary, binary_size, 0x01, file);
    fclose(file);
    free(binary);
}
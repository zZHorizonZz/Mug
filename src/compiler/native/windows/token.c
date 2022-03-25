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
#include <stdlib.h>

#include "token.h"
#include "utilities.h"

void parse_token_letter(token *token, char letter)
{
    char *buffer = malloc(sizeof(char));
    buffer[0] = letter;
    return parse_token(token, buffer);
}

void parse_token(token *token, char *content)
{
    for (size_t i = 0; i < 0x20; i++)
    {
        if (i >= 0x10)
        {
            if (KEYWORD[i] != 0x00 && strcmp(content, KEYWORD[i]) == 0)
            {
                token->type = 0x02;
                token->identifier = i;
                token->data = 0x00;

                return;
            }
            continue;
        }
        else
        {
            if (SEPARATOR[i] != 0x00 && strlen(content) == 1 && content[0] == *SEPARATOR[i])
            {
                token->type = 0x01;
                token->identifier = i;
                token->data = 0x00;

                return;
            }

            if (KEYWORD[i] != 0x00 && strcmp(content, KEYWORD[i]) == 0)
            {
                token->type = 0x02;
                token->identifier = i;
                token->data = 0x00;

                return;
            }

            if (OPERATOR[i] != 0x00 && strcmp(content, OPERATOR[i]) == 0)
            {
                token->type = 0x03;
                token->identifier = i;
                token->data = 0x00;

                return;
            }

            if (BLANK[i] != 0x00 && strcmp(content, BLANK[i]) == 0)
            {
                token->type = 0x04;
                token->identifier = i;
                token->data = 0x00;

                return;
            }
        }
    }

    token->type = 0x00;
    token->identifier = 0x00;

    if (content != 0x00)
    {
        if (is_constant(content) == 0x01)
        {
            token->type = 0x05;
            token->identifier = get_primitive_type(content);
        }

        token->data = malloc(strlen(content) + 1);
        if (token->data == 0x00)
        {
            printf("\n[ERROR] Null pointer exception. (Token data are null)\n");
            exit(0x01);
            return;
        }
        strcpy(token->data, content);
        free(content); // There seems to be bug with freying of content.
    }
}

int is_separator(char letter)
{
    for (size_t i = 0; i < 16; i++)
    {
        if (SEPARATOR[i] != 0x00 && letter == *SEPARATOR[i])
        {
            return 1;
        }
    }

    return 0;
}

int is_operator(char letter)
{
    for (size_t i = 0; i < 16; i++)
    {
        if (OPERATOR[i] != 0x00 && letter == *OPERATOR[i])
        {
            return 1;
        }
    }

    return 0;
}

int is_ignore(char letter)
{
    for (size_t i = 0; i < 16; i++)
    {
        if (IGNORE[i] != 0x00 && letter == *IGNORE[i])
        {
            return 1;
        }
    }

    return 0;
}

int is_constant(char *content)
{
    int length = strlen(content);
    if (strcmp(content, "true") == 0x00 || strcmp(content, "false") == 0x00)
    {
        return 0x01;
    }

    if (length > 1 && content[0x00] == 0x22 && content[length] == 0x22)
    {
        return 0x01;
    }

    for (size_t i = 0; i <= length; i++)
    {
        if ((content[i] >= 0x30 && content[i] <= 0x39))
        {
            if (i = strlen(content))
            {
                return 0x01;
            }

            continue;
        }

        switch (content[i])
        {
        case 0x64:
            return 0x01;
        case 0x66:
            return 0x01;
        case 0x6c:
            return 0x01;
        default:
            return 0x00;
        }
    }

    return 0x00;
}
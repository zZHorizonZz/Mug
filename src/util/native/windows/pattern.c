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

#include "pattern.h"

pattern *compile_pattern(const char *rule)
{
    pattern *rule_pattern = malloc(sizeof(pattern));
    if (rule_pattern == 0x00)
    {
        exit(0x01);
        return 0x00;
    }
    else
    {
        rule_pattern->length = 0x00;
        rule_pattern->pattern = 0x00;
    }

    size_t text_length = 0x00;
    char *text_holder = 0x00;
    char type = 0x00;
    char optional = 0x00;

    for (size_t i = 0; i < strlen(rule); i++)
    {
        char current_char = rule[i];

        switch (current_char)
        {
        case 0x20:
        {
            continue;
        }

        case OPTIONAL_CHARACTER:
        {
            if (optional == 0x00)
            {
                optional = 0x01;
            }
            else
            {
                optional = 0x00;
            }
        }

        case TOKEN_CHARACTER_START:
        {
            type = 0x01;
            continue;
        }

        case TOKEN_CHARACTER_END:
        {
            if (type == 0x01)
            {
                unsigned char token_type = parse_token_type(text_holder);
                if (optional == 0x01)
                {
                    token_type += 0x80;
                }

                expand_pattern(rule_pattern, token_type);
                free(text_holder);

                text_holder = 0x00;
                text_length = 0x00;
                type = 0x00;
            }
            else
            {
                exit(0x01);
                return 0x00;
            }

            continue;
        }

        case EXPRESSION_CHARACTER_START:
        {
            type = 0x02;
            continue;
        }

        case EXPRESSION_CHARACTER_END:
        {
            if (type == 0x02)
            {
                unsigned char expression_type = 0x10 + parse_expression_type(text_holder);
                if (expression_type == 0x01)
                {
                    expression_type += 0x80;
                }

                expand_pattern(rule_pattern, expression_type);
                free(text_holder);

                text_holder = 0x00;
                text_length = 0x00;
                type = 0x00;
            }
            else
            {
                exit(0x01);
                return 0x00;
            }

            continue;
        }

        case SPECIFIC_TOKEN_CHARACTER:
        {
            if (type == 0x00)
            {
                type = 0x03;
            }
            else
            {
                token *token = parse_specific_token_type(text_holder);
                unsigned char value = 0x10 + (token->type * 0x10 + token->identifier);
                if (value == 0x01)
                {
                    value += 0x80;
                }

                expand_pattern(rule_pattern, value);
                free(text_holder);

                text_holder = 0x00;
                text_length = 0x00;
                type = 0x00;
            }

            continue;
        }

        default:
            break;
        }

        text_length++;

        if (text_holder == 0x00)
        {
            text_holder = malloc(sizeof(char) + 0x01);
        }
        else
        {
            text_holder = realloc(text_holder, sizeof(char) * text_length + 0x01);
        }

        text_holder[text_length - 1] = current_char;
        text_holder[text_length] = 0x00;
    }

    return rule_pattern;
}

void expand_pattern(pattern *pattern, const char rule)
{
    pattern->length++;

    if (pattern->pattern == 0x00)
    {
        pattern->pattern = malloc(sizeof(char));
    }
    else
    {
        pattern->pattern = realloc(pattern->pattern, sizeof(char) * pattern->length);
        if (pattern->pattern == 0x00)
        {
            exit(0x01);
        }
    }

    pattern->pattern[pattern->length - 1] = rule;
}

unsigned char parse_token_type(const char *input)
{
    if (input == 0x00)
    {
        return -0x01;
    }

    if (strcmp(input, "PRIMITIVE") == 0x00)
    {
        return 0x05;
    }

    if (strcmp(input, "OPERATOR") == 0x00)
    {
        return 0x03;
    }

    if (strcmp(input, "IDENTIFIER") == 0x00)
    {
        return 0x00;
    }

    return -0x01;
}

unsigned char parse_expression_type(const char *input)
{
    if (input == 0x00)
    {
        return -0x01;
    }

    if (strcmp(input, "EXPRESSION") == 0X00)
    {
        return 0x00;
    }

    if (strcmp(input, "FOUNDATION") == 0x00)
    {
        return 0x01;
    }

    return -0x01;
}

token *parse_specific_token_type(const char *input)
{
    if (input == 0x00)
    {
        return 0x00;
    }

    token *specific_token = malloc(sizeof(token));
    parse_token(specific_token, input);

    return specific_token;
}
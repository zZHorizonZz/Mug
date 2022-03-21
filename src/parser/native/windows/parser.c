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

#include "parser.h"

/*char parse_block(block *block, set *token_set)
{
}*/

char is_mathing(const char *rule, set *token_set)
{
    pattern *rule_patter = compile_pattern(rule);
    for (size_t i = 0; i < rule_patter->pattern; i++)
    {
        char type = rule_patter->pattern[i];
        token *token = token_set->array[i];

        if (type < 0x10 && type == token->type)
        {
            continue;
        }

        if (type >= 0x10 && type < 0x20)
        {
            if (type == 0x10 && type + 0x10 == token->type)
            {
                continue;
            }
        }

        if (type >= 0x20 && type < 0x80)
        {
            char identifier = type % 0x10;
            if (identifier == token->identifier)
            {
                continue;
            }
        }

        return 0x00;
    }

    return 0x01;
}

char parse_token_type(const char *input)
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

char parse_expression_type(const char *input)
{
    if (input == 0x00)
    {
        return -0x01;
    }

    if (strcmp(input, "EXPRESSION") == 0X00)
    {
        return 0x00;
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
    }

    pattern->pattern[pattern->length - 1] = rule;
}

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

    for (size_t i = 0; i < strlen(rule); i++)
    {
        char current_char = rule[i];

        switch (current_char)
        {
        case 0x20:
        {
            continue;
        }

        case 0x3C:
        {
            type = 0x01;
            continue;
        }

        case 0x3E:
        {
            if (type == 0x01)
            {
                char token_type = parse_token_type(text_holder);

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

        case 0x28:
        {
            type = 0x02;
            continue;
        }

        case 0x29:
        {
            if (type == 0x02)
            {
                char expression_type = 0x10 + parse_expression_type(text_holder);

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

        case 0x27:
        {
            if (type == 0x00)
            {
                type = 0x03;
            }
            else
            {
                token *token = parse_specific_token_type(text_holder);
                char value = 0x10 + (token->type * 0x10 + token->identifier);

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

char is_expression(set *token_set)
{
    return is_mathing(EXPRESSION, token_set);
}

char is_value_expression(set *token_set)
{
    return is_mathing(VALUE_EXPRESSION, token_set);
}

char is_operator_expression(set *token_set)
{
    return is_mathing(OPERATOR_EXPRESSION, token_set);
}

char is_reference_expression(set *token_set)
{
    return is_mathing(REFERENCE_EXPRESSION, token_set);
}

char is_declared_field_block(set *token_set)
{
    return is_mathing(DECLARED_FIELD_BLOCK, token_set);
}

char is_field_block(set *token_set)
{
    return is_mathing(FIELD_BLOCK, token_set);
}

char is_return_block(set *token_set)
{
    return is_mathing(RETURN_BLOCK, token_set);
}

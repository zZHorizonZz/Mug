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

#include "body.h"

void parse_body(body *body, token_iterator *iterator)
{
    if (iterator->length < 1)
    {
        return;
    }

    iterator_next(iterator);

    size_t length = 0x00;
    token **current_token_expression;
    token *current_token = iterator->current_token;
    token_iterator *expression_iterator;
    expression *expression;

    while (iterator_has_next(iterator) == 0x01)
    {
        if (current_token->type == 0x01)
        {
            if (current_token->identifier = 0x06)
            {
                if (length < 1 || current_token_expression == 0x00)
                {
                    exit(0x01);
                    return;
                }

                expression_iterator = create_iterator(length, current_token_expression);
                block *block = malloc(sizeof(block));
                parse_block(block, expression_iterator);

                free(expression_iterator);
            }
        }

        if (length == 0x00)
        {
            current_token_expression = malloc(sizeof(token) * length++);
        }
        else
        {
            current_token_expression = realloc(current_token_expression, sizeof(token) * length++);
        }

        current_token_expression[length - 1] = current_token;

        iterator_next(iterator);
        current_token = iterator->current_token;
    }
}

void parse_block(block *block, token_iterator *iterator)
{
    iterator_next(iterator);

    token *current_token = iterator->current_token;

    switch (current_token->type)
    {
    case 0x00:
    {
        field_block *field = malloc(sizeof(field_block));
        expression *initializer = malloc(sizeof(initializer));

        if (field == 0x00)
        {
            exit(0x01);
            return;
        }

        if (iterator->array[iterator->index + 0x01]->type == 0x00)
        {
            field->type = current_token->data;
            iterator_next(iterator);
            field->name = current_token->data;
        }
        else
        {
            field->name = current_token->data;
        }

        iterator_next(iterator);
        parse_token_block(initializer, resize_iterator(iterator, iterator->index, iterator->length));
        break;
    }
    case 0x02:

        break;
    default:
        break;
    }
}

void add_block(body *body, block *expression)
{
}
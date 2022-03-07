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

void evaluate_body(body *body, token_iterator *iterator)
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

                // evaluate_token_block()
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
    }
}

void add_expression(body *body, expression *expression)
{
}
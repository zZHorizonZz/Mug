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
#include "storage.h"

void parse_body(body *body, set *token_set)
{
    if (token_set->length < 1)
    {
        return;
    }

    iterator *token_iterator =create_iterator(token_set);

    iterator_next(token_iterator);

    size_t length = 0x00;
    token **current_token_expression;
    token *current_token = token_iterator->current;
    set *expression_set;
    expression *expression;

    while (iterator_has_next(token_iterator) == 0x01)
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

                expression_set = create_set(length, (void**) current_token_expression);
                block *block = malloc(sizeof(block));
                parse_block(body->body_block, block, expression_set);

                free(expression_set);
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

        iterator_next(token_iterator);
        current_token = token_iterator->current;
    }
}
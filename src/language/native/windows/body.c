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

    iterator *token_iterator = create_iterator(token_set);

    iterator_next(token_iterator);

    token *current_token = token_iterator->current;
    set *expression_set = create_set(0x00, 0x00);
    expression *expression;

    // TODO There is a bug with freeing of expression_set and also it seems like this will pase only one block even if there are two blocks.

    int iterations = 0;
    while (iterator_has_next(token_iterator) == 0x01)
    {
        printf("Iteration %d\n", ++iterations);

        if (current_token->type == 0x01)
        {
            if (current_token->identifier = 0x06)
            {
                if (expression_set->length < 1 || expression_set == 0x00)
                {
                    exit(0x01);
                    return;
                }

                printf("New block.");

                block *block = malloc(sizeof(block));
                parse_block(body->body_block, block, expression_set);

                // free(expression_set);
                expression_set = create_set(0x00, 0x00);
            }
        }

        set_add(expression_set, current_token);
        iterator_next(token_iterator);

        current_token = token_iterator->current;
    }
}
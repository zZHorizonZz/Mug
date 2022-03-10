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

#include "method.h"

void parse_method(method *method, set *token_set)
{
    if (token_set->length < 0)
    {
        return;
    }

    iterator *method_iterator = create_iterator(token_set);
    iterator_next(method_iterator);
    token *current_token = method_iterator->current;

    if (current_token->type == 0x00)
    {
        method->name = current_token->data;
        iterator_next(method_iterator);
        current_token = method_iterator->current;

        if (current_token->type == 0x01 && current_token->identifier == 0x02)
        {
            iterator_next(method_iterator);
            current_token = method_iterator->current;

            if (current_token->type == 0x01 && current_token->identifier == 0x03)
            {
                iterator_next(method_iterator);
                current_token = method_iterator->current;

                if (current_token->type == 0x01 && current_token->identifier == 0x04)
                {
                    set *body_set = create_set(0x00, 0x00);

                    while (method_iterator->index < token_set->length - 1)
                    {
                        iterator_next(method_iterator);
                        current_token = method_iterator->current;

                        set_add(body_set, current_token);
                    }

                    body *method_body = malloc(sizeof(body));
                    if (method_body == 0x00)
                    {
                        exit(0x01);
                        return;
                    }

                    parse_body(method_body, body_set);
                }
            }
        }
    }
    else
    {
        exit(0x01);
        return;
    }
}
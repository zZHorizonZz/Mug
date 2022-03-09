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

#include "block.h"

void parse_block(set *block_set, block *block, set *token_set)
{
    iterator *block_iterator = create_iterator(token_set);
    iterator_next(block_iterator);

    token *current_token = block_iterator->current;

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

        token *future = block_iterator->set->array[block_iterator->index + 0x01];

        if (future->type == 0x00)
        {
            field->type = current_token->data;
            iterator_next(block_iterator);
            field->name = current_token->data;
        }
        else
        {
            field->name = current_token->data;
        }

        iterator_next(block_iterator);
        parse_token_block(initializer, resize_iterator(block_iterator, block_iterator->index, block_iterator->set->length));
        break;
    }
    case 0x02:

        break;
    default:
        break;
    }
}
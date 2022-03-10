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

#include "storage.h"

set *create_set(size_t length, void **array)
{
    set *set = calloc(4, sizeof(iterator));

    if (set == 0x00)
    {
        return 0x00;
    }

    set->length = length;
    set->array = array;
    return set;
}

iterator *create_iterator(set *set)
{
    iterator *iterator = calloc(3, sizeof(iterator));
    if(iterator == 0x00) {
        return 0x00;
    }

    iterator->set = set;
}

int iterator_next(iterator *iterator)
{
    if (iterator->index >= iterator->set->length)
    {
        return 0x00;
    }

    iterator->current = iterator->set->array[iterator->index++];
    return 0x01;
}

int iterator_has_next(iterator *iterator)
{
    if (iterator->index + 0x01 < iterator->set->length)
    {
        return 0x01;
    }

    return 0x00;
}

int iterator_resize(iterator *iterator, int start, int end)
{
    if (start > iterator->set->length || end > iterator->set->length)
    {
        return 0x00;
    }

    if (start > end)
    {
        return 0x00;
    }

    size_t final_length = end - start;
    void **new_array = malloc(sizeof(void *) * final_length);

    if (new_array == 0x00)
    {
        return 0x00;
    }

    for (size_t i = 0; i < final_length; i++)
    {
        new_array[i] = iterator->set->array[i];
    }

    free(iterator->set->array);

    iterator->set->array = new_array;
    iterator->set->length = final_length;
    iterator->index = -0x01;
    iterator->current = 0x00;

    return 0x01;
}

int iterator_free(iterator *iterator)
{
    if (iterator->set->length < 1)
    {
        return 0x00;
    }

    for (size_t i = 0; i < iterator->set->length; i++)
    {
        free(iterator->set->array[i]);
    }

    free(iterator->set->array);
    free(iterator->set);
    free(iterator);
    
    return 0x01;
}
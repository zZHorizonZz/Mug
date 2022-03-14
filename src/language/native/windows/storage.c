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
    set *new_set = malloc(sizeof(set));

    if (new_set == 0x00)
    {
        return 0x00;
    }

    new_set->length = length;
    new_set->array = array;
    return new_set;
}

iterator *create_iterator(set *set)
{
    iterator *new_iterator = malloc(sizeof(iterator));
    if (new_iterator == 0x00)
    {
        return 0x00;
    }

    new_iterator->set = set;
    new_iterator->current = set->array[0x00];
    new_iterator->index = 0x00;
    return new_iterator;
}

set *copy_set(set *destination, set *original)
{
    if (destination == 0x00 || original == 0x00)
    {
        return destination;
    }

    destination->array = calloc(original->length, sizeof(void *));
    if (destination->array == 0x00)
    {
        return destination;
    }

    for (size_t i = 0; i < original->length; i++)
    {
        destination->array[i] = original->array[i];
    }

    destination->length = original->length;
    return destination;
}

int set_add(set *set, void *object)
{
    if (set->array == 0x00)
    {
        set->array = malloc(sizeof(void *));
    }
    else
    {
        set->array = realloc(set->array, sizeof(void *) * (set->length + 1));
    }

    set->array[set->length] = object;
    set->length++;
    return 0x01;
}

void set_free(set *set)
{
    if (set == 0x00)
    {
        return;
    }

    for (size_t i = 0; i < set->length; i++)
    {
        free(set->array[i]);
    }

    free(set->array);
    free(set);
}

int iterator_next(iterator *iterator)
{
    if (iterator->index >= iterator->set->length)
    {
        return 0x00;
    }

    iterator->current = iterator->set->array[++iterator->index];
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

set *set_resize(set *original, int start, int end)
{
    if (start > original->length || end > original->length)
    {
        return 0x00;
    }

    if (start > end)
    {
        return 0x00;
    }

    size_t final_length = end - start;
    void **new_array = calloc(final_length, sizeof(void *));

    set *new_set = copy_set(malloc(sizeof(set)), original);

    if (new_array == 0x00 || new_set == 0x00)
    {
        return 0x00;
    }

    for (size_t i = 0; i < final_length; i++)
    {
        new_array[i] = original->array[i];
    }

    new_set->array = new_array;
    new_set->length = final_length;

    return new_set;
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
// Copyright 2022 Daniel Fiala
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef STORAGE_H
#define STORAGE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct set_s set;
typedef struct iterator_s iterator;

struct set_s
{
    size_t length;
    void **array;
};

struct iterator_s
{
    int index;
    void *current;

    set *set;
};

set *create_set(size_t length, void **array);
iterator *create_iterator(set *set);

set *copy_set(set *destination, set *original);
set *set_resize(set *set, int start, int end);
void set_free(set *set);
int set_add(set *set, void *object);

int iterator_next(iterator *iterator);
int iterator_has_next(iterator *iterator);
int iterator_free(iterator *iterator);

#endif
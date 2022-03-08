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

#include <stdio.h>
#include <string.h>

#include "../obj/list.h"
#include "../obj/object.h"

void test_basic()
{
    printf("--------------------------------\n");
    printf("executening basic test...\n\n");
    char *text = "Test";

    struct list list;
    struct object object;

    int size = 0;
    int flags = 0x00;

    list = create_list(size, flags);
    object = new_object(text);

    printf("List of size %d and with flag bit field of %d has been created successfully. [Done]\n", list.size, list.flags);
    printf("Object with value %d has been created succesfully. [Done]\n", object.value);

    add(&list, object);

    if (list.last_index == 0)
    {
        printf("List doen't contain data. [Failed]");
        return;
    }

    struct object getter = get(&list, 0);

    if (getter.value == 0x00)
    {
        printf("List doesn't contains valid data. [Failed]\n");
        return;
    }
    else
    {
        if (getter.value == text)
        {
            printf("Object added to list is valid. [Done]\n");
        }
        else
        {
            printf("Object is contained in list but doesn't have a valid data. [Failed]\n");
            return;
        }
    }

    printf("\n--------------------------------\n");
    printf("All test has been completed successfully. [Done]\n");
}
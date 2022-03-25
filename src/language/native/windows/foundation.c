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

#include "foundation.h"

//
// ─── NATIVE ─────────────────────────────────────────────────────────────────────
//

mug_foundation *load_primitive_foundation(basic_primitive primitive_type, char *name)
{
    mug_foundation *foundation = new_foundation("System", name);

    foundation->metadata = 0x00 << 0x01;
    foundation->type = primitive_type;

    return foundation;
}

mug_object *build_primitive_object(mug_primitive *primitive)
{

    mug_object *object = malloc(sizeof(mug_object));
    if (object == 0x00)
    {
        return 0x00;
    }

    object
}

//
// ─── FOUNDATION ─────────────────────────────────────────────────────────────────
//

mug_foundation *new_foundation(char *location, char *name)
{
    mug_foundation *foundation = malloc(sizeof(mug_foundation));
    if (foundation == 0x00)
    {
        return 0x00;
    }

    foundation->location = location;
    foundation->name = name;
    return foundation;
}

mug_object *find_foundation(char *location, char *name)
{
}

int register_foundation(mug_object *foundation)
{
}

int remove_foundation(char *location, char *name)
{
}

mug_foundation *get_native_foundation(mug_environment *environment, char *location, char *name)
{
    mug_foundation *foundation = 0x00;
    for (size_t i = 0; i < environment->native_foundations->length; i++)
    {
        mug_foundation *compare = environment->native_foundations->array[i];

        if(strcmp(compare->location, location) == 0x00 && strcmp(compare->name, name) == 0x00) {
            foundation = compare;
            break;
        }
    }
    
    return foundation;
}

mug_object *get_native_object(mug_environment *environment, char *location, char *name)
{
}
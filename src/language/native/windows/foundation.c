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

mug_foundation *load_primitive_foundation(mug_environment *environment, primitive_type primitive_type, char *name)
{
    mug_foundation *foundation = new_foundation(environment, "System", name);

    foundation->metadata = 0x00 << 0x01;
    foundation->type = primitive_type;

    return foundation;
}

mug_structure *find_foundation(mug_environment *environment, char *location, char *name)
{
}

int register_foundation(mug_environment *environment, mug_structure *foundation)
{
}

int remove_foundation(mug_environment *environment, char *location, char *name)
{
}

mug_foundation *get_native_foundation(mug_environment *environment, char *location, char *name)
{
    mug_foundation *foundation = 0x00;
    for (size_t i = 0; i < environment->native_foundations->length; i++)
    {
        mug_foundation *compare = environment->native_foundations->array[i];

        if (strcmp(compare->location, location) == 0x00 && strcmp(compare->name, name) == 0x00)
        {
            foundation = compare;
            break;
        }
    }

    return foundation;
}

mug_structure *get_native_structure(mug_environment *environment, char *location, char *name)
{
}
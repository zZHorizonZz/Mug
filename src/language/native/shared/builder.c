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
#include <stdlib.h>

#include "type.h"

mug_foundation *new_foundation(mug_environment *environment, char *location, char *name)
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

mug_structure *new_structure(mug_environment *environment, mug_foundation *foundation)
{
    mug_structure *structure = malloc(sizeof(mug_structure));
    if (structure == 0x00)
    {
        fprintf(stderr, "Error: Could not allocate memory for structure.\n");
        exit(0x01);
    }

    structure->foundation = foundation;
    return structure;
}

mug_structure *new_primitive_structure(mug_environment *environment, mug_primitive *primitive, primitive_type type)
{
    mug_foundation *foundation = get_native_foundation(environment, "System", get_name(type));
    mug_structure *structure = new_structure(environment, foundation);

    structure->primitive = primitive;
    return structure;
}

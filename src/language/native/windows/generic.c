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

#include "generic.h"

mug_structure *new_primitive_structure(mug_environment *environment, char *data)
{
    mug_primitive *primitive = malloc(sizeof(mug_primitive));
    mug_foundation *foundation = 0x00;

    char type = create_primitive(primitive, data);

    switch (type)
    {
    case 0x00:
    {
        foundation = get_native_foundation(environment, LOCATION, "byte");
        break;
    }
    case 0x01:
    {
        foundation = get_native_foundation(environment, LOCATION, "short");
        break;
    }
    case 0x02:
    {
        foundation = get_native_foundation(environment, LOCATION, "int");
        break;
    }
    case 0x03:
    {
        foundation = get_native_foundation(environment, LOCATION, "long");
        break;
    }
    case 0x04:
    {
        foundation = get_native_foundation(environment, LOCATION, "float");
        break;
    }
    case 0x05:
    {
        foundation = get_native_foundation(environment, LOCATION, "double");
        break;
    }
    case 0x06:
    {
        foundation = get_native_foundation(environment, LOCATION, "string");
        break;
    }
    case 0x07:
    {
        foundation = get_native_foundation(environment, LOCATION, "bool");
        break;
    }
    default:
        break;
    }

    mug_structure *structure = new_structure(foundation);
    structure->primitive = primitive;

    return structure;
}
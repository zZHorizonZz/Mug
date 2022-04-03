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

#include "field.h"

mug_field *get_structure_field(mug_structure *structure, const char *name)
{
    if (name == 0x00)
    {
        return 0x00;
    }

    for (size_t i = 0; i < structure->foundation->fields->length; i++)
    {
        if (strcmp(structure->fields[i]->name, name) == 0x00)
        {
            return structure->fields[i];
        }
    }

    return 0x00;
}

mug_field *get_body_field(body *body, const char *name)
{
    if (name == 0x00)
    {
        return 0x00;
    }

    for (size_t i = 0; i < body->declared_fields->length; i++)
    {
        mug_field *field = body->declared_fields->array[i];
        if (strcmp(field->name, name) == 0x00)
        {
            return field;
        }
    }

    return 0x00;
}

char add_body_field(body *body, mug_field *field)
{
    return set_add(body->declared_fields, field);
}
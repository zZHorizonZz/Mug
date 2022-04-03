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

void call_block(mug_environment *environment, mug_structure *structure, mug_method *method, block *block)
{
    switch (block->type)
    {
    case 0x00:
    {
        call_expression_block(environment, structure, method, block->expression_block);
        break;
    }

    case 0x01:
    {
        call_field_block(environment, structure, method, block->field_block);
        break;
    }
    default:
        break;
    }
}

void call_expression_block(mug_environment *environment, mug_structure *structure, mug_method *method, expression_block *block)
{
    call_expression(environment, structure, method, block->expression);
}

void call_field_block(mug_environment *environment, mug_structure *structure, mug_method *method, field_block *block)
{
    mug_field *field;
    if ((block->metadata & 0x01 << 0x00) != 0x00)
    {
        field = get_body_field(method->body, block->name);
        if (field == 0x00)
        {
            field = get_structure_field(structure, block->name);
        }

        if (field == 0x00)
        {
            printf("Error: Field %s not found in structure %s\n", block->name, structure->foundation->name);
            exit(0x01);
        }
    }
    else
    {
        field = malloc(sizeof(mug_field));
        if (field == 0x00)
        {
            printf("Error: Could not allocate memory for field.\n");
            exit(0x01);
        }

        field->name = block->name;
        field->type = block->type;
    }

    mug_structure *field_value = call_expression(environment, structure, method, block->initializer);

    if (field_value == 0x00)
    {
        printf("Error: Could not initialize structure.\n");
        exit(0x01);
    }

    field->value = field_value;
    add_body_field(method->body, field);
}
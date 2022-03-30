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
    if(//todo add fields methods.)
    field = get_field(structure, block->field_name);
    if (field == 0x00)
    {
        printf("Error: Could not allocate memory for field.\n");
        exit(0x01);
    }

    if (field->type == 0x00)
    {
        field->type = block->type;
    }

    if (field->name == 0x00)
    {
        field->name = block->name;
    }

    mug_structure *structure;

    if (block->initializer_type == BASIC_PRIMITIVE)
    {
        // todo merge these method call_expression to return mug_object and not mug_primitive
        mug_primitive *primitive = call_expression(environment, structure, method, block->initializer);
        structure = new_primitive_structure(environment, primitive, field->type->type);
    }
    else
    {
        // todo up
    }

    if (structure == 0x00)
    {
        printf("Error: Could not initialize structure.\n");
        exit(0x01);
    }

    field->value = structure;
}
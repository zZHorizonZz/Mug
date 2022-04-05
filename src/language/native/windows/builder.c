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

#include "builder.h"

mug_foundation *new_foundation(mug_environment *environment, char *location, char *name)
{
    mug_foundation *foundation = malloc(sizeof(mug_foundation));
    if (foundation == 0x00)
    {
        return 0x00;
    }

    foundation->metadata = 0x00;
    foundation->type = 0x00;

    foundation->location = location;
    foundation->name = name;

    foundation->methods = create_set(0x00, 0x00);
    foundation->fields = create_set(0x00, 0x00);

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

    structure->fields = create_set(0x00, 0x00);
    structure->primitive = 0x00;
    structure->foundation = foundation;

    return structure;
}

mug_structure *new_primitive_structure(mug_environment *environment, mug_primitive *primitive, primitive_type type)
{
    mug_foundation *foundation = get_native_foundation(environment, LOCATION, get_name(type));
    mug_structure *structure = new_structure(environment, foundation);

    structure->primitive = primitive;

    return structure;
}

expression *new_expression()
{
    expression *_expression = malloc(sizeof(expression));
    if (_expression == 0x00)
    {
        fprintf(stderr, "Error: Could not allocate memory for expression.\n");
        exit(0x01);
    }

    _expression->operator_expression = 0x00;
    _expression->reference_expression = 0x00;
    _expression->value_expression = 0x00;

    _expression->type = 0x00;

    return _expression;
}
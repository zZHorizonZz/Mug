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

#include "expression.h"

mug_structure *call_expression(mug_environment *environment, mug_structure *structure, mug_method *method, expression *expression)
{
    switch (expression->type)
    {
    case 0x00:
    {
        return call_value_expression(environment, structure, method, expression->value_expression);
    }

    case 0x01:
    {
        call_operator_expression(environment, structure, method, expression->reference_expression);
        break;
    }

    case 0x02:
    {
        return call_operator_expression(environment, structure, method, expression->operator_expression);
    }
    default:
        break;
    }

    return 0x00;
}

mug_structure *call_value_expression(mug_environment *environment, mug_structure *structure, mug_method *method, value_expression *expression)
{
    // todo add creation of new structures through keyword new or something similar
    return expression->value;
}

mug_structure *call_operator_expression(mug_environment *environment, mug_structure *structure, mug_method *method, operator_expression *expression)
{
    mug_structure *result = 0x00;
    mug_primitive *result_primitive = 0x00;

    switch (expression->operator)
    {
    case 0x00:
    {
        result_primitive = call_operator_add(environment, structure, method, expression);
        break;
    }

    case 0x01:
    {
        result_primitive = call_operator_subtract(environment, structure, method, expression);
        break;
    }

    case 0x02:
    {
        result_primitive = call_operator_multiply(environment, structure, method, expression);
        break;
    }

    case 0x03:
    {
        result_primitive = call_operator_divide(environment, structure, method, expression);
        break;
    }

    default:
        break;
    }

    result = new_primitive_structure(environment, result_primitive, expression->left_side_type);
    return result;
}

mug_structure *call_reference_expression(mug_environment *environment, mug_structure *structure, mug_method *method, reference_expression *expression)
{
    if ((expression->metadata & 0x01 << 0x00) == 0x00)
    {
        mug_field *field = get_body_field(method->body, expression->name);
        if (field == 0x00)
        {
            field = get_structure_field(structure, expression->name);
        }

        if (field == 0x00)
        {
            return 0x00;
        }

        return field->value;
    }

    return 0x00;
}

mug_primitive *call_operator_add(mug_environment *environment, mug_structure *structure, mug_method *method, operator_expression *expression)
{
    if (expression->right_side_type == 0x00)
    {
        return sum_primitive(expression->left_side->value_expression->value->primitive,
                             expression->left_side_type,
                             expression->right_side->value_expression->value->primitive,
                             expression->right_side_type);
    }
    else
    {
        mug_primitive *right_side = call_operator_expression(environment,
                                                             structure,
                                                             method,
                                                             expression->right_side->operator_expression);
        return sum_primitive(expression->left_side->value_expression->value->primitive,
                             expression->left_side_type,
                             right_side,
                             expression->right_side_type);
    }
}

mug_primitive *call_operator_subtract(mug_environment *environment, mug_structure *structure, mug_method *method, operator_expression *expression)
{
    if (expression->right_side_type == 0x00)
    {
        return subtract_primitive(expression->left_side->value_expression->value->primitive,
                                  expression->left_side_type,
                                  expression->right_side->value_expression->value->primitive,
                                  expression->right_side_type);
    }
    else
    {
        mug_primitive *right_side = call_operator_expression(environment,
                                                             structure,
                                                             method,
                                                             expression->right_side->operator_expression);
        return subtract_primitive(expression->left_side->value_expression->value->primitive,
                                  expression->left_side_type,
                                  right_side,
                                  expression->right_side_type);
    }
}

mug_primitive *call_operator_multiply(mug_environment *environment, mug_structure *structure, mug_method *method, operator_expression *expression)
{
    if (expression->right_side_type == 0x00)
    {
        return multiply_primitive(expression->left_side->value_expression->value->primitive,
                                  expression->left_side_type,
                                  expression->right_side->value_expression->value->primitive,
                                  expression->right_side_type);
    }
    else
    {
        mug_primitive *right_side = call_operator_expression(environment,
                                                             structure,
                                                             method,
                                                             expression->right_side->operator_expression);
        return multiply_primitive(expression->left_side->value_expression->value->primitive,
                                  expression->left_side_type,
                                  right_side,
                                  expression->right_side_type);
    }
}

mug_primitive *call_operator_divide(mug_environment *environment, mug_structure *structure, mug_method *method, operator_expression *expression)
{
    if (expression->right_side_type == 0x00)
    {
        return divide_primitive(expression->left_side->value_expression->value->primitive,
                                expression->left_side_type,
                                expression->right_side->value_expression->value->primitive,
                                expression->right_side_type);
    }
    else
    {
        mug_primitive *right_side = call_operator_expression(environment,
                                                             structure,
                                                             method,
                                                             expression->right_side->operator_expression);
        return divide_primitive(expression->left_side->value_expression->value->primitive,
                                expression->left_side_type,
                                right_side,
                                expression->right_side_type);
    }
}
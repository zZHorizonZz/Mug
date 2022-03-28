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

mug_primitive *call_expression(mug_environment *environment, mug_structure *structure, mug_method *method, expression *expression)
{
    switch (expression->type)
    {
    case 0x00:
    {
        call_value_expression(environment, structure, method, expression->value_expression);
        break;
    }

    case 0x01:
    {
        // execute_reference_expression(expression->value_expression);
        break;
    }

    case 0x02:
    {
        call_operator_expression(environment, structure, method, expression->operator_expression);
        break;
    }
    default:
        break;
    }
}

mug_primitive *call_value_expression(mug_environment *environment, mug_structure *structure, mug_method *method, value_expression *expression)
{
    mug_primitive *primitive = expression->value->primitive;
    switch (expression->value->foundation->type)
    {
    case 0x00:
        printf("Byte value is %c", primitive->mug_byte->value);
        break;
    case 0x01:
        printf("Short value is %d", primitive->mug_short->value);
        break;
    case 0x02:
        printf("Int value is %d", primitive->mug_int->value);
        break;
    case 0x03:
        printf("Long value is %d", primitive->mug_long->value);
        break;
    case 0x04:
        printf("Float value is %f", primitive->mug_float->value);
        break;
    case 0x05:
        printf("Double value is %f", primitive->mug_double->value);
        break;
    case 0x06:
        printf("String value is %s", primitive->mug_string->value);
        break;
    case 0x07:
        printf("Boolean value is %c", primitive->mug_boolean->value);
        break;
    default:
        break;
    }
}

mug_primitive *call_operator_expression(mug_environment *environment, mug_structure *structure, mug_method *method, operator_expression *expression)
{
    switch (expression->operator)
    {
    case 0x00:
    {
        call_operator_add(environment, structure, method, expression);
        break;
    }

    case 0x01:
    {
        call_operator_subtract(environment, structure, method, expression);
        break;
    }

    case 0x02:
    {
        call_operator_multiply(environment, structure, method, expression);
        break;
    }

    case 0x03:
    {
        call_operator_divide(environment, structure, method, expression);
        break;
    }

    default:
        break;
    }
}

mug_primitive *call_reference_expression(mug_environment *environment, mug_structure *structure, mug_method *method, reference_expression *expression)
{
}

mug_primitive *call_operator_add(mug_environment *environment, mug_structure *structure, mug_method *method, operator_expression *expression)
{
    if (expression->right_side_type == 0x00)
    {
        mug_primitive *left_side = expression->left_side->primitive;
        mug_primitive *right_side = expression->right_side->primitive;

        // todo sum two values with checks for overflows
        
        //int result = expression->left_side->value_expression->value->primitive->mug_int->value +
          //           expression->right_side->value_expression->value->primitive->mug_int->value;

        
        return result;
    }
    else
    {
        int result = expression->left_side->value_expression->value->primitive->mug_int->value +
                     execute_operator_expression(expression->right_side->operator_expression);

        return result;
    }
}

mug_primitive *call_operator_subtract(mug_environment *environment, mug_structure *structure, mug_method *method, operator_expression *expression)
{
}

mug_primitive *call_operator_multiply(mug_environment *environment, mug_structure *structure, mug_method *method, operator_expression *expression)
{
}

mug_primitive *call_operator_divide(mug_environment *environment, mug_structure *structure, mug_method *method, operator_expression *expression)
{
}
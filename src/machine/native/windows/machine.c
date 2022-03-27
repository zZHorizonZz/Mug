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

#include "machine.h"

void launch_machine(char *path, char *name)
{
    mug_program *program = malloc(sizeof(mug_program));
    mug_environment *environment = malloc(sizeof(mug_environment));

    if (program == 0x00 || environment == 0x00)
    {
        return 0x02;
    }

    program->path = path;
    program->name = name;

    mug_machine *machine = malloc(sizeof(mug_machine));
    if (machine == 0x00)
    {
        return 0x02;
    }

    machine->environment = environment;

    machine->os_type = get_os_type();
    machine->os_name = get_os_name();

    if (machine->os_type == 0x00 || machine->os_type == 0x04)
    {
        printf("Your operation system is not supported!");
        exit(0x03);
    }

    launch_environment(program, environment);
}

void execute_method(mug_method *method)
{
    if (method->body == 0x00)
    {
        return;
    }

    execute_body(method->body);
}

void execute_body(body *body)
{
    if (body->length < 1)
    {
        return;
    }

    for (size_t i = 0; i < body->length; i++)
    {
        block *block = body->body_block->array[i];
        char *type = body->body_type->array[i];

        execute_block(*type, block);
    }
}

void execute_block(char type, block *block)
{
    switch (type)
    {
    case 0x00:
    {
        execute_expression(block->expression_block->expression_type, block->expression_block->expression);
        break;
    }

    case 0x01:
    {
        execute_field_block(block->field_block);
        break;
    }
    default:
        break;
    }
}

void execute_field_block(field_block *field_block)
{
    execute_expression(0x00, field_block->initializer);
}

void execute_expression(char type, expression *expression)
{
    switch (type)
    {
    case 0x00:
    {
        execute_value_expression(expression->value_expression);
        break;
    }

    case 0x01:
    {
        // execute_reference_expression(expression->value_expression);
        break;
    }

    case 0x02:
    {
        execute_operator_expression(expression->operator_expression);
        break;
    }
    default:
        break;
    }
}

void execute_value_expression(value_expression *expression)
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

int execute_operator_expression(operator_expression *expression)
{
    if (expression->right_side_type == 0x00)
    {
        switch ((int)expression->operator)
        {
        case 0x00:
        {
            int result = expression->left_side->value_expression->value->primitive->mug_int->value +
                         expression->right_side->value_expression->value->primitive->mug_int->value;

            return result;
        }
        case 0x01:
        {
            int result = expression->left_side->value_expression->value->primitive->mug_int->value +
                         expression->right_side->value_expression->value->primitive->mug_int->value;

            return result;
        }
        case 0x02:
        {
            int result = expression->left_side->value_expression->value->primitive->mug_int->value +
                         expression->right_side->value_expression->value->primitive->mug_int->value;

            return result;
        }
        case 0x03:
        {
            int result = expression->left_side->value_expression->value->primitive->mug_int->value +
                         expression->right_side->value_expression->value->primitive->mug_int->value;

            return result;
        }
        default:
            break;
        }
    }
    else
    {
        switch ((int)expression->operator)
        {
        case 0x00:
        {
            int result = expression->left_side->value_expression->value->primitive->mug_int->value +
                         execute_operator_expression(expression->right_side->operator_expression);

            return result;
        }
        case 0x01:
        {
            int result = expression->left_side->value_expression->value->primitive->mug_int->value +
                         execute_operator_expression(expression->right_side->operator_expression);

            return result;
        }
        case 0x02:
        {
            int result = expression->left_side->value_expression->value->primitive->mug_int->value +
                         execute_operator_expression(expression->right_side->operator_expression);

            return result;
        }
        case 0x03:
        {
            int result = expression->left_side->value_expression->value->primitive->mug_int->value +
                         execute_operator_expression(expression->right_side->operator_expression);

            return result;
        }
        default:
            break;
        }
    }
}
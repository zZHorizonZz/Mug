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

#include "object.h"

/*
 * ─── OBJECT ─────────────────────────────────────────────────────────────────────
 */

mug_object *new_object(char *value)
{
    mug_object *obj = malloc(sizeof(mug_object));
    obj->value = value;
    return obj;
}

int equals(mug_object *original, mug_object *equal)
{
    int valid = 0;
    if (original->value == equal->value)
    {
        valid = 1;
    }

    return valid;
}

/*
 * ─── METHOD ─────────────────────────────────────────────────────────────────────
 */

mug_method *new_method()
{
    mug_method *method = malloc(sizeof(mug_method));
    if (method == 0x00)
    {
    }

    method->body = new_body();
    return method;
}

void execute_method(mug_method *method)
{
    if (method->body == 0x00)
    {
        return;
    }

    execute_body(method->body);
}

/*
 * ─── BODY ───────────────────────────────────────────────────────────────────────
 */

body *new_body()
{
    body *new_body = malloc(sizeof(body));
    if (new_body == 0x00)
    {
    }

    new_body->body_block = create_set(0x00, 0x00);
    new_body->body_type = create_set(0x00, 0x00);
    new_body->length = 0x00;

    return new_body;
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

/*
 * ─── BLOCK ──────────────────────────────────────────────────────────────────────
 */

block *new_block()
{
    block *new_block = malloc(sizeof(block));
    if (new_block == 0x00)
    {
    }

    return new_block;
}

void execute_block(char type, block *block)
{
    switch (type)
    {
    case 0x00:
        execute_field_block(block->field_block);
        break;

    default:
        break;
    }
}

void execute_field_block(field_block *field_block)
{
    execute_expression(0x00, field_block->initializer);
}

/*
 * ─── EXPRESSION ─────────────────────────────────────────────────────────────────
 */

void execute_expression(char type, expression *expression)
{
    if (type = 0x00)
    {
        execute_value_expression(expression->value_expression);
    }
    else
    {
        printf("Result of calculation is %d", execute_operator_expression(expression->operator_expression));
    }
}

void execute_value_expression(value_expression *expression)
{
    switch (expression->type)
    {
    case 0x00:
        printf("Byte value is %c", expression->primitive->mug_byte->value);
        break;
    case 0x01:
        printf("Short value is %d", expression->primitive->mug_short->value);
        break;
    case 0x02:
        printf("Int value is %d", expression->primitive->mug_int->value);
        break;
    case 0x03:
        printf("Long value is %d", expression->primitive->mug_long->value);
        break;
    case 0x04:
        printf("Float value is %f", expression->primitive->mug_float->value);
        break;
    case 0x05:
        printf("Double value is %f", expression->primitive->mug_double->value);
        break;
    case 0x06:
        printf("String value is %s", expression->primitive->mug_string->value);
        break;
    case 0x07:
        printf("Boolean value is %c", expression->primitive->mug_boolean->value);
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
            int result = expression->left_side->value_expression->primitive->mug_int->value +
                         expression->right_side->value_expression->primitive->mug_int->value;

            return result;
        }
        case 0x01:
        {
            int result = expression->left_side->value_expression->primitive->mug_int->value +
                         expression->right_side->value_expression->primitive->mug_int->value;

            return result;
        }
        case 0x02:
        {
            int result = expression->left_side->value_expression->primitive->mug_int->value +
                         expression->right_side->value_expression->primitive->mug_int->value;

            return result;
        }
        case 0x03:
        {
            int result = expression->left_side->value_expression->primitive->mug_int->value +
                         expression->right_side->value_expression->primitive->mug_int->value;

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
            int result = expression->left_side->value_expression->primitive->mug_int->value +
                         execute_operator_expression(expression->right_side->operator_expression);

            return result;
        }
        case 0x01:
        {
            int result = expression->left_side->value_expression->primitive->mug_int->value +
                         execute_operator_expression(expression->right_side->operator_expression);

            return result;
        }
        case 0x02:
        {
            int result = expression->left_side->value_expression->primitive->mug_int->value +
                         execute_operator_expression(expression->right_side->operator_expression);

            return result;
        }
        case 0x03:
        {
            int result = expression->left_side->value_expression->primitive->mug_int->value +
                         execute_operator_expression(expression->right_side->operator_expression);

            return result;
        }
        default:
            break;
        }
    }
}
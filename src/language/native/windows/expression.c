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
#include "storage.h"

void parse_token_block(expression *expression, set *token_set)
{
    if (token_set->length == 0x01)
    {
        parse_value_expression(expression, token_set);
    }
    else
    {
        expression->operator_expression = malloc(sizeof(operator_expression));
        parse_operator_expression(expression, token_set);
    }
}

void parse_operator_expression(expression *operator_expression, set *token_set)
{
    if (token_set->length < 0)
    {
        return;
    }

    iterator *expression_iterator = create_iterator(token_set);

    iterator_next(expression_iterator);
    token *current_token = expression_iterator->current;
    operator_expression->type = 0x01;

    if (current_token->type == 0x05)
    {
        expression *primitive_expression = malloc(sizeof(expression));

        set *value_token = create_set(0x00, 0x00);
        value_token->array = malloc(sizeof(token));
        value_token->array[0x00] = current_token;
        value_token->length = 0x01;

        parse_value_expression(primitive_expression, value_token);

        iterator_next(expression_iterator);

        operator_expression->operator_expression->left_side = primitive_expression;

        token *operator= expression_iterator->current;
        token *future = expression_iterator->set->array[expression_iterator->index + 0x02];

        operator_expression->operator_expression->operator= operator->identifier;

        if (expression_iterator->index + 0x02 < expression_iterator->set->length && future->type == 0x03)
        {
            operator_expression->operator_expression->right_side = malloc(sizeof(expression));
            parse_operator_expression(operator_expression->operator_expression->right_side, expression_iterator->set);
        }
        else
        {
            iterator_next(expression_iterator);
            current_token = expression_iterator->current;
            expression *primitive_expression = malloc(sizeof(expression));

            set *value_token = create_set(0x00, 0x00);
            value_token->array = malloc(sizeof(token));
            value_token->array[0x00] = current_token;
            value_token->length = 0x01;

            parse_value_expression(primitive_expression, value_token);
            operator_expression->operator_expression->right_side = primitive_expression;
        }
    }
}

void parse_value_expression(expression *value_expression, set *token_set)
{
    if (token_set->length < 1)
    {
        return;
    }

    iterator *value_iterator = create_iterator(token_set);

    iterator_next(value_iterator);
    token *value = value_iterator->current;

    mug_primitive *primitive = malloc(sizeof(mug_primitive));
    if (primitive == 0x00)
    {
        return;
    }

    value_expression->value_expression = malloc(sizeof(struct value_expression_s));
    value_expression->type = 0x00;

    if (value_expression->value_expression == 0x00)
    {
        return;
    }

    value_expression->value_expression->type = create_primitive(primitive, value->data);
    value_expression->value_expression->primitive = primitive;
}

void execute_expression(expression *expression)
{
    if (expression->type = 0x00)
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
    if (expression->right_side->type == 0x00)
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
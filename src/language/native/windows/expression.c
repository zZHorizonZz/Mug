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

token_iterator *split_token_iterator(token_iterator *iterator, char type)
{
    if (iterator->length < 0)
    {
        return 0x00;
    }

    token **array;

    for (size_t i = 0; i < iterator->length; i++)
    {
        token *token = iterator->array[i];
        if (array == 0x00)
        {
            array = malloc(sizeof(struct token_s *));
        }
        else
        {
            array = realloc(array, sizeof(struct token_s *) * i + 1);
        }

        struct token_s *copy = malloc(sizeof(struct token_s));
        array[i] = memcpy(copy, token, sizeof(struct token_s));

        if (token->identifier == type)
        {
            token_iterator *iterator = create_iterator(i, array);
            return iterator;
        }
    }
}

void parse_token_block(expression *expression, token_iterator *iterator)
{
    if (iterator->length == 0x01)
    {
        parse_value_expression(expression, iterator);
    }
    else
    {
        expression->operator_expression = malloc(sizeof(operator_expression));
        parse_operator_expression(expression, iterator);
    }
}

void parse_operator_expression(expression *operator_expression, token_iterator *iterator)
{
    if (iterator->length < 0)
    {
        return;
    }

    iterator_next(iterator);
    token *current_token = iterator->current_token;
    operator_expression->type = 0x01;

    if (current_token->type == 0x05)
    {
        expression *primitive_expression = malloc(sizeof(expression));

        token_iterator *value_token = calloc(4, sizeof(token_iterator));
        value_token->array = malloc(sizeof(token));
        value_token->array[0x00] = current_token;
        value_token->length = 0x01;

        parse_value_expression(primitive_expression, value_token);

        iterator_next(iterator);

        operator_expression->operator_expression->left_side = primitive_expression;
        operator_expression->operator_expression->operator= iterator->current_token->identifier;

        if (iterator->index + 0x02 < iterator->length && iterator->array[iterator->index + 0x02]->type == 0x03)
        {
            operator_expression->operator_expression->right_side = malloc(sizeof(expression));
            parse_operator_expression(operator_expression->operator_expression->right_side, iterator);
        }
        else
        {
            iterator_next(iterator);
            current_token = iterator->current_token;
            expression *primitive_expression = malloc(sizeof(expression));

            token_iterator *value_token = calloc(4, sizeof(token_iterator));
            value_token->array = malloc(sizeof(token));
            value_token->array[0x00] = current_token;
            value_token->length = 0x01;

            parse_value_expression(primitive_expression, value_token);
            operator_expression->operator_expression->right_side = primitive_expression;
        }
    }
}

void parse_value_expression(expression *value_expression, token_iterator *iterator)
{
    if (iterator->length < 1)
    {
        return;
    }

    iterator_next(iterator);
    token *value = iterator->current_token;

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
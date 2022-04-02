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

#include "parser.h"

void parse_structure(mug_environment *environment, mug_structure *structure, set *token_set)
{
}

void parse_method(mug_environment *environment, mug_method *method, set *token_set)
{
    if (token_set->length < 0)
    {
        return;
    }

    iterator *method_iterator = create_iterator(token_set);
    iterator_next(method_iterator);

    token *current_token = method_iterator->current;

    if (current_token->type == 0x00)
    {
        method->name = current_token->data;

        iterator_next(method_iterator);
        current_token = method_iterator->current;

        if (current_token->type == 0x01 && current_token->identifier == 0x02)
        {
            iterator_next(method_iterator);
            current_token = method_iterator->current;

            if (current_token->type == 0x01 && current_token->identifier == 0x03)
            {
                iterator_next(method_iterator);
                current_token = method_iterator->current;

                if (current_token->type == 0x01 && current_token->identifier == 0x04)
                {
                    set *body_set = create_set(0x00, 0x00);

                    while (method_iterator->index < token_set->length - 1)
                    {
                        iterator_next(method_iterator);
                        current_token = method_iterator->current;

                        set_add(body_set, current_token);
                    }

                    if (method->body == 0x00)
                    {
                        exit(0x01);
                        return;
                    }

                    parse_body(environment, method->body, body_set);
                }
            }
        }
    }
    else
    {
        exit(0x01);
        return;
    }
}

void parse_body(mug_environment *environment, body *body, set *token_set)
{
    if (token_set->length < 1)
    {
        return;
    }

    iterator *token_iterator = create_iterator(token_set);

    set *expression_set = create_set(0x00, 0x00);
    expression *expression;

    while (iterator_has_next(token_iterator) == 0x01)
    {
        iterator_next(token_iterator);
        token *current_token = token_iterator->current;

        if (current_token->type == 0x01)
        {
            if (current_token->identifier = 0x06)
            {
                if (expression_set->length < 1 || expression_set == 0x00)
                {
                    exit(0x01);
                    return;
                }

                block *block = new_block();

                parse_block(environment, block, expression_set);
                set_add(body->body_block, block);

                set_free(expression_set);

                expression_set = create_set(0x00, 0x00);

                continue;
            }
        }

        set_add(expression_set, current_token);
    }
}

char parse_block(mug_environment *environment, block *block, set *token_set)
{
    char type = evaluate_type(token_set);

    switch (type)
    {
    case 0x01:
    case 0x02:
    case 0x03:
    {
        expression_block *_expression_block = malloc(sizeof(expression_block));

        block->type = 0x01;
        block->expression_block = _expression_block;

        parse_expression_block(environment, _expression_block, token_set);
        return 0x01;
    }
    case 0x04:
    {
        field_block *_field_block = malloc(sizeof(field_block));
        _field_block->metadata = 0x00;

        block->type = 0x02;
        block->field_block = _field_block;

        parse_field_block(environment, _field_block, token_set);
    }
    case 0x05:
    {
    }

    default:
        break;
    }

    return 0x00;
}

char evaluate_type(set *token_set)
{
    char type = 0x00;

    if (is_value_expression(token_set) == 0x01)
    {
        type = 0x01;
    }

    if (is_operator_expression(token_set) == 0x01)
    {
        type = 0x02;
    }

    if (is_reference_expression(token_set) == 0x01)
    {
        type = 0x03;
    }

    if (is_declared_field_block(token_set) == 0x01)
    {
        type = 0x04;
    }

    if (is_field_block(token_set) == 0x01)
    {
        type = 0x05;
    }

    if (is_return_block(token_set) == 0x01)
    {
        type = 0x06;
    }

    return type;
}

char is_mathing(const char *rule, set *token_set)
{
    pattern *rule_patter = compile_pattern(rule);

    for (size_t i = 0; i < rule_patter->length; i++)
    {
        if (i >= token_set->length)
        {
            return 0x00;
        }

        short type = rule_patter->pattern[i];
        token *_token = token_set->array[i];
        char optional = 0x00;

        if (type - 0x80 >= 0x00)
        {
            optional = 0x01;
            type -= 0x80;
        }

        if (type < 0x10 && type == _token->type)
        {
            continue;
        }

        if (type >= 0x10 && type < 0x20)
        {
            if (type == 0x10)
            {
                if (_token->type == 0x00 || _token->type == 0x05)
                {
                    if (i + 1 < token_set->length)
                    {
                        token *_operator_token = token_set->array[i + 1];
                        if (_operator_token->type == 0x03)
                        {
                            set *expression_set = create_set(0x00, 0x00);
                            for (size_t x = i + 2; x < token_set->length; x++)
                            {
                                set_add(expression_set, token_set->array[x]);
                            }
                            if (is_expression(expression_set) == 0x01)
                            {
                                break;
                            }
                        }
                    }
                }
            }
        }

        if (type >= 0x20 && type < 0x80)
        {
            char identifier = type % 0x10;
            if (identifier == _token->identifier)
            {
                continue;
            }
        }

        if (optional == 0x01)
        {
            continue;
        }

        return 0x00;
    }

    return 0x01;
}

unsigned char parse_token_type(const char *input)
{
    if (input == 0x00)
    {
        return -0x01;
    }

    if (strcmp(input, "PRIMITIVE") == 0x00)
    {
        return 0x05;
    }

    if (strcmp(input, "OPERATOR") == 0x00)
    {
        return 0x03;
    }

    if (strcmp(input, "IDENTIFIER") == 0x00)
    {
        return 0x00;
    }

    return -0x01;
}

unsigned char parse_expression_type(const char *input)
{
    if (input == 0x00)
    {
        return -0x01;
    }

    if (strcmp(input, "EXPRESSION") == 0X00)
    {
        return 0x00;
    }

    return -0x01;
}

token *parse_specific_token_type(const char *input)
{
    if (input == 0x00)
    {
        return 0x00;
    }

    token *specific_token = malloc(sizeof(token));
    parse_token(specific_token, input);

    return specific_token;
}

void expand_pattern(pattern *pattern, const char rule)
{
    pattern->length++;

    if (pattern->pattern == 0x00)
    {
        pattern->pattern = malloc(sizeof(char));
    }
    else
    {
        pattern->pattern = realloc(pattern->pattern, sizeof(char) * pattern->length);
    }

    pattern->pattern[pattern->length - 1] = rule;
}

pattern *compile_pattern(const char *rule)
{
    pattern *rule_pattern = malloc(sizeof(pattern));
    if (rule_pattern == 0x00)
    {
        exit(0x01);
        return 0x00;
    }
    else
    {
        rule_pattern->length = 0x00;
        rule_pattern->pattern = 0x00;
    }

    size_t text_length = 0x00;
    char *text_holder = 0x00;
    char type = 0x00;
    char optional = 0x00;

    for (size_t i = 0; i < strlen(rule); i++)
    {
        char current_char = rule[i];

        switch (current_char)
        {
        case 0x20:
        {
            continue;
        }

        case 0x3F:
        {
            if (optional == 0x00)
            {
                optional = 0x01;
            }
            else
            {
                optional = 0x00;
            }
        }

        case 0x3C:
        {
            type = 0x01;
            continue;
        }

        case 0x3E:
        {
            if (type == 0x01)
            {
                unsigned char token_type = parse_token_type(text_holder);
                if (optional == 0x01)
                {
                    token_type += 0x80;
                }

                expand_pattern(rule_pattern, token_type);
                free(text_holder);

                text_holder = 0x00;
                text_length = 0x00;
                type = 0x00;
            }
            else
            {
                exit(0x01);
                return 0x00;
            }

            continue;
        }

        case 0x28:
        {
            type = 0x02;
            continue;
        }

        case 0x29:
        {
            if (type == 0x02)
            {
                unsigned char expression_type = 0x10 + parse_expression_type(text_holder);
                if (expression_type == 0x01)
                {
                    expression_type += 0x80;
                }

                expand_pattern(rule_pattern, expression_type);
                free(text_holder);

                text_holder = 0x00;
                text_length = 0x00;
                type = 0x00;
            }
            else
            {
                exit(0x01);
                return 0x00;
            }

            continue;
        }

        case 0x27:
        {
            if (type == 0x00)
            {
                type = 0x03;
            }
            else
            {
                token *token = parse_specific_token_type(text_holder);
                unsigned char value = 0x10 + (token->type * 0x10 + token->identifier);
                if (value == 0x01)
                {
                    value += 0x80;
                }

                expand_pattern(rule_pattern, value);
                free(text_holder);

                text_holder = 0x00;
                text_length = 0x00;
                type = 0x00;
            }

            continue;
        }

        default:
            break;
        }

        text_length++;

        if (text_holder == 0x00)
        {
            text_holder = malloc(sizeof(char) + 0x01);
        }
        else
        {
            text_holder = realloc(text_holder, sizeof(char) * text_length + 0x01);
        }

        text_holder[text_length - 1] = current_char;
        text_holder[text_length] = 0x00;
    }

    return rule_pattern;
}

unsigned char get_expression_type(set *token_set)
{
    if (is_operator_expression(token_set) == 0x01)
    {
        return 0x01;
    }

    if (is_reference_expression(token_set) == 0x01)
    {
        return 0x02;
    }

    if (is_value_expression(token_set) == 0x01)
    {
        return 0x03;
    }

    return 0x00;
}

char is_expression(set *token_set)
{
    if (is_operator_expression(token_set) == 0x01)
    {
        return 0x01;
    }

    if (is_reference_expression(token_set) == 0x01)
    {
        return 0x01;
    }

    if (is_value_expression(token_set) == 0x01)
    {
        return 0x01;
    }

    return 0x00;
}

char is_value_expression(set *token_set)
{
    return is_mathing(VALUE_EXPRESSION, token_set);
}

char is_operator_expression(set *token_set)
{
    return is_mathing(OPERATOR_EXPRESSION, token_set);
}

char is_reference_expression(set *token_set)
{
    return is_mathing(REFERENCE_EXPRESSION, token_set);
}

char is_declared_field_block(set *token_set)
{
    return is_mathing(DECLARED_FIELD_BLOCK, token_set);
}

char is_field_block(set *token_set)
{
    return is_mathing(FIELD_BLOCK, token_set);
}

char is_return_block(set *token_set)
{
    return is_mathing(RETURN_BLOCK, token_set);
}

void parse_field_block(mug_environment *environment, field_block *field_block, set *token_set)
{
    iterator *iterator = create_iterator(token_set);

    char declared = 0x00;
    set *expression = create_set(0x00, 0x00);

    char *text_holder = 0x00;

    while (iterator_has_next(iterator))
    {
        token *_token = (token *)iterator_next(iterator);

        if (declared == 0x00)
        {
            if (_token->type == 0x00)
            {
                if (field_block->name == 0x00 && text_holder != 0x00)
                {
                    field_block->name = text_holder;
                    text_holder = 0x00;
                }
                else
                {
                    // todo find foundation.
                }

                text_holder = _token->data;
            }

            if (_token->type == 0x02 && _token->identifier >= 0x0A && _token->identifier <= 0x14)
            {
                mug_foundation *primitive = get_native_foundation(environment, LOCATION, get_name(_token->identifier - 0x0A));
                field_block->type = primitive;
            }
        }
        else
        {
            set_add(expression, _token);
        }

        if (_token->type == 0x03 && _token->identifier == 0x09)
        {
            declared == 0x01;
            if (text_holder != 0x00)
            {
                field_block->name = text_holder;
                field_block->metadata |= (0x01 << 0x00);

                text_holder = 0x00;
            }
        }
    }

    field_block->initializer = malloc(sizeof(expression_block));
    parse_expression(environment, field_block->initializer, expression);
}

void parse_expression_block(mug_environment *environment, expression_block *block, set *token_set)
{
    expression *_expression = malloc(sizeof(expression));
    if (_expression == 0x00)
    {
        exit(0x01);
    }

    parse_expression(environment, _expression, token_set);

    block->expression = _expression;
}

void parse_expression(mug_environment *environment, expression *_expression, set *token_set)
{
    unsigned char type = get_expression_type(token_set);

    switch (type)
    {
    case 0x01:
    {
        parse_value_expression(environment, _expression, token_set);
        break;
    }

    case 0x02:
    {
        parse_operator_expression(environment, _expression, token_set);
        break;
    }

    case 0x03:
    {
        // parse_reference_expression(_expression, token_set);
        break;
    }

    default:
        // TODO Log error
        break;
    }

    _expression->type = type;
}

void parse_operator_expression(mug_environment *environment, expression *_expression, set *token_set)
{
    if (token_set->length < 0)
    {
        return;
    }

    iterator *expression_iterator = create_iterator(token_set);

    iterator_next(expression_iterator);
    token *current_token = expression_iterator->current;

    _expression->operator_expression = malloc(sizeof(operator_expression));

    if (current_token->type == 0x05)
    {
        expression *primitive_expression = malloc(sizeof(expression));

        set *value_token = create_set(0x00, 0x00);
        value_token->array = malloc(sizeof(token));
        value_token->array[0x00] = current_token;
        value_token->length = 0x01;

        parse_value_expression(environment, primitive_expression, value_token);

        iterator_next(expression_iterator);

        _expression->operator_expression->left_side = primitive_expression;

        token *operator= expression_iterator->current;
        token *future = expression_iterator->set->array[expression_iterator->index + 0x02];

        _expression->operator_expression->operator= operator->identifier;

        if (expression_iterator->index + 0x02 < expression_iterator->set->length && future->type == 0x03)
        {
            _expression->operator_expression->right_side = malloc(sizeof(expression));
            parse_operator_expression(environment, _expression->operator_expression->right_side, expression_iterator->set);
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

            parse_value_expression(environment, primitive_expression, value_token);
            _expression->operator_expression->right_side = primitive_expression;
        }
    }
}

void parse_value_expression(mug_environment *environment, expression *value_expression, set *token_set)
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

    if (value_expression->value_expression == 0x00)
    {
        return;
    }

    char type = create_primitive(primitive, value->data);
    value_expression->value_expression->value = new_primitive_structure(environment, primitive, type);
}

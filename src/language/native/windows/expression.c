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

void evaluate_token_block(expression *expression, token_iterator *iterator)
{
}

void evaluate_arithmetic_expression(expression *expression, token_iterator *iterator)
{
    if(iterator->length < 0) {
        return;
    }

    iterator_next(iterator);
    token *token_left = iterator->current_token; 
    
    if(token_left.)
    number *number_left = malloc(sizeof(struct number_s));
    if(number_left == 0x00) {
        return;
    }

    number_left->primitive = malloc(sizeof(mug_primitive));
    mug_primitive *left_side = number_left->primitive;
    if(left_side == 0x00) {
        return;
    }


}
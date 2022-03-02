#include <stdio.h>
#include <stdlib.h>

#include "token.h"

void evaluate_token_letter(token *token, char letter) {
    char *buffer = malloc(sizeof(char));
    buffer[0] = letter;
    return evaluate_token(token, buffer);
}

void evaluate_token(token *token, char *content) {
    for (size_t i = 0; i < 16; i++) {
        if(SEPARATOR[i] != 0x00 && strlen(content) == 1 && content[0] == *SEPARATOR[i]) {
            token->type = 0x01;
            token->identifier = i;
            token->data = 0x00;

            return;
        }

        if(KEYWORD[i] != 0x00 && strcmp(content, KEYWORD[i]) == 0) {
            token->type = 0x02;
            token->identifier = i;
            token->data = 0x00;

            return;
        }

        if(OPERATOR[i] != 0x00 && strcmp(content, OPERATOR[i]) == 0) {
            token->type = 0x03;
            token->identifier = i;
            token->data = 0x00;
            
            return;
        }

        if(BLANK[i] != 0x00 && strcmp(content, BLANK[i]) == 0) {
            token->type = 0x04;
            token->identifier = i;
            token->data = 0x00;
            
            return;
        }
    }

    token->type = 0x00;
    token->identifier = 0x00;
    
    if(token->data != 0x00) {
        token->data = malloc(strlen(content));    
        strcpy(token->data, content);
        free(content);
    }
}

int is_separator(char letter) {
    for (size_t i = 0; i < 16; i++) {
        if(SEPARATOR[i] != 0x00 && letter == *SEPARATOR[i]) {
            return 1;
        }
    }

    return 0;
}

int is_ignore(char letter) {
    for (size_t i = 0; i < 16; i++) {
        if(IGNORE[i] != 0x00 && letter == *IGNORE[i]) {
            return 1;
        }
    }

    return 0;
}

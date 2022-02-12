#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>
#include <string.h>

struct token {
    char type;
    char identifier;

    char *data;
};

static const char *SEPARATOR[16] = { ".", ",", "(", ")", "{", "}", ";", "\"" };
static const char *KEYWORD[16] = { "repository", "structure", "void", "native", "if", "else", "elseif", "while" };
static const char *OPERATOR[16] = { "+", "-", "*", "/", "<<", ">>", "|", "&", "^" };
static const char *BLANK[16] = { "//" };
static const char *IGNORE[16] = { " ", "\n", "\r", "\t"};

struct token evaluate_token_letter(char letter);
struct token evaluate_token(char *content);
int is_separator(char letter);

struct token evaluate_token_letter(char letter) {
    char *buffer = malloc(sizeof(char));
    buffer[0] = letter;
    return evaluate_token(buffer);
}

struct token evaluate_token(char *content) {
    for (int i = 0; i < 16; i++) {
        if(SEPARATOR[i] != 0x00 && strlen(content) == 1 && content[0] == *SEPARATOR[i]) {
            struct token token = { 0x01, i, 0x00 };
            free(content);
            return token;
        }

        if(KEYWORD[i] != 0x00 && strcmp(content, KEYWORD[i]) == 0) {
            struct token token = { 0x02, i, 0x00 };
            free(content);
            return token;
        }

        if(OPERATOR[i] != 0x00 && strcmp(content, OPERATOR[i]) == 0) {
            struct token token = { 0x03, i, 0x00 };
            free(content);
            return token;
        }

        if(BLANK[i] != 0x00 && strcmp(content, BLANK[i]) == 0) {
            struct token token = { 0x04, i, 0x00 };
            free(content);
            return token;
        }
    }

    struct token token = { 0x00, 0x00, 0x00 };
    token.data = content;
    return token;
}

int is_separator(char letter) {
    for (int i = 0; i < 16; i++) {
        if(SEPARATOR[i] != 0x00 && letter == *SEPARATOR[i]) {
            return 1;
        }
    }

    return 0;
}

int is_ignore(char letter) {
    for (int i = 0; i < 16; i++) {
        if(IGNORE[i] != 0x00 && letter == *IGNORE[i]) {
            return 1;
        }
    }

    return 0;
}

#endif
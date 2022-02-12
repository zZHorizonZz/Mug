#include <stdio.h>
#include <string.h>

#include "obj/list.h"
#include "token.h"

#define MAX_LENGTH 1

struct lexer {
    char *content;

    int content_length;
    int last_index;
    int last_token_index;

    struct token current_token;
    struct token *tokens;
};

char *create_binary(struct lexer *lexer);
void evaluate_content(struct lexer *lexer, char *content);
void evaluate_next_token(struct lexer *lexer);
void next_token(struct lexer *lexer, struct token token, int offset);
void next_string_token(struct lexer *lexer);

char *create_binary(struct lexer *lexer) {
    char *binary = malloc(lexer->last_token_index * (sizeof(char) * 0x02));

    size_t offset = 0x00;
    for (size_t i = 0; i <= lexer->last_token_index; i++) {
        struct token token = lexer->tokens[i];
        binary[offset++] = token.type;
        binary[offset++] = token.identifier;
    }
    
    return binary;
}

void evaluate_content(struct lexer *lexer, char *content) {
    lexer->content = content;
    lexer->content_length = strlen(content);
    lexer->last_index = 0x00;

    if(lexer->tokens == 0x00) {
        lexer->tokens = malloc(sizeof(struct token));
    }

    int max_depth = 128;
    int current_depth = 0;

    while(lexer->last_index != lexer->content_length && current_depth <= max_depth) {
        evaluate_next_token(lexer);
        current_depth++;
    }
}

void evaluate_next_token(struct lexer *lexer) {
    struct token token;

    int size = 0;
    int offset = 0;

    char *text = malloc(0x01);
    text[0] = 0x00;

    int current_index = lexer->last_index;
    for (int i = lexer->last_index; i < lexer->content_length; i++) {
        char current_letter = lexer->content[i]; 
        offset++;

        if(is_ignore(current_letter)) {
            if(i == lexer->content_length - 1) {
                lexer->last_index = lexer->content_length;
                return;
            }

            if(size > 0) {
                break;
            } else {
                continue;
            }
        }

        if(size > 0 && is_separator(current_letter) == 0x01) {
            offset--;
            break;
        }

        char *tmp = realloc(text, (++size) + 0x01);
        
        if (tmp != 0x00) {
            text = tmp;
            text[size - 1] = current_letter;
            text[size] = 0x00;
        } else {
            printf("[ERROR] Null pointer exception. (Size %d)\n", size);
        }

        char *token_data = malloc(strlen(text));

        if (tmp == 0x00) {
            printf("[ERROR] Null pointer exception. (Size %d)\n", size);
        }

        token = evaluate_token(strcpy(token_data, text));

        if(token.type == 0x01 && token.identifier == 0x07) {
            int string_start = i;
            lexer->last_index = i + 1;
            next_string_token(lexer);
            i += lexer->last_index - string_start;
            return;
        }

        if(token.type != 0x00) {
            break;
        }
    }

    if(size == 0x00) {
        return;
    }

    next_token(lexer, token, offset);

    free(text);      
}

void next_token(struct lexer *lexer, struct token token, int offset) {
    struct token *tmp = realloc(lexer->tokens, (lexer->last_token_index + 1) * sizeof(struct token));

    if (tmp != 0x00) {
        tmp[lexer->last_token_index++] = token;
        lexer->tokens = tmp;
    }

    lexer->current_token = token;
    lexer->last_index += offset;
}

void next_string_token(struct lexer *lexer) {
    struct token token;
    char *current_text = malloc(sizeof(char));

    int offset = 0;
    int current_index = lexer->last_index;
    for (int i = 0; i < lexer->content_length; i++) {
        offset = i;

        if(lexer->content[lexer->last_index + i] == '"') {
            break;
        }

        char *tmp = realloc(current_text, (i + 1) * sizeof(char));

        if (tmp != 0x00) {
            current_text = tmp;
            tmp[i] = lexer->content[lexer->last_index + i];
            current_text = strcpy(current_text, tmp);
        }
    }

    char *data = malloc(strlen(current_text));
    token.data = strcpy(data, current_text);
    next_token(lexer, token, offset);

    free(current_text);      
}


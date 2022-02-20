#include <stdio.h>
#include <string.h>

#include "obj/list.h"
#include "token.h"
#include "bsd/binary_data.h"

#define MAX_LENGTH 1

typedef struct lexer_s {
    char *content;

    int content_length;
    int last_index;
    int last_token_index;

    token *current_token;
    token **tokens;
} lexer;

char *create_token_binary(lexer *lexer);

void add_binary_header(tag *binary);
void add_binary_content(tag *binary, lexer *lexer);

void evaluate_content(lexer *lexer, char *content);
void evaluate_next_token(lexer *lexer);
void next_token(lexer *lexer, token *token, int offset);
void next_string_token(lexer *lexer);

char *create_token_binary(lexer *lexer) {
    size_t tag_size = sizeof(tag);
    tag *binary = malloc(tag_size);

    create_mapped_list_tag(binary);

    printf("Debug 1\n");
    add_binary_header(binary);
    add_binary_content(binary, lexer);

    printf("Debug 2\n");

    char *binary_data = create_binary(binary);
    printf("Debug 3\n");

    return binary_data;
}

void add_binary_header(tag *binary) {
    printf("Binary header....");
    tag *header = malloc(sizeof(tag));
    tag *name = malloc(sizeof(tag));
    tag *author = malloc(sizeof(tag));

    create_mapped_list_tag(header);
    create_string_tag(name, "test");
    create_string_tag(author, "Horizon");
    printf("Binary header.... 1");
    add_value_to_mapped_list_tag(header, "name", *name);
    add_value_to_mapped_list_tag(header, "author", *author);
    add_value_to_mapped_list_tag(binary, "header", *header);
    printf("Binary header....2");
}

void add_binary_content(tag *binary, lexer *lexer) {
    printf("Binary content....");
    tag *content = malloc(sizeof(tag));

    create_single_type_list_tag(content, 0x04);

    size_t offset = 0x00;
    printf("Binary content....2");
    for (size_t i = 0; i <= lexer->last_token_index; i++) {
        token *token = lexer->tokens[i];

        tag *type = malloc(sizeof(tag));
        tag *identifier = malloc(sizeof(tag));

        create_byte_tag(type, token->type);
        create_byte_tag(identifier, token->identifier);

        add_value_to_single_type_list_tag(content, *type);
        add_value_to_single_type_list_tag(content, *identifier);

        if(token->data != 0x00) {
            tag *data = malloc(sizeof(tag));
            
            create_string_tag(data, token->data);
            add_value_to_single_type_list_tag(content, *data);
        }
    }

    add_value_to_mapped_list_tag(binary, "content", *content);
    printf("Binary content....3");
}

void evaluate_content(lexer *lexer, char *content) {
    printf("Current content: %s\n", content);
    lexer->content = content;
    lexer->content_length = strlen(content);
    lexer->last_index = 0x00;

    if(lexer->tokens == 0x00) {
        lexer->tokens = malloc(sizeof(token));
    }

    int max_depth = 128;
    int current_depth = 0;

    while(lexer->last_index != lexer->content_length && current_depth <= max_depth) {
        evaluate_next_token(lexer);
        //printf("\n[Debug] Token %d (%d) Data: %s", lexer->current_token.type, lexer->current_token.identifier, lexer->current_token.data);
        current_depth++;
    }
}

void evaluate_next_token(lexer *lexer) {
    token *token = malloc(sizeof(struct token_s));
    
    token->data = 0x00;
    token->type = 0x00;
    token->identifier = 0x00;

    int size = 0;
    int offset = 0;
    char *text = 0x00;
    int current_index = lexer->last_index;
    
    for (size_t i = lexer->last_index; i < lexer->content_length; i++) {
        char current_letter = lexer->content[i]; 
        offset++;

        printf("\n[Debug] Current char %c", current_letter);
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

        char *tmp;

        if(text == 0x00) {
            tmp = malloc((++size) + 0x01);
        } else {
            tmp = realloc(text, (++size) + 0x01);
        }

        printf("2");

        if (tmp != 0x00) {
            text = tmp;
            text[size - 1] = current_letter;
            text[size] = 0x00;
            printf("4");
        } else {
            printf("\n[ERROR] Null pointer exception. (Size %d)\n", size);
            exit(0x01);
            return;
        }

        printf("Data: ");
        for (size_t i = 0; i <= size; i++) {
            printf("%d ", text[i]);
        }

        char *token_data = malloc(strlen(text));
        
        printf("7");

        strcpy(token_data, text);
        printf("3");
        evaluate_token(token, token_data);

        printf("2");

        if(token->type == 0x01 && token->identifier == 0x07) {
            int string_start = i;
            lexer->last_index = i + 1;
            next_string_token(lexer);
            i += lexer->last_index - string_start;
            return;
        }

        if(token->type != 0x00) {
            printf("Break. 3");
            break;
        }
        printf("3");
    }

    if(size == 0x00) {
        return;
    }

    next_token(lexer, token, offset);

    if(text != 0x00) {
        free(text);
    }
}

void next_token(lexer *lexer, token *token, int offset) {
    struct token_s **tmp = realloc(lexer->tokens, (lexer->last_token_index + 1) * sizeof(struct token_s));

    if (tmp != 0x00) {
        tmp[lexer->last_token_index++] = token;
        lexer->tokens = tmp;
    }

    lexer->current_token = token;
    lexer->last_index += offset;
}

void next_string_token(lexer *lexer) {
    token *token = malloc(sizeof(token));
    char *current_text = malloc(sizeof(char));

    int offset = 0;
    int current_index = lexer->last_index;
    for (size_t i = 0; i < lexer->content_length; i++) {
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
    token->data = strcpy(data, current_text);
    next_token(lexer, token, offset);

    free(current_text);      
}


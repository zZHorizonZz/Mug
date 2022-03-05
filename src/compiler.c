#include <stdlib.h>
#include <stdio.h>

#include "lexer.c"

struct binary
{
    char *name;
    char *author;
};

int compile_file(char *path, char *name);
int create_binary_file(int *path, char *name, char *binary, int binary_size);

int compile_file(char *path, char *name)
{
    printf("[Compiler] Compiling file %s/%s.\n", path, name);
    FILE *fp = fopen("D:\\program.str", "r");

    if (fp == 0x00)
    {
        printf("Error: could not open file %s", "D:\\program.str");
        return 1;
    }

    char buffer[256];
    lexer *lexer = malloc(sizeof(struct lexer_s));
    lexer->tokens = 0x00;
    lexer->current_token = 0x00;
    lexer->last_token_index = 0x00;

    printf("[Compiler] Evaluating content...");
    while (fgets(buffer, 256, fp))
    {
        evaluate_content(lexer, buffer);
        free(buffer);
    }

    printf(" [Done]\n");

    for (size_t i = 0; i < lexer->last_token_index; i++)
    {
        token *token = lexer->tokens[i];
        if (token->type != 0x00)
        {
            switch (token->type)
            {
            case 0x01:
                printf("[TOKEN] Separator token of type '%s'.\n", SEPARATOR[token->identifier]);
                break;
            case 0x02:
                printf("[TOKEN] Keyword token of type '%s'.\n", KEYWORD[token->identifier]);
                break;
            case 0x03:
                printf("[TOKEN] Operator token of type '%s'.\n", OPERATOR[token->identifier]);
                break;
            default:
                break;
            }
        }
        else
        {
            printf("[TOKEN] Identifier token '%s'.\n", token->data);
        }
    }

    fclose(fp);

    printf("[Compiler] Creating token binary... ");
    char *binary = create_token_binary(lexer);
    printf(" [Done]");

    create_binary_file(0x00, 0x00, binary, lexer->last_token_index * 0x02);

    free(lexer->content);
    free(lexer->tokens);
    free(lexer->current_token);
    free(lexer);
}

int create_binary_file(int *path, char *name, char *binary, int binary_size)
{
    FILE *file;

    if ((file = fopen("D:\\program.mug", "wb")) == 0x00)
    {
        printf("Error! opening file");
        exit(1);
    }

    fwrite(binary, binary_size, 0x01, file);
    fclose(file);
    free(binary);
}
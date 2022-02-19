#include <stdlib.h>
#include <stdio.h>

#include "lexer.c"
#include "bsd/binary_data.c"

struct binary {
    char *name;
    char *author;

    
};

int compile_file(char *path, char *name);
int create_binary_file(int *path, char *name, char *binary, int binary_size);

int compile_file(char *path, char *name) {
    FILE *fp = fopen("D:\\program.str", "r");

    if (fp == NULL)
    {
        printf("Error: could not open file %s", "D:\\program.str");
        return 1;
    }

    char buffer[256];
    struct lexer lexer = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

    while (fgets(buffer, 256, fp)) {
        evaluate_content(&lexer, buffer);    
    }

    for (size_t i = 0; i < lexer.last_token_index; i++) {
        struct token token = lexer.tokens[i];
        if(token.type != 0x00) {
            switch (token.type) {
                case 0x01:
                    printf("[TOKEN] Separator token of type '%s'.\n", SEPARATOR[token.identifier]);
                    break;
                case 0x02:
                    printf("[TOKEN] Keyword token of type '%s'.\n", KEYWORD[token.identifier]);
                    break;
                case 0x03:
                    printf("[TOKEN] Operator token of type '%s'.\n", OPERATOR[token.identifier]);
                    break;    
                default:
                    break;
            }
        } else {
            printf("[TOKEN] Identifier token '%s'.\n", token.data);
        }
    }

    fclose(fp);
    char *binary = create_token_binary(&lexer);
    
    create_binary_file(0x00, 0x00, binary, lexer.last_token_index * 0x02);
}

int create_binary_file(int *path, char *name, char *binary, int binary_size) {
    FILE *file;

   if ((file = fopen("D:\\program.mug","wb")) == 0x00){
       printf("Error! opening file");

       // Program exits if the file pointer returns NULL.
       exit(1);
   }

   fwrite(binary, binary_size, 0x01, file);
   fclose(file); 
   free(binary);
}
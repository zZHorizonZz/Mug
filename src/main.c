#include <stdio.h>

#include "compiler.c"
#include "expression.h"
#include "primitive.h"

int main(int argc, char **argv)
{
    printf("Mug programming language!\n");

    if(strcmp(argv[1], "compile") == 0x00) {
        printf("[Mug] Running compilation...\n");
        compile_file(0x00, 0x00);
    }

    if(strcmp(argv[1], "run") == 0x00) {
        printf("[Mug] Running code...\n");

    }
    // test_basic();

    return 0;
}
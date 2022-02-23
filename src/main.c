#include <stdio.h> 

#include "compiler.c"

int main(int argc, char **argv) {
    printf("Mug programming language!\n");
    //test_basic();

    compile_file(0x00, 0x00);    

    return 0;
}
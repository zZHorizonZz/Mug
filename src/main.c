#include <stdio.h> 

#include "compiler.c"

#include "obj/list.h"
#include "obj/object.h"

#include "tst/list_test.c"

int main(int argc, char **argv) {
    printf("Mug programming language!\n");
    //test_basic();

    compile_file(0x00, 0x00);    

    return 0;
}
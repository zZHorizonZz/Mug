/**
 * Copyright 2022 Daniel Fiala
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
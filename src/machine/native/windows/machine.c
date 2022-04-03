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

#include "lexer.h"
#include "parser.h"
#include "machine.h"

unsigned char launch_machine(char *path, char *name)
{
    mug_program *program = malloc(sizeof(mug_program));
    mug_environment *environment = malloc(sizeof(mug_environment));

    if (program == 0x00 || environment == 0x00)
    {
        return 0x02;
    }

    program->path = path;
    program->name = name;

    mug_machine *machine = malloc(sizeof(mug_machine));
    if (machine == 0x00)
    {
        return 0x02;
    }

    machine->environment = environment;

    // todo there is a bug when building the program

    // machine->os_type = *get_os_type();
    // machine->os_name = get_os_name();

    /*if (machine->os_type == 0x00 || machine->os_type == 0x04)
    {
        printf("Your operation system is not supported!");
        exit(0x03);
    }*/

    char *final_path = malloc(strlen(path) + strlen(name) + 0x01);
    if (final_path == 0x00)
    {
        return 0x02;
    }

    strcpy(final_path, path);
    strcat(final_path, name);

    FILE *file = fopen(final_path, "r");

    if (file == 0x00)
    {
        printf("Error: could not open file %s", "D:\\program.str");
        return 0x02;
    }

    char buffer[256];
    lexer *lexer = malloc(sizeof(struct lexer_s));

    lexer->tokens = 0x00;
    lexer->current_token = 0x00;
    lexer->last_token_index = 0x00;

    printf("[Compiler] Evaluating content...");
    while (fgets(buffer, 256, file))
    {
        parse_content(lexer, buffer);
        free(buffer);
    }

    token **tokens = calloc(lexer->last_token_index - 1, sizeof(token *));
    for (size_t i = 0; i < lexer->last_token_index - 1; i++)
    {
        tokens[i] = lexer->tokens[i];
    }

    set *token_set = create_set(lexer->last_token_index - 1, (void **)tokens);

    launch_environment(program, environment);

    mug_foundation *main_foundation = new_foundation(environment, "src", "main");
    mug_method *main_method = new_method();
    mug_structure *main_structure = new_structure(environment, main_foundation);

    parse_method(environment, main_method, token_set);
    set_add(main_foundation->methods, main_method);

    call_method(environment, main_structure, main_method);
}
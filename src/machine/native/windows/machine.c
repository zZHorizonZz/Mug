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

    launch_environment(program, environment);
}
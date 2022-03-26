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

#include "environment.h"

int launch_environment(mug_program *program_data, mug_environment *environment)
{
    if (program_data->path == 0x00 || program_data->name == 0x00)
    {
        return 0x02;
    }

    environment->native_foundations = create_set(0x00, 0x00);
    environment->native_objects = create_set(0x00, 0x00);

    load_native(environment);


}

void load_native(mug_environment *environment)
{
    set_add(environment->native_foundations, load_primitive_foundation(BYTE, "byte"));
    set_add(environment->native_foundations, load_primitive_foundation(SHORT, "short"));
    set_add(environment->native_foundations, load_primitive_foundation(INT, "int"));
    set_add(environment->native_foundations, load_primitive_foundation(LONG, "long"));
    set_add(environment->native_foundations, load_primitive_foundation(FLOAT, "float"));
    set_add(environment->native_foundations, load_primitive_foundation(DOUBLE, "double"));
    set_add(environment->native_foundations, load_primitive_foundation(STRING, "string"));
    set_add(environment->native_foundations, load_primitive_foundation(BOOL, "bool"));
}

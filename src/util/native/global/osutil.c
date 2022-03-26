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

#include <stdlib.h>

typedef enum os_type_e os_type;

enum os_type_e
{
    WIN32,
    WIN64,
    UNIX,
    BSD,
    APPLE,
    UNKNOWN
};

os_type get_os_type()
{
#ifdef _WIN32
    return WIN32;
#endif

#ifdef _WIN64
    return WIN64;
#endif

#ifdef __unix__
    return UNIX;
#endif

#ifdef BSD
    return BSD;
#endif

#ifdef __APPLE__
    return APPLE;
#endif

#ifdef __MACH__
    return APPLE;
#endif

    return UNKNOWN;
}

char *get_os_name()
{
    os_type type = get_os_type();

    switch (type)
    {
    case 0x00:
        return "Windows 32-bit";
    case 0x01:
        return "Windows 64-bit";
    case 0x02:
        return "Unix";
    case 0x03:
        return "BSD";
    case 0x04:
        return "Apple";
    case 0x05:
    default:
        return "Uknown";
    }
}
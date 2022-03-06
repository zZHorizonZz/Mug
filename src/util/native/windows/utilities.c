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

#include "utilities.h"

char get_primitive_type(char *data) {
     int length = strlen(data);

    if (length < 0x01)
    {
        return 0x08;
    }

    if (strcmp(data, "true") == 0x00 || strcmp(data, "false") == 0x00)
    {
        return 0x07;
    }

    if (length > 1 && data[0x00] == 0x22 && data[length] == 0x22)
    {
        return 0x06;
    }

    for (size_t i = 0; i <= length; i++)
    {
        if ((data[i] >= 0x30 && data[i] <= 0x39))
        {
            continue;
        }

        switch (data[i])
        {
        case 0x64:
            return 0x05;
        case 0x66:
            return 0x04;
        case 0x6c:
            return 0x03;
        default:
            return 0x00;
        }
    }

    return 0x08;
}
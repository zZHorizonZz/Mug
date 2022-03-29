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

#include "primitive.h"

char create_primitive(mug_primitive *primitive, char *data)
{
    int length = strlen(data);

    if (length < 0x01)
    {
        return 0x08;
    }

    char first_char = data[0x00];

    if (first_char == 0x22)
    {
        mug_string *string = malloc(sizeof(mug_string));
        if (string == 0x00)
        {
            return 0x08;
        }

        string->value = data;
        primitive->mug_string = string;
        return 0x06;
    }

    if (first_char >= 0x30 && first_char <= 0x39)
    {
        switch (data[length - 0x01])
        {
        case 0x64:
        {
            char *number = strtok(data, "d");
            mug_double *mug_double = malloc(sizeof(struct double_s));
            if (mug_double == 0x00)
            {
                return 0x08;
            }

            mug_double->value = atof(number);
            primitive->mug_double = mug_double;
            return 0x05;
        }
        case 0x66:
        {
            char *number = strtok(data, "f");
            mug_float *mug_float = malloc(sizeof(struct float_s));
            if (mug_float == 0x00)
            {
                return 0x08;
            }

            mug_float->value = atof(number);
            primitive->mug_float = mug_float;
            return 0x04;
        }
        case 0x6c:
        {
            char *number = strtok(data, "l");
            mug_long *mug_long = malloc(sizeof(struct long_s));
            if (mug_long == 0x00)
            {
                return 0x08;
            }

            mug_long->value = atol(number);
            primitive->mug_long = mug_long;
            free(number);
            return 0x03;
        }
        default:
        {
            mug_int *mug_int = malloc(sizeof(struct int_s));
            if (mug_int == 0x00)
            {
                return 0x08;
            }

            mug_int->value = atoi(data);
            primitive->mug_int = mug_int;
            return 0x02;
        }
        }
    }

    return 0x08;
}

char *get_name(primitive_type type)
{
    switch (type)
    {
    case 0x00:
    {
        return "byte";
    }
    case 0x01:
    {
        return "short";
    }
    case 0x02:
    {
        return "int";
    }
    case 0x03:
    {
        return "long";
    }
    case 0x04:
    {
        return "float";
    }
    case 0x05:
    {
        return "double";
    }
    case 0x06:
    {
        return "string";
    }
    case 0x07:
    {
        return "bool";
    }
    default:
        break;
    }

    return 0x00;
}

char convert_primitive(mug_primitive *primitive, primitive_type type, primitive_type conversion_type)
{
    switch (type)
    {
    case 0x00:
        CONVERT_PRIMITIVE(byte, primitive, primitive->mug_byte, conversion_type);
        break;

    default:
        break;
    }
}

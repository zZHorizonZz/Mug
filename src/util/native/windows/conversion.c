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

#include "conversion.h"

int check_double_conversion(double number, int type)
{
    switch (type)
    {
    case 0x00:
        if (number > SCHAR_MAX)
        {
            return 0x01;
        }
        else if (number < SCHAR_MIN)
        {
            return -0x01;
        }
        else
        {
            return 0x00;
        }
    case 0x01:
        if (number > SHRT_MAX)
        {
            return 0x01;
        }
        else if (number < SHRT_MIN)
        {
            return -0x01;
        }
        else
        {
            return 0x00;
        }
    case 0x02:
        if (number > INT_MAX)
        {
            return 0x01;
        }
        else if (number < INT_MIN)
        {
            return -0x01;
        }
        else
        {
            return 0x00;
        }
    case 0x03:
        return 0x00;
    case 0x04:
        if (number > FLT_MAX)
        {
            return 0x01;
        }
        else if (number < FLT_MIN)
        {
            return -0x01;
        }
        else
        {
            return 0x00;
        }
    case 0x05:
        return 0x00;
    case 0x06:
        return 0x01;
    case 0x07:
        if (number > 0x01)
        {
            return 0x01;
        }
        else if (number < 0x00)
        {
            return -0x01;
        }
        else
        {
            return 0x00;
        }
    default:
        return 0x01;
    }
}

int check_float_conversion(float number, int type)
{
    switch (type)
    {
    case 0x00:
        if (number > SCHAR_MAX)
        {
            return 0x01;
        }
        else if (number < SCHAR_MIN)
        {
            return -0x01;
        }
        else
        {
            return 0x00;
        }
    case 0x01:
        if (number > SHRT_MAX)
        {
            return 0x01;
        }
        else if (number < SHRT_MIN)
        {
            return -0x01;
        }
        else
        {
            return 0x00;
        }
    case 0x02:
    case 0x03:
    case 0x04:
    case 0x05:
        return 0x00;
    case 0x06:
        return 0x01;
    case 0x07:
        if (number > 0x01)
        {
            return 0x01;
        }
        else if (number < 0x00)
        {
            return -0x01;
        }
        else
        {
            return 0x00;
        }
    default:
        return 0x01;
    }
}

int check_long_conversion(long number, int type)
{
    switch (type)
    {
    case 0x00:
        if (number > SCHAR_MAX)
        {
            return 0x01;
        }
        else if (number < SCHAR_MIN)
        {
            return -0x01;
        }
        else
        {
            return 0x00;
        }
    case 0x01:
        if (number > SHRT_MAX)
        {
            return 0x01;
        }
        else if (number < SHRT_MIN)
        {
            return -0x01;
        }
        else
        {
            return 0x00;
        }
    case 0x02:
        if (number > INT_MAX)
        {
            return 0x01;
        }
        else if (number < INT_MIN)
        {
            return -0x01;
        }
        else
        {
            return 0x00;
        }
    case 0x03:
        return 0x00;
    case 0x04:
        if (number > FLT_MAX)
        {
            return 0x01;
        }
        else if (number < FLT_MIN)
        {
            return -0x01;
        }
        else
        {
            return 0x00;
        }
    case 0x05:
        if (number > DBL_MAX)
        {
            return 0x01;
        }
        else if (number < DBL_MIN)
        {
            return -0x01;
        }
        else
        {
            return 0x00;
        }
    case 0x06:
        return 0x01;
    case 0x07:
        if (number > 0x01)
        {
            return 0x01;
        }
        else if (number < 0x00)
        {
            return -0x01;
        }
        else
        {
            return 0x00;
        }
    default:
        return 0x01;
    }
}

int check_int_conversion(int number, int type)
{
    switch (type)
    {
    case 0x00:
        if (number > SCHAR_MAX)
        {
            return 0x01;
        }
        else if (number < SCHAR_MIN)
        {
            return -0x01;
        }
        else
        {
            return 0x00;
        }
    case 0x01:
        if (number > SHRT_MAX)
        {
            return 0x01;
        }
        else if (number < SHRT_MIN)
        {
            return -0x01;
        }
        else
        {
            return 0x00;
        }
    case 0x02:
    case 0x03:
        return 0x00;
    case 0x04:
        if (number > FLT_MAX)
        {
            return 0x01;
        }
        else if (number < FLT_MIN)
        {
            return -0x01;
        }
        else
        {
            return 0x00;
        }
    case 0x05:
        if (number > DBL_MAX)
        {
            return 0x01;
        }
        else if (number < DBL_MIN)
        {
            return -0x01;
        }
        else
        {
            return 0x00;
        }
    case 0x06:
        return 0x01;
    case 0x07:
        if (number > 0x01)
        {
            return 0x01;
        }
        else if (number < 0x00)
        {
            return -0x01;
        }
        else
        {
            return 0x00;
        }
    default:
        return 0x01;
    }
}

int check_short_conversion(short number, int type)
{
    switch (type)
    {
    case 0x00:
        if (number > SCHAR_MAX)
        {
            return 0x01;
        }
        else if (number < SCHAR_MIN)
        {
            return -0x01;
        }
        else
        {
            return 0x00;
        }
    case 0x01:
    case 0x02:
    case 0x03:
        return 0x00;
    case 0x04:
        if (number > FLT_MAX)
        {
            return 0x01;
        }
        else if (number < FLT_MIN)
        {
            return -0x01;
        }
        else
        {
            return 0x00;
        }
    case 0x05:
        if (number > DBL_MAX)
        {
            return 0x01;
        }
        else if (number < DBL_MIN)
        {
            return -0x01;
        }
        else
        {
            return 0x00;
        }
    case 0x06:
        return 0x01;
    case 0x07:
        if (number > 0x01)
        {
            return 0x01;
        }
        else if (number < 0x00)
        {
            return -0x01;
        }
        else
        {
            return 0x00;
        }
    default:
        return 0x01;
    }
}

int check_byte_conversion(char number, int type)
{
    switch (type)
    {
    case 0x00:
    case 0x01:
    case 0x02:
    case 0x03:
        return 0x00;
    case 0x04:
        if (number > FLT_MAX)
        {
            return 0x01;
        }
        else if (number < FLT_MIN)
        {
            return -0x01;
        }
        else
        {
            return 0x00;
        }
    case 0x05:
        if (number > DBL_MAX)
        {
            return 0x01;
        }
        else if (number < DBL_MIN)
        {
            return -0x01;
        }
        else
        {
            return 0x00;
        }
    case 0x06:
        return 0x01;
    case 0x07:
        if (number > 0x01)
        {
            return 0x01;
        }
        else if (number < 0x00)
        {
            return -0x01;
        }
        else
        {
            return 0x00;
        }
    default:
        return 0x01;
    }
}

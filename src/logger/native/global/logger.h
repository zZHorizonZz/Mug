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

#ifndef LOGGER_H
#define LOGGER_H

#include "storage.h"

extern mug_logger *DEFAULT_LOGGER;

typedef struct mug_logger_s mug_logger;
typedef struct record_s record;

struct mug_logger_s 
{
    set *buffer;
}

struct record_s 
{
    unsigned char error_code;

    long timestamp;
    char *metadata;
}

mug_logger *new_default_logger();
record *new_record(unsigned char error_code, long timestamp, char *metadata);

void init_default_logger(mug_logger *logger);

void log_message(mug_logger *logger, char *message, ...);
void log(mug_logger *logger, record *record);

#endif
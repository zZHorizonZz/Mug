// Copyright 2022 Daniel Fiala
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <stdlib.h>
#include <stdio.h>

#include "method.h"

typedef struct foundation_s
{
    char *location;
    char *name;

    size_t method_count;
    size_t field_count;

    method **method;
} foundation;

typedef struct foundation_container_s
{
    size_t length;
    foundation **foundation;
} foundation_container;

foundation *find_foundation(char *location, char *name);
int register_foundation(foundation *foundation);
int remove_foundation(char *location, char *name);
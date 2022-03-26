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

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "parser.h"
#include "object.h"
#include "storage.h"

extern mug_environment ENVIRONMENT;

int launch_environment(mug_program *program, mug_environment *environment);

void load_native(mug_environment *environment);

mug_foundation *get_native_foundation(mug_environment *environment, char *location, char *name);
mug_object *get_native_object(mug_environment *environment, char *location, char *name);

#endif
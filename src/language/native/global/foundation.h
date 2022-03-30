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

//
// ─── NATIVE ─────────────────────────────────────────────────────────────────────
//

#ifndef FOUNDATION_H
#define FOUNDATION_H

#include "primitive.h"
#include "type.h"

mug_foundation *load_primitive_foundation(mug_environment *environment, primitive_type primitive_type, char *name);
mug_foundation *get_native_foundation(mug_environment *environment, char *location, char *name);
mug_structure *get_native_structure(mug_environment *environment, char *location, char *name);

mug_foundation *new_foundation();

#endif
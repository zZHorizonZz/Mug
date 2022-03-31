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

#ifndef FIELD_H
#define FIELD_H

#include "type.h"

mug_field *get_struture_field(mug_structure *structure, const char *name);
mug_field *get_body_field(body *body, const char *name);

char add_body_field(body *body, mug_field *field);
char add_structure_field(mug_structure *structure, mug_field *field);

#endif
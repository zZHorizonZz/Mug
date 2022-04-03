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

#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <stdlib.h>

#include "storage.h"
#include "primitive.h"
#include "token.h"
#include "foundation.h"
#include "type.h"
#include "method.h"

//
// ─── OBJECT ─────────────────────────────────────────────────────────────────────
//

int equals(mug_structure *original, mug_structure *equal);

void load_native_primitive(mug_structure *environment, mug_structure *main_structure);
mug_structure *build_primitive_object(mug_primitive *primitive);

mug_method *new_method();
body *new_body();
block *new_block();

#endif
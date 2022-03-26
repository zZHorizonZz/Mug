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

//
// ─── OBJECT ─────────────────────────────────────────────────────────────────────
//

mug_object *new_object(mug_foundation *foundation);
int equals(mug_object *original, mug_object *equal);

void load_native_primitive(mug_object *environment, mug_object *main_structure);
mug_object *build_primitive_object(mug_primitive *primitive);

//
// ─── METHOD ─────────────────────────────────────────────────────────────────────
//

mug_method *new_method();
void execute_method(mug_method *method);

//
// ─── BODY ───────────────────────────────────────────────────────────────────────
//

body *new_body();
void execute_body(body *body);

//
// ─── BLOCK ──────────────────────────────────────────────────────────────────────
//

block *new_block();
void execute_block(char type, block *block);
void execute_field_block(field_block *field_block);

//
// ─── EXPRESSION ─────────────────────────────────────────────────────────────────
//

void execute_expression(char type, expression *expression);
void execute_value_expression(value_expression *expression);
int execute_operator_expression(operator_expression *expression);

#endif
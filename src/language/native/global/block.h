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

#ifndef BLOCK_H
#define BLOCK_H

#include "type.h"
#include "expression.h"

void call_block(mug_environment *environment, mug_structure *structure, mug_method *method, block *body);

void call_expression_block(mug_environment *environment, mug_structure *structure, mug_method *method, expression_block *body);
void call_field_block(mug_environment *environment, mug_structure *structure, mug_method *method, field_block *body);

#endif
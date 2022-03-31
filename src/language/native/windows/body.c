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

#include "body.h"
#include "block.h"

void call_body_of_method(mug_environment *environment, mug_structure *structure, mug_method *method)
{
    call_body(environment, structure, method, method->body);
}

void call_body(mug_environment *environment, mug_structure *structure, mug_method *method, body *body)
{
    for (size_t i = 0; i < body->body_block->length; i++)
    {
        block *block = body->body_block->array[i];
        call_block(environment, structure, method, block);
    }
}

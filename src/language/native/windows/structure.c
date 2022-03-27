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

#include <stdio.h>
#include <stdlib.h>

#include "structure.h"

/*
 * ─── OBJECT ─────────────────────────────────────────────────────────────────────
 */

mug_structure *new_structure(mug_foundation *foundation)
{
}

int equals(mug_structure *original, mug_structure *equal)
{
}

/*
 * ─── METHOD ─────────────────────────────────────────────────────────────────────
 */

mug_method *new_method()
{
    mug_method *method = malloc(sizeof(mug_method));
    if (method == 0x00)
    {
    }

    method->body = new_body();
    return method;
}

/*
 * ─── BODY ───────────────────────────────────────────────────────────────────────
 */

body *new_body()
{
    body *new_body = malloc(sizeof(body));
    if (new_body == 0x00)
    {
    }

    new_body->body_block = create_set(0x00, 0x00);
    new_body->body_type = create_set(0x00, 0x00);
    new_body->length = 0x00;

    return new_body;
}

/*
 * ─── BLOCK ──────────────────────────────────────────────────────────────────────
 */

block *new_block()
{
    block *new_block = malloc(sizeof(block));
    if (new_block == 0x00)
    {
    }

    return new_block;
}
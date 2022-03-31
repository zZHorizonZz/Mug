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

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "type.h"

mug_structure *call_expression(mug_environment *environment, mug_structure *structure, mug_method *method, expression *expression);

mug_structure *call_value_expression(mug_environment *environment, mug_structure *structure, mug_method *method, value_expression *expression);
mug_structure *call_operator_expression(mug_environment *environment, mug_structure *structure, mug_method *method, operator_expression *expression);
mug_structure *call_reference_expression(mug_environment *environment, mug_structure *structure, mug_method *method, reference_expression *expression);

mug_primitive *call_operator_add(mug_environment *environment, mug_structure *structure, mug_method *method, operator_expression *expression);
mug_primitive *call_operator_subtract(mug_environment *environment, mug_structure *structure, mug_method *method, operator_expression *expression);
mug_primitive *call_operator_multiply(mug_environment *environment, mug_structure *structure, mug_method *method, operator_expression *expression);
mug_primitive *call_operator_divide(mug_environment *environment, mug_structure *structure, mug_method *method, operator_expression *expression);

#endif
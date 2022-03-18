## Parser
This page contains all information about how parser works.
Parsers work is to process [!Tokens](/TOKENS.md) into code structure which can be run
or compiled into binary file. Instructions are separated into different sub-types

> Repository > Structure (Foundation) > Fields, Methods, > Body > Block > Expression

## Processing

## Rules

> Parser rules which parser uses to identify code blocks, bodies, methods, etc.

| Name | Rule | Description |
| ---- | ---------- | ---- |
| Expression | (Value Expression/Operator Expression/Reference Expression) | Expression is parent object for all sub expressions. |
| Value Expression | Any primitive value like string, integer, long, etc. | Value expression contains primitive values and can not be null. |
| Operator Expression | Expression (Operator) Expression | Operator expression has two sides right side and left side which can be expression. |
| Reference Expression | Reference of field or return method of specific type. | Reference expression refers to any value like field or method which should return value of same type. |
| Declared Field Block | Type, Identifier (=) (Expression) | Declared field block declares field in method body or in structure itself. Declared field block can or can not be null. |
| Field Block | Identifier (=/=Operator) (Expression) | Field block edits value of declared field in method body or in structure itself. Value itself can be null. |
| Return Block | return (Expression) | Return block will end execution of the method and returns value from assigned expression if it's required by method. |


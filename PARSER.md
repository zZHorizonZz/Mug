## Parser
This page contains all information about how parser works.
Parsers work is to process [!Tokens](/TOKENS.md) into code structure which can be run
or compiled into binary file. Instructions are separated into different sub-types

> Repository > Structure (Foundation) > Fields, Methods, > Body > Block > Expression

## Processing

## KeyWord:
> Byte value of keyword token is 0x02

| Name | Identifier | Code |
| ---- | ---------- | ---- |
| Repository | 0x00 | repository |
| Structure | 0x01 | structure |
| Void | 0x02 | void |
| Native | 0x03 | native |
| If | 0x04 | if |
| Else | 0x05 | else |
| Else-If | 0x06 | elseif |
| While | 0x07 | while |
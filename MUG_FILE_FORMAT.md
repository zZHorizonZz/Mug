## Format

Format of the structure in its compiled version mug is based on
'Binary Strustured Data Format' in a nutshell BSDF, more informations about
BSDF can be found here [BSDF Docs] (https://bsdf.readthedocs.io/#)

## Tags
Every tag has common or similar header. Every tag starts as one byte and that's its identifier.
If our tag is type of LIST, MAPPED_LIST or STRING we need to provide length of this tag
like number of its elements or number of letters. This is used by program to identify where it
should stop reading our tag, otherwise unexpected results may happen.

Index  | Name | Description
------------- | -------------
0  | END_OF_TAG | This tag is used as identifier where our non single value tag should end.
1  | LIST | This tag is list of un-named tags.
2  | SINGLE_TYPE_LIST | This tag is list of un-named tags of single type. After length byte we need to specify\nbyte value of tag which will be included in the list.
2  | MAPPED_LIST | This tag contains list of named tags.
3  | BYTE | This tag can contain only one byte.
4  | SHORT | This tag is single signed big endian 16 bit integer (2 bytes).
5  | INTEGER | This tag is single signed big endian 32 bit integer (4 bytes).
6  | LONG | This tag is single signed big endian 64 bit integer (8 bytes).
7  | FLOAT | This tag is big endian single precision floating point (4 bytes).
8  | DOUBLE | This tag is big endian double precision floating point (8 bytes).
9  | STRING | String is basically list of bytes. This tag starts with length of string.
10 | BOOLEAN | This tag is basically one byte but for more optimized aproach we should use bitmask.

## File Structure

Every file should start with main tag such as LIST or MAPPED_LIST tag
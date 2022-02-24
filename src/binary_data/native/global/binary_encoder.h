#ifndef BINARY_ENCODER_H
#define BINARY_ENCODER_H

#include "buffer.h"
#include "tag.h"

int add_value_to_list_tag(compound *list_tag, compound *compound);
int add_value_to_list(list_tag *list_tag, compound *compound);
int add_value_to_single_type_list_tag(compound *list_tag, compound *compound);
int add_value_to_single_type_list(single_type_list_tag *list_tag, compound *compound);
int add_value_to_mapped_list_tag(compound *list_tag, char *name, compound *compound);
int add_value_to_mapped_list(mapped_list_tag *mapped_list_tag, char *name, compound *compound);

int write_list_tag(buffer *buffer, compound *compound);
int write_single_type_list_tag(buffer *buffer, compound *compound);
int write_mapped_list_tag(buffer *buffer, compound *compound);

void write_tag(buffer *buffer, compound *compound);

char *create_binary(compound *compound);

#endif

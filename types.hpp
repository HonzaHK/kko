#ifndef TYPES_HPP
#define TYPES_HPP

#include <stdlib.h>

typedef struct {
	char* ptr=NULL;
	int len=0;
} t_str_len;

#endif



void t_str_len_clear(t_str_len*);

void t_str_len_copy(t_str_len, t_str_len*);

void t_str_len_print(t_str_len);
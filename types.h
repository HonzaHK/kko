//author: Jan Kubis / xkubis13
//file: types.h
//created: 2018/02/23
//purpose: string helpers header file

#ifndef TYPES_HPP
#define TYPES_HPP

#include <stdlib.h>

typedef struct {
	char* ptr;
	int len;
} t_str_len;




void t_str_len_clear(t_str_len*);

void t_str_len_copy(t_str_len, t_str_len*);

void t_str_len_print(t_str_len);








#endif
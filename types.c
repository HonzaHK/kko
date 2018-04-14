//author: Jan Kubis / xkubis13
//file: types.c
//created: 2018/02/23
//purpose: string helper file

#include <stdio.h>
#include <string.h>
#include "types.h"

void t_str_len_clear(t_str_len* s){

	free(s->ptr);
	s->ptr=NULL;
	s->len=0;
}

void t_str_len_copy(t_str_len from, t_str_len* to){

	t_str_len_clear(to);
	to->ptr=(char*)malloc(from.len*sizeof(char));
	memcpy(to->ptr,from.ptr,from.len);
	to->len=from.len;
}

void t_str_len_print(t_str_len s){
	for(int i=0;i<s.len;i++){
		printf("%c", s.ptr[i]);
	}
	printf("\n");
}
//author: Jan Kubis / xkubis13
//file: bwt.h
//created: 2018/02/23
//purpose: btw encoding/decoding header file

#include "types.h"

int BWTenc(char*, int, char*);

int BWTdec(char*, int, char*);

void bwt_print(char*, int);
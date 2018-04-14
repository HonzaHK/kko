//author: Jan Kubis / xkubis13
//file: bwted.h
//created: 2018/02/23
//purpose: library (performs all the encodings) header file

#include <stdio.h>
#include <stdint.h>

typedef struct
{
  int64_t uncodedSize;
  int64_t codedSize;
} tBWTED;

int BWTEncoding (tBWTED *, FILE *, FILE *);
int BWTDecoding (tBWTED *, FILE *, FILE *);

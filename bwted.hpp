#include <stdio.h>
#include <stdint.h>

typedef struct
{
  int64_t uncodedSize;
  int64_t codedSize;
} tBWTED;

int BWTEncoding (tBWTED *, FILE *, FILE *);
int BWTDecoding (tBWTED *, FILE *, FILE *);

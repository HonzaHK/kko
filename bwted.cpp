#include <stdlib.h>
#include <string.h>

#include "bwted.hpp"

#include "types.hpp"

#include "bwt.hpp"
#include "mtf.hpp"
#include "rle.hpp"
#include "huf.hpp"



#define INPUT_BLOCK_SIZE 64

//BWT does not modify the length of input; index of original permutation is added (size+=1)
//MTF does not modify the length of input
//RLE at the worst case the length*=2; the real length (usually shorter) is stored inside (size = size*2 + 1)
#define MAX_BLOCK_SIZE ((INPUT_BLOCK_SIZE+1)*2 +1)

//create buffers for separate (bwt,mtf,rle) transformations
char block_a[MAX_BLOCK_SIZE];
char block_b[MAX_BLOCK_SIZE];



int BWTEncoding (tBWTED* rec, FILE* ifile, FILE* ofile){
	
	if(ifile==NULL || ofile==NULL){
		return -1;
	}
	
	rewind(ifile);


	if(rec==NULL){
		return -1;
	}

	int bytes_read = 0;
	while((bytes_read=fread(block_a, 1, INPUT_BLOCK_SIZE, ifile)) > 0){

		//input/output buffers are overdimensioned for the worst case
		//in block_real_size we will store the real size of encoded/decoded block in each step
		int block_real_size = bytes_read;

		//perform bwt encoding
		block_real_size = BWTenc(block_a, block_real_size, block_b);

		//perform mtf encoding (string has length+1 - it has stored index of orig permutation)
		block_real_size = MTFenc(block_b,block_real_size);

		// MTFprint(block_b,block_real_size);
		//save to file
		fwrite(block_b,sizeof(char),block_real_size*sizeof(char),ofile);
	}

	return 0;
}


int BWTDecoding (tBWTED *rec, FILE *ifile, FILE *ofile){
	
	if(ifile==NULL || ofile==NULL){
		return -1;
	}

	rewind(ifile);


	if(rec==NULL){
		return -1;
	}

	int bytes_read = 0;
	while((bytes_read=fread(block_a, 1, INPUT_BLOCK_SIZE+1, ifile)) > 0){

		//input/output buffers are overdimensioned for the worst case
		//in block_real_size we will store the real size of encoded/decoded block in each step
		int block_real_size = bytes_read;

		//perform mtf decoding
		block_real_size = MTFdec(block_a,bytes_read);
		
		//perform bwt decoding
		block_real_size = BWTdec(block_a,bytes_read,block_b);


		//save to file
		fwrite(block_b,sizeof(char),block_real_size*sizeof(char),ofile);
	}


	return 0;
}
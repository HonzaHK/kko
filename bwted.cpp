#include <stdlib.h>
#include <string.h>

#include "bwted.hpp"

#include "types.hpp"

#include "bwt.hpp"
#include "mtf.hpp"
#include "rle.hpp"
#include "huf.hpp"



#define INPUT_BLOCK_SIZE 2048

//BWT does not modify the length of input; index of original permutation is added (size+=2)
//MTF does not modify the length of input
//RLE at the worst case wont encode anything; index of new block size is added (size+=2)
#define MAX_BLOCK_SIZE ((INPUT_BLOCK_SIZE+2)*2+1)

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
	while((bytes_read=fread(block_a, 1, INPUT_BLOCK_SIZE, ifile))>0){

		//input/output buffers are dimensioned for the worst case
		//in block_real_size we will store the real size of encoded/decoded block in each step
		int block_real_size = bytes_read;

		//perform bwt encoding
		block_real_size = BWTenc(block_a, block_real_size, block_b);
		// mtf_print(block_b,block_real_size);

		//perform mtf encoding (string has length+1 - it has stored index of orig permutation)
		block_real_size = MTFenc(block_b,block_real_size);


		block_real_size = RLEenc(block_b,block_real_size,block_a);

		//save to file
		fwrite(block_a,sizeof(char),block_real_size*sizeof(char),ofile);
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


	uint16_t next_block_size=0;

	int bytes_read = 0;
	//read out the size byte, check for EOF, eventualy read the block of specified size
	while(
		(fread(&next_block_size, sizeof(uint16_t), 1, ifile)!=0) && 
		(bytes_read=fread(block_a, 1, next_block_size, ifile)) > 0){

		//input/output buffers are overdimensioned for the worst case
		//in block_real_size we will store the real size of encoded/decoded block in each step
		int block_real_size = bytes_read;

		// perform rle decoding
		block_real_size = RLEdec(block_a,block_real_size,block_b);

		//perform mtf decoding
		block_real_size = MTFdec(block_b,block_real_size);
		
		// mtf_print(block_b,block_real_size);
		//perform bwt decoding
		block_real_size = BWTdec(block_b,block_real_size,block_a);

		//save to file
		fwrite(block_a,sizeof(char),block_real_size*sizeof(char),ofile);
	}


	return 0;
}
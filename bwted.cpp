#include <stdlib.h>
#include <string.h>

#include "bwted.hpp"

#include "types.hpp"

#include "bwt.hpp"
#include "mtf.hpp"
#include "rle.hpp"
#include "huf.hpp"



int BWTEncoding (tBWTED* rec, FILE* ifile, FILE* ofile){
		
	if(ifile==NULL){
		return -1;
	}

	t_str_len input;
	t_str_len output;

	fseek (ifile, 0, SEEK_END);
	input.len = ftell (ifile);
	fseek (ifile, 0, SEEK_SET);
	input.ptr = (char*) malloc((input.len)*sizeof(char));
	if (input.ptr){
		fread (input.ptr, 1, input.len, ifile);
	}

	// printf("MTFenc\n");
	// MTFenc(input);
	// MTFprint(input);

	// printf("MTFdec\n");
	// MTFdec(input);
	// printf("%s (%d)\n", input.ptr, input.len);

	// printf("RLEenc\n");
	// RLEenc(input,&output);
	// printRleCode(output);

	// t_str_len_copy(output,&input);
	// t_str_len_clear(&output);
	// printf("RLEdec\n");
	// RLEdec(input,&output);
	// t_str_len_print(output);

	// t_str_len_clear(&input);
	// t_str_len_clear(&output);

	// BWTenc(input,&output);
	// t_str_len_print(output);
	// BWTdec(output,&input);

	HUFenc(input,&output);
	HUFdec(input,&output);



	free(input.ptr);


	return 0;
}


int BWTDecoding (tBWTED *, FILE *, FILE *){
	printf("BWTDecoding...\n");
	return 0;
}
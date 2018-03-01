#include <stdlib.h>
#include <string.h>

#include "bwted.hpp"

#include "types.hpp"

#include "bwt.hpp"
#include "mtf.hpp"
#include "rle.hpp"
#include "huf.hpp"

#define MTF_BUFFER_SIZE 1024
#define RLE_BUFFER_SIZE 1024
char rle_buffer[RLE_BUFFER_SIZE];





int BWTEncoding (tBWTED* rec, FILE* ifile, FILE* ofile){
		
	if(ifile==NULL){
		return -1;
	}

	fseek (ifile, 0, SEEK_END);
	int filelen = ftell (ifile);
	rewind(ifile);
	
	t_str_len input;
	t_str_len output;

	// input.len = filelen;
	// if((input.ptr = (char*) malloc((25000)*sizeof(char))) == NULL){ 
	// 	return -1;
	// };

	// input.len = 25000;



	int bytes_read = 0;
	while((bytes_read=fread(input.ptr, 1, 1024, ifile)) > 0){
		RLEenc(input,&output);
	}

	



	// MTFenc(input);
	// MTFprint(input);

	// MTFdec(input);
	// t_str_len_print(input);

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

	// HUFenc(input,&output);
	// HUFdec(input,&output);



	free(input.ptr);


	return 0;
}


int BWTDecoding (tBWTED *rec, FILE *ifile, FILE *ofile){
	
	if(ifile==NULL){
		return -1;
	}

	fseek (ifile, 0, SEEK_END);
	int filelen = ftell (ifile);
	fseek (ifile, 0, SEEK_SET);
	
	t_str_len input;
	t_str_len output;

	input.len = filelen;
	if((input.ptr = (char*) malloc((input.len)*sizeof(char))) == NULL){ 
		return -1;
	};

	int bytes_read = 0;
	while((bytes_read=fread(input.ptr, 1, 25000, ifile)) > 0){
		printf("%d\n", bytes_read);
	}




	free(input.ptr);
	return 0;
}
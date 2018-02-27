#include <stdio.h>
#include <stdint.h>
#include "rle.hpp"

void printRleCode(t_str_len code){

	for(int i=0;i<code.len;i++){
		if(i%2==0){
			printf("%d_", code.ptr[i]);
		}
		else{
			printf("%c ", code.ptr[i]);

		}
	}
	printf("\n");
}

void RLEenc(t_str_len input, t_str_len* output){


	//init
	char lastChar = input.ptr[0];
	uint8_t cnt = 1;

	for(int i=1; i<input.len; i++){

		if(input.ptr[i]==lastChar){
			cnt++;
			continue;
		}
		else{
			//write to output;
			output->ptr = (char *) realloc(output->ptr,(output->len+2)*sizeof(char));
			output->ptr[output->len] = cnt;
			output->ptr[output->len+1] = input.ptr[i-1];
			output->len+=2;
			//re-init
			lastChar=input.ptr[i];
			cnt=1;
		}
	}

	//additionaly encode the last run of symbols
	//only if input.len>1 ?
	output->ptr = (char *) realloc(output->ptr,(output->len+2)*sizeof(char));
	output->ptr[output->len] = cnt;
	output->ptr[output->len+1] = input.ptr[input.len-1];
	output->len+=2;
}

void RLEdec(t_str_len input, t_str_len* output){

	//malloc one time, so we do not realloc in cycle
	int calculatedLen = 0;
	for(int i=0; i<input.len;i+=2){
		calculatedLen+=(input.ptr)[i];
	}

	output->ptr = (char*) malloc(calculatedLen*sizeof(char)+1);

	//decode the runs
	for(int i=0; i<input.len; i+=2){

		uint8_t charCnt = input.ptr[i];
		char ch = input.ptr[i+1];
		for(uint8_t j=0; j<charCnt; j++){
			output->ptr[output->len] = ch;
			output->len++;
		}
	}
}

#include <stdio.h>
#include <stdint.h>
#include "rle.hpp"

void RLEprint(char* input, int input_len){

	for(int i=1;i<input_len;i++){
		if(i%2==1){
			printf("%d_", input[i]);
		}
		else{
			printf("%d ", (uint8_t)input[i]);

		}
	}
	printf("[bsize=%d]\n", input[0]);
}

int RLEenc(char* input, int input_len, char* output){


	//init
	char lastChar = input[0];
	uint8_t cnt = 1;

	uint8_t output_len = 0;
	for(int i=1; i<input_len; i++){

		//todo: cnt==256
		if(input[i]==lastChar){
			cnt++;
			continue;
		}
		else{
			//write to output;
			output[output_len] = cnt;
			output[output_len+1] = input[i-1];
			output_len+=2;
			//re-init
			lastChar=input[i];
			cnt=1;
		}
	}

	//additionaly encode the last run of symbols
	//only if input_len>1 ?
	output[output_len] = cnt;
	output[output_len+1] = input[input_len-1];
	output_len+=2;

	//shift all bytes right
	output_len+=1;
	for(int i=output_len-1;i>0;i--){
		output[i] = output[i-1];
	}

	//store the real block size to the beggining of encoded string (do not count this byte)
	output[0] = output_len-1;

	return output_len;
}

int RLEdec(char* input, int input_len, char* output){

	//decode the runs
	int output_len=0;
	for(int i=0; i<input_len; i+=2){

		uint8_t charCnt = input[i];
		char ch = input[i+1];
		for(uint8_t j=0; j<charCnt; j++){
			output[output_len] = ch;
			output_len++;
		}
	}

	return output_len;
}

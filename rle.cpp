#include <stdio.h>
#include <stdint.h>
#include "rle.hpp"

const char rleFlag= (char) 0xFF;

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

	int cnt_packed = 0;

	//init
	char lastChar = input[0];
	uint8_t cnt = 1;

	uint16_t output_len = 0;

	//do not encode last two bytes - these are representing original index of bwt permutation
	for(int i=1; i<input_len-2; i++){

		//todo: cnt==256
		if(input[i]==lastChar){
			cnt++;
			continue;
		}
		else {
			if(cnt==1 || cnt==2 || cnt==3){
				for(int j=0; j<cnt; j++){
					output[output_len+j] = lastChar;
				}
				output_len+=cnt;
			}
			else{
				output[output_len] = rleFlag;
				output[output_len+1] = cnt;
				output[output_len+2] = lastChar;
				output_len+=3;
				cnt_packed+=1;
			}
			
			//re-init
			lastChar=input[i];
			cnt=1;
		}
	}

	//additionaly encode the last run of symbols
	//only if input_len>1 ?
	if(cnt==1 || cnt==2 || cnt==3){
		for(int j=0; j<cnt; j++){
			output[output_len+j] = lastChar;
		}
		output_len+=cnt;
	}
	else{
		output[output_len] = rleFlag;
		output[output_len+1] = cnt;
		output[output_len+2] = lastChar;
		output_len+=3;
		cnt_packed+=1;
	}

	//copy original index of bwt permutation bytes (2)
	output[output_len] = input[input_len-2];
	output[output_len+1] = input[input_len-1];
	output_len+=2;

	//shift all bytes 2 positions right
	output_len+=2;
	for(int i=output_len-1;i>0;i--){
		output[i] = output[i-2];
	}

	//store the real block size to the beggining of encoded string (do not count this byte)
	uint16_t rle_code_len = output_len-2;
	//todo: little/big endian
	output[0] = rle_code_len & 0xFF;
	output[1] = rle_code_len >> 8;

	return output_len;
}

int RLEdec(char* input, int input_len, char* output){

	int cnt_packed=0;

	//decode the runs
	int output_len=0;
	for(int i=0; i<input_len-2; i++){
		if(input[i]==rleFlag){
			cnt_packed+=1;
			uint8_t cnt = input[i+1];
			for(uint8_t j=0; j<cnt; j++){
				output[output_len] = input[i+2];
				output_len+=1;
			}
			i+=2;
		}
		else{
			output[output_len] = input[i];
			output_len+=1;
		}
	}

	//copy original index of bwt permutation bytes (2)
	output[output_len] = input[input_len-2];
	output[output_len+1] = input[input_len-1];
	output_len+=2;
	

	return output_len;
}

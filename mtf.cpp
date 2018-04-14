//author: Jan Kubis / xkubis13
//file: mtf.c
//created: 2018/02/23
//purpose: performs mtf encoding/decoding

#include <stdio.h>
#include <stdint.h>

#include "mtf.hpp"

const int alphalength = 256;
unsigned char alphabet[alphalength];

void initAlphabet(){
	for(int i=0; i<alphalength;i++){
		alphabet[i] = (unsigned char) i;
	}
}

void printAlphabet(){
	for(int i=0; i<alphalength;i++){
		printf("%d", alphabet[i]);
	}
	printf("\n");
}

void mtf_print(char* input, int input_len){
	for(int i=0; i<input_len; i++){
		printf("%d.", (uint8_t)input[i]);
	}
	printf("\n");
}

//finds alphabet index of a char and moves the character to the front of the alphabet
uint8_t getCharIndexAndMoveToFront(unsigned char c){

	// printf("char: %d\n",c);
	//first, record index of character
	uint8_t index = -1;
	for(int i=0; i<alphalength;i++){
		if(alphabet[i]!=c) {continue;}
		index=i;
	}

	// printf("index: %d\n", index);

	//next, move the alphabet (upo to index)
	for(int i=index; i>0; i--){
		alphabet[i] = alphabet[i-1];
	}

	//finaly, insert the character at the beginning
	alphabet[0] = c;

	return index;
}

int MTFenc(char* input, int input_len){

	initAlphabet();
	for(int i=0; i<input_len; i++){
		int index = getCharIndexAndMoveToFront(input[i]);
		input[i]=index;
	}

	//mtf does not modify the length of input
	return input_len;
}

int MTFdec(char* input,int input_len){

	initAlphabet();

	for(int i=0;i<input_len; i++){
		input[i] = alphabet[(uint8_t)input[i]];
		getCharIndexAndMoveToFront(input[i]);
	}

	return input_len;
}
#include <stdio.h>
#include <stdint.h>

#include "mtf.hpp"

const int alphalength = 256;
char alphabet[alphalength];

void initAlphabet(){

	for(int i=0; i<alphalength;i++){
		alphabet[i] = (unsigned char) i;
	}
}

void printAlphabet(){
	for(int i=0; i<alphalength;i++){
		printf("%c", alphabet[i]);
	}
	printf("\n");
}

void MTFprint(t_str_len input){
	for(int i=0; i<input.len; i++){
		printf("%d ", input.ptr[i]);
	}
	printf("\n");
}

//finds alphabet index of a char and moves the character to the front of the alphabet
int getCharIndexAndMoveToFront(char c){

	//first, record index of character
	int index = -1;
	for(int i=0; i<alphalength;i++){
		if(alphabet[i]!=c) {continue;}
		index=i;
	}


	//next, move the alphabet (upo to index)
	for(int i=index; i>0; i--){
		alphabet[i] = alphabet[i-1];
	}

	//finaly, insert the character at the beginning
	alphabet[0] = c;

	return index;
}

void MTFenc(t_str_len input){

	initAlphabet();

	for(int i=0; i<input.len; i++){
		int index = getCharIndexAndMoveToFront(input.ptr[i]);
		input.ptr[i]=index;
	}
}

void MTFdec(t_str_len input){

	initAlphabet();

	for(int i=0;i<input.len; i++){
		input.ptr[i] = alphabet[(int)input.ptr[i]];
		getCharIndexAndMoveToFront(input.ptr[i]);
	}
}
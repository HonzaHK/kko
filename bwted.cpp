#include <stdlib.h>
#include <string.h>

#include "bwted.hpp"

const int alphalength = 26;
const int ascii_first_index =65;
char alphabet[alphalength];

void BWTenc(char* input, int length){

}

void initAlphabet(){
	for(int i=0; i<alphalength;i++){
		alphabet[i] = (unsigned char) ascii_first_index + i;
	}
}

void printAlphabet(){
	for(int i=0; i<alphalength;i++){
		printf("%c", alphabet[i]);
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

void MTFenc(char* input, int length){
	printf("%s (%d)\n", input,length);

	initAlphabet();
	printAlphabet();
	printf("%d\n", getCharIndexAndMoveToFront('M'));
	printAlphabet();
}



void RLEenc(char* input, int length){
	printf("%s (%d)\n", input,length);
}



int BWTEncoding (tBWTED* rec, FILE* ifile, FILE* ofile){
	printf("BWTEncoding...\n");
		
	if(ifile==NULL){
		return -1;
	}

	fseek (ifile, 0, SEEK_END);
	int length = ftell (ifile);
	fseek (ifile, 0, SEEK_SET);
	char* input = (char*) malloc((length+1)*sizeof(char));
	if (input){
		fread (input, 1, length, ifile);
		input[length] = '\0';
	}

	printf("input: %s\n", input);


	MTFenc(input,length);
	return 0;



	char** perms = (char**) malloc(length*sizeof(char*));
	for(int i=0;i<length;i++){
		perms[i] = (char*) malloc((length+1)*sizeof(char));
		strncpy(perms[i],input,length);
		perms[i][length] = '\0';
	}

	for(int i=1;i<length;i++){
		for(int j=0;j<length;j++){
			perms[i][j] = perms[i-1][j-1<0 ? length-1 : j-1];
		}
	}

	
	for(int i=0;i<length;i++){
		printf("%s\n", perms[i]);
	}
	



	for(int i=0;i<length;i++){
		free(perms[i]);
	}
	free(perms);
	free(input);




	return 0;
}


int BWTDecoding (tBWTED *, FILE *, FILE *){
	printf("BWTDecoding...\n");
	return 0;
}
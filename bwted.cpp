#include <stdlib.h>
#include <string.h>

#include "bwted.hpp"

typedef struct {
	char* ptr=NULL;
	int len=0;
} t_str_len;

void t_str_len_clear(t_str_len* s){

	free(s->ptr);
	s->ptr=NULL;
	s->len=0;
}

void t_str_len_copy(t_str_len from, t_str_len* to){

	t_str_len_clear(to);
	to->ptr=(char*)malloc(from.len*sizeof(char));
	memcpy(to->ptr,from.ptr,from.len);
	to->len=from.len;
}

void t_str_len_print(t_str_len s){
	for(int i=0;i<s.len;i++){
		printf("%c", s.ptr[i]);
	}
	printf("\n");
}


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

//finds alphabet index of a char and moves the character to the front of the alphabet
uint8_t getCharIndexAndMoveToFront(char c){

	//first, record index of character
	uint8_t index = -1;
	for(uint8_t i=0; i<alphalength;i++){
		if(alphabet[i]!=c) {continue;}
		index=i;
	}


	//next, move the alphabet (upo to index)
	for(uint8_t i=index; i>0; i--){
		alphabet[i] = alphabet[i-1];
	}

	//finaly, insert the character at the beginning
	alphabet[0] = c;

	return index;
}

void MTFenc(char* input, int length){

	initAlphabet();

	for(int i=0; i<length; i++){
		uint8_t index = getCharIndexAndMoveToFront(input[i]);
		input[i]=index;
	}
}

void MTFdec(char* input, int length){

	initAlphabet();

	for(int i=0;i<length; i++){
		input[i] = alphabet[(uint8_t)input[i]];
		getCharIndexAndMoveToFront(input[i]);
	}
}


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

	for(int i=0; i<input.len; i+=2){

		uint8_t charCnt = input.ptr[i];
		char ch = input.ptr[i+1];
		for(uint8_t j=0; j<charCnt; j++){
			output->ptr[output->len] = ch;
			output->len++;
		}
	}
}



//qsort comparator function for comparing two strings
int comp(const void* elem1, const void* elem2){
    t_str_len e1 = *((t_str_len*)elem1);
    t_str_len e2 = *((t_str_len*)elem2);

    //decide on the first different character
    for(int i=0; i<e1.len; i++){
    	if(e1.ptr[i]>e2.ptr[i]){return 1;}
    	else if(e1.ptr[i]<e2.ptr[i]){return -1;}
    	else {continue;}
    }

    return 0;
}


void BWTenc(t_str_len input,t_str_len* output){

	//alocate memory for the permutations
	t_str_len* perms = (t_str_len*) malloc(input.len*sizeof(t_str_len));
	for(int i=0;i<input.len;i++){
		perms[i].ptr = (char*) malloc(input.len*sizeof(char));
		perms[i].len = input.len;
	}
		
	//the first permutation is the input
	strncpy(perms[0].ptr,input.ptr,input.len);

	//now rotate to get succeeding permutations
	for(int i=1;i<input.len;i++){
		for(int j=0;j<input.len;j++){
			perms[i].ptr[j] = perms[i-1].ptr[j-1<0 ? input.len-1 : j-1];
		}
	}

	//now sort the permutations lexicographicaly
    qsort (perms, input.len, sizeof(t_str_len), comp);

	//allocate memory for output
	output->ptr = (char*) malloc(input.len*sizeof(char));

	//output consists of last char of each permutation after sort
	for(int i=0;i<input.len;i++){
		output->ptr[i] = perms[i].ptr[perms[i].len-1];
		output->len++;
	}
	
	//free memory used
	for(int i=0;i<input.len;i++){
		free(perms[i].ptr);
	}
	free(perms);
}



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
	// MTFenc(input,length);
	// printf("%s (%d)\n", input, length);

	// printf("MTFdec\n");
	// MTFdec(input,length);
	// printf("%s (%d)\n", input, length);

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

	BWTenc(input,&output);

	t_str_len_print(output);


	free(input.ptr);


	return 0;
}


int BWTDecoding (tBWTED *, FILE *, FILE *){
	printf("BWTDecoding...\n");
	return 0;
}
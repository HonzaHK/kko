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

void BWTenc(char* input, int length){

}

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



int BWTEncoding (tBWTED* rec, FILE* ifile, FILE* ofile){
	printf("BWTEncoding...\n");
		
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

	t_str_len_print(input);

	// printf("MTFenc\n");
	// MTFenc(input,length);
	// printf("%s (%d)\n", input, length);

	// printf("MTFdec\n");
	// MTFdec(input,length);
	// printf("%s (%d)\n", input, length);

	printf("RLEenc\n");
	RLEenc(input,&output);
	printRleCode(output);

	t_str_len_copy(output,&input);
	t_str_len_clear(&output);
	printf("RLEdec\n");
	RLEdec(input,&output);
	t_str_len_print(output);

	t_str_len_clear(&input);
	t_str_len_clear(&output);


	return 0;



	// char** perms = (char**) malloc(length*sizeof(char*));
	// for(int i=0;i<length;i++){
	// 	perms[i] = (char*) malloc((length+1)*sizeof(char));
	// 	strncpy(perms[i],input,length);
	// 	perms[i][length] = '\0';
	// }

	// for(int i=1;i<length;i++){
	// 	for(int j=0;j<length;j++){
	// 		perms[i][j] = perms[i-1][j-1<0 ? length-1 : j-1];
	// 	}
	// }

	
	// for(int i=0;i<length;i++){
	// 	printf("%s\n", perms[i]);
	// }
	



	// for(int i=0;i<length;i++){
	// 	free(perms[i]);
	// }
	// free(perms);
	// free(input);




	return 0;
}


int BWTDecoding (tBWTED *, FILE *, FILE *){
	printf("BWTDecoding...\n");
	return 0;
}
#include <stdlib.h>
#include <string.h>

#include "bwted.hpp"


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
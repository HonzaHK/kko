#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "bwt.hpp"


void bwt_print(char* input, int input_len){

	for(int i=0;i<input_len-1;i++){
		printf("%d.", input[i]);
	}

	printf(" [alpha=%d]\n", input[input_len-1]);
}

void print_perms(t_str_len* perms, int cnt_perms){
    printf("PERMS--------------\n");
    for(int i=0;i<cnt_perms;i++){
    	for(int j=0;j<perms[i].len;j++){
    		printf("%d ", perms[i].ptr[j]);
    	}
    	printf("\n");
    }
    printf("-------------------\n");
}


//qsort comparator function for comparing two strings
int comp_strings(const void* elem1, const void* elem2){
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

bool str_equal(char* str1, int str1_len, char* str2, int str2_len){
	
	if(str1_len!=str2_len){
		return false;
	}

	for(int i=0; i<str1_len; i++){
		if(str1[i]!=str2[i]){
			return false;
		}
	}

	return true;
}

int BWTenc(char* input, int input_len, char* output){

	//alocate memory for the permutations
	t_str_len* perms = (t_str_len*) malloc(input_len*sizeof(t_str_len));
	for(int i=0;i<input_len;i++){
		perms[i].ptr = (char*) malloc(input_len*sizeof(char));
		perms[i].len = input_len;
	}
		
	//the first permutation is the input
	for(int i=0; i<input_len; i++){
		perms[0].ptr[i] = input[i];
	}

	//now rotate to get succeeding permutations
	for(int i=1;i<input_len;i++){
		for(int j=0;j<input_len;j++){
			perms[i].ptr[j] = perms[i-1].ptr[j-1<0 ? input_len-1 : j-1];
		}
	}

	//now sort the permutations lexicographicaly
    qsort (perms, input_len, sizeof(t_str_len), comp_strings);

    //find the index of original string among sorted
    //todo: works only for 256 permutations?
    uint16_t orig_index=-1;
    for(int i=0;i<input_len;i++){
    	if(str_equal(input, input_len, perms[i].ptr, perms[i].len)){
    		orig_index=i;
    	}
    }


	//output consists of last char of each permutation after sort
	for(int i=0;i<input_len;i++){
		output[i] = perms[i].ptr[perms[i].len-1];
	}

	//store the original string index
	//todo: little/big endian
	int output_len = input_len + 2;
	output[output_len-2] = orig_index & 0xFF;
	output[output_len-1] = orig_index >> 8;
	
	// printf(">>%d\n", orig_index);
	//free memory used
	for(int i=0;i<input_len;i++){
		free(perms[i].ptr);
	}
	free(perms);

	return output_len;
}


int comp_chars(const void* elem1, const void* elem2){
    char e1 = *((char*)elem1);
    char e2 = *((char*)elem2);

	if(e1>e2) return 1;
	else return -1;

    return 0;
}


int BWTdec(char* input, int input_len, char* output){
	
	//todo: little/big endian
	uint16_t orig_index = (input[input_len-2] & 0xFF) | (uint16_t) input[input_len-1] << 8;
	input_len-=2; //remove the last two bytes (orig index)


	char* sorted;
	sorted = (char*) malloc(input_len*sizeof(char));
	for(int i=0; i<input_len; i++){
		sorted[i] = input[i];
	}

	qsort(sorted, input_len, sizeof(char), comp_chars);

	int alfa = orig_index;
	int output_len = 0;
	while(true){
		char fa = sorted[alfa];
		output[output_len] = fa;
		output_len++;

		int occurence = 0;
		for(int i=0;i<alfa;i++){
			if(sorted[i]==fa){occurence++;}
		}

		int nextAlfa=-1;
		for(int i=0;i<input_len;i++){
			if(input[i]!=fa){continue;}
			if(occurence==0){

			nextAlfa=i;
				break;
			}
			occurence--;
		}
		
		alfa=nextAlfa;
		if(output_len==input_len) break;
	}

	return output_len;
}
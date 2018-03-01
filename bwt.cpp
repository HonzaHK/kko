#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "bwt.hpp"

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
    qsort (perms, input.len, sizeof(t_str_len), comp_strings);

    //find the index of original string among sorted
    //todo: works only for 256 permutations?
    uint8_t orig_index=-1;
    for(int i=0;i<input.len;i++){
    	if(strcmp(input.ptr,perms[i].ptr)==0){
    		orig_index=i;
    	}
    }

	//allocate memory for output (+1 for storing the original string index)
	output->ptr = (char*) malloc(input.len*sizeof(char)+1);

	//output consists of last char of each permutation after sort
	for(int i=0;i<input.len;i++){
		output->ptr[i] = perms[i].ptr[perms[i].len-1];
		output->len++;
	}

	//store the original string index
	output->ptr[input.len] = orig_index;
	output->len++;
	
	//free memory used
	for(int i=0;i<input.len;i++){
		free(perms[i].ptr);
	}
	free(perms);
}


int comp_chars(const void* elem1, const void* elem2){
    char e1 = *((char*)elem1);
    char e2 = *((char*)elem2);

	if(e1>e2) return 1;
	else return -1;

    return 0;
}


void BWTdec(t_str_len input, t_str_len* output){

	int orig_index = input.ptr[input.len-1];
	input.len--; //remove the last char (orig index)

	t_str_len sorted;
	t_str_len_copy(input,&sorted);
	qsort(sorted.ptr, sorted.len, sizeof(char), comp_chars);

	int alfa = orig_index;
	int cnt_found = 0;
	while(true){
		char fa = sorted.ptr[alfa];
		printf("%c\n", fa);
		cnt_found++;

		int occurence = 0;
		for(int i=0;i<alfa;i++){
			if(sorted.ptr[i]==fa){occurence++;}
		}

		int nextAlfa=-1;
		for(int i=0;i<input.len;i++){
			if(input.ptr[i]!=fa){continue;}
			if(occurence==0){

			nextAlfa=i;
				break;
			}
			occurence--;
		}
		
		alfa=nextAlfa;
		if(cnt_found==input.len) break;
	}


}
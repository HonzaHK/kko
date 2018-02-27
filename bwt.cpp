#include <stdio.h>
#include <string.h>
#include "bwt.hpp"

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


//ulozim radek s puvodnim vstupem v serazenych permutacich


void BWTdec(t_str_len input, t_str_len* output){

	t_str_len sorted;
	t_str_len_copy(input,&sorted);





}
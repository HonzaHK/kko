#include <stdio.h>
#include <stdint.h>

#include "huf.hpp"

typedef struct {
	char ch;
	int cnt;
} t_freq_record;

typedef struct {
	t_freq_record* ptr;
	int size;
} t_freq_table;

void freq_table_print(t_freq_table freq_table){
	for(int i=0;i<freq_table.size;i++){
		printf("%c: %d\n",freq_table.ptr[i].ch,freq_table.ptr[i].cnt);
		
	}
}

t_freq_record* freq_table_find(t_freq_table* freq_table, char ch){
	t_freq_record* fr = NULL;
	for(int j=0;j<freq_table->size;j++){
		if(freq_table->ptr[j].ch!=ch){continue;}
		fr = &freq_table->ptr[j];
		break;
	}

	return fr;
}

void freq_table_calc(t_freq_table* freq_table, t_str_len input){

	for(int i=0;i<input.len;i++){
		t_freq_record* fr = freq_table_find(freq_table,input.ptr[i]);

		if(fr==NULL){
			freq_table->ptr = (t_freq_record*)realloc(freq_table->ptr,((freq_table->size+1)*sizeof(t_freq_record)));
			fr = &freq_table->ptr[freq_table->size];
			fr->ch = input.ptr[i];
			freq_table->size++;
		}
		fr->cnt++;
	}


}


//qsort comparator function for sorting character frequency table
int freq_comp(const void* elem1, const void* elem2){
    t_freq_record e1 = *((t_freq_record*)elem1);
    t_freq_record e2 = *((t_freq_record*)elem2);

	if(e1.cnt<e2.cnt){return 1;}
	else {return -1;}


    return 0;
}

// void HUFenc(t_str_len input, t_str_len* output){

// 	t_freq_table freq_table;
// 	freq_table.ptr = NULL;
// 	freq_table.size = 0;
	

// 	freq_table_calc(&freq_table,input);

//     qsort (freq_table.ptr, freq_table.size, sizeof(t_freq_record), freq_comp);

// 	freq_table_print(freq_table);
// }

// void HUFdec(t_str_len input, t_str_len* output){
	
// }

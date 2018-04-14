//author: Jan Kubis / xkubis13
//file: main.c
//created: 2018/02/23
//purpose: entry point for bwted

#include <stdio.h>
#include <string.h>

#include "bwted.hpp"

using namespace std;

enum emode{ //bwted mode (encode/decode)
	undefined,encode,decode
};

typedef struct { //structure for storing command line arguments
	char* ifName=NULL;
	char* ofName=NULL;
	char* lfName=NULL;
	emode mode = undefined; //user has to specify mode

} clargs_t;

void printHelp(){
	printf("Name: Komprese textovych souboru s vyuzitim BWT\n");
	printf("Author: Jan Kubis, xkubis13\n\n");
	
	printf("-i <ifile>: specify input file (STDIN implicitly)\n");
	printf("-o <ofile>: specify output file (STDOUT implicitly)\n");
	printf("-l <logfile>: specify log file\n");
	printf("-c | -x : encode | decode\n");

}

int parseArgs(int argc, char* argv[], clargs_t *clargs){

	for(int i=1;i<argc;i++){
		if(strcmp(argv[i],"-i")==0){
			if(argv[i++]==NULL){return 1;} //move to arg value && check value missing
			clargs->ifName=argv[i];
		}
		else if(strcmp(argv[i],"-o")==0){
			if(argv[i++]==NULL){return 1;} //move to arg value && check value missing
			clargs->ofName=argv[i];
		}
		else if(strcmp(argv[i],"-l")==0){
			if(argv[i++]==NULL){return 1;} //move to arg value && check value missing
			clargs->lfName=argv[i];
		}
		else if(strcmp(argv[i],"-c")==0){
			clargs->mode=encode;
		}
		else if(strcmp(argv[i],"-x")==0){
			clargs->mode=decode;
		}
		else{
			return 1;
		}
	}

	return 0;
}

int main(int argc, char* argv[]){

	if(strcmp(argv[1],"-h")==0){
		printHelp();
		return 0;
	}

	clargs_t clargs;
	if(parseArgs(argc,argv,&clargs)!=0){
		printf("Invalid arguments. Run with -h to display help.\n");
		return 0;
	}

	if(clargs.mode==undefined){
		printf("Mode not specified. Run with -h to display help.\n");
		return 0;
	}

	//open input file or set it to stdin
	FILE* ifile = clargs.ifName!=NULL ? fopen(clargs.ifName,"rb") : stdin;
	//open output file or set it to stdout
	FILE* ofile = clargs.ofName!=NULL ? fopen(clargs.ofName,"wb") : stdout;
	//prepare struct for storing log info
	tBWTED record;
	record.uncodedSize=0;
	record.codedSize=0;

	if(clargs.mode==encode){
		BWTEncoding(&record,ifile,ofile);
	}
	else if(clargs.mode==decode){
		BWTDecoding(&record,ifile,ofile);
	}

	fclose(ifile);
	fclose(ofile);

	if(clargs.lfName!=NULL){
		FILE* lfile = fopen(clargs.lfName,"w");
		fprintf(lfile, "login = xkubis13\n" );
		fprintf(lfile, "uncodedSize = %ld\n", record.uncodedSize );
		fprintf(lfile, "codedSize = %ld\n", record.codedSize );
	}

	return 0;
}
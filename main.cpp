#include <stdio.h>
#include <string.h>

#include "bwted.hpp"

using namespace std;

enum emode{ //bwted mode (encode/decode)
	undefined,encode,decode
};

typedef struct { //structure for storing command line arguments
	char* ifName;
	char* ofName;
	char* lfName;
	emode mode = undefined; //user has to specify mode

} clargs_t;

void printHelp(){
	printf("Name: Komprese textovych souboru s vyuzitim BWT\n");
	printf("Author: Jan Kubis, xkubis13\n\n");

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
	tBWTED record;

	if(clargs.mode==encode){
		int res = BWTEncoding(&record,ifile,ofile);
		printf("encode: %d\n",res);
	}
	else if(clargs.mode==decode){
		int res = BWTDecoding(&record,ifile,ofile);
		printf("decode: %d\n",res);
	}

	fclose(ifile);
	fclose(ofile);
	// todo: write to logfile, if present
	// todo: close files
	return 0;
}
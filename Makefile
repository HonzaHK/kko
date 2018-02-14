CC=g++
CFLAGS=-std=c++11 -Wall -Wextra -pedantic

EXE=bwted

all: exe

lib:

exe: lib
	@echo "--COMPILE EXE------------------------------------------------"
	@${CC} ${CFLAGS} main.cpp bwted.cpp bwted.hpp -o ${EXE}

run: exe
	@echo "--EXECUTE----------------------------------------------------"
	@./${EXE} -i test/test.txt -o test/test_out.txt -l test/test_log.txt -c

clean:
	rm -rf ${EXE} test/*_out.txt

zip:
	echo zip
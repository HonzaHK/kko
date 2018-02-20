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
	@./${EXE} ${args} -o test/test_out.txt -l test/test_log.txt -c

memtest: exe
	@echo "--EXECUTE----------------------------------------------------"
	@valgrind --leak-check=full --show-leak-kinds=all -v ./${EXE} -i test/banana.txt -o test/test_out.txt -l test/test_log.txt -c


clean:
	rm -rf ${EXE} test/*_out.txt

zip:
	echo zip
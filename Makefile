CC=g++
CFLAGS=-std=c++11 -Wall -Wextra -pedantic

EXE=bwted

all: exe

lib:

exe: lib
	@echo "--COMPILE EXE------------------------------------------------"
	@${CC} ${CFLAGS} *.cpp *.hpp -o ${EXE}

run: exe
	@echo "--EXECUTE----------------------------------------------------"
	@./${EXE} ${args} -l test/test_log.txt

memtest: exe
	@echo "--EXECUTE----------------------------------------------------"
	@valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes -v ./${EXE} -i test/banana.txt -o test/test_out.txt -l test/test_log.txt -c


clean:
	rm -rf ${EXE} test/*.out.txt

zip:
	echo zip
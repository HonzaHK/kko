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
	@./${EXE} -c -i test/test.txt -o test/test_enc.out.txt -l test/test_log.txt
	@./${EXE} -x -i test/test_enc.out.txt -o test/test_dec.out.txt -l test/test_log.txt
	# diff test/test.txt test/test_dec.out.txt

memtest: exe
	@echo "--EXECUTE----------------------------------------------------"
	@valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes -v ./${EXE} -i test/banana.txt -o test/test_out.txt -l test/test_log.txt -c


clean:
	rm -rf ${EXE} test/*.out.txt

zip:
	echo zip
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
	@./${EXE} -c -i test/test.txt -o test/test_enc.txt -l test/log_enc.txt
	@echo "-- encode done ----------------------------------------------"
	@./${EXE} -x -i test/test_enc.txt -o test/test_dec.txt -l test/log_dec.txt
	@echo "-- decode done ----------------------------------------------"
	diff test/test.txt test/test_dec.txt

memtest: exe
	@echo "--EXECUTE----------------------------------------------------"
	@valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes -v ./${EXE} -i test/banana.txt -o test/test_out.txt -l test/test_log.txt -c


clean:
	rm -rf ${EXE} test/*.out.txt

zip:
	echo zip
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -pedantic

EXE=bwted

all: exe

lib:

exe: lib
	@echo "--COMPILE EXE------------------------------------------------"
	@${CC} ${CFLAGS} *.c *.h -o ${EXE}

run: exe
	@echo "--EXECUTE----------------------------------------------------"
	@./${EXE} -c -i test/test.txt -o test/test_enc.txt -l test/log_enc.txt
	@echo "-- encode done ----------------------------------------------"
	@./${EXE} -x -i test/test_enc.txt -o test/test_dec.txt -l test/log_dec.txt
	@echo "-- decode done ----------------------------------------------"
	diff test/test.txt test/test_dec.txt

memtest: exe
	@echo "--EXECUTE----------------------------------------------------"
	@valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes -v ./${EXE} -i test/test.txt -o test/test_enc.txt -l test/test_log.txt -c


clean:
	rm -rf ${EXE} test/*.out.txt

zip:
	zip kko.proj2.xkubis13.zip Makefile doc.pdf main.c bwt.c bwt.h bwted.c bwted.h huf.c huf.h mtf.c mtf.h rle.c rle.h types.c types.h
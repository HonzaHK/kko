CC=g++
CFLAGS=-std=c++11 -Wall -Wextra -pedantic

EXE=bwted

all: exe

lib:
	

exe: lib
	${CC} ${CFLAGS} main.cpp -o ${EXE}

run: exe
	./${EXE}
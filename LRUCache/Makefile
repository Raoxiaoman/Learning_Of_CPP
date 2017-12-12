all:
	${CXX} ${CFLAG} ${SRC} -o ${TARGET} ${INC}

CXX    = g++
CFLAG  += -g -std=c++0x -Wno-deprecated
TARGET = test
SRC    = main.cc
OJBS   = ${SRC:.cc=.o}
INC    = -I .

clean:
	rm -rf ${TARGET} ${OJBS}

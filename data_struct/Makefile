all:
	${CXX} ${CFLAG} ${SRC} -o ${TARGET}

CXX    = g++
CFLAG  += -g -std=c++11
TARGET = test
SRC    = $(sc)
OJBS   = ${SRC:.cpp=.o}

clean:
	rm -rf ${TARGET} ${OJBS}

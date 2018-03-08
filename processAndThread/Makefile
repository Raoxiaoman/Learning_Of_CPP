source_name=$(sc)
all:
	${CXX} ${CFLAG} ${SRC} -o ${TARGET}

CXX    = g++
CFLAG  += -g -std=c++11 -pthread
TARGET = test
SRC    = $(source_name)
OJBS   = ${SRC:.cpp=.o}

clean:
	rm -rf ${TARGET} ${OJBS}

PROG = test.cpp
TARGET = proj
HEADER = ../include/
CXX = g++
CXX_VERSION = -std=c++17

${TARGET} : ${PROG} ${HEADER}
	${CXX} ${CXX_VERSION} -o ${TARGET} ${PROG}

run :
	./proj

clean :
	rm -r ${TARGET}

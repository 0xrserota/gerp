#
#
#  COMP 15 
#
#  Makefile
#  Makefile for gerp
#  Modified By (UTLN): rserot01
#          On       : 11/24/2017
#
#

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11 -O2
LDFLAGS  = -g3

HDRS = stringProcessing.h DirNode.h FSTree.h MainHashTable.h ChainLinkedList.h \
		WordVector.h 

SRCS = main.cpp stringProcessing.cpp MainHashTable.cpp ChainLinkedList.cpp \
		WordVector.cpp

OBJS = DirNode.o FSTree.o stringProcessing.o MainHashTable.o ChainLinkedList.o \
		WordVector.o main.o

gerp:  ${OBJS} ${HDRS} ${SRCS}
	${CXX} ${CXXFLAGS} ${LDFLAGS} -o gerp ${OBJS} 


main.o:   	MainHashTable.h MainHashTable.cpp ChainLinkedList.cpp WordVector.cpp \
			FSTree.h stringProcessing.h stringProcessing.cpp  

stringProcessing.o: 	stringProcessing.h stringProcessing.cpp
MainHashTable.o:	MainHashTable.h ChainLinkedList.h ChainLinkedList.cpp 
ChainLinkedList.o:	ChainLinkedList.h WordVector.h WordVector.cpp
WordVector.o:	WordVector.h WordVector.cpp


valgrind:  gerp
	valgrind ./gerp

clean:
	rm -rf gerp ${OBJS} *~ *.dSYM


provide:
	provide comp15 proj2part3 README Makefile main.cpp ChainLinkedList.h \
		ChainLinkedList.cpp MainHashTable.h MainHashTable.cpp WordVector.cpp \
		WordVector.h stringProcessing.h stringProcessing.cpp testMainHashTable.cpp \
		testChainLinkedList.cpp testWordVector.cpp DirNode.o DirNode.h FSTree.h FSTree.o


# End Makefile
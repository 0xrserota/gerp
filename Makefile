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

HDR_DIR = src
HDRS = $(wildcard $(HDR_DIR)/*.h)
SRC_DIR = src/impl
OBJ_DIR = obj
SRCS = $(wildcard $(SRC_DIR)/*.cc)
OBJS =  $(patsubst $(SRC_DIR)/%.cc, $(OBJ_DIR)/%.o, $(SRCS))
BIN_DIR = bin

IFLAGS  = -I$(HDR_DIR)

$(OBJ_DIR)/main.o:   	$(SRC_DIR)/main.cc $(HDR_DIR)/MainHashTable.h $(SRC_DIR)/MainHashTable.cc \
			$(SRC_DIR)/ChainLinkedList.cc $(SRC_DIR)/WordVector.cc $(HDR_DIR)/FSTree.h \
			$(HDR_DIR)/StringProcessing.h $(SRC_DIR)/StringProcessing.cc $(SRC_DIR)/DirNode.cc \
			$(HDR_DIR)/DirNode.h
		${CXX} ${CXXFLAGS} -c $(IFLAGS) $(SRC_DIR)/main.cc -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/DirNode.o: $(HDR_DIR)/DirNode.h $(SRC_DIR)/DirNode.cc
		${CXX} ${CXXFLAGS} -c $(IFLAGS) $(SRC_DIR)/DirNode.cc -o $(OBJ_DIR)/DirNode.o

$(OBJ_DIR)/FSTree.o: $(HDR_DIR)/FSTree.h $(SRC_DIR)/FSTree.cc
		${CXX} ${CXXFLAGS} -c $(IFLAGS) $(SRC_DIR)/FSTree.cc -o $(OBJ_DIR)/FSTree.o

$(OBJ_DIR)/StringProcessing.o: 	$(HDR_DIR)/stringProcessing.h $(SRC_DIR)/stringProcessing.cc
		${CXX} ${CXXFLAGS} -c $(IFLAGS) $(SRC_DIR)/StringProcessing.cc -o $(OBJ_DIR)/StringProcessing.o

$(OBJ_DIR)/MainHashTable.o:	$(HDR_DIR)/MainHashTable.h $(HDR_DIR)/ChainLinkedList.h $(SRC_DIR)/ChainLinkedList.cc 
		${CXX} ${CXXFLAGS} -c $(IFLAGS) $(SRC_DIR)/MainHashTable.cc -o $(OBJ_DIR)/MainHashTable.o

$(OBJ_DIR)/ChainLinkedList.o:	$(HDR_DIR)/ChainLinkedList.h $(HDR_DIR)/WordVector.h $(SRC_DIR)/WordVector.cc
		${CXX} ${CXXFLAGS} -c $(IFLAGS) $(SRC_DIR)/ChainLinkedList.cc -o $(OBJ_DIR)/ChainLinkedList.o

$(OBJ_DIR)/WordVector.o:	$(HDR_DIR)/WordVector.h $(SRC_DIR)/WordVector.cc
		${CXX} ${CXXFLAGS} -c $(IFLAGS) $(SRC_DIR)/WordVector.cc -o $(OBJ_DIR)/WordVector.o

gerp:  ${OBJS} ${HDRS} ${SRCS}
	${CXX} ${CXXFLAGS} ${LDFLAGS} $(IFLAGS) -o $(BIN_DIR)/gerp ${OBJS}

valgrind:  gerp
	valgrind ./gerp

clean:
	rm -rf gerp ${OBJS} *~ *.dSYM

# End Makefile
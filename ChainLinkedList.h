/*
 *
 *  COMP 15 Project 2: Gerp - It's Like grep But Something Is Off
 *
 *  ChainLinkedList.h
 *
 *  ChainLinkedList class is the container for handling hash collisions
 *  in the MainHashTable. Contains ChainNode s which contain keys , values,
 *  next ChainNode pointers, and pointers to a WordVector instance.
 *  This class also stores the pathIndices, lineIndices, caseIndices, lineNums 
 *  vectors. There is a front ChainNode pointer as well.
 *  
 *	
 *  Modified By (UTLN): rserot01
 *           On       : 11/29/2017
 */


#include "WordVector.h"
#include <iostream>

#ifndef _CHAINLINKEDLIST_
#define _CHAINLINKEDLIST_

using namespace std;

class ChainLinkedList {

	public:

		ChainLinkedList();
		~ChainLinkedList();

		bool isEmpty();
		bool isInList(string key);
		bool isCaseInList(string key, string query);
		void addToWordList(string, string, int, size_t, size_t);
		void addAtFront(string, int, string, int, size_t, size_t);

		vector<int> *getLineNums(string);
		vector<size_t> *getLineIndices(string);
		vector<size_t> *getPathIndices(string);

		vector<size_t> *getCaseIndices(string, string);
		vector<int> *getCaseLineNums(string, vector<size_t>*);
		vector<size_t> *getCaseLineIndices(string, vector<size_t>*);
		vector<size_t> *getCasePathIndices(string, vector<size_t>*);

		size_t getWordListLength(string key);
		void moveFrontNode(ChainLinkedList*);
		std::string getFrontKey();
		size_t getChainLength();

	private:

		struct ChainNode {

			std::string key;
			int value;
			WordVector *wv;
			ChainNode *next;
		};

		size_t chainLength;

		ChainNode *front;
		ChainNode *cn;

		// Stores the indices of the pathVec where each line is stored
		vector<size_t> *pathIndices; 

		// Stores the indices of the lineVec where each line is stored
		vector<size_t> *lineIndices;

		// Stores the indices of the same case
		vector<size_t> *caseIndices;

		// Stores the line numbers 
		vector<int> *lineNums;

		ChainNode* getChainNode(string key);
		void addNodeAtFront(ChainNode* cn);
		ChainNode* removeFromFront();
};

#endif

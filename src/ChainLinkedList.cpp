/*
 *
 *  COMP 15 Project 2: Gerp - It's Like grep But Something Is Off
 *
 *  main.cpp
 *  Main function for gerp
 *	
 *  Modified By (UTLN): rserot01
 *           On       : 11/29/2017
 *
 */

#include "ChainLinkedList.h"
#include <iostream>

using namespace std;

/* Default constructor 
ChainLinkedList() */
ChainLinkedList::ChainLinkedList()
{
	front = NULL;
	chainLength = 0;

	pathIndices = new vector<size_t>;
	caseIndices = new vector<size_t>;
	lineIndices = new vector<size_t>;
	lineNums    = new vector<int>;
}

/* Destructor
~ChainLinkedList() */
ChainLinkedList::~ChainLinkedList()
{
	// Memory Leaks here?
	cn = front;
	while (!isEmpty())
	{
		cn = front->next;
		delete front->wv;
		delete front;
		front = cn;
	}

	delete pathIndices;
	delete lineIndices;
	delete caseIndices;
	delete lineNums;
}

/*	Checks if front points to NULL, indicating empty list 
returns a bool
bool isEmpty() */
bool ChainLinkedList::isEmpty()
{
	if (front == NULL)
		return true;

	else return false;
}

/*  Adds a new ChainNode to the front of list 
void addToFront(int, string, string, string) */
void ChainLinkedList::addAtFront(string key, int value, string word, 
								 int lineNum, size_t lineInd, size_t pathInd)
{
	// Initializing new node
	ChainNode *cn = new ChainNode;
	cn->key = key;
	cn->value = value;
	cn->next = front;
	front = cn;

	++chainLength;

	// Allocate new WordVector and add this word at back of WordList
	cn->wv = new WordVector;
	cn->wv->addAtBack(word, lineNum, lineInd, pathInd);
}


/* Adds an instance of a key already in the ChainLinkedList
to the WordVector::wordList
void addToWordList(string, string, int, size_t, size_t) */
void ChainLinkedList::addToWordList(string key, string word, int lineNum, size_t lineInd,
									size_t pathInd)
{
	ChainNode *cn = getChainNode(key);
	cn->wv->addAtBack(word, lineNum, lineInd, pathInd);
}



/* Checks if a key is in the ChainLinkedList  
bool isInList(string) */
bool ChainLinkedList::isInList(string key)
{
	if (isEmpty())
		return false;

	ChainNode *cn = front;
	while (cn != NULL)
	{
		if (cn->key == key)
			return true;
		
		cn = cn->next;
	}
	
	return false;
}

/* Checks if an exact match of a query is in the ChainLinkedList
bool isCaseInList(string, string) */
bool ChainLinkedList::isCaseInList(string key, string query)
{
	if (isInList(key))
	{
		if (getChainNode(key)->wv->isInList(query))
			return true;
	}

	return false;
}


/* 	Gets the length of the wordList at the node specified
by calling WordVector::getListSize(), returns the length.
size_t getWordListLength(string) */
size_t ChainLinkedList::getWordListLength(string key)
{

	ChainNode *cn = getChainNode(key);
	return cn->wv->getListSize();
}



/* vector<int* getLineNums(string) */
vector<int> *ChainLinkedList::getLineNums(string key)
{
	ChainNode *cn = getChainNode(key);
	size_t listSize = cn->wv->getListSize();
	
	for (size_t i = 0; i < listSize; ++i)
	{
		int lineNum = cn->wv->getLineNum(i);
		lineNums->push_back(lineNum);
	} 

	return lineNums;
}

/* vector<size_t>* getLineIndices(string) */
vector<size_t> *ChainLinkedList::getLineIndices(string key)
{
	ChainNode* cn = getChainNode(key);
	size_t listSize = cn->wv->getListSize();

	for (size_t i = 0; i < listSize; ++i)
	{
		int lineInd = cn->wv->getLineIndex(i);
		lineIndices->push_back(lineInd);
	} 

	return lineIndices;
}

/* vector<size_t>* getPathIndices(string) */
vector<size_t> *ChainLinkedList::getPathIndices(string key)
{
	ChainNode* cn = getChainNode(key);
	size_t listSize = cn->wv->getListSize();

	for (size_t i = 0; i < listSize; ++i)
	{
		size_t pathIndex = cn->wv->getPathIndex(i);
		pathIndices->push_back(pathIndex); 
	} 

	return pathIndices;
}

/* vector<size_t>* getCaseIndices(string, string) */
vector<size_t> *ChainLinkedList::getCaseIndices(string key, string query)
{
	ChainNode* cn = getChainNode(key);
	
	for (size_t i = 0; i < cn->wv->getListSize(); ++i)
	{
		if (cn->wv->getWord(i) == query)
		{
			caseIndices->push_back(i);
		}
	}

	return caseIndices;
}

/* vector<int>* getCaseLineNums(string, vector<size_t>*) */
vector<int> *ChainLinkedList::getCaseLineNums(string key, vector<size_t> *inds)
{
	size_t indsSize = inds->size();
	ChainNode *cn = getChainNode(key);

	for (size_t i = 0; i < indsSize; ++i)
	{
		size_t k = (*inds)[i];
		int lineNum = cn->wv->getLineNum(k);
		lineNums->push_back(lineNum);
	} 

	return lineNums;
}

/* vector<size_t>* getCaseLineIndices(string, vector<size_t*) */
vector<size_t> *ChainLinkedList::getCaseLineIndices(string key, 
													vector<size_t> *inds)
{
	size_t indsSize = inds->size();
	ChainNode *cn = getChainNode(key);

	for (size_t i = 0; i < indsSize; ++i)
	{
		size_t k = (*inds)[i];
		size_t lineIndex = cn->wv->getLineIndex(k);
		lineIndices->push_back(lineIndex);
	} 

	return lineIndices;
}

/* vector<size_t>* getCasePathIndices(string, vector<size_t>*) */
vector<size_t> *ChainLinkedList::getCasePathIndices(string key,
													 vector<size_t> *inds)
{
	size_t indsSize = inds->size();
	
	ChainNode *cn = getChainNode(key);

	for (size_t i = 0; i < indsSize; ++i)
	{
		size_t k = (*inds)[i];
		size_t pathIndex = cn->wv->getPathIndex(k);
		pathIndices->push_back(pathIndex); 
	} 

	return pathIndices;
}

/* Returns the length of the chain list
size_t getChainLength() */
size_t ChainLinkedList::getChainLength()
{
	return chainLength;
}

/*  
void moveFrontNode(ChainLinkedList*) */
void ChainLinkedList::moveFrontNode(ChainLinkedList *dstList)
{
	// 
	ChainNode *cn = removeFromFront();
	dstList->addNodeAtFront(cn);
}

/* void addNodeAtFront(ChainNode*) */
void ChainLinkedList::addNodeAtFront(ChainLinkedList::ChainNode *cn)
{
	cn->next = front;
	front = cn;
}

/* ChainNode* getChainNode(string) */
ChainLinkedList::ChainNode* ChainLinkedList::getChainNode(string key)
{
	// Catches error if function called on non-existent key 
	if(not isInList(key))
		throw runtime_error("Cannot return ChainNode* with value == NULL");

	ChainNode *cn = front;
	while (cn != NULL)
	{
		if (cn->key == key)
			return cn;

		cn = cn->next;
	}

	return NULL;
}

/* 
ChainNode* removeFromFront() */
ChainLinkedList::ChainNode* ChainLinkedList::removeFromFront()
{
	ChainNode *cn = front;
	front = front->next;
	cn->next = NULL;
	return cn;
}

/* Returns the key stored in the front node
string getFrontKey() */
string ChainLinkedList::getFrontKey()
{
	return front->key;
}
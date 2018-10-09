/*
 *
 *  COMP 15 Project 2: Gerp - It's Like grep But Something Is Off
 *
 *  MainHashTable.cpp
 *  MainHashTable class implementation
 *	
 *  Modified By (UTLN): rserot01
 *           On       : 11/29/2017
 *
 */


#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "MainHashTable.h"
#include "ChainLinkedList.h"

using namespace std;

/*  Initializes vector size to 83, allocates a ChainLinkedList
	at each index 
MainHashTable() */
MainHashTable::MainHashTable()
{
	for (size_t i = 0; i < 83; ++i)
	{
		tableVec.push_back(new ChainLinkedList);
	}
}

/*  Deletes each LineNode in lineVec, deletes each ChainLinkedList in the 
	vector 
~MainHashTable() */ 
MainHashTable::~MainHashTable()
{
	clearTable();

	for (size_t i = 0; i < lineVec.size(); ++i)
	{
		delete lineVec[i];
	}
}

/* size_t getTableSize() */
size_t MainHashTable::getTableSize()
{
	size_t tableSize = tableVec.size();
	return tableSize;
}

/* size_t addToPathVec(string) */
size_t MainHashTable::addToPathVec(string path)
{
	pathVec.push_back(path);
	return pathVec.size() - 1;
}

/* size_t addToLineVec(string) */
size_t MainHashTable::addToLineVec(string line)
{	
	LineNode* ln = new LineNode;
	ln->beenPrinted = false;
	ln->line = line;
	lineVec.push_back(ln);

	return lineVec.size() - 1;
}

/* void resetBeenPrinted() */
void MainHashTable::resetBeenPrinted()
{
	for (size_t i = 0; i < beenPrintedLineInds.size(); ++i)
	{
		size_t lineInd = beenPrintedLineInds[i];
		lineVec[lineInd]->beenPrinted = false;
	}

	beenPrintedLineInds.clear();
}

/* void addToTable(string, int, size_t, size_t) */
void MainHashTable::addToTable(string word, int lineNum, size_t lineIndex,
 								size_t pathIndex)
{
	string key = toLowercase(word);
	size_t value = hashFunction(key, tableVec.size());

	if (isStored(word))
	{
		tableVec[value]->addToWordList(key, word, lineNum, lineIndex, pathIndex);
	}

	else
	{
		tableVec[value]->addAtFront(key, value, word, lineNum, lineIndex,
									 pathIndex);

		// Checking length of list added to
		size_t chainLength = tableVec[value]->getChainLength();
		
		if (chainLength > 4)
			expand();	
	}
}

/* size_t hashFunction(string, size_t) */
size_t MainHashTable::hashFunction(string word, size_t tableSize)
{
	string key = toLowercase(word);
	size_t value = wordHash(key) % tableSize;

	return value;
}

/* bool isStored(string) */
bool MainHashTable::isStored(string query)
{
	string key   = toLowercase(query);
	size_t value = hashFunction(query, tableVec.size());

	if (tableVec[value]->isInList(key))
	{
		return true;
	}

	else
		return false; 
}

/* bool isCaseStored(string) */
bool MainHashTable::isCaseStored(string query)
{
	string key   = toLowercase(query);
	size_t value = hashFunction(query, tableVec.size());

	if (tableVec[value]->isCaseInList(key, query))
		return true;

	else
		return false;
}

/* Prints every word instance in WordVector::wordList of a key
 void printWord(string) */
void MainHashTable::printWord(string query)
{
	string key = toLowercase(query);

	if (isStored(key))
	{
		size_t value = hashFunction(key, tableVec.size());
		size_t arraySize = tableVec[value]->getWordListLength(key);
		vector<int> *lineNums = tableVec[value]->getLineNums(key);
		vector<size_t> *lineIndices = tableVec[value]->getLineIndices(key);
		vector<size_t> *pathIndices = tableVec[value]->getPathIndices(key);

		for (size_t i = 0; i < arraySize; ++i)
		{
			size_t lineIndex = (*lineIndices)[i];

			if (!lineVec[lineIndex]->beenPrinted)
			{
				int lineNum = (*lineNums)[i];
				size_t pathIndex = (*pathIndices)[i];
				const char* path = pathVec[pathIndex].c_str();
				const char* line = lineVec[lineIndex]->line.c_str();

				lineVec[lineIndex]->beenPrinted = true;
				beenPrintedLineInds.push_back(lineIndex);

				printf("%s:%d: %s\n", path, lineNum, line);
			}
		}
	}
	else
	{	
		if (query == "")
			cout << "\"\"" << " Not Found." << endl;

		else 
			cout << query << " Not Found." << endl;
	}
}

/* void printCaseWord(string) */
void MainHashTable::printCaseWord(string query)
{ 
	if (isCaseStored(query))
	{
		string key   = toLowercase(query);
		size_t value = hashFunction(query, tableVec.size());

		vector<size_t> *caseIndices = tableVec[value]->getCaseIndices(key, query);
		vector<int>    *lineNums  = tableVec[value]->getCaseLineNums(key, caseIndices);
		vector<size_t> *lineIndices = tableVec[value]->getCaseLineIndices(key, caseIndices);
		vector<size_t> *pathIndices = tableVec[value]->getCasePathIndices(key, caseIndices);

		for (size_t i = 0; i < caseIndices->size(); ++i)
		{
			size_t lineIndex = (*lineIndices)[i];

			if (!lineVec[lineIndex]->beenPrinted)
			{
				int lineNum = (*lineNums)[i];
				size_t pathIndex = (*pathIndices)[i];
				const char* path = pathVec[pathIndex].c_str();
				const char* line = lineVec[lineIndex]->line.c_str();

				lineVec[lineIndex]->beenPrinted = true;
				beenPrintedLineInds.push_back(lineIndex);

				printf("%s:%d: %s\n", path, lineNum, line);
			}
		}
	}
	else
	{
		if (query == "")
			cout << "\"\"" << " Not Found. Try with @insensitive or @i." << endl;

		else
			cout << query << " Not Found. Try with @insensitive or @i." << endl;
	}
}

/* void expand() */
void MainHashTable::expand()
{
	//Expanding capacity
	size_t newSize = (tableVec.size() * 2) + 1;
	vector<ChainLinkedList*> tmp;

	for (size_t i = 0; i < newSize; ++i)
	{
		tmp.push_back(new ChainLinkedList);
	}

	//Rehashing data
	for (size_t i = 0; i < tableVec.size(); ++i)
	{
		ChainLinkedList *cll = tableVec[i];
		while (!cll->isEmpty())
		{
			string key = cll->getFrontKey();
			size_t value = hashFunction(key, tmp.size());
			cll->moveFrontNode(tmp[value]);
		}
	}

	// Deletes the old data in tableVec 
	clearTable();
	// Vector copy constructor copies tmp to tableVec
	tableVec = tmp;
	// ~vector() will delete tmp since tmp goes out of scope here
}

/* Deletes all the ChainLinkedLists in a tableVec
void clearTable() */
void MainHashTable::clearTable()
{
	for (size_t i = 0; i < tableVec.size(); ++i)
	{
		delete tableVec[i];
	}
}

/* string toLowercase(string word) */
string MainHashTable::toLowercase(string word)
{
	for (size_t i = 0; i < word.length(); ++i)
	{
		word[i] = tolower(word[i]);
	}

	return word;
}
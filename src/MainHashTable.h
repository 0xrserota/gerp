/*
 *
 *  COMP 15 Project 2: Gerp - It's Like grep But Something Is Off
 *
 *  MainHashTable.h
 *
 *  MainHashTable is the hash table class that uses ChainLinkedLists to
 *  handle collisions. Can be expanded. Uses std::hash function to hash keys.
 *	
 *	
 *  Modified By (UTLN): rserot01
 *           On       : 11/29/2017
 */

#ifndef MAINHASHTABLE_H
#define MAINHASHTABLE_H

#include "ChainLinkedList.h"
#include <vector>
#include <string>

using namespace std;



class MainHashTable {

	public:

		MainHashTable();
		~MainHashTable();

		void addToTable(string, int, size_t, size_t);
		bool isStored(string);
		bool isCaseStored(string);
		string toLowercase(string);
		void printWord(string);
		void printCaseWord(string);	

		size_t addToPathVec(string);
		size_t addToLineVec(string);
		void resetBeenPrinted();

		size_t getTableSize();

	private:

		vector<ChainLinkedList*> tableVec;
		vector<string> pathVec;

		struct LineNode {

			bool beenPrinted;
			string line;
		};

		vector<LineNode*> lineVec;
		vector<size_t> beenPrintedLineInds;

		hash<string> wordHash;

		size_t hashFunction(string, size_t);
		void clearTable();
		void expand();
};

#endif
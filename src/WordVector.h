/*
 *
 *  COMP 15 Project 2: Gerp - It's Like grep But Something Is Off
 *
 *  WordVector.h
 *  
 *	WordVector class stores each instance of the same key in WordNodes, 
 *	including the word itself, the lineNum where the word appears, the index
 *  in lineVec where the line of the word is stored, and the index in pathVec
 *  where the file path of the file containing the word is stored. WordNodes
 *  are stored in a vector of WordNode pointers.
 *
 *  Modified By (UTLN): rserot01
 *           On       : 11/29/2017
 *
 */

#ifndef WORDVECTOR_H
#define WORDVECTOR_H

#include <iostream>
#include <vector>

using namespace std;

class WordVector {

	public:

		WordVector();
		~WordVector();

		void addAtBack(std::string, int, size_t, size_t);	
		bool isEmpty();
		bool isInList(std::string);

		bool isMatch(size_t, std::string);
		string getWord(size_t);
		int getLineNum(size_t);
		size_t getLineIndex(size_t);
		size_t getPathIndex(size_t);
		size_t getListSize();

	private:

		struct WordNode {

			std::string word;
			int lineNum;
			size_t lineIndex;
			size_t pathIndex;
		};

		WordNode *wn;
		vector<WordNode*> wordList;	
};

#endif
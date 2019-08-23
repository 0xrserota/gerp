/*
 *
 *  COMP 15 Project 2: Gerp - It's Like grep But Something Is Off
 *
 *  WordVector.cpp
 *  Implementation of WordVector class.
 *	
 *  Modified By (UTLN): rserot01
 *           On       : 11/29/2017
 *
 */


#include <string>

#include <WordVector.h>


using namespace std;

/* Default constructor
	WordVector() 	*/
WordVector::WordVector()
{
	// nothing to do
}

/* Destructor
   ~WordVector() */
WordVector::~WordVector()
{
	for (size_t i = 0; i < wordList.size(); ++i)
	{
		delete wordList[i];
		wordList[i] = nullptr;
	}
}

/* bool isEmpty() */
bool WordVector::isEmpty()
{
	if (wordList.size() == 0)	{ return true; }

	else
		return false;
}

/* bool isInList(string) */
bool WordVector::isInList(string query)
{
	for (size_t i = 0; i < wordList.size(); ++i)
	{
		if (wordList[i]->word == query)
			return true;
	}

	return false;
}

/* size_t getListSize() */
size_t WordVector::getListSize()
{
	size_t size = wordList.size();

	return size;
}

/* void addAtBack(string, int, size_t, size_t) */
void WordVector::addAtBack(string word, int lineNum, size_t lineIndex,
								size_t pathIndex)
{
	// Initializing new node
	wn = new WordNode;
	wn->lineNum   = lineNum;
	wn->word 	  = word;
	wn->lineIndex = lineIndex;
	wn->pathIndex = pathIndex;

	// Adding to WordVector
	wordList.push_back(wn);
}

/* bool isMatch(size_t, string) */
bool WordVector::isMatch(size_t index, string query)
{
	if (wordList[index]->word == query)
		return true;

	else
		return false;
}

/* string getWord(size_t) */
string WordVector::getWord(size_t index)
{
	return wordList[index]->word;
}

/* int getLineNum(size_t) */
int WordVector::getLineNum(size_t index)
{
	return wordList[index]->lineNum;
}

/* size_t getLineIndex(size_t) */
size_t WordVector::getLineIndex(size_t index)
{
	return wordList[index]->lineIndex;
}

/* size_t getPathIndex(size_t) */
size_t WordVector::getPathIndex(size_t index)
{
	return wordList[index]->pathIndex;
}
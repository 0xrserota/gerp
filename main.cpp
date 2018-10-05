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

#include "MainHashTable.h"
#include "FSTree.h"
#include "stringProcessing.h"

#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

void run(MainHashTable*);
void quit();
void indexFSTree(DirNode*, string, stringstream&, MainHashTable*);
void indexFiles(stringstream&, MainHashTable*);
void indexLine(stringstream&, int, size_t, MainHashTable*);
void traverseTree(DirNode*, string, stringstream&);


/* 
 * Returns an int.
 *
 * Parameters:
 *     argc: size of argv
 *	   argv: array of command-line arguments 
 *
 * int main(int, char* []) */
int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		// Creates an instance of MainHashTable to be used throughout
		MainHashTable *ht = new MainHashTable;

		stringstream pathStream;
		string top = argv[1];
		FSTree fst(top);
		indexFSTree(fst.getRoot(), top, pathStream, ht);
		run(ht);

		// Deletes MainHashTable instance
		delete ht;

		return 0;
	}

	else
	{
		cerr << "Usage: gerp directory\n            " 
			 			<< "where: directory is a valid directory" << endl;

		return EXIT_FAILURE;
	}	
}

/* 
 * Returns nothing.
 *
 * Parameters:
 *
 *		ht: a pointer to the instance of MainHashTable created in main
 *
 * Starts a command loop - exits when CTRL-D or @q/@quit is pressed
 * Calls print and stringProcessing functions
 *
 * void run(MainHashTable*) */
void run(MainHashTable* ht)
{
	string cmd;
	string query;

	while (!cin.eof())
	{
		ht->resetBeenPrinted();
		cout << "Query? ";

		cin >> cmd;
		if (cin.eof())
			break;

		if (cmd == "@q" or cmd == "@quit")
			break;

		else if (cmd == "@i" or cmd == "@insensitive")
		{
			cin >> query;
			if (cin.eof())
				break;

			query = stripNonAlphaNum(query);			
			ht->printWord(query);
		}

		else
		{
			query = cmd;
			query = stripNonAlphaNum(query);
			ht->printCaseWord(query);
		}		
	}
	quit();
}

/* 
 * Returns nothing.
 *
 * Takes no parameters 
 *
 * Prints a quit message to std output
 */
void quit()
{
	cout << "\nGoodbye! Thank you and have a nice day." << endl;
}

/* Returns nothing.
 *
 * Parameters:	
 *
 * 		root: pointer to the DirNode entered as a command-line argument
 *		 top: a string name of the top directory 
 */
void indexFSTree(DirNode *root, string top, stringstream& pathStream, 
				  MainHashTable *ht)
{
	traverseTree(root, top, pathStream);
	indexFiles(pathStream, ht);
}

/* 
 * Returns nothing.
 *
 * Parameters:
 *     pathStream:  reference to a stringstream of a line
 *			   ht:  a pointer to the instance of MainHashTable created in main
 */
void indexFiles(stringstream& pathStream, MainHashTable *ht)
{
	while (!pathStream.eof())
	{
		string filePath;
		pathStream >> filePath;
		ifstream inFile;
		string thisLine;
		int lineNum = 0; 
		inFile.open(filePath);

		if (inFile.is_open())
		{
			size_t pathIndex = ht->addToPathVec(filePath);
			while (!inFile.eof())
			{
				getline(inFile, thisLine);
				stringstream lineStream(thisLine);
				++lineNum;

				indexLine(lineStream, lineNum, pathIndex, ht);
			}
			inFile.close();
		}
	}
}

/* 
 * Returns nothing.
 *
 * Parameters:
 *     lineStream:  reference to a stringstream of a line
 *		  lineNum:  line number of the line being indexed
 *		pathIndex:  the index in the pathVec where the filepath
 *					for this line is stored
 *			   ht:  a pointer to the instance of MainHashTable created in main
 */
void indexLine(stringstream& lineStream, int lineNum, size_t pathIndex, 
				MainHashTable *ht)
{
	string word;
	string line = lineStream.str();
	size_t lineIndex = ht->addToLineVec(line);

	while (!lineStream.eof())
	{
		lineStream >> word;
		word = stripNonAlphaNum(word);

		if (!(word == ""))
		{
			ht->addToTable(word, lineNum, lineIndex, pathIndex);
		}
	}
}

/* 
 * Returns nothing.
 *
 * Parameters:
 *             dn:  pointer a DirNode being indexed
 *		  dirPath:  path of the current directory
 *	   pathStream:  reference to a stringstream storing all paths traversed
 *
 * void traverseTree(DirNode*, string, stringstream&) 
 */
void traverseTree(DirNode *dn, string dirPath, 
							stringstream& pathStream)
{
	/* In-Order Tree Traversal, starting at 
	command-line specified highest directory */
	if (dn->hasSubDir())
	{
		for (int i = 0; i < dn->numSubDirs(); ++i)
		{
			traverseTree(dn->getSubDir(i), 
				dirPath + "/" + dn->getSubDir(i)->getName(), pathStream);
		}
	}

	if (dn->hasFiles())
	{
		for (int i = 0; i < dn->numFiles(); ++i)
		{
			string fpath = dirPath + "/" + dn->getFile(i);
			pathStream << " " << fpath;
		} 
	}
}
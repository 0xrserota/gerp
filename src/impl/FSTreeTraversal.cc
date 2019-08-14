/*
 *
 *  COMP 15 Project 2: Gerp - It's Like grep But Something Is Off
 *
 *  FSTreeTraversal.cc
 *  Main function for gerp
 *	
 *  Modified By (UTLN): rserot01
 *           On       : 11/29/2017
 *
 */

#include "FSTree.h"
#include <iostream>
#include <vector>

using namespace std;

/* Traverses FSTree instantiated in main, iterating through all subdirectories
	in the DirNode *dn, and recursing through each subdirectory. If a dirNode 
	has files, the files are iterated through, and each filename is appended
	to the end of the dirPath string, with a leading forward slash. The full
	filepath string is pushed to the back of the fpath vector, which stores all
	the filepaths traversed, and is later printed. */

/* void traverseTree(DirNode*, string, vector<string>&) */
void traverseTree(DirNode *dn, string dirPath, 
	vector<string>& filePaths)
{
	/* In-Order Tree Traversal, starting at 
	command-line specified highest directory */
	if (dn->hasSubDir())
	{
		for (int i = 0; i < dn->numSubDirs(); ++i)
		{
			traverseTree(dn->getSubDir(i), 
				dirPath + "/" + dn->getSubDir(i)->getName(), filePaths);
		}
		
	}

	if (dn->hasFiles())
	{
		for (int i = 0; i < dn->numFiles(); ++i)
		{
			string fpath = dirPath + "/" + dn->getFile(i);
			filePaths.push_back(fpath);
		} 
	}
}


/* Prints to cout the vector containing all filePaths, each on a new line */

/* void printFilePaths(vector<string>) */
void printFilePaths(vector<string> filePaths)
{
	for (size_t i = 0; i < filePaths.size(); ++i)
	{
		cout << filePaths[i] << endl;
	}
}


/* Main takes a single command-line argument, namely the name of 
	the directory to be made the root of the FSTree. If main does not receive 
	2 arguments, we return. The root directory name is stored in a string,
	and the FSTree constructor is called with this string as the argument.
	To account for the appending of the "/" to the file and directory paths
	in traverseTree below, if the last character in the top string is "/",
	we delete the "/" (to prevent "/foo//top/bar"). The tree traversal function
	is called with the root pointer of the new FSTree, the name of the
	top directory, and a vector passed by reference to store the filepaths. 
	Once traverseTree has finished executing, a function that prints the 
	contents of a vector is called. */

/* int main (int argc, char *argv[]) */
int main(int argc, char *argv[])
{
	if (argc != 2) { return -1; }

	string top = argv[1];
	vector<string> filePaths;

	FSTree fst(top);

	char ch = top.back();
	if (ch == '/')
	{
		top.erase(top.length() - 1);
	}

	traverseTree(fst.getRoot(), top, filePaths);
	printFilePaths(filePaths);

	return 0;
}
//
// Created by Vivek on 10/30/16.
//

#include "DirNode.h"


/*
* default constructor creates empty dirNode;
*/
DirNode::DirNode()
{
	parent = nullptr;
}

/*
* Constructor that sets the name of the node.
*/
DirNode::DirNode(std::string newName)
{
	parent = nullptr;
	DirNode::setName(newName);
}

/*
* Copy Constructor
*/
DirNode::DirNode(const DirNode &other)
{
	;
}

/*
* assignment overload
*/
DirNode& DirNode::operator=(const DirNode &other)
{

}

/*
* Adds a file with the name "newName" to the
* current node
*/
void DirNode::addFile(std::string newName)
{
	fileNames.push_back(newName);
	return;
}

/*
* adds a sub directory (newDir) to the current node
*/
void DirNode::addSubDirectory(DirNode *newDir)
{
	directories.push_back(newDir);
	return;
}

/*
* returns true if there are sub directories in the
* current node
*/
bool DirNode::hasSubDir()
{
	if 
}

/*
* returns true if there are files in the current node
*/
bool hasFiles()
{
	return !fileNames.empty();
}

/*
* returns true if there are no files or sub directories
* in the current node
*/
bool DirNode::isEmpty()
{
	return directories.empty() 
}

/*
* returns the number of sub directories
*/
size_t DirNode::numSubDirs()
{
	return directories.size();
}

/*
* returns the number of files in the current node
*/
size_t DirNode::numFiles()
{
	return fileNames.size();
}

/*
* set the name of the current node
*/
void DirNode::setName(std::string newName)
{
	name = newName;
	return;
}

/*
* returns the name of the current directory
*/
std::string DirNode::getName()
{
	return name;
}

/*
* returns the nth subdirectory
*/
DirNode* DirNode::getSubDir(int n)
{

}

/*
* returns nth file name
*/
std::string DirNode::getFile(int n)
{

}

/*
* get parent directory node
*/
DirNode* DirNode::getParent()
{
	return parent;
}

/*
* set parent directory node
*/
void DirNode::setParent(DirNode *newParent)
{
	parent = newParent;
	return;
}
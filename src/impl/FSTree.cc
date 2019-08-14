#include "DirNode.h"
#include "FSTree.h"

FSTree::FSTree()
{
	root = nullptr;
}

FSTree::FSTree(std::string rootName)
{
	;
}

FSTree::FSTree(const FSTree &other)
{
;
}

FSTree::~FSTree()
{
	FSTree::burnTree();
	root = nullptr;
}

FSTree& FSTree::FSTree(const FSTree &other)
{

}

FSTree::DirNode *buildTree(std::string rootName)
{

}

/*
 * Assignment overload for FSTree.
 */
FSTree& operator=(const FSTree &other);

/*
 * returns the root of the tree in order to traverse it.
 * The destructor will still delete all the allocated data.
 * The user should not manually delete the data.
 */
DirNode *getRoot() const
{
	return root;
}

/*
 * returns true if tree is empty
 */
bool isEmpty()
{
	if (root == nullptr)
		return true;
	
	return false;
}

/*
 * destroys the tree and deletes all the allocated data.
 */
void burnTree();

/*
 * Root of the n-ery tree
 */
DirNode *root;

/*
 * Helper Functions / Utilities (you dont need to worry
 * about these)
 */
bool is_file(const char *path);

bool is_dir(const char *path);

std::string baseName(std::string const & path);

DirNode *buildTree(std::string rootName);

void burnTree(DirNode *root);

DirNode *preOrderCopy(DirNode *currNode, DirNode *parentNode)
{
	DirNode *newNode = new DirNode();

	/*
	 * copy data in currNode to newNode
	 */
	newNode->setName(currNode->getName());
	newNode->setParent(parentNode);

	for (int i = 0; i < currNode->numFiles(); i++) {
		newNode->addFile(currNode->getFile(i));
	}

	/*
	 * recurse and coy rest of tree
	 */
	for (int i = 0; i < currNode->numSubDirs(); i++) {
		newNode->addSubDirectory(preOrderCopy(currNode->getSubDir(i), newNode));
	}

	/*
	 * return newNode (copy of currNode)
	 */
	return newNode;
}
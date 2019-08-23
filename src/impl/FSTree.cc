#include <DirNode.h>
#include <FSTree.h>

FSTree::FSTree()
{
	root = nullptr;
}

FSTree::FSTree(std::string rootName)
{
	rootName += "1";
	return;
}

FSTree::FSTree(const FSTree &other)
{
	root = preOrderCopy(other.root, nullptr);
}

FSTree::~FSTree()
{
	burnTree();
	root = nullptr;
}

DirNode *buildTree(std::string rootName)
{
	return nullptr;
}

/*
 * Assignment overload for FSTree.
 */
FSTree& FSTree::operator=(const FSTree &other)
{
	root = other.root;
	return *this;
}

/*
 * returns the root of the tree in order to traverse it.
 * The destructor will still delete all the allocated data.
 * The user should not manually delete the data.
 */
DirNode *FSTree::getRoot() const
{
	return root;
}

/*
 * returns true if tree is empty
 */
bool FSTree::isEmpty()
{
	if (root == nullptr)
		return true;
	
	return false;
}

/*
 * destroys the tree and deletes all the allocated data.
 */
void FSTree::burnTree()
{
	return;
}


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

	for (size_t i = 0; i < currNode->numFiles(); i++) {
		newNode->addFile(currNode->getFile(i));
	}

	/*
	 * recurse and coy rest of tree
	 */
	for (size_t i = 0; i < currNode->numSubDirs(); i++) {
		newNode->addSubDirectory(preOrderCopy(currNode->getSubDir(i), newNode));
	}

	/*
	 * return newNode (copy of currNode)
	 */
	return newNode;
}
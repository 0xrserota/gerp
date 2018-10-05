#include "ChainLinkedList.h"
#include <iostream>

using namespace std;

int main()
{
	ChainLinkedList links;
	links.addAtFront("hello", 5, "HeLlo", "HeLlo father!", 42, "/h/comp/file1.txt");

	if (links.isInList("hello"))
	{
		links.addToWordList("hello", "HELLO", "HELLO sweetie!", 8, "/h/comp/file2.txt");
		links.addToWordList("hello", "Hello", "Hello darling!", 23, "/h/comp/file3.txt");
	}

	

	//links.printWordList("hello");
	links.printCaseWordList("hello", "HeLlO");


	return 0;
}
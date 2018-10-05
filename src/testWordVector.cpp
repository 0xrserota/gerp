#include "WordVector.h"
#include <iostream>

using namespace std;

int main()
{
	WordVector list;

	if (list.isEmpty())
	{
		cout << "Empty list." << endl;
	}

	list.addAtBack(3, "hello", "hello there!", "/h/file.txt");
	list.printList();
	list.printCaseList("hello");

	return 0;
}
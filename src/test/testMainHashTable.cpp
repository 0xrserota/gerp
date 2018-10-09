#include <iostream>
#include "MainHashTable.h"

using namespace std;

int main()
{
	MainHashTable htable;

	cout << "out1: " << out1 << endl;
	cout << "out2: " << out2 << endl;

	htable.addToTable(out1, "My name is H~I. What's your's?", 23, "/h/name.txt");

	if (htable.isInList(out1))
		cout << "Yup! In list!" << endl;

	return 0;
}
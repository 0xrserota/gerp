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


#include "stringProcessing.h"
#include <iostream>

int main()
{
	std::string inWord;

	std::cout << "Please enter a string to be stripped: "; 
	std::cin >> inWord;

	std::string outWord = stripNonAlphaNum(inWord); 
	std::cout << "Input:  " << inWord << std::endl;
	std::cout << "Output: " << outWord << std::endl;

	return 0;
}
/*
 *
 *  COMP 15 Project 2: Gerp - It's Like grep But Something Is Off
 *
 *  stringProcessing.cpp
 *  Removes non-alphanumeric characters from input, returning parsed string
 *	
 *  Modified By (UTLN): rserot01
 *           On       : 11/29/2017
 *
 */


#include <StringProcessing.h>

/* Removes non-alphanumeric characters from a string argument
	and returns the stripped string. Checks the beginning of the string
	until finding an alphanumeric character, which will be the beginning of
	the processed string. The non-alphanumeric beginning characters are 
	removed from the string. The same process is repeated from the end of the 
	string to the second character in the string. We already know that the
	first character in the string is alphanumeric, since we just made it so.
	The characters following the last alphanumeric character are removed.
	 */

/* std::string stripNonAlphaNum(std::string) */
std::string stripNonAlphaNum(std::string word)
{
	// Checks if string has any alphaNums 
	bool hasAlnum = false;
	for (size_t i = 0; i < word.length(); ++i)
	{
		if (isalnum(word[i])) 
		{
			hasAlnum = true;
			break;
		}
	}

	// If the word is all symbols, return blank string 
	if (hasAlnum == false)
		return ""; 

	//Checks the beginning of the string for non-alphanums
	for (size_t i = 0; i < word.length(); ++i) 
	{
		if (isalnum(word[i])) 
		{
			word.erase(0, i); // cuts off front of string
			break;
		}
	}

	// Checks the back of the string for non-alphanums
	for (size_t j = word.length() - 1; j > 0; --j)
	{
		if (isalnum(word[j]))
		{
			word.erase(j + 1, word.length() - (j + 1)); // cuts off back of string
			break; 
		}
	}

	return word;
}
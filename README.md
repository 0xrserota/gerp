# gerp
C++ implementation of 'grep' that performs fast string search in a directory
/*
 *
 *  COMP 15 Project 2: Gerp - It's Like grep But Something Is Off
 *
 *  README
 *  README file for gerp
 *	
 *  Modified By (UTLN): rserot01
 *           On       : 11/29/2017
 *
 */


 A. 	Title and Author

 		Title: Gerp - It's Like grep But Something Is Off
 		Author: Ravi Serota
 		UTLN: rserot01

 B. 	Purpose

 		The purpose of gerp is to index a file directory, going to every  subdirectory, and indexing the entire contents of every text file
 		in the directory tree. The contents are parsed as words, which
 		are added to data structures, and then the user is able to query
 		a word, which the program answers by printing out every instance in the
 		directory tree where that word occurs. It can search case-sensitive or
 		case-insensitive. 

 C.		Acknowledgements

 		Did not receive any outside help in writing this program. 

 D. 	Files

 				main.cpp: Main function for gerp
 		 MainHashTable.h: Class definition for MainHashTable, the hash table class
 	   MainHashTable.cpp: Class implementation for MainHashTable
 	   ChainLinkedList.h: Class definition for ChainLinkedList class
 	   ChainLinkedList.cpp: Class Implementation for ChainLinkedList class
 	       WordVector.h:	Class definition for WordVector class, the wordlist 					class
 	   		 WordVector.cpp:	Class implementation for WordVector class
 	     stringProcessing.h: String processing function definition
 	   stringProcessing.cpp: String processing function implementation


E. 		Compiling and Running

		To compile type make in the terminal. 
		To run use ./gerp [Directory to index]
		To query case-sensitively use [query]
		To query case-insensitively use @i [query]
		or @insensitive query

		To quit the program, use @q or @quit

F.		Architecture

		HashTable->ChainLists->Wordlists

G. 	 	Data Structures and Algorithms


H.      Testing

		Tested using diff and the guteneberg files provided

#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "CircularLinkedList.h"
#include "AlphabetBST.h"
#include "Queue.h"
#include <cstring>
#include <cstdlib>
#include <string>
class Manager
{
public:
	CircularLinkedList * cll;	// MEMORIZED Circular Linked List
	AlphabetBST	* bst;			// MEMORIZING BST
	Queue * queue;				// TO_MEMORIZE Queue
	ifstream CommandFile;		// Read command 
	ofstream Log;				// Write Log
	char comm[5][100];			// keep part of command 
public:
	Manager();
	~Manager();

	void run(const char * command);	// ifstream fin; fin.open(command); // and read all line

	bool LOAD();	//LOAD
	bool ADD();		//ADD
	bool MOVE();	//MOVE
	bool SAVE();	//SAVE
	bool TEST();	//TEST
	bool SEARCH();	//SEARCH
	bool PRINT();	//PRINT
	bool UPDATE();	//UPDATE
	void ERROR(const char *commandconst, int num); // Print ERROR and some of function's result
	void my_strcpy(char* a,char *b,int size);//Strcpy
};

#endif

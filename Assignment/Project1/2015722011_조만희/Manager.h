#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "CircularLinkedList.h"
#include "AlphabetBST.h"
#include "Queue.h"
#include <utility>
#include <fstream>



class Manager
{
public:
	CircularLinkedList * cll;	// MEMORIZED Circular Linked List
	AlphabetBST	* bst;			// MEMORIZING BST
	Queue * queue;				// TO_MEMORIZE Queue

	ofstream logfile;   //initiate file output stream

public:
	Manager();
	~Manager();

	void run(const char * command);	// ifstream fin; fin.open(command); // and read all line
	
	bool LOAD();
	bool ADD();
	bool MOVE();
	bool SAVE();
	bool TEST();
	bool SEARCH();
	bool PRINT();
	bool UPDATE();

private:

	// Commands
	char* cmds[8] = {
		"LOAD",
		"ADD",
		"MOVE",
		"SAVE",
		"TEST",
		"SEARCH",
		"PRINT",
		"UPDATE"
	};

};

#endif

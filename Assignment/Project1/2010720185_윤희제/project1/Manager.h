#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "CircularLinkedList.h"
#include "AlphabetBST.h"
#include "Queue.h"
#include <utility>
#include <fstream>
#include <string>
using namespace std;

class Manager
{
public:
	CircularLinkedList* cll;	// MEMORIZED Circular Linked List
	AlphabetBST* bst;			// MEMORIZING BST
	Queue* queue;				// TO_MEMORIZE Queue

public:
	Manager();
	~Manager();
	
	int move_num;                   // count the number of move 'to memorize' to 'memorizing'
	char command_text[10];          // store the command line from the command.txt
	char arg1[100];                 // store the first word except command line of command.txt 
	char arg2[100];                 // store the second word except command line of command.txt 
	void run(const char* command);	// ifstream fin; fin.open(command); // and read all line
	
	bool LOAD();
	bool ADD();
	bool MOVE();
	bool SAVE();
	bool TEST();
	bool SEARCH();
	bool PRINT();
	bool UPDATE();

	// initialize all array of temporarily store the word from 'commmand.txt'
	void initialize_arr(char* command_text, char* arg1, char* arg2);
};

#endif

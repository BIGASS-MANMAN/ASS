#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "CircularLinkedList.h"
#include "AlphabetBST.h"
#include "Queue.h"
#include <utility>
#include <fstream>
#include <cstring>

#define LOAD_ERROR 100
#define ADD_ERROR 200
#define MOVE_ERROR 300
#define SAVE_ERROR 400
#define TEST_ERROR 500
#define SEARCH_ERROR 600
#define PRINT_ERROR 700
#define UPDATE_ERROR 800
using namespace std;
class Manager
{
public:
	CircularLinkedList * cll;	// MEMORIZED Circular Linked List
	AlphabetBST	* bst;			// MEMORIZING BST
	Queue * queue;				// TO_MEMORIZE Queue
	char command_text[3][50];	// for storing command text

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
};

#endif

#ifndef _MANAGER_H_
#define _MANAGER_H_


using namespace std;

#include <fstream>
#include "CircularLinkedList.h"
#include "AlphabetBST.h"
#include "Queue.h"
#include <string>
#include <string.h>
#include <utility>
#include <locale>
#pragma execution_character_set("utf-8")

class Manager
{
public:
	CircularLinkedList * cll;
	AlphabetBST	* bst;
	Queue * queue;

public:
	Manager();
	~Manager();

	void run(const char * command);

	bool LOAD();
	bool ADD();
	bool MOVE(int number);
	bool SAVE();
	bool TEST(char * word, char * mean);
	bool SEARCH(char * word);
	bool PRINT(char * word, char * kind);
	bool UPDATE(char * word, char * to);
};

#endif

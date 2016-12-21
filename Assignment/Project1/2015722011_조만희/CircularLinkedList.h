#ifndef _CIRCULARLINKEDLIST_H_
#define _CIRCULARLINKEDLIST_H_

#include "WordNode.h"
#include <fstream>
using namespace std;
class CircularLinkedList
{
public:
	WordNode * pHead;	// Circular Linked List Head Pointer

public:
	CircularLinkedList();
	~CircularLinkedList();

	void		Insert(WordNode * node);			// LOAD, TEST
	WordNode *	Search(char * word);				// SEARCH, UPDATE
	bool		Print(ofstream& logfile);			// PRINT
	bool		Save();						// SAVE
};

#endif

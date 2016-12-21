#ifndef _CIRCULARLINKEDLIST_H_
#define _CIRCULARLINKEDLIST_H_

#include "WordNode.h"
#include <cstring>
class CircularLinkedList
{
public:
	WordNode * pHead;	//Variable pHead declarations


public:
	CircularLinkedList();//Constructor
	~CircularLinkedList();//Destructor

	void		Insert(WordNode * node);// Function Insert declarations (Use LOAD, TEST)
	WordNode *	Search(char * word);	// Function Search declarations (Use SEARCH, UPDATE)
	bool		Print();				// Function Print declarations (Use PRINT)
	bool		Save();					// Function Save declarations (Use SAVE)
};

#endif

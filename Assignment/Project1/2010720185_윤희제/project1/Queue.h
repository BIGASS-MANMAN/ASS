#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "WordNode.h"
#include "AlphabetNode.h"
#include <fstream>
using namespace std;
class AlphabetNode;

class Queue
{
public:
	WordNode* pHead;              // point the first node of word queue                      
	AlphabetNode* alphabet_pHead; // point the first node of alphabet queue

public:
	Queue();
	~Queue();

	void		    Push(WordNode * node);				// LOAD, ADD
	void		    alphabet_Push(AlphabetNode * node); // insert the alphabet node to the alphabet queue
	WordNode*	    Pop();						        // MOVE
	AlphabetNode*	alphabet_Pop();                     // pop the last alphabet node from the alphabet queue
	WordNode*	    Search(char * word);				// SEARCH, UPDATE
	bool		    Print();							// PRINT
	bool		    Save();								// SAVE
};

#endif

#ifndef _CIRCULARLINKEDLIST_H_
#define _CIRCULARLINKEDLIST_H_

#include "WordNode.h"
#include <fstream>
#include <iostream>
using namespace std;

class CircularLinkedList
{
public:
	WordNode * pHead;	// Circular Linked List Head Pointer
	WordNode * pTail;	// Circular Linked List Tail Pointer
	int			WordCnt; //The number of Node
	ofstream 		fout_word;
public:
	CircularLinkedList();
	~CircularLinkedList();

	void		Insert(WordNode * node);			// LOAD, TEST
	WordNode *	Search(char * word);				// SEARCH, UPDATE
	bool		Print();							// PRINT
	bool		Save();								// SAVE
	int			GetWordCnt();
	void		SetWordCnt(int count);
};

#endif

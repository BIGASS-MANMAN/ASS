#ifndef _WORDBST_H_
#define _WORDBST_H_

#include "W_Stack.h"
#include "WordNode.h"
#include <fstream>
#include <cstring>
class WordBST
{
public:
	WordNode * root;	// Word BST Root
	char m_order[32];	////for easily input print order accessing, using member variable 
	ofstream fout_log;	//save print log
	ofstream fout_word;	//save in BST to have word
	int del_count;
public:
	WordBST();
	~WordBST();

	void		Insert(WordNode * node);			// LOAD, MOVE
	WordNode *	Delete(char * word);				// TEST
	WordNode *	Search(char * word);				// ADD, TEST, SEARCH, UPDATE
	bool		Print(char * order);							// PRINT
	void		Print_Pre(WordNode * node);
	void		Print_In(WordNode * node);
	void		Print_Post(WordNode * node);
	void		Iter_Pre(WordNode * node);
	void		Iter_In(WordNode * node);
	void		Iter_Post(WordNode * node);
	void		Iter_Level(WordNode * node);
	bool		Save();								// SAVE
	void		Save_Pre(WordNode * node);			//pre-ordering save node
	void		Delete_BST(WordNode * node);
};

#endif

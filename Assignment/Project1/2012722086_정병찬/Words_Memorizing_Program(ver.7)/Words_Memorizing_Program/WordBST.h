#ifndef _WORDBST_H_
#define _WORDBST_H_

#include "WordNode.h"
#include<fstream>

class WordBST
{
public:
	WordNode * root;	// Word BST Root


public:
	WordBST();
	~WordBST();
	WordNode *	Getroot();
	void		Insert(WordNode * node);			// LOAD, MOVE
	WordNode *	Delete(char * word);				// TEST
	WordNode *	Search(char * word);				// ADD, TEST, SEARCH, UPDATE
	bool		Print(char * order);				// PRINT
	void		R_PRE(WordNode * cur);
	void		I_PRE();
	void		R_IN(WordNode * cur);
	void		I_IN();
	void		R_POST(WordNode * cur);
	void		I_POST();
	void		I_LEVEL();	
	bool		Save();	// SAVE
	int			Bst_count();

};

#endif

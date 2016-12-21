#ifndef _WORDBST_H_
#define _WORDBST_H_
/************************************************************/
/*This is WordBST.h that structred BST						*/
/*Also, It is definition about WordBST Class				*/
/************************************************************/
#define MEMORIZING_FILENAME "memorizing_word.txt"
#include "Queue.h"

class WordBST
{
public:
	/*MEMBER VARIABLE*/
	WordNode * root;	// Word BST Root

	/*MEMBER FUNCTION driven by PRINT()*/
	bool R_PRE(WordNode *node);
	bool R_IN(WordNode *node);
	bool R_POST(WordNode *node);
	bool I_PRE(bool save=false);
	bool I_IN();
	bool I_POST();
	bool I_LEVEL();
	void VISIT(WordNode *node);

public:
	/*CONSTRUCTOR, DESTRUCTOR*/
	WordBST();
	~WordBST();

	/*MEMBER FUNCTION*/
	void		Insert(WordNode * node);			// LOAD, MOVE
	WordNode *	Delete(char * word);				// TEST
	WordNode *	Search(char * word);				// ADD, TEST, SEARCH, UPDATE
	bool		Print(char *order);					// PRINT
	bool		Save();								// SAVE
};

#endif

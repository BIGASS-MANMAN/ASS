#ifndef _WORDBST_H_
#define _WORDBST_H_

#include "WordNode.h"

class WordBST
{

public:
	WordNode * root;							// Word BST Root
	WordBST();
	~WordBST();

	void		Insert(WordNode * node);				// LOAD, MOVE
	WordNode *	Delete(char * word);					// TEST
	WordNode *	Search(char * word);					// ADD, TEST, SEARCH, UPDATE
	bool		Print(char * order);					// PRINT
	bool		Save();							// SAVE
	bool		preSave(WordNode * CurrentNode, ofstream & ingfout);
	
	bool		R_IN();							//R_IN Driver
	void		R_IN(WordNode* root, ofstream &fout);			//R_IN

	bool		R_PRE();						//R_PRE Driver
	void		R_PRE(WordNode* root, ofstream &fout);			//R_PRE

	bool		R_POST();						//R_POST Driver
	void		R_POST(WordNode* root, ofstream &fout);			//R_PRE
	
	bool		I_IN();							//I_IN
	bool		I_PRE();						//I_PRE
	bool		I_POST();						//I_POST
	bool		I_LEVEL();						//I_LEVEL

	void        	Clear(WordNode* root);					//Every Node
};

#endif

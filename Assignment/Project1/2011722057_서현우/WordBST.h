#ifndef _WORDBST_H_
#define _WORDBST_H_

#include "WordNode.h"
#include <cstring>
class WordBST
{
public:
	WordNode * root;	// Word BST Root

public:
	WordBST();
	~WordBST();

	void		Insert(WordNode * node);			// Function Push declarations (Use LOAD, MOVE)
	WordNode *	Delete(char * word);				// Function Push declarations (Use TEST)
	WordNode *	Search(char * word);				// Function Push declarations (Use ADD, TEST, SEARCH, UPDATE)
	bool		Print(char * order);				// Function Push declarations (Use PRINT)
	bool		Save();								// Function Push declarations (Use SAVE)
	void		R_PRE(WordNode* node);// Function R_PRE declarations (Recursive pre order)
	void		I_PRE();// Function I_PRE declarations (Iterative pre order)
	void		R_IN(WordNode* node);// Function R_IN declarations (Recursive in order)
	void		I_IN();// Function I_IN declarations (Iterative in order)
	void		R_POST(WordNode* node);// Function R_POST declarations(Recursive post order)
	void		I_POST();// Function I_POST declarations(Iterative post order)
	void		I_LEVEL();// Function I_LEVEL declarations(Iterative level order)
	WordNode*	R_Delete(WordNode* node, char* word);// Function R_Delete declarations (Recursive Delete Function)
	WordNode*	R_Search(WordNode* node, char* word);// Function R_Search declarations (Recursive Search Function)
	WordNode*	GetRoot();// Function GetRoot declarations 
};

#endif

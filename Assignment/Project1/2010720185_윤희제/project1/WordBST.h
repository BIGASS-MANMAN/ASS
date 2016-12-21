#ifndef _WORDBST_H_
#define _WORDBST_H_

#include "WordNode.h"
#include "AlphabetBST.h"
#include "Stack.h"
#include <fstream>
using namespace std;

class WordBST
{
public:
	WordNode* root;	// Word BST Root

public:
	WordBST();
	~WordBST();

	void		Insert(WordNode * node);			       // LOAD, MOVE
	WordNode*	Delete(char* word);			               // TEST
	WordNode*	Search(char* word);				           // ADD, TEST, SEARCH, UPDATE
	bool		Print(char* order);				           // PRINT
	bool		Save();								       // SAVE
	bool        R_Pre_order(WordNode* node, char* order);  // recursive pre order
	bool        I_Pre_order(char* order);                  // iterative pre order
	bool	    R_In_order(WordNode* node, char* order);   // recursive in order
	bool	    I_In_order(char* order);                   // iterative in order
	bool		R_Post_order(WordNode* node, char* order); // recursive post order
	bool		I_Post_order(char* order);                 // iterative post order
	bool		I_Level_order(char* order);                // iterative level order
};

#endif

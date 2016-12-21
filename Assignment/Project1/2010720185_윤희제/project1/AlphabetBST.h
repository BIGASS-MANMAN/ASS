#ifndef _ALPHABETBST_H_
#define _ALPHABETBST_H_

#include "AlphabetNode.h"
#include "Queue.h"
#include "Stack.h"
#include <iostream>
using namespace std;

#define MAX_WORD 100	// Maximum MEMORIZING Words

class AlphabetBST
{
public:
	AlphabetNode* root; // point the root of bst
	int WordCnt;        // count the number of bst node
	int print_flag;     // to notice 
	int save_flag;      // to notice 

public:
	AlphabetBST();
	~AlphabetBST();

	void			Insert(AlphabetNode* node);	                   // run
	bool			Print(char* order);			                   // PRINT
	AlphabetNode*	Search(char alphabet);		                   // LOAD, MOVE, TEST, SEARCH, UPDATE
	bool			Save();							               // SAVE
	void            R_Pre_order(AlphabetNode* node, char* order);  // print all bst node by recursive pre order
	void            I_Pre_order(char* order);                      // print all bst node by iterative pre order
	void		    R_In_order(AlphabetNode* node, char* order);   // print all bst node by recursive in order
	void		    I_In_order(char* order);                       // print all bst node by iterative in order
	void			R_Post_order(AlphabetNode* node, char* order); // print all bst node by recursive post order
	void			I_Post_order(char* order);                     // print all bst node by iterative post order
	void			I_Level_order(char* order);                    // print all bst node by iterative level order
};

#endif

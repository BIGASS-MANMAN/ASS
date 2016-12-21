#ifndef _ALPHABETBST_H_
#define _ALPHABETBST_H_

#include "AlphabetNode.h"

#define MAX_WORD 100	// Maximum MEMORIZING Words

class AlphabetBST
{

public:
	AlphabetNode * root;
	int WordCnt;	// Number of Words( WordNodes )

public:
	AlphabetBST();
	~AlphabetBST();

	void			Insert(AlphabetNode * node);	// RUN
	bool			Print(char * order, std::ofstream& logfile);			// PRINT
	AlphabetNode *	Search(char alpabet);			// LOAD, MOVE, TEST, SEARCH, UPDATE
	void			Save(AlphabetNode* node);							// SAVE

private:

	// Print methods
	void preOrder(AlphabetNode * currentNode, char * order, ofstream& logfile);
	void NR_preOrder(char * order, ofstream& logfile);
	void inOrder(AlphabetNode * currentNode, char * order, ofstream& logfile);
	void NR_inOrder(char * order, ofstream& logfile);
	void postOrder(AlphabetNode * currentNode, char * order, ofstream& logfile);
	void NR_postOrder(char * order, ofstream& logfile);
	void levelOrder(char * order, ofstream& logfile);

	// Delete tree ( Single alphabet node )
	void deleteTree(AlphabetNode * currentNode);

	// Order commands to print
	char* printOrders[7] = {
		"R_PRE",	// Recursive preOrder
		"I_PRE",	// Iterative preOrder
		"R_IN",		// Recursive inOrder
		"I_IN",		// Iterative inOrder
		"R_POST",	// Recursive postOrder
		"I_POST",	// Iterative postOrder
		"I_LEVEL"	// Recursive levelOrder
	};
};

#endif

#ifndef _WORDBST_H_
#define _WORDBST_H_

#include "WordNode.h"
#include <fstream>


using namespace std;

class WordBST
{
public:
	WordNode * root;	// Word BST Root

public:
	WordBST();
	~WordBST();

	void		Insert(WordNode * node);			// LOAD, MOVE
	WordNode *	Delete(char * word);				// TEST
	WordNode *	Search(char * word);				// ADD, TEST, SEARCH, UPDATE
	bool		Print(char * order, ofstream& logfile);				// PRINT
	void		Save(ofstream& memorizing);		// SAVE

private:
	// Print methods
	void preOrder(WordNode* currentNode, ofstream& logfile);
	void NR_preOrder(ofstream& logfile);
	void inOrder(WordNode* currentNode, ofstream& logfile);
	void NR_inOrder(ofstream& logfile);
	void postOrder(WordNode* currentNode, ofstream& logfile);
	void NR_postOrder(ofstream& logfile);
	void levelOrder(ofstream& logfile);

	void deleteTree(WordNode * currentNode); // WorkHorse for ~WordBST

	// Print orders
	char* printOrders[7] = {
		"R_PRE",
		"I_PRE",
		"R_IN",
		"I_IN",
		"R_POST",
		"I_POST",
		"I_LEVEL"
	};
};

#endif

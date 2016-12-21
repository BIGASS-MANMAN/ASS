#ifndef _WORDBST_H_
#define _WORDBST_H_

#include "WordNode.h"
using namespace std;
#define MAX_WORD 100
class WordBST
{
public:
	WordNode * root;	// Word BST Root
	int leftHeight, rightHeight;
	WordNode * Stk_or_Que[MAX_WORD];
	int numOfWords;
	WordNode * check[100];
	ofstream logfile;

public:
	WordBST();
	~WordBST();

	void		Insert(WordNode * node);			// LOAD, MOVE
	WordNode *	Delete(char * word);				// TEST
	WordNode *	Search(char * word);				// ADD, TEST, SEARCH, UPDATE
	bool		Print(char * order);							// PRINT
	bool		Save();								// SAVE
	int			GetNum();

	void		R_Preorder();
	void		I_Preorder();
	void		R_Inorder();
	void		I_Inorder();
	void		R_Postorder();
	void		I_Postorder();
	void		I_Levelorder();

	void		R_Preorder(WordNode* node);
	void		I_Preorder(WordNode* node);
	void		R_Inorder(WordNode* node);
	void		I_Inorder(WordNode* node);
	void		R_Postorder(WordNode* node);
	void		I_Postorder(WordNode* node);
	void		I_Levelorder(WordNode* node);
};
#endif

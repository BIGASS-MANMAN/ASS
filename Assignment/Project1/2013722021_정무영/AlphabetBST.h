#ifndef _ALPHABETBST_H_
#define _ALPHABETBST_H_

#include "AlphabetNode.h"
#define MAX_WORD 100	// Maximum MEMORIZING Words
#define ALPHABET 26
class AlphabetBST
{
public:
	AlphabetNode * root;
	AlphabetNode * Stk_or_Que[ALPHABET];
	int leftHeight, rightHeight;
	int numOfWords;

public:
	AlphabetBST();
	~AlphabetBST();

	void			Insert(AlphabetNode * node);	// run
	bool			Print(char * order);						// PRINT
	AlphabetNode *	Search(char alpabet);			// LOAD, MOVE, TEST, SEARCH, UPDATE
	bool			Save();							// SAVE
	int				GetNumOfWords();
	void		R_Preorder(AlphabetNode* node);
	void		I_Preorder(AlphabetNode* node);
	void		R_Inorder(AlphabetNode* node);
	void		I_Inorder(AlphabetNode* node);
	void		R_Postorder(AlphabetNode* node);
	void		I_Postorder(AlphabetNode* node);
	void		I_Levelorder(AlphabetNode* node);
};

#endif

#ifndef _ALPHABETBST_H_
#define _ALPHABETBST_H_

#include "AlphabetNode.h"

#define MAX_WORD 100	// Maximum MEMORIZING Words

class AlphabetBST
{
public:
	AlphabetNode * root;
	int WordCnt;

public:
	AlphabetBST();
	~AlphabetBST();

	void			Insert(AlphabetNode * node);	// run
	bool			Print(char * order);			// PRINT
	AlphabetNode *	Search(char alpabet);			// LOAD, MOVE, TEST, SEARCH, UPDATE
	bool			Save();							// SAVE
	bool			IsEmpty() const;
	void		R_Preorder(AlphabetNode* p, char* word);						// Recursive Pre-order
	void		R_Inorder(AlphabetNode* p, char* word);						// Recursive In-order
	void		R_Postorder(AlphabetNode* p, char* word);						// Recursive Post-order
	void		I_Preorder(char* word);						// Iterative Pre-order
	void		I_Inorder(char* word);						// Iterative In-order
	void		I_Postorder(char* word);						// Iterative Post-order
	void		I_Levelorder(char* word);
	void		Dellocate(AlphabetNode* p);
	void		SetVisitZero(AlphabetNode* p);
	void		R_Preorder_save(AlphabetNode* p);
};

#endif

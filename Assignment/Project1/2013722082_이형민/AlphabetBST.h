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
	int GetwordCnt();											//for counting word
	void SetWordCnt(int pWordCnt);								//	print order
	bool Inorder(AlphabetNode * currentNode, char * order);		//
	bool Preorder(AlphabetNode * currentNode, char * order);	//	print order	
	bool Postorder(AlphabetNode * currentNode, char * order);//	print order
	bool Inorder_save(AlphabetNode * currentNode);//for saving order
	void Postorder_delete(AlphabetNode * currentNode);//for destructing order
	void			Insert(AlphabetNode * node);	// insert
	bool			Print(char * order);			// PRINT
	AlphabetNode *	Search(char alpabet);			// search
	bool			Save();							//save
	bool			Nonrec_Inorder(char * order);	//	print order
	bool			Nonrec_Postorder(char*order);//	print order
	bool			Nonrec_Preorder(char * order);//	print order
	bool			Level_order(char * order);//	print order
	// SAVE
};

#endif

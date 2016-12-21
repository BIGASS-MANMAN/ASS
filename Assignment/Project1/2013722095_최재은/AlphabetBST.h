#ifndef _ALPHABETBST_H_
#define _ALPHABETBST_H_

#include "AlphabetNode.h"

#define MAX_WORD 100	// Maximum MEMORIZING Words
/* MEMORIZING */
class AlphabetBST
{

public:
	AlphabetNode* root;
	AlphabetNode* Sroot;
	int WordCnt;
	AlphabetBST();
	~AlphabetBST();

	void			Insert(AlphabetNode* node);		// INSERT
	bool			Print(char* order);				// PRINT
	AlphabetNode *	Search(char alpabet);			// SEARCH
	bool			Save();							// SAVE

	void APreorder(); // Driver of Inorder
	void APreorder(AlphabetNode* currentNode); // Workhorse of Inorder
	void Saveroot(AlphabetNode* node); //Saveroot
	void PlusWC(); //plusWC
	void Preorder(); //Preorder
	void Preorder(AlphabetNode* node); //Preorder
	void Inorder(); //Inorder
	void Inorder(AlphabetNode* node);//Inorder
	void Postorder(); //Postorder
	void Postorder(AlphabetNode* node);  //Postorder
	void	I_POST(); //I_POST (Iterative)
	void	I_LEVEL(); //I_LEVEL(Iterative)
	void	I_IN(); //I_IN(Iterative)
	void	I_PRE(); //I_PRE(Iterative)

};

class Stack2   //stack2
{
private:   //private
	AlphabetNode* pHead;//AlphabetNode pHead

public:   //public
	Stack2();
	~Stack2();
	bool IsEmpty(); //IsEmpty
	bool Push(AlphabetNode* pNode); //push pNode
	AlphabetNode* Pop(); //pop
	AlphabetNode* Top(); //top
};
class Queue3
{
private:
	AlphabetNode* pHead; //alphabetnode phead
	AlphabetNode* pTail; //alphabetnode ptail

public:
	Queue3();
	~Queue3();

	void		Push(AlphabetNode* node); //push node
	AlphabetNode*	Pop();	//alphabetNode pop
	AlphabetNode*	front(); //alphabetNode front
	bool		empty(); //empty
};
#endif

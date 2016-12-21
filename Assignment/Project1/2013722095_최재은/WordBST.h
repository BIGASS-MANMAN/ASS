#ifndef _WORDBST_H_
#define _WORDBST_H_

#include "WordNode.h"

class WordBST 
{
public:
	WordNode* root;	// Word BST Root
	WordNode* Sroot; // Word BST Sroot

	WordBST();
	~WordBST();

	void		Insert(WordNode* node);			// LOAD, MOVE
	WordNode *	Delete(char* word);				// TEST
	WordNode *	Search(char* word);				// ADD, TEST, SEARCH, UPDATE
	bool		Print(char* order);				// PRINT
	bool		Save();							// SAVE
	void		WPostorder();					//Deriver of Preorder
	void		WPostorder(WordNode* currentNode); // Workhorse of Preorder
	char* up(char* word); //up
	char* low(char* word); //low
	void		Saveroot(WordNode* node); //saveroot
	void		WPreorder();// Deriver of Preorder
	void		WPreorder(WordNode* currentNode);// Workhorse of Preorder
	void		R_PRE(); //R_PRE(recursive)
	void		R_PRE(WordNode* currentNode); //R_PRE(recursive)
	void		I_PRE(); //I_PRE(Iterative)
	void		R_IN(); //R_IN(recursive)
	void		R_IN(WordNode* currentNode); //R_IN(recursive)
	void		I_IN(); //I_IN (Iterative)
	void		R_POST();//R_POST(recursive)
	void		R_POST(WordNode* currentNode); //R_POST(recursive)
	void		I_POST(); //I_POST(Iterative)
	void		I_LEVEL(); //I_LEVEL(Iterative)

};
class Stack   //declare Stack class
{
private:   //declare private
	WordNode* pHead; //WordNode pHead

public:   //public
	Stack();
	~Stack();
	bool IsEmpty(); //IsEmpty
	bool Push(WordNode* pNode); //Push node
	WordNode* Pop(); //pop
	WordNode* Top(); //top
};
class Queue2 //declare queue2 
{
private: //declare private
	WordNode* pHead; //WordNode pHead
	WordNode* pTail; //WordNode pTail

public: //declare public
	Queue2(); 
	~Queue2();

	void		Push(WordNode* node);		// node push
	WordNode*	Pop();						// pop
	WordNode*	front();					// front
	bool		empty();					//empty
};
#endif

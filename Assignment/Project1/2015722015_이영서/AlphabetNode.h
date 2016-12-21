#ifndef _ALPHABETNODE_H_
#define _ALPHABETNODE_H_

#include "WordBST.h"


////////////////////////AlphabetNode class////////////////////////////
class AlphabetNode
{
private:
	char alphabet;
	WordBST * bst;
	AlphabetNode * pLeft;		// BST Left Pointer
	AlphabetNode * pRight;		// BST Right Pointer
	AlphabetNode * pNext;		// BST Next Pointer

public:
	AlphabetNode();
	~AlphabetNode();

	char			GetAlphabet(){return alphabet;}					// Get Alphabet
	WordBST	*		GetBST(){return bst;}							// Get Word BST
	AlphabetNode *	GetLeft(){return pLeft;}						// Get BST Left Pointer
	AlphabetNode *	GetRight(){return pRight;}						// Get BST Right Pointer
	AlphabetNode *	GetNext(){return pNext;}

	void			SetAlphabet(char alphabet){this->alphabet=alphabet;}		// Set Alphabet
	void			SetLeft(AlphabetNode * node){pLeft=node;}					// Set BST Left Pointer
	void			SetRight(AlphabetNode * node){pRight=node;}					// Set BST Right Pointer
	void			SetNext(AlphabetNode * node){pNext=node;}					// Set BST Next Pointer 

};

////////////////////////AlphabetQueue class////////////////////////////
class AlpaQueue
{
private:
	AlphabetNode * pHead;				

public:
	AlpaQueue(){pHead = '\0';}
	~AlpaQueue(){}

	void			Push(AlphabetNode * node);		// insert node
	AlphabetNode *	Pop();							// pop node
	AlphabetNode *	Search(char * word);			// searching node

	AlphabetNode* GetHead(){return pHead;}			//get AlpaQueue head
};

////////////////////////AlphabetStack class////////////////////////////
class AlphaStack
{
private:
	AlphabetNode * pHead;

public:
	AlphaStack();
	~AlphaStack(){}

	void		Push(AlphabetNode * n);			//insert node
	AlphabetNode *	Pop();						//pop node

	AlphabetNode* GetHead(){return pHead;}		//get AlphaStack
};
#endif

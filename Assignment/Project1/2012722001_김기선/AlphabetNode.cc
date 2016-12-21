#include "AlphabetNode.h"

AlphabetNode::AlphabetNode()	//constructor//
{		/*first set*/
	bst = new WordBST;	//make word bst
	alphabet = '\0';	//null set
	pLeft = '\0';
	pRight = '\0';
	pNext = '\0';
}


AlphabetNode::~AlphabetNode()	//destructor//
{
	delete bst;	//delete word bst
}
/*GET PART*/
WordBST	* AlphabetNode::GetBST()	
{
	return bst;		//return wordbst
}

char AlphabetNode::GetAlphabet()
{
	return alphabet;	//return alphabet
}


AlphabetNode * AlphabetNode::GetLeft()
{
	return pLeft;	//return Left child
}


AlphabetNode *	AlphabetNode::GetRight()
{
	return pRight;	//return Right child
}

AlphabetNode *	AlphabetNode::GetNext()
{
	return pNext;	//return Next
}
/*SET PART*/
void AlphabetNode::SetAlphabet(char alphabet)
{
	this->alphabet = alphabet;	//setting new alphabet
}


void AlphabetNode::SetLeft(AlphabetNode * node)
{
	pLeft = node;	//setting Left 
}


void AlphabetNode::SetRight(AlphabetNode * node)
{
	pRight = node;	//setting Right
}

void AlphabetNode::SetNext(AlphabetNode * node)
{
	pNext = node;	//setting Next
}

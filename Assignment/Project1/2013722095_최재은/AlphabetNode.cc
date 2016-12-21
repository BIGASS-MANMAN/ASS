#include "AlphabetNode.h"



AlphabetNode::AlphabetNode()
{
	alphabet = '\0';	//set alphabet into null
	bst = new WordBST;	//set bst into new
	pLeft = '\0';	//set pleft into null
	pRight = '\0';	//set pright into null
}


AlphabetNode::~AlphabetNode()
{
	delete bst;
}

void AlphabetNode::SetAlphabet(char alphabet)			//alphabet setalphabet
{
	this->alphabet = alphabet;
};
void AlphabetNode::SetLeft(AlphabetNode* node)			//alphabet setleft
{
	pLeft = node;
};
void AlphabetNode::SetRight(AlphabetNode* node)			//alphabet setright
{
	pRight = node;
};
void AlphabetNode::SetSNext(AlphabetNode* node)			//alphabet setsnext
{
	pSNext = node;
};

AlphabetNode* AlphabetNode::GetSNext()					//alphabet getsnext
{
	return pSNext;
}
char AlphabetNode::GetAlphabet()						//alphabet getalphabet
{
	return this->alphabet;
};
WordBST* AlphabetNode::GetBST()							//alphabet getbst
{
	return bst;
}
AlphabetNode* AlphabetNode::GetLeft()					//alphabet getleft
{
	return pLeft;
};
AlphabetNode* AlphabetNode::GetRight()					//alphabet getright
{
	return pRight;
};
void AlphabetNode::SetNext(AlphabetNode* node)			//alphabet setnext
{
	pNext = node;
}
AlphabetNode*	AlphabetNode::GetNext()					//alphabet getnext
{
	return pNext;
};
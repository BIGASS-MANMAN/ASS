#include "WordNode.h"



WordNode::WordNode()
{
	wordmean.first = new char[32]; //initialize wordmean.first
	wordmean.second = new char[32]; //initialize wordmean.second 
	pLeft = '\0'; //set pLeft to NULL
	pRight = '\0'; //set pRight to NULL
	pNext = '\0'; //set pNext to NULL
	pSnext = '\0'; //set pSnext to NULL
}
WordNode::~WordNode()
{
	delete wordmean.first;
	delete wordmean.second;
}
WordNode*	WordNode::GetLeft()				// Get BST Left Pointer
{
	return pLeft;
};
WordNode* WordNode::GetRight()					// Get BST Right Pointer
{
	return pRight;
};
WordNode*	WordNode::GetNext()					// Get Queue Next Pointer
{
	return pNext;
};
WordNode* WordNode::GetSnext()			//Get BST Save Next Pointer
{
	return pSnext;
}
char*	WordNode::GetWord()				// Get Word
{
	return wordmean.first;
};
char*	WordNode::GetMean()				// Get Word Mean
{
	return wordmean.second;
};
void WordNode::SetWord(char* word) //Set word
{
	strcpy(wordmean.first, word);
};
void WordNode::SetMean(char* mean) //Set mean
{
	
	strcpy(wordmean.second,mean);
};
void WordNode::SetLeft(WordNode* node) //Set BST left
{
	pLeft = node;
};
void WordNode::SetRight(WordNode* node) //Set BST right
{
	pRight = node;
}
void WordNode::SetNext(WordNode* node) //set next
{
	pNext = node;
}
void WordNode::SetSnext(WordNode* node) // Set snext
{
	pSnext = node;
}
void WordNode::SetNext2(WordNode* node)    // Set next2
{
	pNext2 = node;
}
WordNode*	WordNode::GetNext2()	// Get Queue Next2
{
	return pNext2;
};
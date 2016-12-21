#include "WordNode.h"

WordNode::WordNode()
{
	wordmean.first = word; // pair wordmean's first point the word.
	wordmean.second = mean; // pair wordmean's second point the mean.
	pLeft = '\0';
	pRight = '\0';
	pNext = '\0';
}

WordNode::~WordNode()
{
}

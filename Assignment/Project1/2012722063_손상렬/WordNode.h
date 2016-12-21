#ifndef _WORDNODE_H_
#define _WORDNODE_H_

#include <iostream>
#include <utility>
#include <malloc.h>
#pragma execution_character_set("utf-8")

using namespace std;

class WordNode
{
public:
	std::pair<char *, char *> wordmean;
	WordNode * pLeft;
	WordNode * pRight;
	WordNode * pNext;


public:
	WordNode();
	~WordNode();

	char *		GetWord();
	char *		GetMean();
	WordNode *	GetLeft();
	WordNode *	GetRight();
	WordNode *	GetNext();

	void		SetWord(char * word);
	void		SetMean(char * mean);
	void		SetLeft(WordNode * node);
	void		SetRight(WordNode * node);
	void		SetNext(WordNode * node);
};

#endif

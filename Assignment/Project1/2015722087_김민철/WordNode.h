#ifndef _WORDNODE_H_
#define _WORDNODE_H_

#include <utility>
#include <cstring>

class WordNode
{
private:
	std::pair<char *, char *> wordmean;
	char word[32];
	char mean[32];
	WordNode * pLeft;	// BST Left Pointer
	WordNode * pRight;	// BST Right Pointer
	WordNode * pNext;	// Queue Next Pointer

public:
	WordNode();
	~WordNode();

	char * GetWord()
	{
		return wordmean.first;
	}

	char * GetMean()
	{
		return wordmean.second;
	}

	WordNode * GetLeft()
	{
		return pLeft;
	}

	WordNode * GetRight()
	{
		return pRight;
	}

	WordNode * GetNext()
	{
		return pNext;
	}

	void SetWord(char * word)
	{
		int cnt = 0;
		// copy string
		while (1)
		{
			wordmean.first[cnt++] = *word;
			if (*word == NULL)
				return;
			else
				word += 1;
		}
	}

	void SetMean(char * mean)
	{
		int cnt = 0;
		// copy string
		while (1)
		{
			wordmean.second[cnt++] = *mean;
			if (*mean == NULL)
				return;
			else
				mean += 1;
		}
	}

	void SetLeft(WordNode * node)
	{
		pLeft = node;
	}

	void SetRight(WordNode * node)
	{
		pRight = node;
	}

	void SetNext(WordNode * node)
	{
		pNext = node;
	}
};

#endif

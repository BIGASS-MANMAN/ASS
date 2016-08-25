#pragma once

#include "Alphabet.h"

class Word
{
    private:
	char m_Word[128];
	char m_Mean[128];
	Word* m_pLeft;
	Word* m_pRight;
	Word* m_pNext;
    public:
	Word();
	~Word();

	void setWord(char* Word);
	void setMean(char* Mean);
	void setLeft(Word* Left);
	void setRight(Word* Right);
	void setNext(Word* Next);

	char* getWord();
	char* getMean();
	Word* getLeft();
	Word* getRight();
	Word* getNext();
};

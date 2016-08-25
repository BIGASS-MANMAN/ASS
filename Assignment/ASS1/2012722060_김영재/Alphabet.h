#pragma once

#include <limits.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <signal.h>
#include "WORD_BST.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

class Word;
class Alphabet
{
    private:
	WORD_BST* WORD;

	char m_Alp;
	Alphabet *m_pLeft, *m_pRight;
    public:
	Alphabet();
	~Alphabet();

	WORD_BST* getBST();
	Word* getRoot();

	void setAlp(char Alp);
	void setLeft(Alphabet* Left);
	void setRight(Alphabet* Right);

	char getAlp();
	Alphabet* getLeft();
	Alphabet* getRight();
};

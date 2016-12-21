#pragma once
#include <stdio.h>

class Word;
class Alphabet;
class WORD_BST
{
    private:
	Word* m_pRoot;
	Alphabet* m_Index;

    public:
	WORD_BST();

	void setRoot(Word* Root);
	void setIndex(Alphabet* Index);

	Word* getRoot();
	Alphabet* getIndex();

	int Insert(Word* Node);
	Word* Pop(char* word);
	Word* Search(char* word);
	void Traversal(Word* Node);
	void PreTraversal(Word* Node, FILE* file);
	int Update(char* word, char* Mean);
};

#pragma once

#include "ALP_BST.h"
#include "Queue.h"
#include "CircularQueue.h"

class Manager
{
    private:
	//Queue* Q;
	//CircularQueue* CQ;
	//ALP_BST* ALPTREE;

	//ifstream m_fin;
	//ofstream m_fout;
	FILE* m_fin;
	FILE* m_fin2;
	FILE* m_fout;

	int MemorizingCount;

    public:
	Manager();
	~Manager();
	Queue* Q;
	CircularQueue* CQ;
	ALP_BST* ALPTREE;


	Word* MakeNode(char* str);
	Alphabet* MakeNode2(char alp);
	int InsertAlp(char* str);
	int InsertWord(Word* Node);

	int InputFileOpen(char* file);
	int InputFileOpen2(char* file);
	int OutputFileOpen(char* file);

	int COMMAND(char* file);
	int LOAD();
	int LOAD(char* file);

	int SAVE();

	int MEMORIZE(char* word, char* mean);

	int SEARCH(char* word);

	void TRAVERSAL(char* command);

	void SubTraversal(Alphabet* Node);
	void PreTraversal(Alphabet* Node);

	int UPDATE(char* word, char* mean);
};

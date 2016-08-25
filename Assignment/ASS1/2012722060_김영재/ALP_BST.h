#pragma once

#include "Word.h"

extern void segfault_sigaction(int signal, siginfo_t *si, void *arg);

class ALP_BST
{
    private:
	Alphabet* m_pRoot;

    public:
	ALP_BST();

	void setRoot(Alphabet* Root);
	Alphabet* getRoot();

	int Insert(Alphabet* Node);
	Alphabet* Search(char alp);
	void Traversal(Alphabet* Node);
};

#pragma once

#include "Node.h"
#include <signal.h>
#include <stdlib.h>

void segfault_sigaction(int signal, siginfo_t *si, void *arg);

class BST
{
    private:
	Node* pRoot;

    public:
	BST();
	void setRoot(Node* Root);
	Node* getRoot();
	Node* Insert(int value);
	int Delete(int value);
	char* traversal(Node* pCur, char* arr);
};


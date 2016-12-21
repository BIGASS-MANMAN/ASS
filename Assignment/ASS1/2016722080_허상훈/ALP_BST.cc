#include "ALP_BST.h"
/*
void segfault_sigaction(int signal, siginfo_t *si, void *arg)
{
    if(signal == SIGSEGV)
    {
	cerr<<"segmentation fault";
	exit(-1);
    }
    else if(signal == SIGALRM)
    {
	cerr<<"infinite loop";
	exit(-1);
    }
}*/


ALP_BST::ALP_BST()
{
    m_pRoot = NULL;
}

void ALP_BST::setRoot(Alphabet* Root)
{
    m_pRoot = Root;
}

Alphabet* ALP_BST::getRoot()
{
    return m_pRoot;
}

int ALP_BST::Insert(Alphabet* Node)
{
    
    Alphabet* pCur = this->m_pRoot;

    if(this->m_pRoot == '\0')
    {
	this->m_pRoot = Node;
	return 0;
    }

    while(1)
    {
	if(pCur->getAlp() < Node->getAlp())
	{
	    if(pCur->getRight() == '\0')
	    {
		pCur->setRight(Node);
		return 0;
	    }
	    else
	    {
		pCur = pCur->getRight();
	    }
	}
	else
	{
	    if(pCur->getLeft() == '\0')
	    {
		pCur->setLeft(Node);
		return 0;
	    }
	    else
	    {
		pCur = pCur->getLeft();
	    }
	}
    }

}

Alphabet* ALP_BST::Search(char alp)
{
    Alphabet* pCur = this->m_pRoot;

    while(pCur->getAlp() != alp)
    {
	if(pCur->getAlp() < alp)
	{
	    pCur = pCur->getRight();
	}
	else
	{
	    pCur = pCur->getLeft();
	}
	if(pCur == NULL)
	    return NULL;
    }
    return pCur;
}

void ALP_BST::Traversal(Alphabet* Node)
{
    if(Node == NULL)
	return;
    cout<<Node->getAlp()<<endl;
    Traversal(Node->getLeft());
    Traversal(Node->getRight());
}

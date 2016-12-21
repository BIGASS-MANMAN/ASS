#include "WORD_BST.h"
#include "Alphabet.h"
#include "Word.h"

void segfault_sigaction(int signal, siginfo_t *si, void *arg);


WORD_BST::WORD_BST()
{
    m_pRoot = NULL;
    m_Index = NULL;
}

void WORD_BST::setRoot(Word* Root)
{
    m_pRoot = Root;
}

void WORD_BST::setIndex(Alphabet* Index)
{
    m_Index = Index;
}

Word* WORD_BST::getRoot()
{
    return m_pRoot;
}

Alphabet* WORD_BST::getIndex()
{
    return m_Index;
}

int WORD_BST::Insert(Word* Node)
{
    Word* pCur = this->m_pRoot;

    if(this->m_pRoot == '\0')
    {
	this->m_pRoot = Node;
	return 0;
    }

    while(1)
    {
	if(strcmp(pCur->getWord(),Node->getWord()) < 0)
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
	else if(strcmp(pCur->getWord(), Node->getWord()) > 0)
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
	else
	{
	    cout<<"Same Word"<<endl;
	    return 0;
	}
    }

}

Word* WORD_BST::Search(char* word)
{
    Word* pCur = this->m_pRoot;

    if(pCur == NULL)
	return NULL;

    while(strcmp(pCur->getWord(),word) != 0)
    {
	if(strcmp(pCur->getWord(),word) < 0)
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

void WORD_BST::Traversal(Word* Node)
{
    if(Node == NULL)
	return;
    Traversal(Node->getLeft());
    cout<<Node->getWord()<<" : "<<Node->getMean()<<endl;
    Traversal(Node->getRight());

}

void WORD_BST::PreTraversal(Word* Node, FILE* file)
{
    char sentence[128];
    memset(sentence,0,128);

    if(Node == NULL)
	return;

    strcpy(sentence, Node->getWord());
    strcat(sentence, "\t");
    strcat(sentence, Node->getMean());
    strcat(sentence, "\n");

    fputs(sentence, file);
    PreTraversal(Node->getLeft(),file);
    PreTraversal(Node->getRight(),file);
}

int WORD_BST::Update(char* word, char* Mean)
{
    Word* pCur = this->m_pRoot;

    while(strcmp(pCur->getWord(),word) != 0)
    {
	//if(pCur->getValue() < a->getValue())
	if(strcmp(pCur->getWord(),word) < 0)
	{
	    pCur = pCur->getRight();
	}
	else
	{
	    pCur = pCur->getLeft();
	}
	if(pCur == NULL)
	    return -1;
    }

    pCur->setMean(Mean);
    return 0;

}

Word* WORD_BST::Pop(char* word)
{
    Word* pCur = m_pRoot;
    Word* ppCur = '\0';
    Word* temp = '\0', *temp2 = '\0';


	//while(pCur->getValue() != value)
	while(strcmp(pCur->getWord(),word) != 0)
	{
	    ppCur = pCur;

	    if(strcmp(pCur->getWord(),word) < 0)
	    {
		pCur = pCur->getRight();
	    }
	    else
	    {
		pCur = pCur->getLeft();
	    }
	}


    if(pCur->getLeft() == '\0' && pCur->getRight() == '\0')
    {
	if(pCur == m_pRoot)
	{
	    m_pRoot = '\0';
	}
	else
	{
	    if(ppCur->getLeft() == pCur)
		ppCur->setLeft('\0');
	    else
		ppCur->setRight('\0');
	}

	return pCur;
    }
    else if(pCur->getLeft() == '\0' || pCur->getRight() == '\0')
    {
	temp = (pCur->getLeft() != '\0') ? pCur->getLeft() : pCur->getRight();
	if(pCur == m_pRoot)
	{
	    m_pRoot = temp;
	}
	else
	{
	    if(ppCur->getLeft() == pCur)
		ppCur->setLeft(temp);
	    else
		ppCur->setRight(temp);
	}

	return pCur;
    }
    else
    {
	temp = pCur->getRight();
	if(temp->getLeft() == '\0')
	{
	    temp->setLeft(pCur->getLeft());
	    if(pCur == m_pRoot)
	    {
		m_pRoot = temp;
	    }
	    else
	    {
		if(ppCur->getLeft() == pCur)
		    ppCur->setLeft(temp);
		else
		    ppCur->setRight(temp);
	    }
	    return pCur;
	}
	while(temp->getLeft() != '\0')
	{
	    temp2 = temp;
	    temp = temp->getLeft();
	}
	temp2->setLeft(temp->getRight());
	temp->setLeft(pCur->getLeft());
	temp->setRight(pCur->getRight());
	pCur->setLeft(NULL);
	pCur->setRight(NULL);
	cout<<pCur->getWord()<<endl;
	if(pCur == m_pRoot)
	{
	    m_pRoot = temp;
	    return pCur;
	}

	if(ppCur->getLeft() == pCur)
	    ppCur->setLeft(temp);
	else
	    ppCur->setRight(temp);

	return pCur;
    }
    return 0;
}

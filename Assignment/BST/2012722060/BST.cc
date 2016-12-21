#include "/usr/local/Auto_Scoring_System/src/signal.h"
#include "BST.h"

BST::BST()
{
    pRoot = '\0';
}
void BST::setRoot(Node* Root)
{
    this->pRoot = Root;
}

Node* BST::getRoot()
{
    return this->pRoot;
}

char* BST::traversal(Node* pCur, char* arr)
{
    char buf[100] = {0,};
    if(pCur == pRoot)
    {
	memset(arr,0,1000);
    }

    if(pCur == '\0') 
    {
	return arr;
    }

    traversal(pCur->getLeft(), arr);

    sprintf(buf, "%d", pCur->getValue());
    strcat(arr, buf);

    traversal(pCur->getRight(), arr);
    return arr;
}

Node* BST::Insert(int value)
{
	struct sigaction sa;
	set_sigaction(sa);
	alarm(3);

    Node* a = new Node;
    Node* pCur = this->pRoot;

    a->setValue(value);
    if(this->pRoot == '\0')
    {
	this->pRoot = a;
	return '\0';
    }

    while(1)
    {
	if(pCur->getValue() < a->getValue())
	{
	    if(pCur->getRight() == '\0')
	    {
		pCur->setRight(a);
		return '\0';
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
		pCur->setLeft(a);
		return '\0';
	    }
	    else
	    {
		pCur = pCur->getLeft();
	    }
	}
    }
}

int BST::Delete(int value)
{
	struct sigaction sa;
	set_sigaction(sa);
	alarm(3);

    Node* pCur = pRoot;
    Node* ppCur = '\0';
    Node* temp = '\0';
    int data = 0;

    while(1)

    while(pCur->getValue() != value)
    {
	ppCur = pCur;
	if(pCur->getValue() < value)
	    pCur = pCur->getRight();
	else
	    pCur = pCur->getLeft();
    }


    data = pCur->getValue();

    if(pCur->getLeft() == '\0' && pCur->getRight() == '\0')
    {
	if(pCur == pRoot)
	{
	    pRoot = '\0';
	}
	else
	{
	    if(ppCur->getLeft() == pCur)
		ppCur->setLeft('\0');
	    else
		ppCur->setRight('\0');
	}

	delete pCur;
	return data;
    }
    else if(pCur->getLeft() == '\0' || pCur->getRight() == '\0')
    {
	temp = (pCur->getLeft() != '\0') ? pCur->getLeft() : pCur->getRight();
	if(pCur == pRoot)
	{
	    pRoot = temp;
	}
	else
	{
	    if(ppCur->getLeft() == pCur)
		ppCur->setLeft(temp);
	    else
		ppCur->setRight(temp);
	}

	delete pCur;
	return data;
    }
    else
    {
	temp = pCur->getRight();
	if(temp->getLeft() == '\0')
	{
	    temp->setLeft(pCur->getLeft());
	    if(pCur == pRoot)
	    {
		pRoot = temp;
	    }
	    else
	    {
		ppCur->setRight(temp);
	    }
	    delete pCur;
	    return data;
	}
	ppCur = temp;

	while(temp->getLeft() != '\0')
	{
	    ppCur = temp;
	    temp = temp->getLeft();
	}
	ppCur->setLeft('\0');
	pCur->setValue(temp->getValue());
	delete temp;
	return data;
    }
    return 0;
}

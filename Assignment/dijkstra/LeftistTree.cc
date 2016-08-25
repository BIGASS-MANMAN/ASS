#include "LeftistTree.h"
LeftistTree::LeftistTree()
{
    root = NULL;
}
Edge* LeftistTree::getRoot()
{
    return this->root;
}
void LeftistTree::setRoot(Edge* root)
{
    this->root = root;
}
Edge* LeftistTree::Insert(edge* a, edge* b)
{
    if (!a)			//a = NULL, root = b;
    {
	this->setRoot(b);
	return this->root;
    }

    else if (b)		//a, b exist
    {
	Edge* temp = NULL;	//Node* for swap

	if (a->getCost() > b->getCost())//변한 값이 안 넘어옴
	    return this->Insert(b, a);

	else
	{
	    if (a->getRight())
		a->setRight(Insert(a->getRight(), b));
	    else
		a->setRight(b);
	}

	if (!a->getLeft()) {
	    a->setLeft(a->getRight());
	    a->setRight(NULL);
	}

	else if (a->getLeft()->getShort() < a->getRight()->getShort())
	{
	    temp = a->getRight();
	    a->setRight(a->getLeft());
	    a->setLeft(temp);
	}
	else{}

	if (!a->getRight()) {
	    a->setShort(1);
	}

	else {
	    a->setShort((a->getRight())->getShort() + 1);
	}
    };
    return a;

}
Edge* LeftistTree::Delete()
{
    Edge* Left = NULL;
    Edge* Right = NULL;
    Edge* Root = NULL;
    Edge* oldRoot = this->getRoot();

    Left = this->root->getLeft();
    Right = this->root->getRight();

    this->root->setLeft(NULL);
    this->root->setRight(NULL);

    Root = this->Insert(Left, Right);
    this->setRoot(Root);
    return oldRoot;
}

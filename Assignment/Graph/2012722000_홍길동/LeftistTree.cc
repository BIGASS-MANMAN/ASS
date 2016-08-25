#include "LeftistTree.h"
LeftistTree::LeftistTree()
{
	root = NULL;
}
edge* LeftistTree::getRoot()
{
	return this->root;
}
void LeftistTree::setRoot(edge* root)
{
	this->root = root;
}
edge* LeftistTree::Insert(edge* a, edge* b)
{
	if (!a)					//a = NULL, root = b;
	{
		this->setRoot(b);
		return this->root;
	}

	else if (b)				//a, b exist
	{
		edge* temp = NULL;	//Node* for swap

		
		if (a->getCost() > b->getCost())//변한 값이 안 넘어옴
		{
			return this->Insert(b, a);//


		}
		else
		{
			if (a->getRight())
			{
				a->setRight(Insert(a->getRight(), b));
				//this->Insert(a->getRight(), b);
			}
			else
			{
				a->setRight(b);
			}
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

		if (!a->getRight()) {
			a->setShort(1);
		}

		else {
			a->setShort((a->getRight())->getShort() + 1);
		}
	};
	return a;

}
edge* LeftistTree::Delete()
{
	edge* Left = NULL;
	edge* Right = NULL;
	edge* Root = NULL;
	edge* oldRoot = this->getRoot();

	Left = this->root->getLeft();
	Right = this->root->getRight();

	this->root->setLeft(NULL);
	this->root->setRight(NULL);

	Root = this->Insert(Left, Right);
	this->setRoot(Root);
	return oldRoot;
}

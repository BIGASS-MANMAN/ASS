#include "WordBST.h"

template<class T>
Stack<T>::Stack(int stackCapacity) : capacity(stackCapacity)
{
	if (capacity < 1) throw "Stack capacity must be >0";
	stack = new T[capacity];
	top = -1;
}

template<class T>
bool Stack<T>::IsEmpty() const { return top == -1; }


template<class T>
T & Stack<T>::Top() const
{
	if (IsEmpty()) throw "Stack is empty";
	return stack[top];
}


template<class T>
void Stack<T>::Push(const T & item)
{
	if (top == capacity - 1)
	{
		throw "Stack capacity is FULL";
	}
	stack[++top] = item;
}

template<class T>
void Stack<T>::Pop()
{
	if (IsEmpty()) throw "Stack is empty. Cannot delete.";
	stack[top--];
}

WordBST::WordBST()
{
	root = '\0';
}


WordBST::~WordBST()
{
	/* You must fill here */

}

void WordBST::Rec_preorder_Print()
{
	Rec_preorder_Print(root);
}

void WordBST::Rec_preorder_Print(WordNode * currentNode)
{
	if (currentNode) {
		ofstream FILEOUT;
		FILEOUT.open("log.txt", ios::app);

		FILEOUT << currentNode->GetWord() << " " << currentNode->GetMean() << endl;
		Rec_preorder_Print(currentNode->GetLeft());
		Rec_preorder_Print(currentNode->GetRight());

		FILEOUT.close();
	}
}

void WordBST::Iter_preorder_Print()
{
	ofstream FILEOUT;
	FILEOUT.open("log.txt", ios::app);

	WordNode * p = root, *pp = nullptr;

	while (1) {
		pp = p;
	
	}
}

void WordBST::Rec_inorder_Print()
{
	Rec_inorder_Print(root);
}

void WordBST::Rec_inorder_Print(WordNode * currentNode)
{
	if (currentNode) {
		ofstream FILEOUT;
		FILEOUT.open("log.txt", ios::app);

		Rec_inorder_Print(currentNode->GetLeft());
		FILEOUT << currentNode->GetWord() << " " << currentNode->GetMean() << endl;
		Rec_inorder_Print(currentNode->GetRight());

		FILEOUT.close();
	}
}

void WordBST::Iter_inorder_Print()
{
}

void WordBST::Rec_postorder_Print()
{
	Rec_postorder_Print(root);
}

void WordBST::Rec_postorder_Print(WordNode * currentNode)
{
	if (currentNode) {
		ofstream FILEOUT;
		FILEOUT.open("log.txt", ios::app);

		Rec_postorder_Print(currentNode->GetLeft());
		Rec_postorder_Print(currentNode->GetRight());
		FILEOUT << currentNode->GetWord() << " " << currentNode->GetMean() << endl;

		FILEOUT.close();
	}
}

void WordBST::Iter_postorder_Print()
{
}

void WordBST::Iter_level_Print()
{
}

void WordBST::Insert(WordNode * node)
{
}

WordNode * WordBST::Delete(char * word)
{
	return nullptr;
}

WordNode * WordBST::Search(char * word)
{
	return nullptr;
}

bool WordBST::Print(char * order)
{
	ofstream FILEOUT;
	FILEOUT.open("log.txt", ios::app);

	// memorizing BST - Recursive pre-order
	if (!strcmp(order, "R_PRE")) {
		FILEOUT << "======== PRINT ========" << endl;
	
		FILEOUT << "=======================" << endl << endl;
	}

	// memorizing BST - Iterative pre-order
	else if (!strcmp(order, "I_PRE")) {
		FILEOUT << "======== PRINT ========" << endl;

		FILEOUT << "=======================" << endl << endl;
	}

	// memorizing BST - Recursive in-order
	else if (!strcmp(order, "R_IN")) {
		FILEOUT << "======== PRINT ========" << endl;

		FILEOUT << "=======================" << endl << endl;
	}

	// memorizing BST - Iterative in-order
	else if (!strcmp(order, "I_IN")) {
		FILEOUT << "======== PRINT ========" << endl;

		FILEOUT << "=======================" << endl << endl;
	}

	// memorizing BST - Recursive post-order
	else if (!strcmp(order, "R_POST")) {
		FILEOUT << "======== PRINT ========" << endl;

		FILEOUT << "=======================" << endl << endl;
	}

	// memorizing BST - Iterative post-order
	else if (!strcmp(order, "I_POST")) {
		FILEOUT << "======== PRINT ========" << endl;

		FILEOUT << "=======================" << endl << endl;
	}

	// memorizing BST - Iterative level-order
	else if (!strcmp(order, "I_LEVEL")) {
		FILEOUT << "======== PRINT ========" << endl;

		FILEOUT << "=======================" << endl << endl;
	}
	else {
		return false;
	}
	return true;
}

bool WordBST::Save()
{
	return false;
}

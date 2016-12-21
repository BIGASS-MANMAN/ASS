#include "AlphabetBST.h"
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
/* Most Comments skip, because this file's code is very similar to WordBST */
/////////////////////////////////////////////////////////////////////////////

AlphabetBST::AlphabetBST()
{
	root = '\0';
	WordCnt = 0;
}


AlphabetBST::~AlphabetBST()		// Destructor using I_Post Travelsal
{
	if (!root)
		return;

	AlphabetStack s;
	AlphabetNode * pCur = root;
	AlphabetNode * pTemp = root;	// Recently the output node
	while (1)
	{
		if (pCur->GetLeft() == 0 && pCur->GetRight() == 0)	// If pCur is leaf node
		{
			delete pCur;
			pTemp = pCur;
			pCur = s.Top();
			s.Pop();
			if (pTemp == root)
				return;
			else
				continue;
		}

		s.Push(pCur);
		if (pCur->GetRight() == pTemp || pCur->GetLeft() == pTemp)	// If child is Recently the output node
		{
			s.Pop();
			delete pCur;
			pTemp = pCur;
			pCur = s.Top();
			s.Pop();
			if (pTemp == root)
				return;
			else
				continue;
		}
		// If pCur's child is exist, Push
		if (pCur->GetRight())	s.Push(pCur->GetRight());
		if (pCur->GetLeft())	s.Push(pCur->GetLeft());

		pCur = s.Top();
		s.Pop();
	}
}


void			AlphabetBST::Insert(AlphabetNode * node)	// run
{
	if (!root)		// If AlphabetBST is empty
	{
		root = node;	// root point the new node
		return;
	}

	AlphabetNode * pCur = root;
	while (1)
	{
		if (node->GetAlphabet() < pCur->GetAlphabet())
		{
			if (pCur->GetLeft())
				pCur = pCur->GetLeft();
			else
			{
				pCur->SetLeft(node);
				return;
			}
		}
		else if (node->GetAlphabet() > pCur->GetAlphabet())
		{
			if (pCur->GetRight())
				pCur = pCur->GetRight();
			else
			{
				pCur->SetRight(node);
				return;
			}
		}
		else
			return;
	}
}


AlphabetNode *	AlphabetBST::Search(char alphabet)	// LOAD, MOVE, TEST, SEARCH, UPDATE
{
	if (!root)
		return 0;

	AlphabetNode * pCur = root;
	char temp;

	// If input alphabet is lower case, converse to upper case
	if (alphabet > 'Z')
		temp = alphabet - ('a' - 'A');
	else
		temp = alphabet;

	while (1)
	{
		if (temp < pCur->GetAlphabet())
		{
			if (pCur->GetLeft())
				pCur = pCur->GetLeft();
			else
				return 0;
		}
		else if (temp > pCur->GetAlphabet())
		{
			if (pCur->GetRight())
				pCur = pCur->GetRight();
			else
				return 0;
		}
		else
			return pCur;
	}
}


bool			AlphabetBST::Print(char * order)	// PRINT
{
	ofstream fout("log.txt", ios::app);
	if (!root || WordCnt == 0)		// If BST is empty or empty words
		return false;

	if (strcmp(order, "R_PRE") == 0)
	{
		fout << "======== PRINT ========" << endl;
		cout << "======== PRINT ========" << endl;
		R_PreOrder(root, order);
		fout << "=======================" << endl << endl;
		cout << "=======================" << endl << endl;
		return true;
	}
	else if (strcmp(order, "I_PRE") == 0)
	{
		fout << "======== PRINT ========" << endl;
		cout << "======== PRINT ========" << endl;
		AlphabetStack s;
		AlphabetNode * pCur = root;
		while (pCur)
		{
			(pCur->GetBST())->Print(order);
			if (pCur->GetRight())	s.Push(pCur->GetRight());
			if (pCur->GetLeft())	s.Push(pCur->GetLeft());
			if (!s.pHead)
			{
				fout << "=======================" << endl << endl;
				cout << "=======================" << endl << endl;
				return true;
			}
			pCur = s.Top();
			s.Pop();
		}
	}
	else if (strcmp(order, "R_IN") == 0)
	{
		fout << "======== PRINT ========" << endl;
		cout << "======== PRINT ========" << endl;
		R_InOrder(root, order);
		fout << "=======================" << endl << endl;
		cout << "=======================" << endl << endl;
		return true;
	}
	else if (strcmp(order, "I_IN") == 0)
	{
		fout << "======== PRINT ========" << endl;
		cout << "======== PRINT ========" << endl;
		AlphabetStack s;
		AlphabetNode * pCur = root;
		while (1) {
			while (pCur)
			{
				s.Push(pCur);
				pCur = pCur->GetLeft();
			}
			if (!s.pHead)
			{
				fout << "=======================" << endl << endl;
				cout << "=======================" << endl << endl;
				return true;
			}
			pCur = s.Top();
			s.Pop();
			(pCur->GetBST())->Print(order);
			pCur = pCur->GetRight();
		}
	}
	else if (strcmp(order, "R_POST") == 0)
	{
		fout << "======== PRINT ========" << endl;
		cout << "======== PRINT ========" << endl;
		R_PostOrder(root, order);
		fout << "=======================" << endl << endl;
		cout << "=======================" << endl << endl;
		return true;
	}
	else if (strcmp(order, "I_POST") == 0)
	{
		fout << "======== PRINT ========" << endl;
		cout << "======== PRINT ========" << endl;
		AlphabetStack s;
		AlphabetNode * pCur = root;
		AlphabetNode * pTemp = root;
		while (1)
		{
			if (pCur->GetLeft() == 0 && pCur->GetRight() == 0)
			{
				(pCur->GetBST())->Print(order);
				pTemp = pCur;
				pCur = s.Top();
				s.Pop();
				if (pTemp == root)
				{
					fout << "=======================" << endl << endl;
					cout << "=======================" << endl << endl;
					return true;
				}
				else
					continue;
			}

			s.Push(pCur);
			if (pCur->GetRight() == pTemp || pCur->GetLeft() == pTemp)
			{
				s.Pop();
				(pCur->GetBST())->Print(order);
				pTemp = pCur;
				pCur = s.Top();
				s.Pop();
				if (pTemp == root)
				{
					fout << "=======================" << endl << endl;
					cout << "=======================" << endl << endl;
					return true;
				}
				else
					continue;
			}
			if (pCur->GetRight())	s.Push(pCur->GetRight());
			if (pCur->GetLeft())	s.Push(pCur->GetLeft());

			pCur = s.Top();
			s.Pop();
		}
	}
	else if (strcmp(order, "I_LEVEL") == 0)
	{
		fout << "======== PRINT ========" << endl;
		cout << "======== PRINT ========" << endl;
		AlphabetQueue q;
		AlphabetNode * pCur = root;
		while (pCur)
		{
			(pCur->GetBST())->Print(order);
			if (pCur->GetLeft())	q.Push(pCur->GetLeft());
			if (pCur->GetRight())	q.Push(pCur->GetRight());
			if (!q.pHead)
			{
				fout << "=======================" << endl << endl;
				cout << "=======================" << endl << endl;
				return true;
			}
			pCur = q.pHead;
			q.Pop();
		}
	}
	fout.close();
	return false;
}


bool			AlphabetBST::Save()		// SAVE
{
	if (!root || WordCnt == 0)			// If BST is empty or empty words
		return false;

	ofstream fout("memorizing_word.txt");
	fout.close();

	Save_InOrder(root);				// Save using I_InOrder traversal
	return true;
}


void		AlphabetBST::R_PreOrder(AlphabetNode * node, char * order)
{
	if (node)
	{
		(node->GetBST())->Print(order);
		R_PreOrder(node->GetLeft(), order);
		R_PreOrder(node->GetRight(), order);
	}
}


void		AlphabetBST::R_InOrder(AlphabetNode * node, char * order)
{
	if (node)
	{
		R_InOrder(node->GetLeft(), order);
		(node->GetBST())->Print(order);
		R_InOrder(node->GetRight(), order);
	}
}


void		AlphabetBST::R_PostOrder(AlphabetNode * node, char * order)
{
	if (node)
	{
		R_PostOrder(node->GetLeft(), order);
		R_PostOrder(node->GetRight(), order);
		(node->GetBST())->Print(order);
	}
}


void		AlphabetBST::Save_InOrder(AlphabetNode * node)		// Save using I_InOrder traversal
{
	AlphabetStack s;
	AlphabetNode * pCur = root;
	while (1) {
		while (pCur)
		{
			s.Push(pCur);
			pCur = pCur->GetLeft();
		}
		if (!s.pHead)
			return;
		pCur = s.Top();
		s.Pop();
		(pCur->GetBST())->Save();
		pCur = pCur->GetRight();
	}
}


AlphabetStack::AlphabetStack()
{
	pHead = '\0';		// Head pointer
}


AlphabetStack::~AlphabetStack()
{
	if (!pHead)		// If Stack is empty
		return;

	AlphabetNode * pCur = 0;
	while (pHead)
	{
		pCur = pHead;
		pHead = pHead->GetNext();
		pCur->SetNext(0);
		delete pCur;
	}
}


void		AlphabetStack::Push(AlphabetNode * node)
{
	if (!pHead)		// If Stack is empty
	{
		pHead = node;
		return;
	}

	AlphabetNode * pCur = pHead;
	while (pCur->GetNext())
		pCur = pCur->GetNext();
	pCur->SetNext(node);
}


void		AlphabetStack::Pop()
{
	if (!pHead)		// If Stack is empty
		return;

	if (!pHead->GetNext())
	{
		pHead = 0;
		return;
	}

	AlphabetNode * pCur = pHead;
	AlphabetNode * pPre = pHead;
	while (pCur->GetNext())
	{
		pPre = pCur;
		pCur = pCur->GetNext();
	}
	pPre->SetNext(0);
	return;
}


AlphabetNode *	AlphabetStack::Top()
{
	if (!pHead)		// If Stack is empty
		return 0;

	AlphabetNode * pCur = pHead;
	while (pCur->GetNext())
		pCur = pCur->GetNext();
	return pCur;
}


AlphabetQueue::AlphabetQueue()
{
	pHead = '\0';
}


AlphabetQueue::~AlphabetQueue()
{
	if (!pHead)		// If Queue is empty
		return;

	AlphabetNode * pCur = pHead;
	while (pHead)
	{
		pCur = pHead;
		pHead = pHead->GetNext();
		pCur->SetNext(0);
		delete pCur;
	}
}


void		AlphabetQueue::Push(AlphabetNode * node)
{
	if (!pHead)		// If Queue is empty
	{
		pHead = node;
		return;
	}

	AlphabetNode * pCur = pHead;
	while (pCur->GetNext())
		pCur = pCur->GetNext();
	pCur->SetNext(node);
}


AlphabetNode *	AlphabetQueue::Pop()
{
	if (!pHead)
		return 0;

	AlphabetNode * pCur = pHead;
	pHead = pHead->GetNext();
	pCur->SetNext(0);
	return pCur;
}

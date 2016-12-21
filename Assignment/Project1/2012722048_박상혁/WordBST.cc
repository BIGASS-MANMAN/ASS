#include "WordBST.h"
#include "Queue.h"
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;


WordBST::WordBST()
{
	root = '\0';
}


WordBST::~WordBST()		// Destructor using I_Post Travelsal
{
	if (!root)
		return;

	Stack s;
	WordNode * pCur = root;
	WordNode * pTemp = root;	// Recently the output node
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


void		WordBST::Insert(WordNode * node)	// LOAD, MOVE
{
	if (!root)		// If WordBST is empty
	{
		root = node;	// root point the new node
		return;
	}

	WordNode * pCur = root;
	while (1)
	{
		if (strcmp(node->GetWord(), pCur->GetWord()) < 0)	// If new node's word is smaller
		{
			if (pCur->GetLeft())				// If Left child is exist
				pCur = pCur->GetLeft();
			else						// If Left chlid isn't exist
			{
				pCur->SetLeft(node);			// Insert
				return;
			}
		}
		else if (strcmp(node->GetWord(), pCur->GetWord()) > 0)	// If new node's word is bigger
		{
			if (pCur->GetRight())				// If Right child is exist
				pCur = pCur->GetRight();
			else						// If Right child isn't exist
			{
				pCur->SetRight(node);			// Insert
				return;
			}
		}
		else 			// If same word is exist
			return;
	}
}


WordNode *	WordBST::Delete(char * word)		// TEST
{
	if (!root)			// If WordBST is empty
		return 0;

	WordNode * pCur = root;		// pCur: target
	WordNode * pPre = pCur;		// pPre: pCur's parents (If pCur is root, pCur = pPre)
	while (1)
	{
		if (strcasecmp(word, pCur->GetWord()) < 0)	// If word is smaller
		{
			if (pCur->GetLeft())			// If Left child is exist
			{
				pPre = pCur;
				pCur = pCur->GetLeft();		// Move to Left child
			}
			else					// If cannot find word
				return 0;
		}
		else if (strcasecmp(word, pCur->GetWord()) > 0)	// If word is bigger
		{
			if (pCur->GetRight())			// If Right child is exist
			{
				pPre = pCur;
				pCur = pCur->GetRight();	// Move to Right child
			}
			else					// If cannot find word
				return 0;
		}
		else						// If find the word
		{
			// case1: target is leaf node / No child
			if (pCur->GetLeft() == 0 && pCur->GetRight() == 0)
			{
				if (pCur == root)	// If target is root
				{
					root = '\0';	// Set the root NULL
					return pCur;
				}

				if (pPre->GetLeft() == pCur)	// If target is pPre's Left child
					pPre->SetLeft(0);
				else				// If target is pPre's Right child
					pPre->SetRight(0);
				
				return pCur;
			}
			else if (pCur->GetLeft() != 0)	// case2,4: target have Left child
			{
				WordNode * pTemp = pCur->GetLeft();	// pTemp: will be located in the deleted node
				WordNode * pTemp2 = pCur;		// pTemp2: pTemp's parents	(If pTemp is root, pTemp = pTemp2)

				while (pTemp->GetRight())	// Until pTemp doesn't have a Right child, move Right
				{
					pTemp2 = pTemp;
					pTemp = pTemp->GetRight();	// Move Right
				}

				if(pCur != pTemp2)
					pTemp2->SetRight(pTemp->GetLeft());

				if (pCur == root)		// If Target is root
				{
					if (pCur != pTemp2)	// If pTemp doesn't have a Right child
					{
						pTemp->SetLeft(root->GetLeft());
						pTemp->SetRight(root->GetRight());
						root = pTemp;
						return pCur;
					}
					else
					{
						pTemp->SetRight(root->GetRight());
						root = pTemp;
						return pCur;
					}
				}
				else if (pPre->GetLeft() == pCur)	// If pCur is pPre's Left child
					pPre->SetLeft(pTemp);		// Set pPre's Left pointer
				else					// If pCur is pPre's Right child
					pPre->SetRight(pTemp);		// Set pPre's Right pointer
				
				if (pCur != pTemp2)
					pTemp->SetLeft(pCur->GetLeft());	// Set pTemp's Left pointer

				pTemp->SetRight(pCur->GetRight());		// Set pTemp's Right pointer

				return pCur;
			}
			else				// case3: target only have Right child, (comment skip becuase similar to case2,4)
			{
				WordNode * pTemp = pCur->GetRight();
				WordNode * pTemp2 = pCur;

				while (pTemp->GetLeft())
				{
					pTemp2 = pTemp;
					pTemp = pTemp->GetLeft();
				}
			
				if(pCur != pTemp2)
					pTemp2->SetLeft(pTemp->GetRight());

				if (pCur == root)
				{
					if (pCur != pTemp2)
					{
						pTemp->SetRight(root->GetRight());
						root = pTemp;
						return pCur;
					}
					else
					{
						root = root->GetRight();
						return pCur;
					}
				}
				else if (pPre->GetLeft() == pCur)
					pPre->SetLeft(pTemp);
				else
					pPre->SetRight(pTemp);

				if (pCur != pTemp2)
					pTemp->SetRight(pCur->GetRight());

				return pCur;
			}
		}
	}
}

// Order name: R_(Recursive), I_(Iterative)
WordNode *	WordBST::Search(char * word)		// ADD, TEST, SEARCH, UPDATE
{
	if (!root)		// If WordBST is empty
		return 0;
	
	WordNode * pCur = root;
	while (1)
	{
		if (strcasecmp(word, pCur->GetWord()) < 0)	// If word is smaller
		{
			if (pCur->GetLeft())			// If pCur have Left child
				pCur = pCur->GetLeft();
			else					// If pCur doesn't have Left child
				return 0;
		}
		else if (strcasecmp(word, pCur->GetWord()) > 0)	// If word is bigger
		{
			if (pCur->GetRight())			// If pCur have Right child
				pCur = pCur->GetRight();
			else					// If pCur doesn't have Right child
				return 0;
		}
		else						// If find the word
			return pCur;				// Return that node
	}
}


bool		WordBST::Print(char * order)		// PRINT
{
	ofstream fout("log.txt", ios::app);	// Open the log.txt

	if (!root)		// If WordBST is empty
		return false;

	if (strcmp(order, "R_PRE") == 0)	// If order is R_PreOrder
	{
		R_PreOrder(root);
		return true;
	}
	else if (strcmp(order, "I_PRE") == 0)	// If order is I_PreOrder
	{
		Stack s;
		WordNode * pCur = root;
		while (pCur)
		{
			fout << pCur->GetWord() << " " << pCur->GetMean() << endl;
			cout << pCur->GetWord() << " " << pCur->GetMean() << endl;
		 	if (pCur->GetRight())	s.Push(pCur->GetRight());
			if (pCur->GetLeft())	s.Push(pCur->GetLeft());
			if (!s.pHead)
				return true;
			pCur = s.Top();
			s.Pop();
		}
	}
	else if (strcmp(order, "R_IN") == 0)	// If order is R_InOrder
	{
		R_InOrder(root);
		return true;
	}
	else if (strcmp(order, "I_IN") == 0)	// If order is I_InOrder
	{
		Stack s;
		WordNode * pCur = root;
		while (1) {
			while (pCur)
			{
				s.Push(pCur);
				pCur = pCur->GetLeft();
			}
			if (!s.pHead)
				return true;
			pCur = s.Top();
			s.Pop();
			fout << pCur->GetWord() << " " << pCur->GetMean() << endl;
			cout << pCur->GetWord() << " " << pCur->GetMean() << endl;
			pCur = pCur->GetRight();
		}
	}
	else if (strcmp(order, "R_POST") == 0)	// If order is R_PostOrder
	{
		R_PostOrder(root);
		return true;
	}
	else if (strcmp(order, "I_POST") == 0)	// If order is I_PostOrder
	{
		Stack s;
		WordNode * pCur = root;
		WordNode * pTemp = root;	// Recently the output node
		while (1)
		{
			if (pCur->GetLeft() == 0 && pCur->GetRight() == 0)	// If pCur is leaf node
			{
				fout << pCur->GetWord() << " " << pCur->GetMean() << endl;
				cout << pCur->GetWord() << " " << pCur->GetMean() << endl;
				pTemp = pCur;
				pCur = s.Top();
				s.Pop();
				if (pTemp == root)
					return true;
				else
					continue;
			}

			s.Push(pCur);
			if (pCur->GetRight() == pTemp || pCur->GetLeft() == pTemp)	// If child is Recently the output node
			{
				s.Pop();
				fout << pCur->GetWord() << " " << pCur->GetMean() << endl;
				cout << pCur->GetWord() << " " << pCur->GetMean() << endl;
				pTemp = pCur;
				pCur = s.Top();
				s.Pop();
				if (pTemp == root)
					return true;
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
	else if (strcmp(order, "I_LEVEL") == 0)		// If order is I_LEVEL order
	{
		Queue q;
		WordNode * pCur = root;
		while (pCur)
		{
			fout << pCur->GetWord() << " " << pCur->GetMean() << endl;
			cout << pCur->GetWord() << " " << pCur->GetMean() << endl;
			if (pCur->GetLeft())	q.Push(pCur->GetLeft());
			if (pCur->GetRight())	q.Push(pCur->GetRight());
			if (!q.pHead)	return true;
			pCur = q.pHead;
			q.Pop();
		}
	}
	fout.close();
	return false;		// If input order is not match
}


bool		WordBST::Save()			// SAVE
{
	if (!root)		// If WordBST is empty
		return false;
	
	Save_PreOrder(root);	// Save using PreOrder
	return true;
}


void		WordBST::R_PreOrder(WordNode * node)	// R_PreOrder traversal
{
	ofstream fout("log.txt", ios::app);		// Open the log.txt
	if (node)
	{
		fout << node->GetWord() << " " << node->GetMean() << endl;
		cout << node->GetWord() << " " << node->GetMean() << endl;
		R_PreOrder(node->GetLeft());
		R_PreOrder(node->GetRight());
	}
	fout.close();
}


void		WordBST::R_InOrder(WordNode * node)	// R_InOrder traversal
{
	ofstream fout("log.txt", ios::app);		// Open the log.txt

	if (node)
	{
		R_InOrder(node->GetLeft());
		fout << node->GetWord() << " " << node->GetMean() << endl;
		cout << node->GetWord() << " " << node->GetMean() << endl;
		R_InOrder(node->GetRight());
	}
	fout.close();
}


void		WordBST::R_PostOrder(WordNode * node)	// R_PostOrder traversal
{
	ofstream fout("log.txt", ios::app);		// Open the log.txt

	if (node)
	{
		R_PostOrder(node->GetLeft());
		R_PostOrder(node->GetRight());
		fout << node->GetWord() << " " << node->GetMean() << endl;
		cout << node->GetWord() << " " << node->GetMean() << endl;
	}
	fout.close();
}


void		WordBST::Save_PreOrder(WordNode * node)	// Save using I_PreOrder traversal
{	
	ofstream fout("memorizing_word.txt", ios::app);	// Open the file

	Stack s;
	WordNode * pCur = root;
	while (pCur)
	{
		fout << pCur->GetWord() << " " << pCur->GetMean() << endl;
		if (pCur->GetRight())	s.Push(pCur->GetRight());
		if (pCur->GetLeft())	s.Push(pCur->GetLeft());
		if (!s.pHead)
			return;
		pCur = s.Top();
		s.Pop();
	}
	fout.close();
}


Stack::Stack()
{
	pHead = '\0';			// Head pointer
}


Stack::~Stack()
{
	if (!pHead)			// If Stack is empty
		return;

	WordNode * pCur = 0;
	while (pHead)			// Until pHead is exist
	{
		pCur = pHead;
		pHead = pHead->GetNext();
		pCur->SetNext(0);
		delete pCur;
	}
}


void		Stack::Push(WordNode * node)	// Insert node
{
	if (!pHead)				// If Stack is empty
	{
		pHead = node;			// Head pointer point the new node
		return;
	}

	WordNode * pCur = pHead;
	while (pCur->GetNext())			// Until reach the end node
		pCur = pCur->GetNext();		// Move Next
	pCur->SetNext(node);
}


void		Stack::Pop()
{
	if (!pHead)				// If Stack is empty
		return;

	if (!pHead->GetNext())
	{
		pHead = 0;
		return;
	}

	WordNode * pCur = pHead;
	WordNode * pPre = pHead;
	while (pCur->GetNext())			// Until reach the end node
	{
		pPre = pCur;
		pCur = pCur->GetNext();		// Move Next
	}
	pPre->SetNext(0);			// Cut the pointer between pPre <-> end node
	return;
}


WordNode *	Stack::Top()			// Return recently the input node
{
	if (!pHead)				// If Stack is empty
		return 0;

	WordNode * pCur = pHead;
	while (pCur->GetNext())			// Until the end node
		pCur = pCur->GetNext();		// Move Next
	return pCur;
}

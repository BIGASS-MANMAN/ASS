#ifndef _CIRCULARLINKEDLIST_H_
#define _CIRCULARLINKEDLIST_H_

#include <fstream>
#include <iostream>
using namespace std;

#include "WordNode.h"

class CircularLinkedList
{
public:
	WordNode * pHead;

public:
	CircularLinkedList();
	~CircularLinkedList();

	void Insert(WordNode * node) // new node into the list
	{
		if (pHead == NULL) // first insert
		{
			pHead = node; // pHead point the new node.
			pHead->SetNext(pHead); // pHead's Next pointer point pHead
		}
		else
		{
			WordNode * pWork;
			pWork = pHead; // pWork point the pHead

			while (1) // new node insert to CircularLinkedList
			{
				if (pWork->GetNext() == pHead) // if pWork->Next same with pHead,
				{
					pWork->SetNext(node); // pWork->Next point the new node.
					node->SetNext(pHead); // new node->Next point the head node.
					break; // Insert Complete
				}
				else
					pWork = pWork->GetNext(); // pWork point the node that Next of pWork.
			}
		}
	}

	WordNode * Search(char * word) // search data in list
	{
		WordNode * pWork;
		pWork = pHead; // pWork point the head node.

		if (pHead == NULL) // if zero node in List,
		{
			return NULL;
		}

		while (1)
		{
			if (strcasecmp(pWork->GetWord(), word) == 1) // if find the node that user want to search,
				return pWork; // return search node
			else
			{
				if (pWork->GetNext() == pHead) // if fail to search the node,
					break;
				else
					pWork = pWork->GetNext(); // pWork point the node that Next of pWork.
			}
		}

		return NULL;
	}

	bool Print()
	{
		if (pHead != NULL) // if list exist
		{
			WordNode * pWork;
			pWork = pHead;

			ofstream foutprintc;
			foutprintc.open("log.txt", ios::app); // open the textfile "log.txt",

			cout << "======== PRINT ========" << endl; // print to screen
			foutprintc << "======== PRINT ========" << endl; // print to text file
			while (1)
			{
				cout << pWork->GetWord() << "  " << pWork->GetMean() << endl;
				foutprintc << pWork->GetWord() << "  " << pWork->GetMean() << endl;

				if (pWork->GetNext() == pHead) // if pWork is last node of list
					break;
				else
					pWork = pWork->GetNext();

			}
			cout << "=======================" << endl << endl;
			foutprintc << "=======================" << endl << endl;
			foutprintc.close(); // close the file.
			return true;
		}
		else
			return false;
	}

	bool Save()
	{
		if (pHead != NULL) // list exist
		{
			ofstream fout;
			fout.open("memorized_word.txt"); // open file

			WordNode * pWork;
			pWork = pHead;

			while (1)
			{
				fout << pWork->GetWord() << "," << pWork->GetMean() << endl; // print to text file.

				if (pWork->GetNext() == pHead)
					break;
				else
					pWork = pWork->GetNext();

			}
			return true;
		}
		else
			return false;
	}

};

#endif
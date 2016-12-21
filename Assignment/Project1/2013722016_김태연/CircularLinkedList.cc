#include "CircularLinkedList.h"
#include <iostream>
#include <fstream>
using namespace std;


CircularLinkedList::CircularLinkedList()                                      // constructor                      
{
	pHead = '\0';
}


CircularLinkedList::~CircularLinkedList()                                     // destructor
{
   WordNode* scan = pHead;
   WordNode* temp = NULL;
   while (pHead && scan!= pHead)
   {
      temp = scan->GetNext();
      delete scan;
      scan = temp;
   }
   delete scan;
}
void CircularLinkedList::Insert(WordNode* node) {                              // Insert

	WordNode *newNode = new WordNode();                                        // dynamic allocation   

	newNode->SetWord(node->GetWord());
	newNode->SetMean(node->GetMean());

	if (pHead == NULL) {                                                       // There is no Node
		pHead = newNode;
		return;
	}
	else {
		WordNode * scan = pHead;
		while (1) {
			if (scan->GetNext() == pHead || scan->GetNext() == NULL) {         // Node is Head, Null
				scan->SetNext(newNode);
				newNode->SetNext(pHead);
				return;
			}
			else {
				scan = scan->GetNext();
			}
		}
	}
}

WordNode* CircularLinkedList::Search(char * word) {                             // Search
	WordNode *pTemp = pHead;

	if (pHead == NULL) {                                                        // There is no Node
		return NULL;
	}
	else {
		while (1) {
			if (strcmp(pTemp->GetWord(), word) == 0) {                          // Search success
				ofstream fout;
				fout.open("log.txt", ios::app);
				fout << pTemp->GetWord() << " " << pTemp->GetMean() << endl;
				fout.close();
				cout << pTemp->GetWord() << " " << pTemp->GetMean() << endl;
				return pTemp;
			}
			if (pTemp->GetNext() == pHead || pTemp->GetNext() == NULL) {        // Search failure
				return NULL;
			}
			pTemp = pTemp->GetNext();
		}
	}
}
bool CircularLinkedList::Print() {                                               // Print
	WordNode* scan = pHead;
	ofstream fout;
	fout.open("log.txt", ios::app);
	if (pHead == NULL) {                                                         // There is no Node
		return 0;
	}
	else {
		cout << "======== PRINT =========" << endl;
		while (1) {
			fout << scan->GetWord() << " " << scan->GetMean() << endl;
			cout << scan->GetWord() << " " << scan->GetMean() << endl;
			if (scan->GetNext() == pHead || scan->GetNext() == NULL) {           // Node is Head, Null
				cout << "=======================" << endl;
				fout.close();
				return 1;
			}
			scan = scan->GetNext();
		}
	}
}
bool CircularLinkedList::Save() {                                               // Print
	ofstream fin_3;
	fin_3.open("memorized_word.txt");
	WordNode* scan = pHead;

	if (pHead == NULL) {                                                         // Node is Head, Null
		return 0;
	}
	else {
		while (1) {
			fin_3 << scan->GetWord() << "\t" << scan->GetMean() << endl;
			if (scan->GetNext() == pHead || scan->GetNext() == NULL) {           // Node is Head, Null
				fin_3.close();
				return 1;
			}
			scan = scan->GetNext();
		}
	}
}

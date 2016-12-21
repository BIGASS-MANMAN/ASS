#include "Queue.h"
#include <iostream>
#include <fstream>
using namespace std;


Queue::Queue() // Queue constructor
{
	pHead = '\0';
}


Queue::~Queue() // Queue destructor
{
	WordNode* scan = pHead;
	WordNode* temp = NULL;
	while (pHead && scan->GetNext()) // traversal to delete
	{
		temp = scan->GetNext();
		delete scan;
		scan = temp;
	}
	delete scan;
}
void Queue::Push(WordNode* node) // Push Function
{
	if (!node)
		return;

	WordNode * temp = pHead;

	WordNode * newnode = new WordNode(); // dynamic allocation
	newnode->SetMean(node->GetMean()); // Set newnode's mean
	newnode->SetWord(node->GetWord()); // Set newnode's word
	newnode->SetNext(NULL);   // Set newnode
	if (pHead == NULL)  // if pHead is NULL
		pHead = newnode; // pHead = newnode

	else // if pHead is not NULL
	{
		while (temp->GetNext()) // move to next node until tail
			temp = temp->GetNext();

		temp->SetNext(newnode);
	}
}

WordNode* Queue::Pop() // Pop Function
{
	WordNode* temp = pHead; 


	if (pHead == NULL) { // if pHead is NULL
		return NULL;
	}
	else if (pHead->GetNext() == NULL) // if there is only pHead
	{
		temp->SetNext(NULL);
		pHead = NULL; 
	}
	else // if queue has WordNodes more than 2
	{
		pHead = pHead->GetNext(); 
		temp->SetNext(NULL);
	}

	return temp; // return temp;
}

WordNode *Queue::Search(char * word) // Search Function
{
	WordNode* temp = pHead;

	if (!temp) // if temp is NULL
		return 0;
	while (temp) { // while temp is not NULL
		if (!strcmp(temp->GetWord(), word)) 
			return temp;	
		temp = temp->GetNext();
	}
	return 0;
}

bool Queue::Print() { // Print Function
	WordNode * temp = pHead;
	if (temp == NULL) { // if pHead is NULL
		return false;
	}
	else { // if pHead is not NULL
		ofstream fout; fout.open("log.txt", ios::app); 
		fout << "======== PRINT =========" << endl;
		cout << "======== PRINT =========" << endl;
		while (temp) { // while temp is not NULL
			fout <<  temp->GetWord() << " " << temp->GetMean() << endl;
			cout << temp->GetWord() << " " << temp->GetMean() << endl;
			temp = temp->GetNext();
		}
		cout << "=======================" << endl;
		fout << "=======================" << endl;
		fout.close();
		return true;
	}
}
bool Queue::Save() { // Save Function
	ofstream fin_1;
	fin_1.open("to_memorize_word.txt");

	WordNode * temp = pHead;
	if (temp == NULL) { // if pHead is NULL
		return false;
	}
	else { // if pHead is not NULL
		while (temp) {
			fin_1 << temp->GetWord() << "\t" << temp->GetMean() << endl;
			temp = temp->GetNext();
		}
		fin_1.close();
		return true;
	}
}

bool Queue::IsEmpty() { // IsEmpty Function
	return pHead == NULL;  
}

WordNode* Queue::GetpHead() { // GetpHead Function
	return pHead;
}

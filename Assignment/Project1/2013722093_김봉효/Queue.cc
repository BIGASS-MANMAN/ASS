#include "Queue.h"
#include <iostream>
#include<fstream>
#include<cstring>
using namespace std;


Queue::Queue()
{
	pHead = '\0';
}


Queue::~Queue()
{
	WordNode* cur = pHead, *temp=0;
	while (cur) {
		temp = cur;
		cur = cur->GetNext();
		delete temp;
	}

}
int Queue::CountNode() {
	int num = 0;
	WordNode* cur = pHead;
	while (cur) {
		cur = cur->GetNext();
		num++;
	}
	return num;
}
void Queue::Push(WordNode* node)
{	
	
	if (pHead == NULL) {
		pHead = node;
		return;
	}
	WordNode* rear = pHead;
	while (rear->GetNext() != NULL) {
		rear = rear->GetNext();
	}
	rear->SetNext(node);
}

WordNode* Queue::Pop()
{
	if (IsEmpty()) return 0;
	WordNode* front = pHead;
	pHead = pHead->GetNext();
	return front;
}

WordNode* Queue::Search(char* word)
{
	WordNode* cur = pHead;
	while (cur) {
		if (!strcasecmp(cur->GetWord(), word)) {
			return cur;
		}
		else
			cur = cur->GetNext();
	}
	return cur;
}

bool Queue::Print() 
{
	if (IsEmpty()) {
		return 0;
	}
	ofstream flog;
	flog.open("log.txt", ios::app);
	WordNode* cur = pHead;
	cout << "======== PRINT ========" << endl;
	flog << "======== PRINT ========" << endl;
	while (cur) {
		cout << cur->GetWord() << " " << cur->GetMean() << endl;
		flog << cur->GetWord() << " " << cur->GetMean() << endl;
		cur = cur->GetNext();
	}
	cout << "=======================\n" << endl;
	flog << "=======================\n" << endl;
	flog.close();
	return 1;
}

bool Queue::IsEmpty()
{
	if (pHead == NULL)
		return 1;
	return 0;
}
bool Queue::Save()
{
	WordNode* node = pHead;
	ifstream fin;
	fin.open("to_memorize_word.txt");
	if (!fin) {
		cout << "to_memorize_word.txt is not exist" << endl;
		return false;
	}
	if (IsEmpty()) {
		return 1;
	}
	ofstream fout;
	fout.open("to_memorize_word.txt",ios::trunc);
		while (node!= NULL) {
			fout << node->GetWord() << " " << node->GetMean() << endl;
			node = node->GetNext();
		}
		fin.close();
		fout.close();
		return true;
}

#include "CircularLinkedList.h"
#include <iostream>
#include <fstream>
using namespace std;


CircularLinkedList::CircularLinkedList()//Initialization of variables
{
	pHead = '\0';

}


CircularLinkedList::~CircularLinkedList()//Frees memory
{
	WordNode* pDel;
	if(pHead==NULL)
		delete pHead;
	else if(pHead->GetNext()==pHead)
		delete pHead;
	else
	{
		while(pHead)
		{
			pDel = pHead;
			pHead = pHead->GetNext();
			delete pDel;
		}
	}
}
void CircularLinkedList::Insert(WordNode* node)// Input node
{
	if(pHead == NULL)// case 1 : CLL is empty
	{
		pHead=new WordNode;//memory allocation
		pHead=node;
		pHead->SetNext(pHead);
	}
	else if(pHead->GetNext() == pHead)// case 2 : CLL has only pHead node
	{
		WordNode* pNext=new WordNode;
		pNext=node;
		pHead->SetNext(pNext);
		pNext->SetNext(pHead);
	}
	else// case 3 : CLL has many node
	{
		WordNode* pTemp=pHead;
		while(pTemp->GetNext() !=pHead)// Move form pHead to last node
		{
			pTemp=pTemp->GetNext();
		}
		WordNode* pNext=node;
		pTemp->SetNext(pNext);
		pNext->SetNext(pHead);
	}
}
WordNode* CircularLinkedList::Search(char* word)// Searching node
{
	if(pHead==NULL)// if CLL is empty return 0
		return 0;

	WordNode* pTemp=pHead;
	if(pTemp->GetNext() == pHead)
	{
		if(strcmp(pTemp->GetWord(),word) == 0)//Searching node has same word 
		{
			return pTemp;
		}
	}
	while(pTemp->GetNext() != pHead)//Move form pHead to last node
	{
		if(strcmp(pTemp->GetWord(),word) == 0)//Searching node has same word 
		{
			return pTemp;
		}
		pTemp=pTemp->GetNext();
	}
	if(pTemp->GetNext() == pHead)//if don't fine node
	{
		return NULL;//return NULL
	}
}
bool CircularLinkedList::Print()//print
{
	if(pHead==NULL)// if CLL is empty return 0;
	{
		return 0;
	}
	ofstream log;
	log.open("log.txt",ios::app);//log file open
	if(log.fail())
		return 0;
	WordNode* pTemp=pHead;
	cout<<"======== PRINT ========"<<endl;
	log<<"======== PRINT ========"<<endl;
	while(pTemp->GetNext() != pHead)// Move from pHead to last node and print
	{
		cout<<pTemp->GetWord()<<" "<<pTemp->GetMean()<<endl;
		log<<pTemp->GetWord()<<" "<<pTemp->GetMean()<<endl;
		pTemp=pTemp->GetNext();
	}
	cout<<"======================="<<endl;
	log<<"======================="<<endl;
	log.close();
	return 1;
}
bool CircularLinkedList::Save()// save the CLL
{
	if(pHead==NULL)// if CLL is empty return 0
		return 0;
	WordNode* pTemp=pHead;
	ofstream memorized;
	memorized.open("memorized_word.txt",ios::trunc);// open txt file
	if(memorized.fail())
	{
		return 0;
	}
	if(pHead->GetNext()==pHead)// CLL has one node 
		memorized<<pTemp->GetWord()<<"	"<<pTemp->GetMean()<<endl;
	else// CLL has many node
	{
		while(pTemp->GetNext()!=pHead)//Move from pHead to last node and out the txt file
		{
			memorized<<pTemp->GetWord()<<"	"<<pTemp->GetMean()<<endl;
		}
	}
	memorized.close();// close txt file
	return 1;
}

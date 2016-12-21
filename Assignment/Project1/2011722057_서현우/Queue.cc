#include "Queue.h"
#include <iostream>
#include <fstream>
using namespace std;


Queue::Queue()//Initialization of variables
{
	pHead = '\0';
}


Queue::~Queue()//Frees memory
{
	while(pHead!=NULL)
	{
		WordNode* pDel=pHead;
		pHead=pHead->GetNext();
		delete pDel;
	}

}
void Queue::Push(WordNode* node)// input node
{
	if(pHead==NULL)// case 1 : pHead is NULL
	{
		//pHead=new WordNode;// memory allocation
		pHead=node;//Substituting node to pHead
	}
	else// case 2: pHead is not NULL
	{
		WordNode* pTemp=pHead;//Substituting pHead to pTemp
		while(pTemp->GetNext()!=NULL)//Move last node
		{
			pTemp=pTemp->GetNext();
		}
		pTemp->SetNext(node);//Setting the last node's next node
	}

		
}
WordNode* Queue::Pop()// output node
{
	if(pHead==NULL)
		return NULL;
	else if(pHead->GetNext()==NULL)// case 1 : pHead's next node is NULL (queue has one node) 
	{
		WordNode* pTemp=new WordNode;
		pTemp->SetWord(pHead->GetWord());
		pTemp->SetMean(pHead->GetMean());
		pHead=NULL;		
		delete pHead;
		return pTemp;
	}
	else// case 2: queue has many node
	{
		WordNode* pTemp=pHead; //Substituting pHead to pTemp
		pHead=pHead->GetNext();//Move pHead to next node
		pTemp->SetNext(NULL);//set pTemp's next node NULL
		return pTemp;//return pTemp
	}
}
WordNode* Queue::Search(char* word)//Searching queue
{
	WordNode* pTemp=pHead;
	while(pTemp!=NULL)//Move pTemp to last node 
	{
		if(strcmp(pTemp->GetWord(),word)==0)//Searching node has same word 
		{
			return pTemp;// if find, return pTemp;
		}
		pTemp=pTemp->GetNext();
	}
	if(pTemp==NULL)// if don't fine node
	{
		return NULL;// return NULL
	}
}
bool Queue::Print()// print node
{
	if(pHead==NULL)// case 1: queue is empty
	{
		return 0;// return 0
	}
	ofstream log;
	log.open("log.txt",ios::app);//log file open
	if(log.fail())
		return 0;
	WordNode* pTemp=pHead;
	cout<<"======== PRINT ========"<<endl;
	log<<"======== PRINT ========"<<endl;
	while(pTemp != NULL)//Move node from pHead to last node
	{
		cout<<pTemp->GetWord()<<" "<<pTemp->GetMean()<<endl;// print
		log<<pTemp->GetWord()<<" "<<pTemp->GetMean()<<endl;// print
		pTemp=pTemp->GetNext();
	}
	cout<<"======================="<<endl;
	log<<"======================="<<endl;
	log.close();// log file close
	return 1;// return 1
}
bool Queue::Save()// save txt file
{
	ofstream output;
	output.open("to_memorize_word.txt",ios::trunc);// txt file open
	if(output.fail())// if fail to open txt file
	{
		return 0;
	}
	WordNode* pTemp=pHead;
	while(pTemp!=NULL)// Move node from pHead to last node
	{
		output<<pTemp->GetWord()<<"	"<<pTemp->GetMean()<<endl;// output to txt file
		pTemp=pTemp->GetNext();
	}
	output.close();// txt file close
	return 1;
}

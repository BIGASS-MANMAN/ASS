#include "Queue.h"
#include"WordNode.h"
#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;

/*constructor*/
Queue::Queue()
{
	pHead = '\0';
}


/*destructor, delete all node*/
Queue::~Queue()
{
	WordNode*temp=pHead;
	while(pHead!=NULL)
	{
		pHead=pHead->GetNext();
		delete temp;
		temp=pHead;
	}
	/* You must fill here */
}

/*insert node in queue list*/
void Queue::Push(WordNode*node)
{
	WordNode*pWork=pHead;
	/*if there's no node in queue list*/
	if(pHead==NULL)
		pHead=node;
	/*find last node in queue list and link after the last node*/
	else
	{
		for(pWork=pHead;pWork->GetNext()!=NULL;pWork=pWork->GetNext()){}
		pWork->SetNext(node);
	}
}

/*insert word and mean directly*/
void Queue::Push(const char*word,const char*mean)
{
	WordNode*node=new WordNode;
	node->SetWord(word);
	node->SetMean(mean);
	Push(node);
}

/*pop the first node in the queue list*/
WordNode*Queue::Pop()
{
	WordNode*pWork=pHead;
	pHead=pWork->GetNext();
	pWork->SetNext(NULL);
	return pWork;
}

/*search english word*/
WordNode*Queue::Search(const char*word)
{
	for(WordNode*ptr=pHead;ptr!=NULL;ptr=ptr->GetNext())
	{
		if(strcmp(ptr->GetWord(),word)==0)
			return ptr;
	}
	/*if there has not same word print error*/
	return NULL;
}

/*print the queue list*/
bool Queue::Print()
{
	if(pHead==NULL)
		return false;
	else
	{
		ofstream fout;
		fout.open("log.txt", ios::app);
		for(WordNode*ptr=pHead;ptr!=NULL;ptr=ptr->GetNext())
		{
			fout<<ptr->GetWord()<<"	"<<ptr->GetMean()<<endl;
			cout<<ptr->GetWord()<<"	"<<ptr->GetMean()<<endl;
		}
		fout.close();
		return true;
	}
}

/*save the queue list to to_memorize_word.txt using file i/o*/
bool Queue::Save()
{
	WordNode*ptr=pHead;
	ofstream fout;
	fout.open("to_memorize_word.txt",ios::trunc);
	/*if there has no file print error*/
	if(!fout)
	{
		return false;
	}
	/*save in the txt file*/
	while(ptr!=NULL)
	{
		fout<<ptr->GetWord()<<"	"<<ptr->GetMean()<<endl;
		ptr=ptr->GetNext();
	}
	fout << endl;
	fout.close();
	return true;
}


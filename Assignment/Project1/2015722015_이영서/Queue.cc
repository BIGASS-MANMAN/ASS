#include "Queue.h"
#include <fstream>
#include <cstring>

void Queue::Push(WordNode * node)
{
	if(node==NULL)
		return;

	if(pHead==NULL)
		pHead=node;
	else
	{
		WordNode* current=pHead;

		while(current->GetNext()){
			if(!strcmp(current->GetWord(),node->GetWord()) && !strcmp(current->GetMean(),node->GetMean()))
				return;//find same node
			current=current->GetNext();
		}
		current->SetNext(node);
	}

	SetWordCntup();
}
WordNode* Queue::Pop()
{
	if(pHead==NULL)
		return NULL;

	WordNode* node=pHead->GetNext();
	WordNode* popnode;

	pHead->SetNext(NULL);
	popnode=pHead;
	pHead=node;
	
	SetWordCntdown();

	return popnode;
}
WordNode* Queue::Search(char* word)
{
	if(pHead==NULL)
		return NULL;

	WordNode* current=pHead;
	while(current->GetNext()!=NULL){
		if(!strcmp(current->GetWord(),word))
				return current;//find same node
			current=current->GetNext();
	}
	return NULL;
}
bool Queue::Print()
{
	if(pHead==NULL){
		return false;
	}
	else{
		ofstream fout;	
		fout.open("log.txt",ios::app);

		cout<<"======== PRINT ========"<<endl;
		fout<<"======== PRINT ========"<<endl;
		WordNode* node=pHead;
		
		while(node){
			cout<<node->GetWord()<<" "<<node->GetMean()<<endl;
			fout<<node->GetWord()<<" "<<node->GetMean()<<endl;
			node=node->GetNext();
		}
		cout<<"======================="<<endl;
		fout<<"======================="<<endl;

		fout.close();

		return true;
	}
}
bool Queue::Save()
{
	WordNode* node=pHead;
	
	ofstream fout;
	fout.open("to_memorize_word.txt");
		
	while(node){
		fout<<node->GetWord()<<"\t"<<node->GetMean()<<endl;
		node=node->GetNext();
	}
	fout.close();
	return true;
}
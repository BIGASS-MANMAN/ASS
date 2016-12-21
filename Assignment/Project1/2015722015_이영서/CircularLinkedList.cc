#include "CircularLinkedList.h"
#include <fstream>
#include <cstring>

CircularLinkedList::CircularLinkedList()
{
	pHead = '\0';
}
CircularLinkedList::~CircularLinkedList()
{
	WordNode* node=pHead;
	WordNode* del;

	while(node->GetNext()!=NULL){
		del=node;
		node=node->GetNext();
		node=node->GetNext();
	}
}
void CircularLinkedList::Insert(WordNode * node)
{
	if(pHead==NULL){	//the first node
		pHead=node;
		pHead->SetNext(pHead);
	}
	else
	{
		WordNode* current=pHead;
		while(current->GetNext()!=pHead){
			if(!strcmp(current->GetWord(),node->GetWord()) && !strcmp(current->GetMean(),node->GetMean()))
				return;//find same node
			current=current->GetNext();
		}
		current->SetNext(node);
		node->SetNext(pHead);
	}
}
WordNode* CircularLinkedList::Search(char * word)
{
	if(pHead==NULL)	// circular linked list is empty
		return NULL;

	WordNode* current=pHead;
	while(current->GetNext()!=pHead){
		if(!strcmp(current->GetWord(),word))
				return current;//find same node
			current=current->GetNext();
	}
	return NULL;
}
bool CircularLinkedList::Print()
{
	if(pHead==NULL){	// circular linked list is empty
		return false;
	}
	else{
		ofstream fout;
		fout.open("log.txt",ios::app);

		WordNode* node=pHead;
		
		cout<<"======== PRINT ========"<<endl;
		fout<<"======== PRINT ========"<<endl;
		cout<<node->GetWord()<<" "<<node->GetMean()<<endl;
		fout<<node->GetWord()<<" "<<node->GetMean()<<endl;

		node=node->GetNext();
		while(node!=pHead){
			cout<<node->GetWord()<<" "<<node->GetMean()<<endl;
			fout<<node->GetWord()<<" "<<node->GetMean()<<endl;
			node=node->GetNext();
		}
		cout<<"======================="<<endl;

		fout.close();
		return true;
	}
}
bool CircularLinkedList::Save()
{
	if(pHead==NULL){	// circular linked list is empty
		return false;
	}

	WordNode* node=pHead;
	
	ofstream fout;
	fout.open("memorized_word.txt");
	
	fout<<node->GetWord()<<"\t"<<node->GetMean()<<endl;
	node=node->GetNext();

	while(node!=pHead){
		fout<<node->GetWord()<<"\t"<<node->GetMean()<<endl;
		node=node->GetNext();
	}

	fout.close();
	return true;
}
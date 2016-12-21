#include "Queue.h"

using namespace std;


Queue::Queue()
{
	pHead = '\0';      //initialize
}


Queue::~Queue()            //It deletes the memory
{
	WordNode* p = pHead;

	while (p) {

		pHead = p->GetNext();
		p->SetNext(NULL);
		delete p;
		p = pHead;
	}

}

bool Queue::IsEmpty() {         //Determine whether the queue is empty
	WordNode* p = pHead;
	if (p == NULL)            //Queue is empty
		return false;
	return true;
}


void Queue::Push(WordNode* node) {      //Push function
	WordNode* p = pHead;
	if (pHead == NULL)
		{
		 pHead = node;        
		 p = pHead;    //when there is no head
		}
	else {
		while (1)         //connect, turn the loop from head to tail
		{	
			if(p->GetNext() != NULL)
			p = p->GetNext();  
			else
			break;
		}       //'p' to move the tail
		p->SetNext(node);
	}
}

WordNode* Queue::Pop() {            //Pop function
	WordNode* p = pHead;

	if (IsEmpty() == false) {      //whene there is no Node
		return NULL;
	}

	else {
		pHead = p->GetNext();      //Moving a head and return p to the front 
		return p;
	}
}

WordNode* Queue::Search(char* word) {      //Search function
	WordNode* p = pHead;

	while (p->GetNext()) {                  ////turn the loop from head to tail
		if (strcmp(p->GetWord(), word) == 0)      //If you find a word and return
			return p;
		else
			p = p->GetNext();               //next node navigation
	}

	if (strcmp(p->GetWord(), word) == 0)         //Head when looking for a word
		return p;

	return NULL;                        //when a word is not found
}

bool Queue::Print() {         //Print function
	WordNode* p = pHead;

	ofstream fout;
	fout.open("log.txt", ios::app);

	if (!fout)
		return false;

	if (p == NULL) {
		return false;         //when there is no word output
	}

	while (p->GetNext()) {      //print, turn the loop from head to tail
		cout << p->GetWord() << " " << p->GetMean() << endl;
		fout << p->GetWord() << " " << p->GetMean() << endl;
		p = p->GetNext();
	}

	cout << p->GetWord() << " " << p->GetMean() << endl;
	fout << p->GetWord() << " " << p->GetMean() << endl;
	return true;
}

bool Queue::Save() {       //Save function
	WordNode* p = pHead;
	ofstream fout;

	fout.open("TO_MEMORIZED");
	if (!fout) {     //when there is no file
		return false;
	}
	if (p == NULL) {
		return false;         //when there is no word output
	}
	while (p->GetNext()) {      ////turn the loop from head to tail
		fout << p->GetWord() << " " << p->GetMean() << endl;      //save
		p = p->GetNext();
		
	}

	fout << p->GetWord() << " " << p->GetMean() << endl;
	return true;
}

int Queue::cnt() {         //Counting the number of nodes function
	WordNode* p = pHead;
	int i = 0;

	while (1) {   ////turn the loop from head to tail

		if(p->GetNext()==NULL)
		break;

		p = p->GetNext();
		i++;
	}
	i++;
	return i;
}

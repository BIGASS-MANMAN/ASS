#include "Queue.h"



Queue::Queue()
{
	pHead = '\0';
}


Queue::~Queue()
{
	if(pHead == NULL)
		return;
	
	WordNode* temp1 = pHead;      //initialize temp1 to pHead
	WordNode* temp2 = temp1;

	for (; temp1 != '\0'; )      //traversal all nodes
	{
		temp2 = temp1->GetNext();
		delete temp1;
		temp1 = temp2;
	}

}
void Queue::Push(WordNode * node)               // LOAD, ADD
{
	WordNode* p = pHead;
	if (pHead == '\0')         //if pHead equal to '\0'
		pHead = node;
	else                  //if pHead is not equal to '\0'
	{
		for (; p->GetNext() != '\0'; p = p->GetNext())
		{
		}
		p->SetNext(node);
	}

	return;
}

WordNode * Queue::Pop()
{
	if (pHead == '\0')
		return NULL;
	else
	{
		WordNode* pCur = pHead;
		WordNode* temp = new WordNode();		

		temp->SetWord(pHead->GetWord());         //copy node to temp
		temp->SetMean(pHead->GetMean());

		pHead = pCur->GetNext();				// deliver pHead to next node of pCur

		delete pCur;

		return temp;
	}
}

WordNode * Queue::Search(char * word)
{
	WordNode * temp = pHead;
	char arr1[50] = { '\0' }; //temp's small letter version
	char arr2[50] = { '\0' }; //word's small letter version

	if (pHead == NULL) return NULL;

	for (int i = 0; i < strlen(word); i++) { //Loop for change word's capital letter
		if (word[i] < 97)
			arr2[i] = (char)(word[i] + 32);
		else
			arr2[i] = word[i];
	}

	while (1) {
		for (int i = 0; i < 50; i++) //arr1 initialize
			arr1[i] = '\0';

		for (int i = 0; i < strlen(temp->GetWord()); i++) { //Loop for change currentNode's capital letter
			if (temp->GetWord()[i] < 97)
				arr1[i] = (char)(temp->GetWord()[i] + 32);
			else
				arr1[i] = temp->GetWord()[i];
		}

		if (strcmp(arr1, arr2) == 0) { //compare arr1 with arr2
			return temp; //search success
		}
		else {
			temp = temp->GetNext();
		}

		if (temp == NULL)
			return NULL; //search fail
	}
}

bool Queue::Print()
{

	if (pHead)               //Queue is exist
	{
		ofstream fout;
		fout.open("log.txt", ios::app);
		WordNode* temp = pHead;

		for (; temp; temp = temp->GetNext())
		{
			cout << temp->GetWord() << " " << temp->GetMean() << endl;
			fout << temp->GetWord() << " " << temp->GetMean() << endl;
		}

		fout.close();
		return true;
	}
	else                  //Queue is not exist
		return false;

}

bool Queue::Save()
{
	ofstream tofout;                        //open "to_memorize_word.txt"
	tofout.open("to_memorize_word.txt");

	if (pHead != '\0')                           //if Queue is not empty
	{

		WordNode* CurrentNode = pHead;

		for (; CurrentNode != NULL; CurrentNode = CurrentNode->GetNext())            //write data in text file
			tofout << CurrentNode->GetWord() << " " << CurrentNode->GetMean() << endl;

		tofout.close();
		return true;
	}
	else                                    //if Queue is empty      
	{
		tofout.close();
		return false;
	}
}

WordNode* Queue::GetQueueHead() {
	return pHead;
}

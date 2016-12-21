#include "CircularLinkedList.h"

CircularLinkedList::CircularLinkedList()
{
	pHead = '\0';
}

CircularLinkedList::~CircularLinkedList()
{
	if(pHead == NULL)
		return;

	WordNode* pCur = pHead;
	if (pCur->GetNext() == pHead)
		delete pHead;
	else {
		pCur = pCur->GetNext();
		WordNode* pDel = new WordNode();
		for (; pCur != pHead;) {
			pDel = pCur;
			pCur = pCur->GetNext();
			delete pDel;
		}
		delete pHead;
	}

}

void CircularLinkedList::Insert(WordNode * node) {
	WordNode *  temp = pHead;
	if (temp == NULL) {
		node->SetNext(node);
		pHead = node;
		return;
	}
	for (; temp->GetNext() != pHead; temp = temp->GetNext()) {
	}
	temp->SetNext(node);
	node->SetNext(pHead);
}

WordNode* CircularLinkedList::Search(char * word)            // SEARCH, UPDATE
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
		if (temp == pHead)
			return 0; //search fail
	}
}

bool CircularLinkedList::Save()
{
	ofstream esdfout;                     //open "memorized_word.txt"
	esdfout.open("memorized_word.txt");

	if (pHead != '\0')                     //if CLL is not empty
	{
		WordNode* CurrentNode = pHead;
		esdfout << CurrentNode->GetWord() << " " << CurrentNode->GetMean() << endl;         //write data in text file

		CurrentNode = CurrentNode->GetNext();
		for (CurrentNode; CurrentNode != pHead; CurrentNode = CurrentNode->GetNext())
			esdfout << CurrentNode->GetWord() << " " << CurrentNode->GetMean() << endl;

		esdfout.close();
		return true;
	}
	else                              //if CLL is empty
	{
		esdfout.close();
		return false;
	}
}

bool CircularLinkedList::Print()
{
	if (pHead)               //CLL is exist
	{
		ofstream fout;
		fout.open("log.txt", ios::app);
		WordNode* temp = pHead;

		cout << temp->GetWord() << " " << temp->GetMean() << endl;
		fout << temp->GetWord() << " " << temp->GetMean() << endl;
		temp = temp->GetNext();

		for (; temp != pHead; temp = temp->GetNext())
		{
			cout << temp->GetWord() << " " << temp->GetMean() << endl;
			fout << temp->GetWord() << " " << temp->GetMean() << endl;
		}

		fout.close();
		return true;
	}
	else                  //CLL is not exist
		return false;
}

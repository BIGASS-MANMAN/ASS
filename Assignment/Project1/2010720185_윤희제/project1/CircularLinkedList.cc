#include "CircularLinkedList.h"

CircularLinkedList::CircularLinkedList()
{
	pHead = '\0';
}

CircularLinkedList::~CircularLinkedList()
{	
	while (pHead != '\0')
	{		
		WordNode* temp = pHead;
		pHead = pHead->GetNext();
		delete[] temp;
	}
}

void CircularLinkedList::Insert(WordNode * node)
{
	if (pHead == '\0')                 // empty
	{
		pHead = new WordNode;
		pHead = node;
	}
	else if (pHead->GetNext() == '\0') // one node exists
	{
		WordNode* temp = pHead;
		node->SetNext(pHead);
		pHead = node;
		temp->SetNext(pHead);		
	}
	else                               // more than one node exists
	{
		node->SetNext(pHead);
		pHead = node;
	}
}

WordNode* CircularLinkedList::Search(char * word)
{
	if (pHead == '\0')
		return 0;

	int flag = 0;
	WordNode* search = pHead;

	/* make upper case to lower case */
	for (int i = 0; word[i] != '\0'; i++)
	{
		if (word[i] >= 65 && word[i] <= 90) // if upper case
			word[i] += 32;                  // make lower case
	}

	while (search->GetNext() != pHead)
	{
		if (strcmp(search->GetWord(), word) == 0)
		{
			flag = 1;
			break;
		}
		search = search->GetNext();
	}
	if (strcmp(search->GetWord(), word) == 0)
		flag = 1;

	if (flag == 0)
		return 0;
	if (flag == 1)
		return search;
}

bool CircularLinkedList::Print()
{	
	ofstream log_file("log.txt", ios::app);
	CircularLinkedList cll;

	WordNode* temp1 = pHead;
	WordNode* temp2 = cll.pHead;

	if (pHead == '\0')
	{
		log_file << "======== ERROR ========"   << endl;
		log_file << "700"                       << endl;
		log_file << "=======================\n" << endl;
		log_file.close();
		return 0;
	}
	else
	{
		while (temp1->GetNext() != '\0')
		{
			cll.Insert(temp1);
			temp1 = temp1->GetNext();
		}
		cll.Insert(temp1);

		log_file << "======== PRINT ========" << endl;
		while (temp2->GetNext() != pHead)
		{
			log_file << temp2->GetWord() << " " << temp2->GetMean() << endl;
			temp2 = temp2->GetNext();
		}
		log_file << temp2->GetWord() << " " << temp2->GetMean() << endl;
		log_file << "=======================\n" << endl;
		log_file.close();
		return 1;
	}
}

bool CircularLinkedList::Save()
{
	if (pHead == '\0')
	{
		return 0;
	}
	else
	{
		ofstream log_file("log.txt", ios::app);
		ofstream output("memorized_word.txt");
		CircularLinkedList cll;

		WordNode* temp1 = pHead;
		WordNode* temp2 = cll.pHead;

		while (temp1->GetNext() != pHead)
		{
			cll.Insert(temp1);
			temp1 = temp1->GetNext();
		}
		cll.Insert(temp1);

		while (temp2->GetNext() != pHead)
		{
			output << temp2->GetWord() << " " << temp2->GetMean() << endl;
			temp2 = temp2->GetNext();
		}
		output << temp2->GetWord() << " " << temp2->GetMean() << endl;

		log_file << "======== SAVE ========"   << endl;
		log_file << "Success"                  << endl;
		log_file << "======================\n" << endl;

		output.close();
		log_file.close();
		return 1;
	}
}
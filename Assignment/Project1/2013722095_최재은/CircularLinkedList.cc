#include "CircularLinkedList.h"



CircularLinkedList::CircularLinkedList()
{
	pHead = '\0';
}

CircularLinkedList::~CircularLinkedList() 
{
	if (pHead == '\0') //if phead is null return
		return;
	WordNode* temp = pHead; //declare temp and set into phead
	while(1)
	{
		if (temp->GetNext() == pHead) //if temp getnext is phead
			break; //break
		temp = temp->GetNext(); //temp is temp getnext
	}
	temp->SetNext('\0'); // circle shape destroy
	temp = pHead; //temp is phead
	while (1)
	{
		if (temp== '\0') //if temp is null
			break; //break
		temp = temp->GetNext(); //temp is temp getnext
		delete pHead; //delete phead
		pHead = temp; //phead is temp
	}
}

void CircularLinkedList::Insert(WordNode* node)
{

	WordNode* temp = pHead; //declare temp and set as phead

	if (pHead == '\0') // if no node in cll, phead is null
	{
		pHead = node;//phead is node
		node->SetNext(pHead); //node setnext is phead
	}
	else if (pHead->GetNext() == pHead) // if there is one word in cll
	{
		pHead->SetNext(node); //phead setnext is node
		node->SetNext(pHead); //node setnext phead
	}
	else// if there is more then 2 word in cll
	{
		while (1) // goto the most recent word input
		{
			if (temp->GetNext() == pHead)//if temp getnext is same as phead
				break; //break
			temp = temp->GetNext(); //temp is temp getnext
		}
		node->SetNext(pHead); // node setnext is phead
		temp->SetNext(node);	// temp setnext is node
	}
};

bool CircularLinkedList::Print()
{
	ofstream logfile; //declare logfile
	logfile.open("log.txt", ios::app); //open log.txt
	if (pHead == '\0') //if phead is null
	{
		logfile << "======== PRINT ========" << endl;
		logfile << "700" << endl;
		logfile << "=======================" << endl;

		cout << "======== PRINT ========" << endl;
		cout << "700" << endl;
		cout << "=======================" << endl;
		logfile.close(); //close logfile
		return false; //return false
	}

	WordNode* ptemp = pHead; //declare ptemp and set as phead
	cout << "======== PRINT ========" << endl;
	logfile << "======== PRINT ========" << endl;
	while (1)
	{
		cout << ptemp->GetWord() << "\t" << ptemp->GetMean() << endl; //print
		logfile << ptemp->GetWord() << "\t" << ptemp->GetMean() << endl; //save in txt
		if (ptemp->GetNext() == pHead) //if ptemp getnext is same as phead
			break; //break
		ptemp = ptemp->GetNext(); //ptemp is ptemp getnext
	}
	cout << "========================" << endl;
	logfile << "========================" << endl;
	logfile.close(); //close logfile
	return true; //return true
};
char* CircularLinkedList::up(char* word)
{
	char arr[20] = { '\0' }; //declare arr and set into null
	for (int a = 0; word[a] != '\0'; a++) //until word[a] reaches null
		arr[a] = toupper(word[a]);//arr[a] is toupper(word[a])
	return arr; //return arr
}
WordNode* CircularLinkedList::Search(char* word)
{
	WordNode* ptemp = pHead; //declare ptemp and set into pHead
	char arrptemp[32] = { '\0' }; //declare arrtemp and set into null
	char arrword[32] = { '\0' }; //declare arrword and set into null
	while (1)
	{
		if (pHead == '\0') //if phead is null
		{
			ptemp = '\0'; //ptemp is null
			return ptemp; //return ptemp
		}
		
		strcpy(arrptemp, up(ptemp->GetWord())); //copy arrtemp, up(ptemp getword
		strcpy(arrword, up(word)); //copy arrword, up(word)
		
		if (strcmp(arrptemp,arrword)==0) //if arrptemp and arrword length are same
		{
			return ptemp; //return ptemp
		}
		if (ptemp->GetNext() == pHead) //after one cycle if there is no value that was inputted
		{
			ptemp = '\0'; //ptemp is null
			return ptemp; //return ptemp
		}
		ptemp = ptemp->GetNext(); //ptemp is ptemp getnext
	}
}
bool	CircularLinkedList::Save()										// SAVE
{
	WordNode* temp = pHead; //declare temp and set into pHead
	ofstream cllfile; //declare cllfile
	cllfile.open("memorized_word.txt"); //open memorized_word.txt

	if (cllfile.fail())
	{
		return false; //return false
	}
	if (temp == '\0') // if there were no words to save
	{
		cllfile.close(); //close cillfile
		return false; //return false
	}
	while (1)
	{
		cllfile << temp->GetWord() << "\t" << temp->GetMean() << endl; //save
		temp = temp->GetNext(); //temp is temp getnext
		if (temp == pHead) //if temp is pHead
			break; //break
	}

	cllfile.close();//close cllfile
	return true;
}
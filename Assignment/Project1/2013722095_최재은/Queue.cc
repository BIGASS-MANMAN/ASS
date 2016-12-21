#include "Queue.h"


Queue::Queue()
{
	pHead = 0; //set phead into 0
	pTail = 0;//set ptail into 0
};


Queue::~Queue()
{
	if (pHead == '\0') //if phead is null
		return; //return
	WordNode* del; //declare del

	while (pHead != '\0') //until phead reach null
	{
		del = pHead; //del is phead
		del->SetNext('\0'); //del setnext is null
		pHead = pHead->GetNext(); //phead is phead getnext
		delete del; //delete del
	}
	pHead = '\0'; //phead is null
};

void Queue::Push(WordNode* node) //push node
{
	if (pHead == '\0')  //if phead is null
	{
		pHead = node; //phead is node
		pTail = node; //ptail is node
		pTail->SetNext('\0'); //ptail setnext is null
	}
	else
	{
		pTail->SetNext(node); //ptail setnext is node
		pTail = node; //ptail is node
		pTail->SetNext('\0'); //ptail setnext if null
	}
}

WordNode* Queue::Pop()
{
	WordNode* temp = pHead; //declare temp and set as phead
	if (temp == 0) //if temp is 0
		return pHead; //return phead
	else
	{
		pHead = temp->GetNext(); //phead is temp getnext
		temp->SetNext('\0');//temp setnext is null
		return temp; //return temp
	}
}
char* Queue::up(char* word)
{
	char arr[20] = { '\0' }; //declare arr and set into null
	for (int a = 0; word[a] != '\0'; a++) //until word[a] reach null
		arr[a] = toupper(word[a]); //arr[a] is toupper(word[a])
	return arr; //return arr
}
WordNode* Queue::Search(char * word)
{
	char arrpwalker[32] = {'\0'}; //declare arrpwalker and set as null
	char arrword[32] = {'\0'}; //declare arrword and set as null
	WordNode* pwalker; //declaer pwalker 
	pwalker = pHead; //pwalker is phead
	int reg = 0; //declare reg set into 0
	if (pHead == '\0') //if phead is null
	{
		pwalker = '\0'; //pwalker set null
		return pwalker; //return pwalker
	}
	else
	{
		while (pwalker != '\0') //until pwalker reach null
		{
			strcpy(arrpwalker, up(pwalker->GetWord())); //copy arrwalker to up(pwalker getword)
			strcpy(arrword, up(word)); //copy arrword to up(word)

			if (strcmp(arrpwalker, arrword) ==0) //if arrpwalker and arrword length are same
			{
				reg++; //reg add
				return pwalker; //return pwalker
			}
			else
				pwalker = pwalker->GetNext(); //pwalker is pwalker getnext
		}
	}
	if (reg != 0)// if reg is not 0
	{
		pwalker = '\0'; //pwalker is null
		return pwalker; //return pwalker
	}
}

bool Queue::Print()
{
	ofstream logfile; //declare logfile
	logfile.open("log.txt", ios::app); //open log.txt
	if(pHead == '\0') //if phead is null
	{
		logfile << "======== PRINT ========" << endl;
		logfile << "700" << endl;
		logfile << "=======================" << endl;
		logfile.close();
		cout << "======== PRINT ========" << endl;
		cout << "700" << endl;
		cout << "=======================" << endl;
		return false; //return false
	}
	WordNode* pwalker; //declare pwalker
	WordNode* next; //declare next

	next = pHead->GetNext(); //next is phead getnext
	pwalker = pHead; //pwalker is phead
	cout << "======== PRINT ========" << endl;
	logfile << "======== PRINT ========" << endl;
	if (next->GetWord() == 0) { //if next getword is 0
		cout << pwalker->GetWord() << "\t" << pwalker->GetMean() << endl; //print
		logfile << pwalker->GetWord() << "\t" << pwalker->GetMean() << endl; //save in txt
	}
	else 
	{
		while (pwalker != '\0') //until pwalker reach null
		{
			logfile << pwalker->GetWord() << "\t" << pwalker->GetMean() << endl; //print
			cout << pwalker->GetWord()<<"\t" << pwalker->GetMean() << endl; //save in txt
			pwalker = pwalker->GetNext(); //pwalker is pwalker getnext
		}
	}
	cout << "=======================" << endl;
	logfile << "=======================" << endl;
	logfile.close(); //close logfile
	return true; //return ture
}

bool Queue::Save()
{
	ofstream save; //declare save
	save.open("to_memorize_word.txt"); //open to_memorize_word.txt
	WordNode* pwalker; //declare pwalker
	pwalker = pHead; //pwalker is phead
	if (pHead == '\0') //if phead is null
	{
		save.close(); //close save
		return false; //return false
	}
	
	while (1)
	{
		if (pwalker == '\0') //if pwalker is null
			break; //break
		save << pwalker->GetWord() << "\t" << pwalker->GetMean() << endl; //save
		pwalker = pwalker->GetNext();//pwalker is pwalker getnext
	}
	save.close(); //close save
	return true; //return true
}
int Queue::Cntqueue() // counting the node of the existing queue
{
	int cntqueue = 0; //declare cntqueue
	WordNode* temp = pHead; //declare temp and set as phead
	while (1)
	{
	
		cntqueue++; //cntqueue++
		temp = temp->GetNext(); //temp is temp getnext
		if (temp == '\0') //if temp is null
			break; //break
		
	}
	return cntqueue; //return cntqueue
}
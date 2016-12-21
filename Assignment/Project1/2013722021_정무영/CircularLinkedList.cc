#include "CircularLinkedList.h"



CircularLinkedList::CircularLinkedList()
{
	pHead = '\0';
	prvHead = '\0';
	numOfWords = 0;
	logfile.open("log.txt", ios::app);
}


CircularLinkedList::~CircularLinkedList()		//delete all memories in CLL.
{
	/* You must fill here */
	if (pHead == '\0') return;					//If list is empty do not delete.
	WordNode* driver = pHead;
	WordNode* temp;
	do {										//check condition. after delete memory.
		temp = driver;
		driver = driver->GetNext();
		delete temp;
	} while (!(driver == pHead));
	logfile.close();
}

void CircularLinkedList::Insert(WordNode * node) {		//Insert a word to CLL, this function use at LOAD, and TEST.
	if (Search(node->GetWord()) != '\0') { // if there is already exist same word, delete the memory
		delete node;
		return;
	}
	if (!pHead) {  //if linkedlist is empty
		pHead = node;
		prvHead = node;
		pHead->SetNext(prvHead);
		prvHead->SetNext(pHead);
	}
		
	else {							//another case
		prvHead->SetNext(node);
		prvHead = node;
		prvHead->SetNext(pHead);
	}
	numOfWords++;		//add 1 to the number of words
}			// LOAD, TEST
WordNode* CircularLinkedList::Search(char * word) {		//Search a word in CLL.
	if (pHead == '\0') return '\0';		//If LIst is empty, return '\0'
	WordNode* driver = pHead;
	do {
		if (!strcmp(driver->GetWord(), word)) return driver;
		else driver = driver->GetNext();
	} while (!(driver==pHead));
	return '\0';
}				// SEARCH, UPDATE
bool CircularLinkedList::Print() {		//Print all words in CLL.
	if (pHead == '\0') return '\0';		
	WordNode* driver = pHead;
	do {
		cout << driver->GetWord() << " " << driver->GetMean() << endl;
		logfile << driver->GetWord() << " " << driver->GetMean() << endl;
		driver = driver->GetNext();
	} while (!(driver == pHead));
	return true;
}							// PRINT
bool CircularLinkedList::Save(){		//Save all words to "memorized_word.txt" file.
	ofstream file("memorized_word.txt");
	if (file.is_open() == false || pHead == '\0') return false;

	WordNode* driver = pHead;
	while (driver) {
		file << driver->GetWord() << "\t" << driver->GetMean() << endl;
		driver = driver->GetNext();
		if (driver == pHead)	break;
	}
	file.close();
	return true;
}// SAVE
int CircularLinkedList::GetNum() {		//return the number of word in CLL.
	return numOfWords;
}
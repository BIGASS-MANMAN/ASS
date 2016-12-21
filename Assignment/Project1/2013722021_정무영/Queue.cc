#include "Queue.h"



Queue::Queue()
{
	pHead = '\0';
	pTail = '\0';
	numOfWords = 0;
	logfile.open("log.txt", ios::app);
}


Queue::~Queue()			//delete all memories in Queue.
{
	/* You must fill here */
	WordNode* driver = pHead;
	WordNode* temp;
	while (driver) {		//if Head is '\0'(there is nothing in Queue) or driver reach end of Queue, escape the while loop
		temp = driver;
		driver=driver->GetNext();
		delete temp;
	}
	logfile.close();
}

void Queue::Push(WordNode * node) {		//Add word in queue.
	if (Search(node->GetWord()) != '\0') {
		delete node;
		return;
	}		//if already exist same word, do not push and delete adress.
	if (!pHead) pHead = node, pTail = node;		//first node input
	else {						//already node exist
		pTail->SetNext(node);
		pTail = node;
	}
	numOfWords++;
}				// LOAD, ADD
WordNode * Queue::Pop() {		//delete word in queue.
	if (!pHead) {				//nothing in Queue 
		return '\0'; 
	}
	else {					//FIFO
		WordNode * temp;
		temp = pHead;
		pHead = pHead->GetNext();
		numOfWords--;
		return temp;
	}
}						// MOVE
WordNode * Queue::Search(char * word) {		//Find a word in Queue
	WordNode* finder = pHead;
	while (finder) {	//if Head is '\0'(there is nothing in Queue) or there is no words to find anymore, escape the while loop
		if (!strcmp(finder->GetWord(), word)) return finder;
		finder = finder->GetNext();
	}
	return '\0';
}				// SEARCH, UPDATE
bool Queue::Print() {			//Print all words in Queue
	if (pHead == '\0') return false;
	WordNode* driver = pHead;
	while (driver) {		//if Head is '\0'(there is nothing in Queue) or driver reach end of Queue, escape the while loop
		cout << driver->GetWord() << " " << driver->GetMean() << endl;
		logfile << driver->GetWord() << " " << driver->GetMean() << endl;
		driver=driver->GetNext();
	}
	return true;
}							// PRINT
bool Queue::Save() {			//Save all words to "to_memorize_word.txt"
	ofstream file("to_memorize_word.txt");
	if (file.is_open() == false || pHead=='\0') return false; //if error occur during open file or there is no data in Queue, return false

	WordNode* driver=pHead;
	while (driver!='\0') {			//print word informations to file
		file << driver->GetWord() << "\t" << driver->GetMean() << endl;
		driver = driver->GetNext();
	}
	file.close();

	return true;
}								// SAVE

int Queue::GetNum() {		//return the number of words in Queue
	return numOfWords;
}
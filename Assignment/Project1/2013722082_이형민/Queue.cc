#include "Queue.h"


Queue::Queue()
{
	pHead = '\0';// initialinzing pHead
}

Queue::~Queue()//destuctor
{

	WordNode * temp = pHead, *del;
	while (temp)
	{
		del = temp;
		temp = temp->GetNext();// first in first out (FIFO)is queue
		delete del;
	}
}

int Queue::count()// count the number of node
{
	WordNode * temp = pHead;
	int count = 0;// variable for count
	if (!pHead) {
		return 0;
	}
	while (temp) {
		count++;
		temp = temp->GetNext();
	}
	return count;// counted number
}

void Queue::Push(WordNode * node)				// Push
{
	if (pHead == 0) {
		pHead = node;
		return;
	}
	else
	{
		WordNode * temp = pHead;
		while (temp)
		{
			if (strcmp(temp->GetWord(), node->GetWord()) == 0)// if the node is equal to temp
			{
				delete node;// deleting
				return;
			}
			if (temp->GetNext() == 0) {// go to last place
				temp->SetNext(node);// specify the temp to the next node
				return;
			}
			temp = temp->GetNext();//temp move forword one node
		}
	}
}

WordNode *	Queue::Pop()						// POP
{
	if (pHead == 0)
		return 0;
	WordNode *temp = pHead;
	pHead = pHead->GetNext();//phead move forword one node
	temp->SetNext(0);// delete link
	return temp;
}

WordNode *	Queue::Search(char * word)				// SEARCH, UPDATE
{
	WordNode * temp = pHead;
	char pword[32],pgetword[32];
	strcpy(pword,word);
	while (temp) {
		strcpy(pgetword,temp->GetWord());
		if (strcmp(GetBigWord(pword), GetBigWord(pgetword)) == 0)// if you node want to find
			return temp;
		temp = temp->GetNext();
	}
	return 0;
}

bool Queue::Print()							// PRINT
{
	WordNode * temp = pHead;

	if (!pHead) {
		return 0;
	}
	std::ofstream log("log.txt", std::ios::app);
	log << "=========PRINT=======" << std::endl;
	cout << "=========PRINT=======" << std::endl;
	while (temp) {
		log << temp->GetWord() << "  " << temp->GetMean() << std::endl;
		cout << temp->GetWord() << "  " << temp->GetMean() << std::endl;// queue node print
		temp = temp->GetNext();// for printing to next node
	}
	log << "=====================\n\n" << std::endl;
	cout << "=====================\n\n" << std::endl;
	log.close();
	return 1;
}

bool Queue::Save()								// SAVE
{
	if (pHead == 0)
		return 0;
	else
	{
		WordNode *temp = pHead;
		std::ofstream f;
		f.open("to_memorize_word.txt");//open the file for saving

		while (temp) {
			f << temp->GetWord() << "\t" << temp->GetMean() << "\n";// flie for saving
			temp = temp->GetNext();
		}
		f.close();// file close
	}

	return 1;
}
char * Queue::GetBigWord(char * word)
{
	int loop =0;// count of array part
	while (word[loop] != '\0')
	{
		word[loop]=(char)toupper(word[loop]);// all small word change to bic word
		loop++;// the next one
	}
	return word;//return the converted value
}

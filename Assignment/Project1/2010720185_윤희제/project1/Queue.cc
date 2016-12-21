#include "Queue.h"

Queue::Queue()
{
	pHead = '\0';             // initialize pHead to NULL
	alphabet_pHead = '\0';
}

Queue::~Queue()
{
	while (pHead != '\0')     // while node isn't exist, execute pop function
		delete Pop();
}

void Queue::Push(WordNode * node)
{
	if (pHead == '\0')        // if there is no node, pHead points input node 
	{
		pHead = node;
	} 
	else                      // at least exist one node
	{		
		node->SetNext(pHead); // new node points the pHead
		pHead = node;         // move pHead to new node
	}
}

void Queue::alphabet_Push(AlphabetNode * node)
{
	if (alphabet_pHead == '\0')        // if there is no node, pHead points input node 
	{
		alphabet_pHead = node;
	}
	else                               // at least exist one node
	{
		node->SetNext(alphabet_pHead); // new node points the pHead
		alphabet_pHead = node;         // move pHead to new node
	}
}

WordNode* Queue::Pop()
{
	WordNode* finder;                     // declare finder to delete last node of queue
	WordNode* pre_finder = '\0';          // pre_finder is previous node of finder
	finder = pHead;                       // initialize finder to pHead

	if (finder == '\0')                   // if queue is empty, return false to print error message
		return 0;
	else                                  // not empty queue
	{
		while (finder->GetNext() != '\0') // find the last node
		{
			pre_finder = finder;
			finder = finder->GetNext();
		}
		pre_finder->SetNext('\0');
	}
	return finder;                        // return the last node
}

AlphabetNode* Queue::alphabet_Pop()
{
	AlphabetNode* finder;                     // declare finder to delete last node of queue
	AlphabetNode* pre_finder = '\0';          // pre_finder is previous node of finder
	finder = alphabet_pHead;                  // initialize finder to pHead

	if (finder == '\0')                       // if queue is empty, return false to print error message
		return 0;
	else                                      // not empty queue
	{
		while (finder->GetNext() != '\0')     // find the last node
		{
			pre_finder = finder;
			finder = finder->GetNext();
		}
		pre_finder->SetNext('\0');
	}
	return finder;                            // return the last node
}

WordNode* Queue::Search(char * word)
{
	if (pHead == '\0')                     // if queue is empty, exit
		return 0;

	int flag = 0;                          // delcare flag to notice that the search is success
	WordNode* search = pHead;              // search node stores pHead 

	/* make upper case to lower case */
	for (int i = 0; word[i] != '\0'; i++)
	{
		if (word[i] >= 65 && word[i] <= 90) // if upper case
			word[i] += 32;                  // make lower case
	}

	while (search->GetNext() != '\0') // while search node isn't the last node
	{
		if (strcmp(search->GetWord(), word) == 0) // if find the word, initialize flag to 1
		{
			flag = 1;
			break;
		}
		search = search->GetNext();               // change the search to next node
	}
	if (strcmp(search->GetWord(), word) == 0)     // if find the word, initialize flag to 1
		flag = 1;

	if (flag == 0) // can't find the word
		return 0;
	if (flag == 1) // if find the word, return the search node
		return search;
}

bool Queue::Print()
{
	WordNode* temp = pHead;  // temp node stores pHead 
	ofstream log_file("log.txt", ios::app); // open the log.txt file

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
		log_file << "======== PRINT ========" << endl;
		while (temp->GetNext() != '\0')
		{
			log_file << temp->GetWord() << " " << temp->GetMean() << endl;
			temp = temp->GetNext();
		}			
		log_file << temp->GetWord() << " " << temp->GetMean() << endl;
		log_file << "=======================\n" << endl;
		log_file.close();
		return 1;
	}
}

bool Queue::Save()
{
	if (pHead == '\0')
	{
		return 0;
	}	
	else
	{
		ofstream log_file("log.txt", ios::app);
		ofstream output("to_memorize_word.txt");
		Queue q;
		WordNode* temp1 = pHead;
		WordNode* temp2 = q.pHead;

		while (temp1->GetNext() != '\0')
		{
			q.Push(temp1);
			temp1 = temp1->GetNext();
		}	
		q.Push(temp1);

		while (temp2->GetNext() != '\0')
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
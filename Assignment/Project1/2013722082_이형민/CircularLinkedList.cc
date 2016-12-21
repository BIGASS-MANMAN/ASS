#include "CircularLinkedList.h"

CircularLinkedList::CircularLinkedList()//declaring of constructor
{
	pHead = '\0';// initializing pHead
}

CircularLinkedList::~CircularLinkedList()// constructor of circular linked list
{
	WordNode * temp = pHead;
	WordNode *del;

	if(pHead ==0)// if circularlinkedlist has nothing
		return ;
	while (1)// if circularlinkedlist has node
	{
		if (pHead == 0 || temp->GetNext() == pHead)//circularlinkedlist has only phead.
		{
			delete temp;// delete last node
			break;
		}
		del = temp;
		temp = temp->GetNext();// phead is move next node
		delete del;//delete node
	}
}

void CircularLinkedList::Insert(WordNode * node)// Insert
{

	if (node == Search(node->GetWord()))// if insert to same word
	{
		delete node;
		return;
	}
	if (pHead == 0) {// if circularlinked list has nothing
		pHead = node;
		node->SetNext(node);//pointing to phead self
	}
	else {// when circularlinked list has one more node
		WordNode * temp = pHead;
		while (temp->GetNext() != pHead)// if not the last came,temp except phead
		{
			temp = temp->GetNext();//temp is move next node
		}
		temp->SetNext(node);//pointing to node from temp
		node->SetNext(pHead);// node is pointing to phead
	}

}

WordNode* CircularLinkedList::Search(char*word)//search
{
	WordNode * temp = pHead;
	if (pHead == 0)
		return 0;
	
	char pword[32],pgetword[32];
	strcpy(pword,word);// copy to pword = word
	
	do
	{
		strcpy(pgetword,temp->GetWord());
		if (strcmp(GetBigWord(pword), GetBigWord(pgetword)) == 0)// when you find the search word,
			return temp;
		temp = temp->GetNext();
	} while (temp != pHead);//conditional execution

	return 0;
}

bool CircularLinkedList::Print()//Print
{
	if (pHead == 0)//exception point
		return 0;//false
	else
	{
		std::ofstream log("log.txt",ios::app);
		WordNode * temp = pHead;
		cout << "=========PRINT=======" << endl;
		log << "=========PRINT=======" << endl;
		do
		{
			log << temp->GetWord() << "\t" << temp->GetMean() << "\n";
			cout<< temp->GetWord() << "\t" << temp->GetMean() << "\n";//print word and mean
			temp = temp->GetNext();//move go to foward
		} while (temp != pHead);

		cout<< "=====================\n\n" << endl;		
		log << "=====================\n\n" << endl;
		log.close();
	}
	return 1;
}

bool CircularLinkedList::Save()//Save
{
	if (pHead == 0)
		return 0;//false
	else
	{
		WordNode * temp = pHead;
		std::ofstream f;
		f.open("memorized_word.txt");// open the file for saving
		do
		{
			f << temp->GetWord() << "\t" << temp->GetMean() << "\n";// flie for saving
			temp = temp->GetNext();// next node
		} while (temp != pHead);
		f.close();// file close
	}
	return 1;
}
WordNode * CircularLinkedList::GetHead()//for pointing phead
{
	return pHead;
}

char* CircularLinkedList::GetBigWord(char* word)
{
	int loop =0;// count of array part
	while (word[loop] != '\0')
	{
		word[loop]=(char)toupper(word[loop]);// all small word change to big word
		loop++;// the next one
	}
	return word;//return the converted value
}

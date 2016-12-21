#include "Queue.h"

	
Queue::Queue()	//Queue constructor
{
	pHead = '\0';	 //pHead
	pTail = NULL;	 //Tail
}


Queue::~Queue()	//Queue destructor
{
	WordNode* current = pHead;
	WordNode* temp = NULL;
	while (current)
	{
		if (current->GetNext() != NULL)	 //If next word is exist
		{
			temp = current->GetNext();	//temp = next word
		}
		else	// else
		{
			delete current;	//Delete current allocated dinamically
			break;	// break
		}
		delete current;	//Delete current allocated dinamically
		current = temp;	//current = temp
	}

}
void Queue::setHead(WordNode * node)  //set and get member
{
	pHead = node;
}
void Queue::setTail(WordNode * node )
{
	pTail = node;
}
WordNode *  Queue::getHead()
{
	return pHead;
}
WordNode *  Queue::getTail()
{
	return pTail;
}

void Queue::Push(WordNode * node)//push
{
	WordNode* temp = NULL;
	if (IsEmpty() || node == pHead)	//If IsEmpty  or node == pHead
	{
		(this)->setHead(node); (this)->setTail(node);
		return;
	}	 // setHead, setTail
	temp = Search(node->GetWord());
	if (temp != NULL)
	{
		return;
	}	//if word is already exist
	else
	{
		WordNode* current = this->getTail();
		current->SetNext(node);
		this->setTail(node);
	}	//connect new word next to current word

	return;
}// LOAD, ADD

WordNode * Queue::Pop()	 //pop
{
	WordNode * current = this->getHead();
	WordNode * temp = NULL;
	
	if (current == NULL)
	{
		return NULL;	//if current is NULL, return NULL 
	}
	temp = new WordNode;
	temp->SetWord(current->GetWord());
	temp->SetMean(current->GetMean());	//Save current word and mean 
			this->setHead(current->GetNext());	//Setting HeadPoint to next node
			delete current;	// delete current node
			return temp;		 // return saved word and mean
}// MOVE
WordNode *	Queue::Search(char * word)
{
	WordNode * current = this->getHead();
	if (current == NULL)
	{
		return NULL;	//if current is NULL, return NULL 
	}
	while (current)
	{
		if (strcmp(word, current->GetWord()) == 0) return current;
		current = current->GetNext();
	}	//do GetNext() until find word
	return NULL;	 //return NULL
}// SEARCH, UPDATE
bool	Queue::Print()
{
	WordNode* current = this->getHead();
	ofstream ouf;
	ouf.open("log.txt",ios_base::app);
	if (current == NULL)
	{
		return false;	//If current is NULL, return false
	}
	else
	{
		while (current)			//print getword() and getmean()    
		{
			cout << current->GetWord() << " " << current->GetMean() << endl;
			
			current = current->GetNext();	//return true
		}
		return true;
	}
	
}// PRINT

bool    Queue::IsEmpty()  //IsEmpty()
{
	WordNode * current = pHead;
	if (current == NULL)
	{	
		return true;	 //If current is NULL, return true
	}
	else
	{
		return false;	//return false
	}
}
bool	Queue::	Save()
{
	if (IsEmpty())
	{
		return false;	//If current is NULL,return false
	}
	else
	{
		WordNode * current = pHead;
		ofstream ouf;			//write file
		ouf.open("to_memorize_word.txt");	//write file open
		if (current == NULL || !ouf.good())		//current = NULL or ouf is problem
		{
			return false;		 //return false
		}
		while (current)
		{
			ouf << current->GetWord() << "	" << current->GetMean() << endl;
			current = current->GetNext();
		}	//write GetNext() 
		ouf.close();	//write file close
		return true;	//return true
	}
}// SAVE
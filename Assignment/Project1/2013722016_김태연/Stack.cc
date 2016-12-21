#include "Stack.h"


Stack::Stack(void) // stack constructor
{
	count = 0; 
	top = NULL; 
	list = NULL; 

}


Stack::~Stack(void) // stack destructor
{
	WordNode* scan = top;
	WordNode* temp = NULL;
	while (top && scan->GetNext()) // traversal to delete
	{
		temp = scan->GetNext();
		delete scan;
		scan = temp;
	}
	delete scan;
}

void Stack::setTop(WordNode* top) { this->top = top; } // setTop function

void Stack::Push(WordNode*newNode) // push function
{
	if (!newNode) // if newNode is NULL
		return;
	newNode->SetNext(NULL);

	if (list == NULL) list = newNode; // if stack is empty
	else { // if stack is not empty
		WordNode* tempNode = list; // temp declare

		while (tempNode->GetNext() != NULL) // while tempNode's next is not NULL
			tempNode = tempNode->GetNext(); 

		tempNode->SetNext(newNode); 
	}

	top = newNode; count++; 
}
WordNode* Stack::Pop() // Pop function
{
	WordNode* topNode = top; // topNode = top

	if (list == NULL) return topNode;
	else if (list == top) { list = NULL; top = NULL; count--; } // if there is only one node
	
	else {// if there is nodes more than 2
		WordNode* currentNode = list; 

		while (currentNode->GetNext()->GetNext()) // while curentNode's nextnode's nextnode is not NULL
			currentNode = currentNode->GetNext();

		top = currentNode;
		currentNode->SetNext(NULL); 
		count--; 
	}
	return topNode; //return topNode
}

bool Stack::isEmpty() { return (list == NULL); } // isEmpty function

WordNode* Stack::getTop() { return top; } // getTop function
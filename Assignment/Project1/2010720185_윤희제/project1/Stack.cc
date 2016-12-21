#include "Stack.h"

Stack::Stack()
{
	word_top = '\0';             // initialize pHead to NULL
	alphabet_top = '\0';
}

Stack::~Stack()
{
	while (word_top != '\0')     // while node isn't exist, execute pop function
		Pop_word();
	while (alphabet_top != '\0')
		Pop_alphabet();
}

void Stack::Push_word(WordNode * node)
{
	if (word_top == '\0')
	{
		word_top = node;
	}
	else
	{
		node->SetNext(word_top);
		word_top = node;;
	}
}

void Stack::Push_alphabet(AlphabetNode * node)
{
	if (alphabet_top == '\0')
	{
		alphabet_top = node;
	}
	else
	{
		node->SetNext(alphabet_top);
		alphabet_top = node;;
	}
}

WordNode* Stack::Pop_word()
{
	if (word_top != '\0')
	{
		WordNode* temp = word_top;

		if (word_top->GetNext() != '\0')
			word_top = word_top->GetNext();
		temp->SetNext('\0');
		return temp;
	}	
}

AlphabetNode* Stack::Pop_alphabet()
{
	if (alphabet_top != '\0')
	{
		AlphabetNode* temp = alphabet_top;

		if (alphabet_top->GetNext() != '\0')
			alphabet_top = alphabet_top->GetNext();
		temp->SetNext('\0');
		return temp;
	}	
}
#ifndef _STACK_H_
#define _STACK_H_

#include "WordNode.h"
#include "AlphabetNode.h"
using namespace std;

class AlphabetNode;

class Stack
{
public:
	WordNode* word_top;         // point top of word stack
	AlphabetNode* alphabet_top; // point top of alphabet stack

public:
	Stack();
	~Stack();

	void	      Push_word(WordNode * node);	      // insert the word node to top of the stack
	void		  Push_alphabet(AlphabetNode * node); // insert the alphabet node to top of the stack
	WordNode*     Pop_word();                         // pop the node from the top of word stack
	AlphabetNode* Pop_alphabet();                     // pop the node from the top of alphabet stack
};

#endif
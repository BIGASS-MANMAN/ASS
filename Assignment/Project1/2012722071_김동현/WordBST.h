#ifndef _WORDBST_H_
#define _WORDBST_H_

#include "WordNode.h"
#include <fstream>
#include "Queue.h"
#include <queue>
#include "Stack.cc"

class WordBST
{
public:
	WordNode * root;	// Word BST Root

public:
	WordBST();
	~WordBST();

	void		Insert(WordNode * node);			// LOAD, MOVE
	WordNode *	Delete(char * word);				// TEST
	WordNode *	Search(char * word);				// ADD, TEST, SEARCH, UPDATE
	bool		Print(char * order);				// PRINT
	bool		Save();								// SAVE
	void		Define(WordNode * getnode, WordNode * givenode);
	void			Inorder(WordNode * currentnode);
	void			preorder(WordNode * currentnode);
	void			postorder(WordNode * currentnode);
	void			IterativeInorder(WordNode * currentnode);
	void			Iterativepreorder(WordNode * currentnode);
	void			Iterativepostorder(WordNode * currentnode);
	void			Levelorder(WordNode * currentnode);
	void			Visit(WordNode * currentnode);

	char(*Expressword(WordNode * currentnode))[64]//Print word to text file
	{
	static char wordpack[100][64];//this variable get words from alphabet nodes
	int d = 0;// when stack 'pp' get pop, d count words 
	for (int i = 0; i < 100; i++)
		memset(wordpack[i], 0, 64);
	Stack<WordNode *> pp;//use to make a word stack
	Stack<WordNode *> go;//use to pop word stack
	pp.Push(currentnode);//start push currentnode
	while (1)//when pp is empty escape while form
	{	
		if(pp.IsEmpty() == true)
			break;
		WordNode * out = pp.Top();// variable out get prev node of currentnode
		go.Push(out);             //push variable out
		pp.Pop();                 //'pp' get pop
		d++;                      //count word

		if (out->GetLeft() != NULL)       //when out->GetLeft() is not NULL, push that
		pp.Push(out->GetLeft());
		if (out->GetRight() != NULL)      //when out->GetRight() is not NULL, push that
		pp.Push(out->GetRight());
		
	}
	for (int i = 0; i < d; i++)//the number of for loop's is control by number of words(d)
	{
		strcpy(wordpack[i], go.Top()->GetWord());// wordpack get word
		for (int j = 0; j < 64; j++)
		{
			if (wordpack[i][j] >= 'a' && wordpack[i][j] <= 'z')//if elements is alphabet
				continue;
			else if (wordpack[i][j] == '\0')// if elements is null
				wordpack[i][j] = '\t';
			else                            // if elements is anything without alphabet and null
				wordpack[i][j] = '\0';
		}
		strcat(wordpack[i],go.Top()->GetMean());// wordpack get mean behind '\t'
		go.Pop();// get pop
	}
	return wordpack;// return wordpack
	}


};

#endif

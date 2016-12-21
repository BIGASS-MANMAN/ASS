#include "WordBST.h"
#include <fstream>
#include <cstring>

WordBST::WordBST()
{
	root = '\0';
}

WordBST::~WordBST()
{
	Remove(root);
}
void WordBST::Remove(WordNode* n)
{
	if(n!=NULL){
		Remove(n->GetLeft());
		Remove(n->GetRight());
		delete n;
	}
}
void WordBST::Insert(WordNode * node)
{
	WordNode*p=root,*pp=NULL;

	while(p){
		pp=p;//pp is  the parent of p
		if(strcmp(node->GetWord(),p->GetWord())<0)
			p=p->GetLeft();
		else if(strcmp(node->GetWord(),p->GetWord())>0)
			p=p->GetRight();
		else
		{
			return;//the input node is exist in bst
		}
	}
	if(root!=NULL){//tree is not empty
		if(strcmp(node->GetWord(),pp->GetWord())<0)
			pp->SetLeft(node);
		else
			pp->SetRight(node);
	}
	else	//the first node in AlphabetBST
		root=node;
}
WordNode *WordBST::Delete(char * word)
{
	int del=0;

	WordNode* p=Search(word);
	if(p==NULL)
		return NULL;//the node is not found

	WordNode* q=p->GetParent();//q is parent of p

	if(p->GetLeft()==NULL&&p->GetRight()==NULL)//p is leaf
	{
		if(q==NULL)
			root=NULL;
		else if(q->GetLeft()==p)
			q->SetLeft(NULL);
		else
			q->SetRight(NULL);

		return p;
	}
	else if(p->GetLeft()==NULL)//p only has right child
	{
		if(q==NULL)
			root=p->GetRight();
		else if(q->GetLeft()==p)
			q->SetLeft(p->GetRight());
		else
			q->SetRight(p->GetRight());
		
		return p;
	}
	else if(p->GetRight()==NULL)//p only has left child
	{
		if(q==NULL)
			root=p->GetLeft();
		else if(q->GetLeft()==p)
			q->SetLeft(p->GetLeft());
		else
			q->SetRight(p->GetLeft());
		
		return p;
	}

	//p has left and right child 
	WordNode* prevprev=p;
	WordNode* prev=p->GetLeft();
	WordNode* current=p->GetLeft()->GetRight();

	while(current)
	{
		prevprev=prev;
		prev=current;
		current=current->GetRight();
	}//current is NULL, prev is the node to be deleted prevprev is prev's parent
	//prev->GetRight() is NULL

	if(prev->GetLeft()!=NULL)	//set child of prevprev 
		prevprev->SetRight(prev->GetLeft());
	else
		prevprev->SetRight(prev->GetRight());

	prev->SetLeft(p->GetLeft());	//changing location of prev
	prev->SetRight(p->GetRight());

	if(p!=root){	//change child of q
		if(q->GetLeft()==p)
			q->SetLeft(prev);
		else
			q->SetRight(prev);
	}
	else	//change root
		root=prev;

	return p;
}
bool WordBST::Print(char * order)
{
	if(!strcmp("R_PRE",order))
	{
		R_PRE(root);
	}
	if(!strcmp("I_PRE",order))
	{
		I_PRE();
	}
	if(!strcmp("R_IN",order))
	{
		R_IN(root);
	}
	if(!strcmp("I_IN",order))
	{
		I_IN();
	}
	if(!strcmp("R_POST",order))
	{
		R_POST(root);
	}
	if(!strcmp("I_POST",order))
	{
		I_POST();
	}
	if(!strcmp("I_LEVEL",order))
	{
		I_LEVEL();
	}

	return true;
}
bool WordBST::Save()
{
	ofstream fout;
	fout.open("memorizing_word.txt",ios::app);
	
	Stack s;
	WordNode* current=root;

	s.Push(current);
	while(s.GetHead()!=NULL)
	{
		current=s.Pop();
		if(current){
			fout<<current->GetWord()<<"\t"<<current->GetMean()<<endl;
			s.Push(current->GetRight());
			s.Push(current->GetLeft());
		}
	}
	fout.close();
	return true;
}
WordNode* WordBST::Search(char * word)
{
	WordNode* node =root;

	return Get(node, word);
}
WordNode* WordBST::Get(WordNode* node, char* word)
{
	if(node==NULL)
		return NULL;

	int len=0;
	
	if(strlen(word) > strlen(node->GetWord()))
		len=strlen(node->GetWord());
	else
		len=strlen(word);

	for(int i=0; i<len; i++)
	{
		if(word[i]>=65 && word[i]<=90)	//word is uppercase
		{
			if(node->GetWord()[i]>word[i]+32) //go to the left child if input node is smaller than current node
			{
				if(node->GetLeft()!=NULL)
					node->GetLeft()->SetParent(node);	//set parent of next node 
				return Get(node->GetLeft(),word);
			}
			else if(node->GetWord()[i]<word[i]+32)	//go to the right child if input node is bigger than current node
			{
				if(node->GetRight()!=NULL)
					node->GetRight()->SetParent(node);
				return Get(node->GetRight(),word);
			}
		}
		else if(word[i]>=97 && word[i]<=122)	//word is lowercase
		{
			if(node->GetWord()[i]>word[i])	//go to the left child if input node is smaller than current node
			{
				if(node->GetLeft()!=NULL)	
					node->GetLeft()->SetParent(node);
				return Get(node->GetLeft(),word); 
			}
			else if(node->GetWord()[i]<word[i])	//go to the right child if input node is bigger than current node
			{
				if(node->GetRight()!=NULL)
					node->GetRight()->SetParent(node);
				return Get(node->GetRight(),word);
			}
		}
		else	//word is not made of alphabet
			return NULL;
	}
	
	if(strlen(word)!=strlen(node->GetWord()))	//char word and node's word are not same
		return NULL;
	else
		return node;
}
void WordBST::Visit(WordNode* n)
{
	ofstream fout;
	fout.open("log.txt",ios::app);

	cout<<n->GetWord()<<" "<<n->GetMean()<<endl;
	fout<<n->GetWord()<<" "<<n->GetMean()<<endl;

	fout.close();
}

void WordBST::R_IN(WordNode* n)//recursive in-order
{
	if(n!=NULL)
	{
		R_IN(n->GetLeft());
		Visit(n);
		R_IN(n->GetRight());
	}
}
void WordBST::R_PRE(WordNode* n)//recursive pre-order
{
	if(n!=NULL)
	{
		Visit(n);
		R_PRE(n->GetLeft());
		R_PRE(n->GetRight());
	}
}
void WordBST::R_POST(WordNode* n)//recursive post-order
{
	if(n!=NULL)
	{
		R_POST(n->GetLeft());
		R_POST(n->GetRight());
		Visit(n);
	}
}
void WordBST::I_PRE()//iterative pre-order
{
	Stack s;
	WordNode* current=root;

	s.Push(current);
	while(s.GetHead()!=NULL)
	{
		current=s.Pop();
		if(current){
			Visit(current);
			s.Push(current->GetRight());
			s.Push(current->GetLeft());
		}
	}
}
void WordBST::I_IN()//iterative  in-order
{
	Stack s;
	WordNode* current=root;

	while(1)
	{
		while(current)
		{
			s.Push(current);
			current=current->GetLeft();
		}
		if(s.GetHead()==NULL)
			return;
		current=s.Pop();
		Visit(current);
		current=current->GetRight();
	}
}
void WordBST::I_POST()//iterative post-order
{
	Stack s;
	WordNode* current=root;
	WordNode* node=NULL;

	while(1)
	{
		while(current)
		{
			s.Push(current);
			current=current->GetLeft();
		}
		while(s.GetHead()!=NULL)
		{
			node=current;
			current=s.Pop(); 
			if(current->GetRight())
			{
				if(current->GetRight()==node)
					Visit(current);
				else
				{
					s.Push(current);
					current=current->GetRight();
					break;
				}
			}
			else
				Visit(current);
		}
		return;
	}
}
void WordBST::I_LEVEL()//iterative level-order
{
	Queue q;
	WordNode* current=root;

	while(current)
	{
		Visit(current);
		if(current->GetLeft())
			q.Push(current->GetLeft());
		if(current->GetRight())
			q.Push(current->GetRight());
		if(q.GetHead()==NULL)
			return;
		current=q.Pop();
	}
}
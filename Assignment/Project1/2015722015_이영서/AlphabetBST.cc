#include "AlphabetBST.h"
#include <fstream>
#include <cstring>

AlphabetBST::AlphabetBST()
{
	root = '\0';
	WordCnt = 0;

	const char alphabet[26]={'P','H','X','D','L','T','Z','B','F','J','N','R','V','Y','A','C','E','G','I','K','M','O','Q','S','U','W'};

	for(int i=0; i<26; i++){
		AlphabetNode* node=new AlphabetNode();
		node->SetAlphabet(alphabet[i]);
		
		Insert(node);
	}
}
AlphabetBST::~AlphabetBST()
{
	Remove(root);
}
void AlphabetBST::Remove(AlphabetNode* n)
{
	if(n!=NULL){
		Remove(n->GetLeft());
		Remove(n->GetRight());
		delete n;
	}
}
void AlphabetBST::Insert(AlphabetNode * node)
{
	AlphabetNode*p=root,*pp=NULL;

	while(p){
		pp=p;//pp is  the parent of p
		if(node->GetAlphabet()<p->GetAlphabet()) //go to the left child if input node is smaller than current node
			p=p->GetLeft();
		else if(node->GetAlphabet()>p->GetAlphabet()) //go to the right child if input node is bigger than current node
			p=p->GetRight();
		else//find same node
		{
			return;
		}
	}
	if(root!=NULL){//tree is not empty
		if(node->GetAlphabet()<pp->GetAlphabet())	//set input node to left child if input node is smaller than parent node
			pp->SetLeft(node);
		else	//set input node to right child if input node is bigger than parent node
			pp->SetRight(node);
	}
	else	//the first node in AlphabetBST
		root=node;

}
bool AlphabetBST::Print(char * order)
{
	ofstream fout;
	fout.open("log.txt",ios::app);

	cout<<"======== PRINT ========"<<endl;
	fout<<"======== PRINT ========"<<endl;

	if(!strcmp("R_PRE",order))//recursive pre-order
	{
		R_PRE(root,order);
	}
	if(!strcmp("I_PRE",order))//iterative pre-order
	{
		I_PRE(order);
	}
	if(!strcmp("R_IN",order))//recursive in-order
	{
		R_IN(root,order);
	}
	if(!strcmp("I_IN",order))//iterative  in-order
	{
		I_IN(order);
	}
	if(!strcmp("R_POST",order))//recursive post-order
	{
		R_POST(root,order);
	}
	if(!strcmp("I_POST",order))//iterative post-order
	{
		I_POST(order);
	}
	if(!strcmp("I_LEVEL",order))//iterative level-order
	{
		I_LEVEL(order);
	}
	cout<<"========================"<<endl;
	fout<<"========================"<<endl;

	fout.close();

	return true;
}
AlphabetNode* AlphabetBST::Search(char alpabet)
{
	AlphabetNode* node=root;

	return Get(node, alpabet);
}
AlphabetNode* AlphabetBST::Get(AlphabetNode* node,char alpa)
{
	if(node==NULL)
		return NULL;

	if(alpa>=65 && alpa<=90)		//alpha is uppercase
	{
		if(alpa < node->GetAlphabet())	//go to the left child if input node is smaller than current node
			return Get(node->GetLeft(),alpa); 
		if(alpa > node->GetAlphabet())	 //go to the right child if input node is bigger than current node
			return Get(node->GetRight(),alpa);
		return node;
	}
	else if(alpa>=97 && alpa<=122)	//alpa is lowercase
	{
		if(alpa-32 < node->GetAlphabet())	//go to the left child if input node is smaller than current node
			return Get(node->GetLeft(),alpa); 
		if(alpa-32 > node->GetAlphabet())	//go to the right child if input node is bigger than current node
			return Get(node->GetRight(),alpa);
		return node;
	}
	else
		return NULL;
}
bool AlphabetBST::Save()
{
	AlphaStack s;
	AlphabetNode* current=root;

	//iterative pre-order saving
	s.Push(current);
	while(s.GetHead()!=NULL)
	{
		current=s.Pop();
		if(current){
			current->GetBST()->Save();
			s.Push(current->GetRight());
			s.Push(current->GetLeft());
		}
	}
	return true;
}
void AlphabetBST::R_IN(AlphabetNode* n,char * order)//recursive in-order
{
	if(n!=NULL)
	{
		R_IN(n->GetLeft(),order);
		n->GetBST()->Print(order);
		R_IN(n->GetRight(),order);
	}
}
void AlphabetBST::R_PRE(AlphabetNode* n,char * order)//recursive pre-order
{
	if(n!=NULL)
	{
		n->GetBST()->Print(order);
		R_PRE(n->GetLeft(),order);
		R_PRE(n->GetRight(),order);
	}
}
void AlphabetBST::R_POST(AlphabetNode* n,char * order)//recursive post-order
{
	if(n!=NULL)
	{
		R_POST(n->GetLeft(),order);
		R_POST(n->GetRight(),order);
		n->GetBST()->Print(order);
	}
}
void AlphabetBST::I_PRE(char * order)//iterative pre-order
{
	AlphaStack s;
	AlphabetNode* current=root;

	s.Push(current);
	while(s.GetHead()!=NULL)
	{
		current=s.Pop();
		if(current){
			current->GetBST()->Print(order);
			s.Push(current->GetRight());
			s.Push(current->GetLeft());
		}
	}
}
void AlphabetBST::I_IN(char * order)//iterative  in-order
{
	AlphaStack s;
	AlphabetNode* current=root;

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
		current->GetBST()->Print(order);
		current=current->GetRight();
	}
}
void AlphabetBST::I_POST(char * order)//iterative post-order
{
	AlphaStack s;
	AlphabetNode* current=root;
	AlphabetNode* node=NULL;

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
					current->GetBST()->Print(order);
				else
				{
					s.Push(current);
					current=current->GetRight();
					break;
				}
			}
			else
				current->GetBST()->Print(order);
		}
		if(s.GetHead()==NULL)
			return;
	}
}

void AlphabetBST::I_LEVEL(char * order)//iterative level-order
{
	AlpaQueue q;
	AlphabetNode* current=root;

	while(current)
	{
		current->GetBST()->Print(order);
		if(current->GetLeft())
			q.Push(current->GetLeft());
		if(current->GetRight())
			q.Push(current->GetRight());
		current=q.Pop();
	}
}
#include "AlphabetBST.h"
#include<iostream>
using namespace std;
AlphabetBST::AlphabetBST()						//Alphabet BST constructor
{												//root = NULL ,  WordCnt = 0
	root = '\0';									
	WordCnt = 0;

	char Alphabet[27] = { 'P','H','X' ,'D' ,'L' ,'T' ,'Z' ,'B' ,'F' ,'J' ,'N' ,'R' ,'V' ,'Y' ,'A' ,'C' ,'E' ,'G' ,'I' ,'K','M','O','Q','S','U','W' };// for make BST
	for (int i = 0; i < 26; i++)
	{
		AlphabetNode *Alpha = new AlphabetNode;//using insert function, make Alphabet bst tree
		Alpha->SetAlphabet(Alphabet[i]);
		this->Insert(Alpha);
	}

}
AlphabetBST::~AlphabetBST()									//Alphabet BST distructor
{
	Stack<AlphabetNode> Astack;								//Astack for Post order
	Stack<AlphabetNode> Bstack;								//Bstack for Post order
	AlphabetNode *node = root;								//move node
	Astack.push(node);
	while (!Astack.empty())									//this work in Post order that parent is not delete while all of child is delete
	{														//while Astack don't have node loop is acting
		node = Astack.pop();								//Astack give stack's top to node
		Bstack.push(node);									//Bstack have node at top
		if (node == NULL)									//node is NULL -> end
			return;
		if (node->GetLeft())								//if node have child, Astack have that at top
			Astack.push(node->GetLeft());
		if (node->GetRight())
			Astack.push(node->GetRight());
	}
	while (!Bstack.empty())									//delete all of Bstack's node
		delete Bstack.pop();
}											

void			AlphabetBST::Insert(AlphabetNode * node)				// use in LOAD, MOVE / insert Word Node
{
if (root == NULL)														//if root is NULL, root == NULL
{
	root = node;
}																		
else if (node->GetAlphabet() != 0)
{
	AlphabetNode * pWork = root;										
	AlphabetNode * pWork2 = root;										
	while (pWork != NULL)												//if root is exit / it is pre order insert , while pWork isn't 0
	{
		pWork2 = pWork;
		if ((int)node->GetAlphabet() > pWork->GetAlphabet())			//if pWork's word is first in word dictionary then node pWork go to left
			pWork = pWork->GetRight();									// else if not equal , go to right
		else if ((int)node->GetAlphabet() < pWork->GetAlphabet())		//if equal, break
			pWork = pWork->GetLeft();									
		}
		if ((int)node->GetAlphabet() > pWork2->GetAlphabet())			//if  pWork2's word is first in word dictionary then node, node = pWork2's left child
			pWork2->SetRight(node);										// else if not equal , right child
		else if ((int)node->GetAlphabet() < pWork2->GetAlphabet())
			pWork2->SetLeft(node);										
	}
}
bool			AlphabetBST::Print(char * order)			// PRINT
{
	if (root != NULL)										//call Word bst's print by order of the order
	{
		if (!strcmp(order, "R_PRE")) {
			cout << "======== PRINT ========" << endl;
			this->R_PRE(root);
			cout << "=======================" << endl;
			return 1;
		}
		else if (!strcmp(order, "I_PRE")) {
			cout << "======== PRINT ========" << endl;
			this->I_PRE();
			cout << "=======================" << endl;
			return 1;
		}
		else if (!strcmp(order, "R_IN")) {
			cout << "======== PRINT ========" << endl;
			this->R_IN(root);
			cout << "=======================" << endl;
			return 1;
		}
		else if (!strcmp(order, "I_IN")) {
			cout << "======== PRINT ========" << endl;
			this->I_IN();
			cout << "=======================" << endl;
			return 1;
		}
		else if (!strcmp(order, "R_POST")) {
			cout << "======== PRINT ========" << endl;
			this->R_POST(root);
			cout << "=======================" << endl;
			return 1;
		}
		else if (!strcmp(order, "I_POST")) {
			cout << "======== PRINT ========" << endl;
			this->I_POST();
			cout << "=======================" << endl;
			return 1;
		}
		else if (!strcmp(order, "I_LEVEL")) {
			cout << "======== PRINT ========" << endl;
			this->I_LEVEL();
			cout << "=======================" << endl;
			return 1;
		}
		else {
			return 0;
		}
	}
	return 1;
}
AlphabetNode *	AlphabetBST::Search(char alpabet)			// find alpabet
{
	Stack<AlphabetNode> Astack;								//by post order
	Stack<AlphabetNode> Bstack;
	AlphabetNode *node = root;
	Astack.push(node);
	while (!Astack.empty())									//while Astack isn't empty
	{
		node = Astack.pop();								//node = Astack's top
		Bstack.push(node);									//Bstack's top is node
		if (node == NULL)									//if node == NULL return 0;
			return 0;
		if (node->GetLeft())								//if node has child, Astak has that or these
			Astack.push(node->GetLeft());
		if (node->GetRight())
			Astack.push(node->GetRight());
		if (alpabet == node->GetAlphabet() || toupper(alpabet) == node->GetAlphabet())	//if finded alphabet, return that
			return node;
	}
	return NULL;
}
bool AlphabetBST::Save()						// SAVE
{
	Stack<AlphabetNode> Astack;
	AlphabetNode *node = root;									//node = root 
	Astack.push(node);											//Astack has node
	while (!Astack.empty())										//while Astack Not empty and node != NULL
	{
		node = Astack.pop();									//node = Astack's top
		node->GetBST()->Save();
		if (node == NULL)										//node == NULL ->end
			return 0;
		if (node->GetRight())									//node's child be saved in Astack
			Astack.push(node->GetRight());
		if (node->GetLeft())
			Astack.push(node->GetLeft());
	}
	return 0;
}

void			AlphabetBST::R_IN(AlphabetNode * node)
{																//recursive inroder
	if (node != NULL)
	{
		R_IN(node->GetLeft());									//go to left
		node->GetBST()->Print("R_IN");							//call word bst's print
		R_IN(node->GetRight());									//go to right
	}
}
void			AlphabetBST::I_IN()								//interative inorder
{
	Stack<AlphabetNode> Astack;
	AlphabetNode *node = root;									//pWork is root
	while (1)													
	{
		while (node != NULL)									//while go to left, save all of passed node in myStack
		{
			Astack.push(node);									
			node = node->GetLeft();
		}
		node = Astack.pop();
		if (node == NULL)
			return;												
		node->GetBST()->Print("I_IN");							//print infomation
		node = node->GetRight();								//pWork = pWork's Right child
	}															
}
void			AlphabetBST::R_PRE(AlphabetNode * node)			//recursive inroder
{
	if (node != NULL)
	{															
		node->GetBST()->Print("R_PRE");							//call word bst's print
		R_PRE(node->GetLeft());									//go to left
		R_PRE(node->GetRight());								//go to right
	}															
}
void			AlphabetBST::I_PRE()							//interative preorder
{																
	Stack<AlphabetNode> Astack;									
	AlphabetNode *node = root;									//node = root 
	Astack.push(node);											//Astack has node
	while (!Astack.empty())										//while Astack Not empty and node != NULL
	{															
		node = Astack.pop();									//node = Astack's top
		node->GetBST()->Print("I_PRE");							//call word bst's print by pre order
		if (node == NULL)										//node == NULL ->end
			return;												
		if (node->GetRight())									//node's child be saved in Astack
			Astack.push(node->GetRight());						
		if (node->GetLeft())									
			Astack.push(node->GetLeft());						
	}															
}																
void			AlphabetBST::R_POST(AlphabetNode * node)
{
	if (node != NULL)
	{															
		R_POST(node->GetLeft());								//go to left
		R_POST(node->GetRight());								//go to right
		node->GetBST()->Print("R_POST");						//call word bst's print
	}															
}
void			AlphabetBST::I_POST()							//interative post order
{																
	Stack<AlphabetNode> Astack;									
	Stack<AlphabetNode> Bstack;									
	AlphabetNode *node = root;									//node = root
	Astack.push(node);											//Astack has node
	while (!Astack.empty())										//while Astack isn't empty and node isn't NULL, loop work
	{															
		node = Astack.pop();									//node = stack's top
		Bstack.push(node);										//Bstack has node
		if (node == NULL)										
			return;												
		if (node->GetLeft())									//Astack has node's child
			Astack.push(node->GetLeft());						
		if (node->GetRight())									
			Astack.push(node->GetRight());						
	}															
	while (!Bstack.empty())										//all of Bstack's node be called and Print that infomation by preorder
		Bstack.pop()->GetBST()->Print("I_PRE");					
}																
void			AlphabetBST::I_LEVEL()							//interative Level order
{																
	AlphabetNode *node = root;									//node = root
	AlphabetNode *arr[26] = { 0 };								//array work like queue
	int num = 0, i = 0;											
	while (node)												//while node exist
	{															
		node->GetBST()->Print("I_LEVEL");						//call word bst's print by level order
		if (node->GetLeft())									//array save node's child
		{														
			arr[i] = node->GetLeft();							
			i++;												
		}														
		if (node->GetRight())									
		{														
			arr[i] = node->GetRight();							
			i++;												
		}														
		node = arr[0];											//node is array's first (same to queue's pop)
		if (node == NULL)										//if node is NULL end
			return;												
		num = 1;												
		while (num <= i - 1)									//work like queue's pop
		{														
			arr[num - 1] = arr[num];							
			num++;												
		}														
		arr[i - 1] = NULL;										
		i--;													
	}															
}																

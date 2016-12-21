#include "AlphabetBST.h"



AlphabetBST::AlphabetBST()
{
	root = '\0';
	WordCnt = 0;
}

AlphabetBST::~AlphabetBST()
{
	Clear(root);
}

void AlphabetBST::Insert(AlphabetNode * node)   // run
{
	AlphabetNode * p = root, *pp = 0;
	while (p) { //loop
		pp = p;
		if (node->GetAlphabet()< p->GetAlphabet()) { //perform if thePair's value is smaller than p's first value
			p = p->GetLeft(); //move to leftchild
		}
		else if (node->GetAlphabet() > p->GetAlphabet()) { //perform if thePair's value is bigger than p's first value 
			p = p->GetRight(); //move to rightchild
		}
	}
	if (root) { //root is not NULL
		if (node->GetAlphabet() < pp->GetAlphabet()) pp->SetLeft(node);
		else pp->SetRight(node);
	}
	else //root is NULL
		root = node; //set p to root
}

AlphabetNode *	AlphabetBST::Search(char alphabet) {			// LOAD, MOVE, TEST, SEARCH, UPDATE
	AlphabetNode * currentNode = root;

	while (currentNode) {
		if(alphabet >='a' && alphabet <='z')
			if (currentNode->GetAlphabet() > alphabet - 32) //compare root's alphabet with alphabet to move left or right direction
				currentNode = currentNode->GetLeft();
			else if (currentNode->GetAlphabet() < alphabet - 32)
				currentNode = currentNode->GetRight();
			else { //search success
				return currentNode;
			}
		else
			if (currentNode->GetAlphabet() > alphabet) //compare root's alphabet with alphabet to move left or right direction
				currentNode = currentNode->GetLeft();
			else if (currentNode->GetAlphabet() < alphabet)
				currentNode = currentNode->GetRight();
			else { //search success
				return currentNode;
			}
	}
	return 0; //search fail
}

bool AlphabetBST::Save()
{
	if (GetWordCnt() == 0)
		return false;
	else {
		ofstream ingfout;                     //for memorizing_word.txt file
		ingfout.open("memorizing_word.txt");
		ingfout.close();
		inSave(root);
		return true;
	}
}

void AlphabetBST::inSave(AlphabetNode * root)            //inorder traversal
{
	AlphabetNode* CurrentNode = root;
	if (CurrentNode)
	{
		inSave(CurrentNode->GetLeft());
		CurrentNode->GetBST()->Save();			
		inSave(CurrentNode->GetRight());
	}	
}

int AlphabetBST::GetWordCnt() {
	return WordCnt;
}


void AlphabetBST::SetWordCnt(int word_cnt)
{
	WordCnt = word_cnt;
}

bool AlphabetBST::Print(char * order)
{
	if (GetWordCnt() != 0)
	{				
		if (strcmp(order, "R_PRE") == 0)		//Recursive Pre Order
		{	
			R_PRE(root, order);
			return true;
		}
		else if (strcmp(order, "I_PRE") == 0)	//Iterative Pre Order
		{
			I_PRE(order);
			return true;
		}
		else if (strcmp(order, "R_IN") == 0)	//Recursie In Order
		{
			R_IN(root, order);
			return true;
		}
		else if (strcmp(order, "I_IN") == 0)	//Iterative In Order
		{
			I_IN(order);
			return true;
		}
		else if (strcmp(order, "R_POST") == 0)	//Recursive Post Order
		{
			R_POST(root, order);
			return true;
		}
		else if (strcmp(order, "I_POST") == 0)	//Iterative Post Order
		{
			I_POST(order);
			return true;
		}		
		else if (strcmp(order, "I_LEVEL") == 0)
		{
			I_LEVEL(order);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
		return false;
}

void AlphabetBST::R_IN(AlphabetNode* root, char * order)		//R_IN
{
	AlphabetNode* CurrentNode = root;

	if (CurrentNode)
	{
		R_IN(CurrentNode->GetLeft(), order);
		CurrentNode->GetBST()->Print(order);
		R_IN(CurrentNode->GetRight(), order);
	}
}

void AlphabetBST::R_PRE(AlphabetNode * root, char * order)	//R_PRE
{
	AlphabetNode* CurrentNode = root;

	if (CurrentNode)
	{
		CurrentNode->GetBST()->Print(order);
		R_PRE(CurrentNode->GetLeft(), order);
		R_PRE(CurrentNode->GetRight(), order);
	}
}

void AlphabetBST::R_POST(AlphabetNode * root, char * order)	//R_POST
{
	AlphabetNode* CurrentNode = root;

	if (CurrentNode)
	{
		R_POST(CurrentNode->GetLeft(), order);
		R_POST(CurrentNode->GetRight(), order);
		CurrentNode->GetBST()->Print(order);
	}
}


bool AlphabetBST::I_IN(char * order)						//I_IN
{
	if (root == NULL)
		return false;
	else
	{
		AlphabetNode* arr[101] = { '\0' };						//declare WordNode* array
		int cnt = 0;
		int top = 0;
		AlphabetNode* CurrentNode = root;
				
		while (1)
		{
			while (CurrentNode)
			{
				arr[cnt] = CurrentNode;
				CurrentNode = CurrentNode->GetLeft();
				cnt++;
				top++;
			}

			if (cnt == 0)
			{				
				return true;
			}
			top--;
			CurrentNode = arr[top];
			arr[cnt] = '\0';
			cnt--;
			CurrentNode->GetBST()->Print(order);
			CurrentNode = CurrentNode->GetRight();
		}
	}

}

bool AlphabetBST::I_PRE(char * order)					//I_PRE
{
	if (root == NULL)
		return false;
	else
	{
		AlphabetNode* arr[101] = { '\0' };					//declare WordNode* array
		int cnt = 0;
		int top = 0;
		AlphabetNode* CurrentNode = root;
				
		while (1)
		{
			while (CurrentNode)
			{
				arr[cnt] = CurrentNode;
				CurrentNode->GetBST()->Print(order);
				CurrentNode = CurrentNode->GetLeft();
				cnt++;
				top++;
			}

			if (cnt == 0)
			{
				return true;
			}
			top--;
			CurrentNode = arr[top];
			arr[cnt] = '\0';
			cnt--;
			CurrentNode = CurrentNode->GetRight();
		}
	}
}

bool AlphabetBST::I_POST(char * order)					//I_POST
{

	if (root == NULL)
		return false;
	else
	{
		AlphabetNode* arr[101] = { '\0' };						//declare WordNode* array
		int cnt = 0;
		AlphabetNode* CurrentNode = root;
				
		while (1)
		{
			while (CurrentNode)
			{
				if (CurrentNode->GetRight())
				{
					arr[cnt] = CurrentNode->GetRight();
					cnt++;
				}
				arr[cnt] = CurrentNode;
				CurrentNode = CurrentNode->GetLeft();
				cnt++;
			}

			if (cnt == 0)
			{
				return true;
			}

			cnt--;
			CurrentNode = arr[cnt];
			arr[cnt] = '\0';
			cnt--;

			if (CurrentNode->GetRight() && arr[cnt] == CurrentNode->GetRight())
			{
				arr[cnt] = CurrentNode;
				CurrentNode = CurrentNode->GetRight();
				cnt++;
			}
			else
			{
				CurrentNode->GetBST()->Print(order);
				CurrentNode = '\0';
				cnt++;
			}

		}
	}
}

bool AlphabetBST::I_LEVEL(char * order)
{
	AlphabetNode* arr[101] = { '\0' };
	int cnt = 0;
	int frt = cnt;
	AlphabetNode* CurrentNode = root;
	if (root)
	{
		while (CurrentNode)
		{
			CurrentNode->GetBST()->Print(order);
			if (CurrentNode->GetLeft())
			{
				arr[cnt] = CurrentNode->GetLeft();
				cnt++;
			}
			if (CurrentNode->GetRight())
			{
				arr[cnt] = CurrentNode->GetRight();
				cnt++;
			}
			if (frt == cnt)
			{
				return true;
			}
			CurrentNode = arr[frt];
			arr[frt] == '\0';
			frt++;
		}
	}
	return false;
}

void AlphabetBST::Clear(AlphabetNode * root)
{
	AlphabetNode* CurrentNode = root;
	if (CurrentNode)
	{
		Clear(CurrentNode->GetLeft());
		Clear(CurrentNode->GetRight());		
		delete CurrentNode;
	}
}

#include "AlphabetBST.h"
#include <iostream>
using namespace std;


AlphabetBST::AlphabetBST()//Initialization of variables 
{
	root = '\0';
	WordCnt = 0;
	AlphabetNode* node=new AlphabetNode;
	node->SetAlphabet('P');
	Insert(node);
	node=new AlphabetNode;
	node->SetAlphabet('H');
	Insert(node);
	node=new AlphabetNode;
	node->SetAlphabet('X');
	Insert(node);
	node=new AlphabetNode;
	node->SetAlphabet('D');
	Insert(node);
	node=new AlphabetNode;
	node->SetAlphabet('L');
	Insert(node);
	node=new AlphabetNode;
	node->SetAlphabet('T');
	Insert(node);
	node=new AlphabetNode;
	node->SetAlphabet('Z');
	Insert(node);
	node=new AlphabetNode;
	node->SetAlphabet('B');
	Insert(node);
	node=new AlphabetNode;
	node->SetAlphabet('F');
	Insert(node);
	node=new AlphabetNode;
	node->SetAlphabet('J');
	Insert(node);
	node=new AlphabetNode;
	node->SetAlphabet('N');
	Insert(node);
	node=new AlphabetNode;
	node->SetAlphabet('R');
	Insert(node);
	node=new AlphabetNode;
	node->SetAlphabet('V');
	Insert(node);
	node=new AlphabetNode;
	node->SetAlphabet('Y');
	Insert(node);
	node=new AlphabetNode;
	node->SetAlphabet('A');
	Insert(node);
	node=new AlphabetNode;
	node->SetAlphabet('C');
	Insert(node);
	node=new AlphabetNode;
	node->SetAlphabet('E');
	Insert(node);
	node=new AlphabetNode;
	node->SetAlphabet('G');
	Insert(node);
	node=new AlphabetNode;
	node->SetAlphabet('I');
	Insert(node);
	node=new AlphabetNode;
	node->SetAlphabet('K');
	Insert(node);
	node=new AlphabetNode;
	node->SetAlphabet('M');
	Insert(node);
	node=new AlphabetNode;
	node->SetAlphabet('O');
	Insert(node);
	node=new AlphabetNode;
	node->SetAlphabet('Q');
	Insert(node);
	node=new AlphabetNode;
	node->SetAlphabet('S');
	Insert(node);
	node=new AlphabetNode;
	node->SetAlphabet('U');
	Insert(node);
	node=new AlphabetNode;
	node->SetAlphabet('W');
	Insert(node);

}


AlphabetBST::~AlphabetBST()//Frees memory same WordBST's Destructor
{
	int stack=0, count, done;
	AlphabetNode * arr[100]={0,};
	AlphabetNode* pTemp=root;
	arr[0]=pTemp;
	if(pTemp->GetRight()!=NULL)
	{
		arr[1]=pTemp->GetRight();
		stack=1;
	}
	else
		stack=1;
	count=3;
	AlphabetNode* Left=pTemp->GetLeft();
	AlphabetNode* left[100]={0,};
	int c_left=0;
	while(1)
	{
		done=0;
		pTemp=arr[stack];
		if(pTemp->GetRight()!=NULL)
		{
			arr[++stack]=pTemp->GetRight();
			done=1;
			count++;
		}
		if(pTemp->GetLeft()!=NULL)
		{
			left[c_left]=pTemp->GetLeft();
			done=1;
			c_left++;	
		}
		if(pTemp->GetRight()==NULL)
		{
			if(c_left==0)
				break;
			arr[++stack]=left[--c_left];
			if(arr[stack]->GetLeft()!=NULL || arr[stack]->GetRight()!=NULL || ( arr[stack]->GetLeft()==NULL && arr[stack]->GetRight()==NULL && left[c_left]!=NULL))
				done=1;
		}
		if(done==0)
			break;
	}
	pTemp=Left;
	arr[++stack]=pTemp;
	while(1)
	{
		done=0;
		pTemp=arr[stack];
		if(pTemp->GetRight()!=NULL)
		{
			arr[++stack]=pTemp->GetRight();
			done=1;
			count++;
		}
		if(pTemp->GetLeft()!=NULL)
		{
			left[c_left]=pTemp->GetLeft();
			done=1;
			c_left++;	
		}
		if(pTemp->GetRight()==NULL)
		{
			if(c_left==0)
				break;
			arr[++stack]=left[--c_left];
			if(arr[stack]->GetLeft()!=NULL || arr[stack]->GetRight()!=NULL || ( arr[stack]->GetLeft()==NULL && arr[stack]->GetRight()==NULL && left[c_left]!=NULL))
				done=1;
		}
		if(done==0)
			break;
	}
	for(int j=stack;j>=0;j--)
	{
		if(arr[j]->GetBST()!=NULL && arr[j]->GetBST()->root!=NULL)
		{
			arr[j]->GetBST()->~WordBST();
			delete arr[j];
		}
	}

	
}
void AlphabetBST::Insert(AlphabetNode * node)// Insert node
{
	if(root==NULL)// case 1 : BST is empty 
	{
		root=node;// Substitutes the root node
		return;
	}
	//case 2 : BST is not empty
	AlphabetNode* pTemp=root;
	while(1)
	{
		if(pTemp->GetAlphabet()<node->GetAlphabet())// current node's alphabet < input node's alphabet
		{
			if(pTemp->GetRight()==NULL)// if currnt node's right node is empty
			{
				pTemp->SetRight(node);// current node's right node set input node
				return;
			}
			else  //if currnt node's left node is empty
			{
				pTemp=pTemp->GetRight();// current node's left node set input node
				continue;
			}
		}
		else
		{
			if(pTemp->GetLeft()==NULL) //if currnt node's right node is empty
			{
				pTemp->SetLeft(node);// current node's left node set input node
				return;
			}
			else   //if currnt node's right node is empty
			{
				pTemp=pTemp->GetLeft();// current node's right node set input node
				continue;
			}
		}
	}
}
bool AlphabetBST::Print(char * order)// print node
{
	ofstream log;
	log.open("log.txt", ios::app);
	if(log.fail())
		return 0; 
	if(strcmp(order,"R_PRE")==0)// order is R_PRE
	{
		cout<<"======== PRINT ========"<<endl;
		log<<"======== PRINT ========"<<endl;
		this->R_PRE(root);// call WordBST's R_PRE print function

	}
	else if(strcmp(order,"I_PRE")==0)//order is I_PRE
	{
		cout<<"======== PRINT ========"<<endl;
		log<<"======== PRINT ========"<<endl;
		this->I_PRE();// call WordBST's I_PRE print function

	}
	else if(strcmp(order,"R_IN")==0)//order is R_IN
	{
		cout<<"======== PRINT ========"<<endl;
		log<<"======== PRINT ========"<<endl;
		this->R_IN(root);// call WordBST's R_IN print function
	}
	else if(strcmp(order,"I_IN")==0)//order is I_IN
	{
		cout<<"======== PRINT ========"<<endl;
		log<<"======== PRINT ========"<<endl;
		this->I_IN();// call WordBST's I_IN print function
	}
	else if(strcmp(order,"R_POST")==0)//order is R_POST
	{
		cout<<"======== PRINT ========"<<endl;
		log<<"======== PRINT ========"<<endl;
		this->R_POST(root);// call WordBST's R_POST print function
	}
	else if(strcmp(order,"I_POST")==0)//order is I_POST
	{
		cout<<"======== PRINT ========"<<endl;
		log<<"======== PRINT ========"<<endl;
		this->I_POST();// call WordBST's I_POST print function
	}
	else if(strcmp(order,"I_LEVEL")==0)//order is I_LEVEL
	{
		cout<<"======== PRINT ========"<<endl;
		log<<"======== PRINT ========"<<endl;
		this->I_LEVEL();// call WordBST's I_LEVEL print function
	}
	else
	{
		cout<<"======== ERROR ========"<<endl<<"700"<<endl<<"======================="<<endl;
		log<<"======== ERROR ========"<<endl<<"700"<<endl<<"======================="<<endl;
	}
	cout<<"======================="<<endl;
	log<<"======================="<<endl;
	log.close();
	return 1;
}
AlphabetNode * AlphabetBST::Search(char alpabet)//search node
{
	if(root==NULL)//if BST is empty return NULL
		return NULL;

	return R_Search(root, alpabet);// call recursive Search funciont

}
bool AlphabetBST::Save()// same WordBST's Save function but call WordBST's save function 
{
	ofstream memorizing;
	memorizing.open("memorizing_word.txt", ios::trunc);
	if(memorizing.fail())
		return 0;
	int stack=0;
	AlphabetNode * arr[100]={0,};
	AlphabetNode* pTemp=root;
	arr[stack++]=root;
	while(stack!=0)
	{
		pTemp=arr[--stack];	
		arr[stack]->GetBST()->Save();
		arr[stack]=NULL;
		if(pTemp->GetRight()!=NULL)
			arr[stack++]=pTemp->GetRight();
		if(pTemp->GetLeft()!=NULL)
			arr[stack++]=pTemp->GetLeft();
	}
	memorizing.close();
	return 1;
}
void AlphabetBST::R_PRE(AlphabetNode* node)//same WordBST's R_PRE print
{
	if(node==NULL)
		return;
	node->GetBST()->R_PRE(node->GetBST()->GetRoot());//call WordBST's R_PRE print function
	R_PRE(node->GetLeft());
	R_PRE(node->GetRight());
}
void AlphabetBST::I_PRE()//same WordBST's I_PRE print
{
	int stack=1;
	AlphabetNode * arr[100]={0,};
	AlphabetNode* pTemp=root;
	arr[0]=root;
	while(stack!=0)
	{
		pTemp=arr[--stack];	
		arr[stack]->GetBST()->I_PRE();//call WordBST's I_PRE print function
		arr[stack]=NULL;
		if(pTemp->GetRight()!=NULL)
			arr[stack++]=pTemp->GetRight();
		if(pTemp->GetLeft()!=NULL)
			arr[stack++]=pTemp->GetLeft();
	}

}
void AlphabetBST::R_IN(AlphabetNode* node)//same WordBST's R_IN print
{
	if(node==NULL)
		return;
	R_IN(node->GetLeft());
	node->GetBST()->R_IN(node->GetBST()->GetRoot());//call WordBST's R_IN print function
	R_IN(node->GetRight());
}
void AlphabetBST::I_IN()//same WordBST's I_IN print
{
	AlphabetNode* pTemp=root;
	AlphabetNode* arr[100]={0,};
	int stack=0;
	while(1)
	{
		while(pTemp!=NULL)
		{
			arr[stack]=pTemp;
			pTemp=pTemp->GetLeft();
			stack++;
		}
		if(arr[0]==NULL)
			break;
		pTemp=arr[--stack];
		arr[stack]->GetBST()->I_IN();//call WordBST's I_IN print function
		pTemp=arr[stack]->GetRight();
		arr[stack]=NULL;
		arr[stack]=pTemp;
		if(stack==-1)
			break;
	}


}
void AlphabetBST::R_POST(AlphabetNode* node)//same WordBST's R_POST print
{
	if(node==NULL)
		return;
	R_POST(node->GetLeft());
	R_POST(node->GetRight());
	node->GetBST()->R_POST(node->GetBST()->GetRoot());//call WordBST's R_POST print function
}
void AlphabetBST::I_POST()//same WordBST's I_POST print
{
	int stack=0, count, done;
	AlphabetNode * arr[100]={0,};
	AlphabetNode* pTemp=root;
	arr[0]=pTemp;
	if(pTemp->GetRight()!=NULL)
	{
		arr[1]=pTemp->GetRight();
		stack=1;
	}
	else
		stack=1;
	count=3;
	AlphabetNode* Left=pTemp->GetLeft();
	AlphabetNode* left[100]={0,};
	int c_left=0;
	while(1)
	{
		done=0;
		pTemp=arr[stack];
		if(pTemp->GetRight()!=NULL)
		{
			arr[++stack]=pTemp->GetRight();
			done=1;
			count++;
		}
		if(pTemp->GetLeft()!=NULL)
		{
			left[c_left]=pTemp->GetLeft();
			done=1;
			c_left++;	
		}
		if(pTemp->GetRight()==NULL)
		{
			if(c_left==0)
				break;
			arr[++stack]=left[--c_left];
			if(arr[stack]->GetLeft()!=NULL || arr[stack]->GetRight()!=NULL || ( arr[stack]->GetLeft()==NULL && arr[stack]->GetRight()==NULL && left[c_left]!=NULL))
				done=1;
		}
		if(done==0)
			break;
	}
	pTemp=Left;
	arr[++stack]=pTemp;
	while(1)
	{
		done=0;
		pTemp=arr[stack];
		if(pTemp->GetRight()!=NULL)
		{
			arr[++stack]=pTemp->GetRight();
			done=1;
			count++;
		}
		if(pTemp->GetLeft()!=NULL)
		{
			left[c_left]=pTemp->GetLeft();
			done=1;
			c_left++;	
		}
		if(pTemp->GetRight()==NULL)
		{
			if(c_left==0)
				break;
			arr[++stack]=left[--c_left];
			if(arr[stack]->GetLeft()!=NULL || arr[stack]->GetRight()!=NULL || ( arr[stack]->GetLeft()==NULL && arr[stack]->GetRight()==NULL && left[c_left]!=NULL))
				done=1;
		}
		if(done==0)
			break;
	}
	for(int j=stack;j>=0;j--)
	{
		if(arr[j]->GetBST()!=NULL && arr[j]->GetBST()->root!=NULL)
			arr[j]->GetBST()->I_POST();//call WordBST's I_POST print function
	}

}
void AlphabetBST::I_LEVEL()//same WordBST's I_LEVEL print
{
	AlphabetNode* pTemp=root;
	AlphabetNode* arr[100]={0,};
	int stack=0,i=0;
	arr[i]=pTemp;
	while(pTemp!=NULL)
	{
		if(arr[i]!=NULL)
		{
			arr[i]->GetBST()->I_LEVEL();//call WordBST's I_LEVEL print function
		}
		if(pTemp->GetLeft()!=NULL)
			arr[++stack]=pTemp->GetLeft();
		if(pTemp->GetRight()!=NULL)
			arr[++stack]=pTemp->GetRight();
		if(i==stack)
			return;
		pTemp=arr[++i];
	}
}
AlphabetNode* AlphabetBST::R_Search(AlphabetNode* node, char alphabet)// //same WordBST's R_Search function 
{
	if(alphabet==0)
		return NULL;
	if(node->GetLeft()==NULL && node->GetRight()==NULL && node->GetAlphabet()!=alphabet)
		return NULL;
	if(node->GetAlphabet()==alphabet)
		return node;
	else if(node->GetAlphabet() > alphabet)
		this->R_Search(node->GetLeft(),alphabet);
	else if(node->GetAlphabet() < alphabet)
		this->R_Search(node->GetRight(),alphabet);
}

#include "WordBST.h"
#include <iostream>
#include <fstream>
using namespace std;


WordBST::WordBST()//Initialization of variables
{
	root = '\0';
}


WordBST::~WordBST()//Frees memory using iterative post order
{
	int stack=0, count, done;
	WordNode * arr[100]={0,};
	WordNode* pTemp=root;
	arr[0]=pTemp;
	if(pTemp->GetRight()!=NULL)
	{
		arr[1]=pTemp->GetRight();
		stack=1;
	}
	else
		stack=0;
	count=3;
	WordNode* Left=pTemp->GetLeft();
	WordNode* left[100]={0,};
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
	if(stack!=0&&pTemp!=NULL)
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
		arr[j]=NULL;
		delete arr[j];

	}


}
void WordBST::Insert(WordNode* node)// insert node
{
	if(root==NULL)// case 1 : BST is empty 
	{
		root=node;
		return;
	}
	// case 2 : BST is not empty
	WordNode* pTemp=root;
	while(1)
	{
		if(strcmp(pTemp->GetWord(), node->GetWord())==-1)// current node<input node
		{
			if(pTemp->GetRight()==NULL)// current node's right is empty
			{
				pTemp->SetRight(node);// set right node
				return;
			}
			else// current node's right is not empty
			{
				pTemp=pTemp->GetRight();// move right node
				continue;
			}
		}
		else// current node >= input node
		{
			if(pTemp->GetLeft()==NULL)//current node's left is empty
			{
				pTemp->SetLeft(node);//set left node
				return;
			}
			else//current node's left is not empty
			{
				pTemp=pTemp->GetLeft();//move left node
				continue;
			}
		}
	}
}
WordNode* WordBST::Delete(char* word)// delete node, like queue's pop
{
	if(root==NULL)//if BST is empty return NULL
		return NULL;
	return this->R_Delete(root, word);// call recursive delete function
}
WordNode* WordBST::Search(char* word)//search node
{
	if(root==NULL)//if BST is empty return NULL
		return NULL;
	return this->R_Search(root,word);// call recursive Search funciont
}
bool WordBST::Print(char* order)// print node
{
	ofstream log;
	log.open("log.txt", ios::app);
	if(log.fail())
		return 0;
	if(strcmp(order,"R_PRE")==0)// order is R_PRE
	{
		cout<<"======== PRINT ========"<<endl;
		log<<"======== PRINT ========"<<endl;
		this->R_PRE(root);//call R_PRE function
		cout<<"======================="<<endl;
		log<<"======================="<<endl;
		return 1;
	}
	else if(strcmp(order,"I_PRE")==0)//order is I_PRE
	{
		cout<<"======== PRINT ========"<<endl;
		log<<"======== PRINT ========"<<endl;
		this->I_PRE();//call I_PRE function
		cout<<"======================="<<endl;
		log<<"======================="<<endl;
		return 1;
	}
	else if(strcmp(order,"R_IN")==0)//order is R_IN
	{
		cout<<"======== PRINT ========"<<endl;
		log<<"======== PRINT ========"<<endl;
		this->R_IN(root);//call R_IN function
		cout<<"======================="<<endl;
		log<<"======================="<<endl;
		return 1;
	}
	else if(strcmp(order,"I_IN")==0)//order is I_IN
	{
		cout<<"======== PRINT ========"<<endl;
		log<<"======== PRINT ========"<<endl;
		this->I_IN();//call I_IN function
		cout<<"======================="<<endl;
		log<<"======================="<<endl;
		return 1;
	}
	else if(strcmp(order,"R_POST")==0)//order is R_POST
	{
		cout<<"======== PRINT ========"<<endl;
		log<<"======== PRINT ========"<<endl;
		this->R_POST(root);//call R_POST function
		cout<<"======================="<<endl;
		log<<"======================="<<endl;
		return 1;
	}
	else if(strcmp(order,"I_POST")==0)//order is I_POST
	{
		cout<<"======== PRINT ========"<<endl;
		log<<"======== PRINT ========"<<endl;
		this->I_POST();//call I_POST function
		cout<<"======================="<<endl;
		log<<"======================="<<endl;
		return 1;
	}
	else if(strcmp(order,"I_LEVEL")==0)//order is I_LEVEL
	{
		cout<<"======== PRINT ========"<<endl;
		log<<"======== PRINT ========"<<endl;
		this->I_LEVEL();//call I_LEVEL function
		cout<<"======================="<<endl;
		log<<"======================="<<endl;
		return 1;
	}
	else// if input another order
	{	
		return 0;
	}
}
bool WordBST::Save()//save function use iterative pre order
{
	if(root==NULL)//if BST is empty return 0
		return 0;
	ofstream memorizing;
	memorizing.open("memorizing_word.txt",ios::app);// txt file open
	if(memorizing.fail())
		return 0;
	int stack=0;																	///////////////////////ITERATIVE PRE ORDER //////////////////////
	WordNode * arr[100]={0,};	
	WordNode* pTemp=root;		
	arr[stack++]=pTemp;															
	while(stack!=0)
	{
		pTemp=arr[--stack];	
		memorizing<<pTemp->GetWord()<<"	"<<pTemp->GetMean()<<endl;
		arr[stack]=NULL;
		if(pTemp->GetRight()!=NULL)
			arr[stack++]=pTemp->GetRight();
		if(pTemp->GetLeft()!=NULL)
			arr[stack++]=pTemp->GetLeft();
	}																				////////////////////////////////////////////////////////////////////
	memorizing.close();
	return 1;
}
void WordBST::R_PRE(WordNode* node)//Recursive pre order
{
	if(node==NULL)// Escape condition
		return;
	ofstream log;
	log.open("log.txt",ios::app);
	if(log.fail())
		return;
	cout<<node->GetWord()<<" "<<node->GetMean()<<endl;//print
	log<<node->GetWord()<<" "<<node->GetMean()<<endl;
	log.close();
	R_PRE(node->GetLeft());//call R_PRE function move left
	R_PRE(node->GetRight());//call R_PRE function move right
}
void WordBST::I_PRE()
{
	if(root==NULL)//Escape condition
		return;
	int stack=0;
	ofstream log;
	log.open("log.txt",ios::app);//txt file open
	if(log.fail())
		return;
	WordNode * arr[100]={0,};// initialized value
	WordNode* pTemp=root;// initialized value
	arr[stack++]=pTemp;// array like stack
	while(stack!=0)
	{
		pTemp=arr[--stack];	//pTemp initialized
		cout<<pTemp->GetWord()<<" "<<pTemp->GetMean()<<endl;//print
		log<<pTemp->GetWord()<<" "<<pTemp->GetMean()<<endl;
		arr[stack]=NULL;// like Pop
		if(pTemp->GetRight()!=NULL)// pTemp->right is not empty
			arr[stack++]=pTemp->GetRight();// Push the array
		if(pTemp->GetLeft()!=NULL)//pTemp->left is not empty
			arr[stack++]=pTemp->GetLeft();// Push the array
	}
	log.close();// txt file close

}
void WordBST::R_IN(WordNode* node)// Recursive In order
{
	if(node==NULL)//Escape condition
		return;
	ofstream log;
	log.open("log.txt",ios::app);
	if(log.fail())
		return;
	R_IN(node->GetLeft());//call R_IN move left
	cout<<node->GetWord()<<" "<<node->GetMean()<<endl;//print
	log<<node->GetWord()<<" "<<node->GetMean()<<endl;
	R_IN(node->GetRight());//call R_IN move left
	log.close();
}
void WordBST::I_IN()//Iterative In order 
{
	ofstream log;
	log.open("log.txt",ios::app);
	if(log.fail())
		return;
	WordNode* pTemp=root;
	WordNode* arr[100]={0,};// array like stack
	int stack=0;
	while(1)
	{
		while(pTemp!=NULL)// move to left
		{
			arr[stack]=pTemp;//push node
			pTemp=pTemp->GetLeft();// move
			stack++;
		}
		if(arr[0]==NULL)// array is empty break loop
			break;
		pTemp=arr[--stack];
		cout<<arr[stack]->GetWord()<<" "<<arr[stack]->GetMean()<<endl;//print
		log<<arr[stack]->GetWord()<<" "<<arr[stack]->GetMean()<<endl;
		pTemp=arr[stack]->GetRight();//pop array's right node
		arr[stack]=NULL;
		arr[stack]=pTemp;// Push pTemp;
		if(stack==-1)//Escape condition
			break;
	}
	log.close();
}
void WordBST::R_POST(WordNode* node)
{
	if(node==NULL)//Escape condition
		return;
	ofstream log;
	log.open("log.txt",ios::app);
	if(log.fail())
		return;
	R_POST(node->GetLeft());//call R_POST move left
	R_POST(node->GetRight());//call R_POST move right
	cout<<node->GetWord()<<" "<<node->GetMean()<<endl;//print
	log<<node->GetWord()<<" "<<node->GetMean()<<endl;
	log.close();
}
void WordBST::I_POST()//Iterative Post order
{
	ofstream log;
	log.open("log.txt",ios::app);
	if(log.fail())
		return;
	int stack=0, count, done;
	WordNode * arr[100]={0,};// like stack
	WordNode* pTemp=root;
	arr[0]=pTemp;//Top node setting
	if(pTemp->GetRight()!=NULL)//root has right node
	{
		arr[1]=pTemp->GetRight();
		stack=1;
	}
	else
		stack=0;
	count=3;
	WordNode* Left=pTemp->GetLeft();// remember root's left node
	WordNode* left[100]={0,};// current node's left node save
	int c_left=0;
	while(1)// post traverse using root's right node 
	{
		done=0;
		pTemp=arr[stack];//Initialized current node
		if(pTemp->GetRight()!=NULL)//if right node is not empty Push to stack array
		{
			arr[++stack]=pTemp->GetRight();
			done=1;
			count++;
		}
		if(pTemp->GetLeft()!=NULL)//if left node is not empty save to left array
		{
			left[c_left]=pTemp->GetLeft();
			done=1;
			c_left++;	
		}
		if(pTemp->GetRight()==NULL)// if right node is empty Push node that left array's Pop
		{
			if(c_left==0)
				break;
			arr[++stack]=left[--c_left];
			if(arr[stack]->GetLeft()!=NULL || arr[stack]->GetRight()!=NULL || ( arr[stack]->GetLeft()==NULL && arr[stack]->GetRight()==NULL && left[c_left]!=NULL))
				done=1;
		}
		if(done==0)//Escape condition
			break;
	}
	pTemp=Left;
	if(stack!=0&&pTemp!=NULL)// left node is not empty
		arr[++stack]=pTemp;
	
	while(1)//same first loop  // post traverse using root's left node 
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

	for(int j=stack;j>=0;j--)//print
	{
		cout<<arr[j]->GetWord()<<" "<<arr[j]->GetMean()<<endl;//visit
		log<<arr[j]->GetWord()<<" "<<arr[j]->GetMean()<<endl;
	}
	log.close();


}
void WordBST::I_LEVEL()//Iterative Level order 
{
	ofstream log;
	log.open("log.txt",ios::app);
	if(log.fail())
		return;
	WordNode* pTemp=root;
	WordNode* arr[100]={0,};//stack array
	int stack=0,i=0;
	arr[i]=pTemp;
	while(pTemp!=NULL)
	{
		if(arr[i]!=NULL)
		{
			log<<arr[i]->GetWord()<<" "<<arr[i]->GetMean()<<endl;
			cout<<arr[i]->GetWord()<<" "<<arr[i]->GetMean()<<endl;//print
		}
		if(pTemp->GetLeft()!=NULL)//if current node's left node is not empty push current node's left node
			arr[++stack]=pTemp->GetLeft();
		if(pTemp->GetRight()!=NULL)//if current node's right node is not empty push current node's right node
			arr[++stack]=pTemp->GetRight();
		if(i==stack)//Escape condition
			break;
		pTemp=arr[++i];
	}
	log.close();
}
WordNode* WordBST::R_Delete(WordNode* node, char* word)// Recursive delete
{
	if(strcmp(root->GetWord(),word)==0)// case 1 : delete root
	{
		if(root->GetLeft()!=NULL && root->GetRight()!=NULL)// if root has left, right node
		{
			WordNode* pTemp=root;
			WordNode* pLeft=root->GetLeft();// save root's left node
			WordNode* pRight=root->GetRight();// save root's right node
			pTemp=pTemp->GetLeft();// move pTemp to left node
			while(pTemp->GetRight()->GetRight()!=NULL)// move pTemp to right leaf node's parent node
				pTemp=pTemp->GetRight();
			WordNode* pTemp_Right=pTemp->GetRight();//save pTemp's right node 
			pTemp->SetRight(NULL);// break link
			WordNode* return_node=root;// save root address
			root=pTemp_Right;// change root
			root->SetLeft(pLeft);// link root's left node
			root->SetRight(pRight);// link root's right node
			return return_node;
		}
		else if(root->GetLeft()==NULL || root->GetRight()==NULL)// if root has only left node or right node
		{
			if(root->GetLeft()==NULL)// if root's left node is empty
			{
				WordNode* pTemp=root;// save root address
				root=root->GetRight();// move root to right node
				return pTemp;// return pTemp;
			}
			else// if root's right node is empty
			{
				WordNode* pTemp=root;// save root address
				root=root->GetLeft();// move root to leftt node
				return pTemp;// return pTemp;
			}
		}
		else// if root is leaf node
		{
			WordNode* pTemp=root;//save root address
			root=NULL;// initializing root 
			return pTemp;// return pTemp;
		}
	}
	//case 2 : delete current node's left node // current node's left node's left , right node is not empty
	else if(node->GetLeft() != NULL && strcmp(node->GetLeft()->GetWord(),word)==0 && node->GetLeft()->GetLeft()!=NULL && node->GetLeft()->GetRight()!=NULL)
	{
		WordNode* pLeft=node->GetLeft()->GetLeft();
		WordNode* pRight=node->GetLeft()->GetRight();
		WordNode* pTemp=node->GetLeft();
		node=node->GetLeft();
		while(node->GetRight()->GetRight()!=NULL)// move to right leaf node's parent node
			node=node->GetRight();
		WordNode* pTTemp=node->GetRight();
		node->SetRight(NULL);
		WordNode* Return_node=pTemp;
		pTemp=pTTemp;
		pTemp->SetLeft(pLeft);
		pTemp->SetRight(pRight);
		return Return_node;
	}
	//case 3 : delete current node's left node // current node's left node has only left node or right node
	else if(node->GetLeft()!=NULL && strcmp(node->GetLeft()->GetWord(),word)==0 && (node->GetLeft()->GetLeft()!=NULL || node->GetLeft()->GetRight()!=NULL))
	{
		WordNode* pLeft=node->GetLeft()->GetLeft();
		WordNode* pRight=node->GetLeft()->GetRight();
		if(node->GetLeft()->GetLeft()==NULL)// current node's left node's left node is empty
		{
			WordNode* Return_node=node->GetLeft();
			WordNode* pTemp=node->GetLeft()->GetRight();
			node->SetLeft(pTemp);
			return Return_node;
		}
		else if(node->GetLeft()->GetRight()==NULL)//current node's left node's right node is empty
		{
			WordNode* Return_node=node->GetLeft();
			WordNode* pTemp=node->GetLeft()->GetLeft();
			node->SetLeft(pTemp);
			return Return_node;
		}
	}
	//case 4 : delete current node's left node // current node's left node is leaf node
	else if(node->GetLeft()!=NULL && strcmp(node->GetLeft()->GetWord(),word)==0 && node->GetLeft()->GetLeft()==NULL && node->GetLeft()->GetRight()==NULL)
	{
		WordNode* Return_node=node->GetLeft();
		node->SetLeft(NULL);
		return Return_node;
	}
	//case 4 : delete current node's right node // current node's right node has left node and right node

	else if(node->GetRight()!=NULL && strcmp(node->GetRight()->GetWord(),word)==0 && node->GetRight()->GetLeft()!=NULL && node->GetRight()->GetRight()!=NULL)
	{
		WordNode* pLeft=node->GetRight()->GetLeft();
		WordNode* pRight=node->GetRight()->GetRight();
		WordNode* pTemp=node->GetRight();
		node=node->GetRight();
		while(node->GetLeft()->GetLeft()!=NULL)
			node=node->GetLeft();
		WordNode* pTTemp=node->GetLeft();
		node->SetLeft(NULL);
		WordNode* Return_node=pTemp;
		pTemp=pTTemp;
		pTemp->SetLeft(pLeft);
		pTemp->SetRight(pRight);
		return Return_node;
	}
	//case 5 : delete current node's right node // current node's right node has only left node or right node
	else if(node->GetRight()!=NULL && strcmp(node->GetRight()->GetWord(),word)==0 && (node->GetRight()->GetLeft()!=NULL || node->GetRight()->GetRight()!=NULL))
	{
		WordNode* pLeft=node->GetRight()->GetLeft();
		WordNode* pRight=node->GetRight()->GetRight();
		if(node->GetRight()->GetLeft()==NULL)
		{
			WordNode* Return_node=node->GetRight();
			WordNode* pTemp=node->GetRight()->GetRight();
			node->SetLeft(pTemp);
			return Return_node;
		}
		else if(node->GetLeft()->GetRight()==NULL)
		{
			WordNode* Return_node=node->GetRight();
			WordNode* pTemp=node->GetRight()->GetLeft();
			node->SetLeft(pTemp);
			return Return_node;
		}
	}
	// case 6 : delete current node's right node // current node's right node is leaf node
	else if(node->GetRight()!=NULL && strcmp(node->GetRight()->GetWord(),word)==0 && node->GetRight()->GetLeft()==NULL && node->GetRight()->GetRight()==NULL)
	{
		WordNode* Return_node=node->GetRight();
		node->SetRight(NULL);
		return Return_node;
	}
	else if(strcmp(node->GetWord(),word)==-1)// current node's word < delete node's word
	{
		node=node->GetRight();// move right node and call R_Delete function
		R_Delete(node,word);
	}
	else if(strcmp(node->GetWord(),word)==1)// current node's word > delete node's word
	{
		node=node->GetLeft();// move left node and call R_Delete function
		R_Delete(node,word);
	}
}
WordNode* WordBST::R_Search(WordNode* node, char* word)//Recursive Search funcion
{
	if(node==NULL)//Escape condition
		return NULL;
	if(strcmp(word,"")==0)//Escape condition
		return NULL;
	if(node->GetLeft()==NULL && node->GetRight()==NULL && strcmp(node->GetWord(),word)!=0)// current node is lear node but don't fine node return NULL
		return NULL;
	if(strcmp(node->GetWord(),word)==0)// if fine node return current node
		return node;
	else if(strcmp(node->GetWord(),word)==1)// if current node's word > search word , move left call R_Search function
		this->R_Search(node->GetLeft(),word);
	else if(strcmp(node->GetWord(),word)==-1)// if current node's word < search word , move right call R_Search function
		this->R_Search(node->GetRight(),word);
}
WordNode* WordBST::GetRoot()//return root function
{
	return this->root;
}

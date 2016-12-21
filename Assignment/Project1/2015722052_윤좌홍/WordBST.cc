#include "WordBST.h"



WordBST::WordBST()
{
	root = 0;	//root node setting
}
//in this case
//insert function binary search method, if push_node is NULL, return function
void WordBST::Insert(WordNode * push_node)
{
	if(push_node == 0) return;

	WordNode *parent_node = root;	//used by parent node, if bigger than parent_node enter the right node else, enter the left node
	if(root != 0){
		for( ; ; ){
			if(strcmp(parent_node->GetWord(), push_node->GetWord()) == 0){
				//overlab word prevent to insert in BST
				return;
			}
			if(strcmp(parent_node->GetWord(), push_node->GetWord()) > 0
				&& parent_node->GetLeft() == 0){	//left
				parent_node->SetLeft(push_node);
					break;
			}
			else if(strcmp(parent_node->GetWord(), push_node->GetWord()) > 0){
				parent_node = parent_node->GetLeft();	//right
				continue;
			}
			else if(strcmp(parent_node->GetWord(), push_node->GetWord()) < 0	//insert right
				&& parent_node->GetRight() == 0){
				parent_node->SetRight(push_node);
					break;
			}
			else if(strcmp(parent_node->GetWord(), push_node->GetWord()) < 0){	//insert left
				parent_node = parent_node->GetRight();
				continue;
			}
		}
	}
	else{
		root = push_node;
	}
}
//in this case
//1. delete node have the number of child 0
//2. delete node have the number of child 1
//3. delete node have the number of child 2
//4. no search delete node
//5. node's point out cutting, not delete node
WordNode * WordBST::Delete(char * word)
{
	WordNode *parent_node = root, *left_child = NULL, *right_child = NULL;
	WordNode *predecessor = NULL, *successor = NULL;
	WordNode *target = root;
 	if(root){	//if BST is non empty
		while(target != NULL){
			if(strcmp(target->GetWord(), word) < 0){	//searching delete node and parent
				parent_node = target;
				target = target->GetRight();
			}
			else if(strcmp(target->GetWord(), word) > 0){	//searching delete node and parent
				parent_node = target;
				target = target->GetLeft();
			}
			else					//if searching, break routin target<-node
				break;
		}
		//case leaf node
		if(target->GetLeft() == NULL && target->GetRight() == NULL){

			if(target == root){		//if delete node is root
				root = NULL;
			}
			else{					//if delete node is leaf node
				if(parent_node->GetLeft() == target){//left leaf
					parent_node->SetLeft(NULL);
				}
				else if(parent_node->GetRight() == target){								//right leaf
					parent_node->SetRight(NULL);
				}
			}
		}
		//case The number of child node is 2
		else if(target->GetLeft() != NULL && target->GetRight() != NULL){	//if The number of child node is 2

			predecessor = target->GetLeft();
			successor = predecessor;
			while(successor->GetRight() != NULL){		//searching the lagest node in left subtree
				predecessor = successor;
				successor = successor->GetRight();
			}
			
			if(predecessor == successor){		//delete node's left subtree have left child node, no right child node
				parent_node->SetLeft(predecessor);//pointing Child Node for Delete node == target
				predecessor->SetRight(target->GetRight());//searched changing to delete node, bubble up target node's child node
			}
			else{								//delete node's left subtree have left, right child
				predecessor->SetRight(successor->GetLeft());//bubble up delete node's left child
				successor->SetLeft(target->GetLeft());
				successor->SetRight(target->GetRight());//delete node's left, right pointer copy
			}
			
			if(target == root){					//delete node is root node
				root = successor;
			}
			}	
		//case The number of chile nod is 1
		else{

			if(target->GetLeft() != NULL){
				if(parent_node->GetLeft() == target){		//if left node is delete node, stride node to delete node
					parent_node->SetLeft(target->GetLeft());
				}
				else if(parent_node->GetRight() == target){
					parent_node->SetRight(target->GetLeft());
				}
			}
			else{
				predecessor = target->GetRight(); //if right node is delete node ,stride node to delete node
				successor = predecessor;
				while(successor->GetLeft() != NULL){
					predecessor = successor;
					successor = successor->GetLeft();
				}

				if(predecessor == successor){
					if(predecessor != NULL){
					parent_node->SetRight(predecessor);
					}
				}
				else{
					predecessor->SetLeft(successor->GetRight());
					successor->SetLeft(target->GetLeft());
					successor->SetRight(target->GetRight());
				}

			}

			if(target == root){	//if delete root, pointing root
				root = successor;
			}
			
		}
			
		return target;		//return the delete node
	} 
	else
	return 0;
}
//this case
//1. search node isn't exist in BST
//2. search node is exist
WordNode * WordBST::Search(char * word)
{
	if(root){
		WordNode *parent_node = root;
		for( ; ; ){
			if(parent_node == 0) return 0;	//search node isn't exist in BST
			if(strcmp(parent_node->GetWord(), word) > 0){
				parent_node = parent_node->GetLeft();
				continue;
			}
			else if(strcmp(parent_node->GetWord(), word) < 0){
				parent_node = parent_node->GetRight();
				continue;
			}
			else
				return parent_node;
		}
	}
	else
		return 0;			//root node is empty
}
//this case
//1. BST counting wordnode is 0, return false;
//2. order is not defined order, return false;
//3. success printing, return true;
bool WordBST::Print(char * order)
{
	if(order) strcpy(m_order, order);	//exception order error
	if(fout_log.is_open() == false) fout_log.open("log.txt", ios::app);

	if(!strcmp("R_PRE", m_order)){
		Print_Pre(root);
	}
	else if(!strcmp("R_IN", m_order)){
		Print_In(root);
	}
	else if(!strcmp("R_POST", m_order)){
		Print_Post(root);
	}
	else if(!strcmp("I_PRE", m_order)){
		Iter_Pre(root);
	}
	else if(!strcmp("I_IN", m_order)){
		Iter_In(root);
	}
	else if(!strcmp("I_POST", m_order)){
		Iter_Post(root);
	}
	else if(!strcmp("I_LEVEL", m_order)){
		Iter_Level(root);
	}
	else
		return false;	//order is not defined order

	return true;		//print success!!
}
void WordBST::Print_Pre(WordNode * parm_pNode)
{
	if(parm_pNode){
		fout_log<<parm_pNode->GetWord()<<"	"<<parm_pNode->GetMean()<<endl;
		cout<<parm_pNode->GetWord()<<"	"<<parm_pNode->GetMean()<<endl;
		Print_Pre(parm_pNode->GetLeft());
		Print_Pre(parm_pNode->GetRight());
	}
}
void WordBST::Print_In(WordNode * parm_pNode)
{
	if(parm_pNode){
		Print_In(parm_pNode->GetLeft());
		fout_log<<parm_pNode->GetWord()<<"	"<<parm_pNode->GetMean()<<endl;
		cout<<parm_pNode->GetWord()<<"	"<<parm_pNode->GetMean()<<endl;
		Print_In(parm_pNode->GetRight());
	}
}
void WordBST::Print_Post(WordNode * parm_pNode)
{
	if(parm_pNode){
		Print_Post(parm_pNode->GetLeft());
		Print_Post(parm_pNode->GetRight());
		fout_log<<parm_pNode->GetWord()<<"	"<<parm_pNode->GetMean()<<endl;
		cout<<parm_pNode->GetWord()<<"	"<<parm_pNode->GetMean()<<endl;
	}
}
void WordBST::Iter_Pre(WordNode * parm_pNode)
{
	W_Stack *s = new W_Stack;
	WordNode *cur = NULL;
	WordNode *LeftChild = NULL;
	WordNode *RightChild = NULL;
	s->Push(parm_pNode);

	while(1){
		if(s->isEmpty() == true){		//if stack is empty, stop routin
			break;
		}
		else{
			cur = s->Pop();				//to assist traversal structure Memorize visiting order
			if(cur != NULL){
				fout_log<<cur->GetWord()<<"	"<<cur->GetMean()<<endl;
				cout<<cur->GetWord()<<"	"<<cur->GetMean()<<endl;
				
				LeftChild = cur->GetLeft();
				RightChild = cur->GetRight();
				
				if(RightChild != NULL)
					s->Push(RightChild);
				if(LeftChild != NULL)
					s->Push(LeftChild);
				//side node push for visiting
			}
		}
	}
}
//in this case
//1. using stack structure, access at parent node;
void WordBST::Iter_In(WordNode * parm_pNode)
{
	W_Stack *s = new W_Stack;
	WordNode *cur = parm_pNode;
	WordNode *stack_node = NULL;
	while(1){
		for( ; cur!= 0; cur = cur->GetLeft()){
			s->Push(cur);
		}
		if(s->isEmpty() == true){
			break;
		}
		
		else{
			stack_node = s->Pop();
			if(stack_node != NULL){
				fout_log<<stack_node->GetWord()<<"	"<<stack_node->GetMean()<<endl;
				cout<<stack_node->GetWord()<<" "<<stack_node->GetMean()<<endl;
				stack_node = stack_node->GetRight();
				cur = stack_node;
			}
		}
	}

}
//in this case
//1. using stack structure, access at parent node;
void WordBST::Iter_Post(WordNode * parm_pNode)
{
	WordNode * visit_node = 0;
	WordNode * cur = root;
	W_Stack * s = new W_Stack;
	if(root){
		
		while(cur || !s->isEmpty()){
			if(cur){
				s->Push(cur);
				cur = cur->GetLeft();
				//push root node and if exist left node, enter the left edge node
			}
			else{
				cur = s->Pop();//access parent node and push left, right
				while(cur->GetRight() == NULL || cur->GetRight() == visit_node){
					cout<<cur->GetWord()<<"	"<<cur->GetMean()<<endl;
					fout_log<<cur->GetWord()<<"	"<<cur->GetMean()<<endl;
					visit_node = cur;
					if(s->isEmpty()){//all node visit
						delete s;
						return;
					}
					cur = s->Pop();//print data and visit parent node
				}
				if(cur != visit_node)
					s->Push(cur);
				visit_node = cur;	//memory visit node
				cur = cur->GetRight();	//post order's characteristic, root node last visit
			}
		}
	}
	delete s;
	return;
}
//in this case
//1.using queue structure, access at under the child node
void WordBST::Iter_Level(WordNode * parm_pNode)
{
	WordNode * cur = 0;
	W_Stack * s = new W_Stack;
	if(parm_pNode){
		s->Push(parm_pNode);
		while(!s->isEmpty()){
			cur = s->First_Pop();	//memory parent node's childnode
			cout<<cur->GetWord()<<"	"<<cur->GetMean()<<endl;
			fout_log<<cur->GetWord()<<"	"<<cur->GetMean()<<endl;
			if(cur->GetLeft())
				s->Push(cur->GetLeft());
			if(cur->GetRight())
				s->Push(cur->GetRight());
		}
	}
	delete s;
}
bool WordBST::Save()
{
	if(fout_word.is_open() == false){
	fout_word.open("memorizing_word.txt", ios::app);
	}
	//if ofstream not opening, open the file out stream
	if(root){
		Save_Pre(root);
		return true;
	}
	else return false;
}
void WordBST::Save_Pre(WordNode * parm_pNode)
{
	if(parm_pNode){
		fout_word<<parm_pNode->GetWord()<<"	"<<parm_pNode->GetMean()<<endl;
		Save_Pre(parm_pNode->GetLeft());
		Save_Pre(parm_pNode->GetRight());
	}
}
//to using post order method
void WordBST::Delete_BST(WordNode * parm_pNode)
{
	if(parm_pNode){
		if(parm_pNode->isDel == true){
		Delete_BST(parm_pNode->GetLeft());
		Delete_BST(parm_pNode->GetRight());
		parm_pNode->SetRight(0);
		parm_pNode->SetLeft(0);
		delete parm_pNode;
		parm_pNode = 0;
		}
	}
}
WordBST::~WordBST()
{
	/* You must fill here */
	if(root) Delete_BST(root);
	if(fout_log) fout_log.close();
	if(fout_word) fout_word.close();
}

#include "AlphabetBST.h"



AlphabetBST::AlphabetBST()
{
	root = '\0';
	WordCnt = 0;
	fout_log.open("log.txt", ios::app);
	//this statement for memorizing file reset
	char ch_arr[] = {'P', 'H', 'X', 'D', 'L', 'T', 'Z', 'B', 'F', 'J', 'N', 'R', 'V', 'Y', 'A', 'C', 'E', 'G', 'I', 'K', 'M', 'O', 'Q', 'S', 'U', 'W'};
	for(int i = 0; i<26; i++){
		AlphabetNode * push_node = new AlphabetNode;
		push_node->SetAlphabet(ch_arr[i]);
		Insert(push_node);
	}
		//when made AlphabetBST, the BST has alphabetnode
}
void AlphabetBST::Insert(AlphabetNode * push_node)
{
	if(push_node == 0) return;
	
	if(root != 0){
		AlphabetNode * ParentNode = root;
		for( ; ; ){
			if(ParentNode->GetAlphabet() > push_node->GetAlphabet()
				&& ParentNode->GetLeft() == 0){
					ParentNode->SetLeft(push_node);
					break;
			}
			else if(ParentNode->GetAlphabet() > push_node->GetAlphabet()){
				ParentNode = ParentNode->GetLeft();
				continue;
			}
			else if(ParentNode->GetAlphabet() < push_node->GetAlphabet()
				&& ParentNode->GetRight() == 0){
					ParentNode->SetRight(push_node);
					break;
			}
			else if(ParentNode->GetAlphabet() < push_node->GetAlphabet()){
				ParentNode = ParentNode->GetRight();
				continue;
			}
		}
	}
	else{
		root = push_node;
	}
}
//searching alphabet, enter that alphabetnode insert WordBST
//Node inserting only this function execute
//in this case
//1. if parameter node has no string, ex) word[0] = '\0' return;
//or parameter node is empty
//2. only insert WordNode in BST
//3. when inserting node, WordCnt++;
//4. searching alphabet is upper, inserting word must be lower
void AlphabetBST::Insert(WordNode *push_node)
{
	if(push_node == 0) return;
	
				//if wordnode push, than counting wordnode
	char alphabet = push_node->GetWord()[0] -32;	//this case is lower alphabet return, than upper case change
	AlphabetNode *target_node = Search(alphabet);
	WordNode *overlab = target_node->GetBST()->Search(push_node->GetWord());
	if(overlab == 0){
	target_node->GetBST()->Insert(push_node);
	WordCnt++;
	}
						//searching alphabet node, insert that alphabet WordBST
}
AlphabetNode * AlphabetBST::Search(char alphabet)
{
	if(root){
		AlphabetNode * parent = root;
		for( ; ; ){
			if(!parent) return 0;	//parameter alphabet not exist in BST
			if(parent->GetAlphabet() > alphabet){
				parent = parent->GetLeft();
				continue;
			}
			else if(parent->GetAlphabet() < alphabet){
				parent = parent->GetRight();
				continue;
			}
			else
				return parent;
		}
	}
	else
		return 0;		//empty BST, failed
}
bool AlphabetBST::Save()
{
	ofstream fout;
	fout.open("memorizing_word.txt");
	fout.close();
	if(root){			//is BST exist, than saving
	Save_Pre(root);
	return true;
	}
	else				//if BST empty, failed
		return false;
}
void AlphabetBST::Save_Pre(AlphabetNode * parm_pNode)
{
	if(parm_pNode){
		parm_pNode->GetBST()->Save();		//pre-ordering save
		Save_Pre(parm_pNode->GetLeft());
		Save_Pre(parm_pNode->GetRight());
	}
}
bool AlphabetBST::Print(char * order)
{
	if(order) strcpy(m_order, order);	//exception order error
	if(WordCnt <= 0) return false;
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
	return true;
}
void AlphabetBST::Print_Pre(AlphabetNode * parm_pNode)
{
	if(parm_pNode){
		cout<<"Alphabet: "<<parm_pNode->GetAlphabet()<<endl;
		fout_log<<"Alphabet: "<<parm_pNode->GetAlphabet()<<endl;
		parm_pNode->GetBST()->Print(m_order);
		Print_Pre(parm_pNode->GetLeft());
		Print_Pre(parm_pNode->GetRight());
	}
}
void AlphabetBST::Print_In(AlphabetNode * parm_pNode)
{
	if(parm_pNode){
		Print_In(parm_pNode->GetLeft());
		cout<<"Alphabet: "<<parm_pNode->GetAlphabet()<<endl;
		fout_log<<"Alphabet: "<<parm_pNode->GetAlphabet()<<endl;
		parm_pNode->GetBST()->Print(m_order);
		Print_In(parm_pNode->GetRight());
	}
}
void AlphabetBST::Print_Post(AlphabetNode * parm_pNode)
{
	if(parm_pNode){
		Print_Post(parm_pNode->GetLeft());
		Print_Post(parm_pNode->GetRight());
		cout<<"Alphabet: "<<parm_pNode->GetAlphabet()<<endl;
		fout_log<<"Alphabet: "<<parm_pNode->GetAlphabet()<<endl;
		parm_pNode->GetBST()->Print(m_order);
	}
}
void AlphabetBST::Iter_Pre(AlphabetNode * parm_pNode)
{
	A_Stack *s = new A_Stack;
	AlphabetNode *cur = NULL;
	AlphabetNode *LeftChild = NULL;
	AlphabetNode *RightChild = NULL;
	s->Push(parm_pNode);
	while(1){
		if(s->isEmpty() == true){
			break;
		}
		else{
			cur = s->Pop();
			if(cur != NULL){
				cout<<"Alphabet: "<<cur->GetAlphabet()<<endl;
				fout_log<<"Alphabet: "<<cur->GetAlphabet()<<endl;
				cur->GetBST()->Print(m_order);
				
				LeftChild = cur->GetLeft();
				RightChild = cur->GetRight();
				
				if(RightChild != NULL)
					s->Push(RightChild);
				if(LeftChild != NULL)
					s->Push(LeftChild);
			}
		}
	}

	delete s;
}
void AlphabetBST::Iter_In(AlphabetNode * parm_pNode)
{
	A_Stack *s = new A_Stack;
	AlphabetNode *stack_node = NULL;
	AlphabetNode *cur = parm_pNode;
	WordBST *node_bst = NULL;
	while(1){
		for( ; cur != 0; cur = cur->GetLeft()){
			s->Push(cur);
		}
		
		if(s->isEmpty() == true){
			break;
		}
		else{
			stack_node = s->Pop();
			if(stack_node != NULL){
			cout<<"Alpahbet: "<<stack_node->GetAlphabet()<<endl;
			fout_log<<"Alpahbet: "<<stack_node->GetAlphabet()<<endl;
			node_bst = stack_node->GetBST();
			node_bst->Print(m_order);
			stack_node = stack_node->GetRight();
			cur = stack_node;
			}
		}
	}
	delete s;
}
void AlphabetBST::Iter_Post(AlphabetNode * parm_pNode)
{
	AlphabetNode * visit_node = 0;
	AlphabetNode * cur = root;
	A_Stack * s = new A_Stack;
	if(root){
		
		while(cur || !s->isEmpty()){
			if(cur){
				s->Push(cur);
				cur = cur->GetLeft();
			}
			else{
				cur = s->Pop();
				while(cur->GetRight() == NULL || cur->GetRight() == visit_node){
				cout<<"Alpahbet: "<<cur->GetAlphabet()<<endl;
				fout_log<<"Alpahbet: "<<cur->GetAlphabet()<<endl;
					cur->GetBST()->Print(m_order);
					visit_node = cur;
					if(s->isEmpty()){
						delete s;
						return;
					}
					cur = s->Pop();
				}
				if(cur != visit_node)
					s->Push(cur);
				visit_node = cur;
				cur = cur->GetRight();
			}
		}
	}
	delete s;
	return;
}
void AlphabetBST::Iter_Level(AlphabetNode * parm_pNode)
{
	A_Stack * s = new A_Stack;
	AlphabetNode * cur = 0;
	if(parm_pNode){
		s->Push(parm_pNode);
		while(!s->isEmpty()){	//if A_Stack empty, return true else return false;
			
			cur = s->First_Pop();
			cout<<"Alphabet: "<<cur->GetAlphabet()<<endl;
			fout_log<<"Alphabet: "<<cur->GetAlphabet()<<endl;
			cur->GetBST()->Print(m_order);
			if(cur->GetLeft())
				s->Push(cur->GetLeft());
			if(cur->GetRight())
				s->Push(cur->GetRight());
		}
	}
	delete s;
}
void AlphabetBST::Delete_BST(AlphabetNode *parm_pNode)
{
	if(parm_pNode){		//recursive traversal method to using remove node
		Delete_BST(parm_pNode->GetLeft());
		Delete_BST(parm_pNode->GetRight());
		delete parm_pNode;
		parm_pNode = NULL;
	}
}

int AlphabetBST::GetWordCnt()
{
	return WordCnt;
}
void AlphabetBST::SetWordCnt(int count)
{
	WordCnt = count;
}
AlphabetBST::~AlphabetBST()
{
	/* You must fill here */
	if(root) Delete_BST(root);
}

#include "AlphabetBST.h"	//include header


AlphabetBST::AlphabetBST()//constructor
{
	/*setting null*/
	root = '\0';
	WordCnt = 0;
	/*make alphabet tree*/
	char input_alp[26] = { 'P', 'H', 'X', 'D', 'L', 'T', 'Z', 'B', 'F', 'J', 'N', 'R', 'V', 'Y', 'A', 'C', 'E', 'G', 'I', 'K', 'M', 'O', 'Q', 'S', 'U', 'W' };
	for (int i = 0; i < 26; i++)
	{
		AlphabetNode* pNew = new AlphabetNode;	//make node by dynamic allocation
		pNew->SetAlphabet(input_alp[i]);
		Insert(pNew);	//insert node to bst
	}
}

AlphabetBST::~AlphabetBST()	//destructor
{/////////////////using I_POST order///////////////////////
	//////////////////////delete all node in bst//////////////////
	if (root == NULL)	//case. bst is empty
		return;

	AlphabetNode* pCur = root;	//walker
	stack_alp s;	//declare stack

	while (1)	//start traversal
	{
		while (pCur != NULL)	//push point until pCur is NULL
		{
			if (pCur->GetRight() != NULL)
				s.push(pCur->GetRight());	//push right child
			s.push(pCur);					//push pCur
			pCur = pCur->GetLeft();			//move to left child
		}
		pCur = s.top();		//get stack's top
		s.pop();			//pop in stack

		if (pCur->GetRight() != NULL && pCur->GetRight() == s.top())	//push point 2
		{
			s.pop();		//pop in stack
			s.push(pCur);	//push pCur
			pCur = pCur->GetRight();	//move to right child
		}
		else
		{
			delete pCur;	////delete node !
			pCur = NULL;	//initialize
		}

		if (s.empty() == true)	//stop point
			break;	//break statement
	}
	return;	//exit func
	
}

void			AlphabetBST::Insert(AlphabetNode * node)   // Insert alphabet to bst
{
	ofstream fout("log.txt", ios::app);		//make FO stream , accumulate save
	AlphabetNode* pCur = root;		//walker
	AlphabetNode* pPre = root;		//prev walker

	if (root == NULL)	//case bst is empty
	{
		root = node;	//set root
		fout.close();	//close file stream
		return;			//exit func
	}
	/*SEARCH*/
	while (1)//search area
	{
		if (pCur == NULL)	//stop point
			break;

		pPre = pCur;		//move pPre

		if (pCur->GetAlphabet() > node->GetAlphabet()) {	//compare ASCII code
			pCur = pCur->GetLeft();		//move to left child
		}
		else if (pCur->GetAlphabet() < node->GetAlphabet()) {
			pCur = pCur->GetRight();	//move to right child
		}
		else {////if(pCur==node);;;stop point
			fout.close();//close stream
			return;//exit func
		}
	}
	if (pPre->GetAlphabet() == node->GetAlphabet())	//exception (alread exist)
	{
		fout.close();//close stream
		return;		 //exit func
	}

	/*INSERT*/
	if (pPre->GetAlphabet() > node->GetAlphabet())
		pPre->SetLeft(node);
	else
		pPre->SetRight(node);

}

bool AlphabetBST::Print(const char * order)	//Print func
{
	ofstream fout("log.txt", ios::app);	//declare FO stream 
	if (WordCnt == 0)	//exception : bst haven't word
	{
		fout.close();	//exit func
		return false;
	}
		
	/*Switch order*/
	if (strcmp("R_PRE", order) == 0) {
		fout << "======== PRINT ========" << endl;
		R_PRE(root);
	}
	else if (strcmp("I_PRE", order) == 0) {
		fout << "======== PRINT ========" << endl;
		I_PRE();
	}
	else if (strcmp("R_IN", order) == 0) {
		fout << "======== PRINT ========" << endl;
		R_IN(root);
	}
	else if (strcmp("I_IN", order) == 0) {
		fout << "======== PRINT ========" << endl;
		I_IN();
	}
	else if (strcmp("R_POST", order) == 0) {
		fout << "======== PRINT ========" << endl;
		R_POST(root);
	}
	else if (strcmp("I_POST", order) == 0) {
		fout << "======== PRINT ========" << endl;
		I_POST();

	}
	else if (strcmp("I_LEVEL", order) == 0){
		fout << "======== PRINT ========" << endl;
		I_LEVEL();
	}
	else {//exception case
		///order is not corrected
		fout.close();	//exit func
		return false;
	}
	fout << "=======================" << endl << endl;
	fout.close();	//exit func 
	return true;	//success point
}

AlphabetNode *	AlphabetBST::Search(char alpabet)	//search corrected alphabet
{
	AlphabetNode* pCur = root;	//walker

	if (root == NULL)//exception case. bst empty
		return 0;	//exit func

	while (1)	//roop
	{
		if (pCur == NULL)	//stop point
			return 0;

		if (pCur->GetAlphabet() > alpabet)	//move point 1
			pCur = pCur->GetLeft();
		else if (pCur->GetAlphabet() < alpabet)	//move point 2
			pCur = pCur->GetRight();
		else		//search success
			return pCur;	//return searched node
	}
}

bool AlphabetBST::Save()
{		//using i_preorder
	ofstream fnull("memorizing_word.txt", ios::trunc);	//declare FO stream and remove information in text file
	fnull.close();	//close stream

	AlphabetNode* pCur = root;	//walker
	stack_alp s;				//declare stack

	s.push(pCur);				//push to stack
	while (1)
	{
		if (s.empty() == true)//stop point
			return true;		//exit func

		pCur = s.top();		//point stack's top 
		if (Visit(pCur) == false)	//visit node to save
			return false;

		s.pop();	//pop stack

		if (pCur->GetRight() != NULL)	//push point
			s.push(pCur->GetRight());
		if (pCur->GetLeft() != NULL)
			s.push(pCur->GetLeft());
	}
}



void AlphabetBST::wordcnt_up()
{///////////word count up
	WordCnt++;
}

void AlphabetBST::wordcnt_down()
{///////////word count down
	WordCnt--;
}

int AlphabetBST::getWordCnt()
{///////////return word count value
	return WordCnt;
}

void AlphabetBST::Visit(AlphabetNode* pCur, const char* order)//for print
{
	pCur->GetBST()->Print(order);	//transmit order to word bst
}

bool AlphabetBST::Visit(AlphabetNode* pCur)//for save
{
	return pCur->GetBST()->Save();	//call word bst's save
}

void AlphabetBST::R_PRE(AlphabetNode* pCur)
{////Reculsive Preorder////
	if (pCur != NULL)
	{
		const char* order="R_PRE";
		Visit(pCur, order);			//visit and transmit order
		R_PRE(pCur->GetLeft());		//call function self
		R_PRE(pCur->GetRight());	//call function self
	}
}

void AlphabetBST::I_PRE()
{////Iterative Preorder////
	AlphabetNode* pCur = root;	//walker
	stack_alp s;				//using stack

	s.push(pCur);				//push walker
	const char* order="I_PRE";	//save order
	while (1)		//roop
	{
		if (s.empty() == true)	//stop point
			return;

		pCur = s.top();			//get stack's top
		Visit(pCur, order);		//visit node
		s.pop();				//pop node

		if (pCur->GetRight() != NULL)	//move point
			s.push(pCur->GetRight());
		if (pCur->GetLeft() != NULL)	//next move point
			s.push(pCur->GetLeft());
	}
}

void AlphabetBST::R_IN(AlphabetNode* pCur)	//parameter is walker
{////Reculsive In order////
	if (pCur != NULL)//stop point 
	{
		const char* order="R_IN";	//save order
		R_IN(pCur->GetLeft());		//insert left child node to func
		Visit(pCur, order);			//visit and transmit order
		R_IN(pCur->GetRight());		//insert right child node to func
	}
}

void AlphabetBST::I_IN()
{////Iterative In order////
	AlphabetNode* pCur = root;	//walker
	stack_alp s;				//declare stack
	const char* order="I_IN";	//save order
	while (1)
	{
		while (pCur != NULL)	//push point
		{
			s.push(pCur);
			pCur = pCur->GetLeft();
		}

		if (s.empty() == true)	//stop point
			return;				//exit func

		pCur = s.top();			//get stack's top node
		s.pop();				//pop
		Visit(pCur,order);		//visit node and transmit order
		pCur = pCur->GetRight();//move point
	}
}

void AlphabetBST::R_POST(AlphabetNode* pCur)
{////Reculsive Post order////
	if (pCur != NULL)
	{
		const char* order="R_POST";	//save order
		R_POST(pCur->GetLeft());	//reculsive left child
		R_POST(pCur->GetRight());	//reculsive right child
		Visit(pCur,order);			//visit node and transmit order
	}
}

void AlphabetBST::I_POST()
{////Iterative Post order////
	AlphabetNode* pCur = root;	//walker
	stack_alp s;				//declare stack
	const char* order="I_POST";	//save order

	while (1)
	{
		while (pCur != NULL)	//push point
		{
			if (pCur->GetRight() != NULL)
				s.push(pCur->GetRight());
			s.push(pCur);
			pCur = pCur->GetLeft();	//move point
		}
		pCur = s.top();		//get top
		s.pop();			//pop

		if (pCur->GetRight() != NULL && pCur->GetRight() == s.top())	//pick
		{
			s.pop();					//pop
			s.push(pCur);				//push
			pCur = pCur->GetRight();	//move to right
		}
		else
		{			//visit point
			Visit(pCur,order);	//visit node and transmit order
			pCur = NULL;		//set null
		}

		if (s.empty() == true)	//stop point
			break;
	}
	return;	//exit func
}

void AlphabetBST::I_LEVEL()
{////Iterative Level order////
	AlphabetNode* pCur = root;	//walker
	queue_alp q;				//declare queue
	const char* order="I_LEVEL";//save order
	while (pCur != NULL)	//stop point
	{
		Visit(pCur,order);	//visit node and transmit order

		if (pCur->GetLeft())	//if left child is exist
			q.push(pCur->GetLeft());	//push left child
		if (pCur->GetRight())	//if right child is exist
			q.push(pCur->GetRight());	//push right child
		if (q.empty() == true)	//stop point 
			return;

		pCur = q.front();	//get front
		q.pop();			//pop
	}
}


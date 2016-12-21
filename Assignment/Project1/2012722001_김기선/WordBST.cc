#include "WordBST.h"

WordBST::WordBST()	//constructor//
{
	root = '\0';	//first set
	leaf_WordCnt = 0;
}

WordBST::~WordBST()	//destructor//
{	//using iterative postorder
	//////////////////////delete all node in bst//////////////////
	if (root == NULL)	//exception case
		return;

	WordNode* pCur = root;	//walker
	stack_word s;			//declare stack

	while (1)	//start traversal
	{	
		while (pCur != NULL)		//push point until pCur is NULL
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

void		WordBST::Insert(WordNode * node)			// LOAD, MOVE
{
	WordNode* pCur = root;	//walker
	WordNode* pPre = root;	//prev of walker

	if (root == NULL)	//first insert
	{
		root = node;	//root set
		leaf_WordCnt++;	//word cnt up
		return;			//exit func
	}

	while (1)//search area
	{
		if (pCur == NULL)	//stop point
			break;

		pPre = pCur;	//preCur move
		/*search area*/
		if (strcmp(pCur->GetWord(), node->GetWord()) > 0) {
			pCur = pCur->GetLeft();
		}
		else if (strcmp(pCur->GetWord(), node->GetWord()) < 0) {
			pCur = pCur->GetRight();
		}
		else//same node exist already
			return;
	}
	if (strcmp(pPre->GetWord(), node->GetWord()) == 0)//same data exist already
		return;

	//insert part
	if (strcmp(pPre->GetWord(), node->GetWord()) > 0)//Pre set Next
		pPre->SetLeft(node);
	else
		pPre->SetRight(node);

	leaf_WordCnt++;//count up
}

WordNode *	WordBST::Delete(char * word)	//return node that will move to memorized
{
	if (root == NULL)   // bst haven't node
		return 0;

	WordNode* pFlag = root;         //applicable node
	WordNode* pParent_Flag = NULL;   //flag's parent node

									 /*search node*/
	while (strcmp(pFlag->GetWord(), word) != 0)      //found flag
	{
		pParent_Flag = pFlag;   //save parent

		if (strcmp(pFlag->GetWord(), word) > 0)      //move flag
			pFlag = pFlag->GetLeft();
		else
			pFlag = pFlag->GetRight();
	}

	if (pFlag == NULL)   //not exist
		return 0;
	/*delete*/
	/////////case 1. flag node is leaf/////////
	if (pFlag->GetLeft() == NULL && pFlag->GetRight() == NULL)
	{
		if (pParent_Flag == NULL)   //case (flag is root)
			root = NULL;
		else if (pParent_Flag->GetLeft() == pFlag)   //parent's next set NULL
			pParent_Flag->SetLeft(NULL);
		else
			pParent_Flag->SetRight(NULL);

		leaf_WordCnt--;
		return pFlag;   //return flag 
	}

	/////////case 2. flag node has only L-child/////////
	if (pFlag->GetLeft() != NULL && pFlag->GetRight() == NULL)
	{
		if (pParent_Flag == NULL)   //case (flag is root)
			root = pFlag->GetLeft();
		else if (pParent_Flag->GetLeft() == pFlag)   //parent's next set 
			pParent_Flag->SetLeft(pFlag->GetLeft());
		else
			pParent_Flag->SetRight(pFlag->GetLeft());

		return pFlag;   //return flag 
	}

	/////////case 3. flag node has only R-child/////////
	if (pFlag->GetLeft() == NULL && pFlag->GetRight() != NULL)
	{
		if (pParent_Flag == NULL)   //case (flag is root)
			root = pFlag->GetRight();
		else if (pParent_Flag->GetLeft() == pFlag)   //parent's next set 
			pParent_Flag->SetLeft(pFlag->GetRight());
		else
			pParent_Flag->SetRight(pFlag->GetRight());

		return pFlag;   //return flag 
	}
	/////////clse 4. flag node has R-child & L-child/////////
	WordNode* pCur = pFlag->GetRight()->GetLeft();
	WordNode* pPrev = pFlag->GetRight();   //will be smallest node
	WordNode* pPrevPrev = pFlag;
	WordNode* pTemp = new WordNode;

	/*find smallest node in right sub-tree*/
	while (pCur != NULL)   //must be leaf
	{
		pPrevPrev = pPrev;   //move each
		pPrev = pCur;
		pCur = pCur->GetLeft();
	}
	pTemp->SetWord(pFlag->GetWord());//Set return node's data
	pTemp->SetMean(pFlag->GetMean());
	pFlag->SetWord(pPrev->GetWord());//Set replaced node's data
	pFlag->SetMean(pPrev->GetMean());
	if (pPrevPrev == pFlag)			 //Set replaced area
		pPrevPrev->SetRight(pPrev->GetRight());
	else
		pPrevPrev->SetLeft(pPrev->GetRight());
	/*return flag*/
	return pTemp;
}

bool		WordBST::Print(const char * order)							// PRINT
{
	if (leaf_WordCnt == 0)	//exception : wordbst is empty
	{
		return false;
	}
	/*Switch*/
	if (strcmp("R_PRE", order) == 0) {
		R_PRE(root);
	}
	else if (strcmp("I_PRE", order) == 0) {
		I_PRE();
	}
	else if (strcmp("R_IN", order) == 0) {
		R_IN(root);
	}
	else if (strcmp("I_IN", order) == 0) {
		I_IN();
	}
	else if (strcmp("R_POST", order) == 0) {
		R_POST(root);
	}
	else if (strcmp("I_POST", order) == 0) {
		I_POST();
	}
	else if (strcmp("I_LEVEL", order) == 0)
	{
		I_LEVEL();
	}
	else//order is not corrected
		return false;

	return true;
}

WordNode *	WordBST::Search(char * word)	//search node 
{
	WordNode* pCur = root;	//walker

	while (pCur != NULL)
	{
		if (strcmp(pCur->GetWord(), word) > 0)	//if smaller data
			pCur = pCur->GetLeft();				//move left
		else if (strcmp(pCur->GetWord(), word) < 0)	//if bigger data
			pCur = pCur->GetRight();			//move right
		else //search success
			return pCur;
	}

	return 0;	//not found
}

bool WordBST::Save()	//Save bst
{	///////////////using I_PREORDER
	if (root == NULL)	//exception case. empty bst
		return true;

	ofstream fout("memorizing_word.txt", ios_base::app);	//declare FOstream
	WordNode* pCur = root;	//walker
	stack_word s;			//declare stack

	s.push(pCur);	//push root
	while (1)
	{
		if (s.empty() == true)	//stop point
		{
			fout.close();	//exit func
			return true;
		}
		pCur = s.top();		//get top node
		fout << pCur->GetWord() << "\t" << pCur->GetMean() << endl; ;	//file out data to text file
	
		s.pop();	//pop

		if (pCur->GetRight() != NULL)	//push point
			s.push(pCur->GetRight());
		if (pCur->GetLeft() != NULL)
			s.push(pCur->GetLeft());
	}
}

void WordBST::Visit(WordNode* pCur)	//VISIT
{
	ofstream fout("log.txt", ios::app);		//declare FOstream
	fout << pCur->GetWord() << "\t" << pCur->GetMean() << endl;	//file out data by 'fout' stream
	fout.close();	//close stream
}

void WordBST::R_PRE(WordNode* pCur)	
{////Reculsive Preorder////
	if (pCur != NULL)
	{
		Visit(pCur);			//visit and transmit order
		R_PRE(pCur->GetLeft()); //call function self
		R_PRE(pCur->GetRight());//call function self
	}
}

void WordBST::I_PRE()
{////Iterative Preorder////
	WordNode* pCur = root;	//walker
	stack_word s;				//using stack

	if (root == NULL)
		return;

	s.push(pCur);				//push walker
	while (1)
	{
		if (s.empty() == true)	//stop point
			break;

		pCur = s.top();			//get stack's top
		Visit(pCur);			//visit node
		s.pop();				//pop node

		if (pCur->GetRight() != NULL)	//move point
			s.push(pCur->GetRight());
		if (pCur->GetLeft() != NULL)	//next move point
			s.push(pCur->GetLeft());
	}
	return;
}

void WordBST::R_IN(WordNode* pCur)	//parameter is walker
{////Reculsive In order////
	if (pCur != NULL)//stop point
	{
		R_IN(pCur->GetLeft());		//insert left child node to func
		Visit(pCur);				//visit
		R_IN(pCur->GetRight());		//insert right child node to func
	}
}

void WordBST::I_IN()
{////Iterative In order////
	WordNode* pCur = root;	//walker
	stack_word s;			//declare stack

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
		Visit(pCur);			//visit node and transmit order
		pCur = pCur->GetRight();//move point
	}
}

void WordBST::R_POST(WordNode* pCur)
{////Reculsive Post order////
	if (pCur != NULL)
	{
		R_POST(pCur->GetLeft());	//reculsive left child
		R_POST(pCur->GetRight());	//reculsive right child
		Visit(pCur);				//visit node
	}
}

void WordBST::I_POST()
{////Iterative Post order////
	WordNode* pCur = root;	//walker
	stack_word s;			//declare stack

	if (root == NULL)
		return;

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
		else			//visit point
		{
			Visit(pCur);	//visit node and transmit order
			pCur = NULL;	//set null
		}

		if (s.empty() == true)	//stop point
			break;
	}
	return;	//exit func
}
void WordBST::I_LEVEL()
{////Iterative Level order////
	WordNode* pCur = root;	//walker
	queue_word q;			//declare queue
	while (pCur != NULL)	//stop point
	{
		Visit(pCur);	//visit node and transmit order

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


#include "AlphabetBST.h"



AlphabetBST::AlphabetBST()
{
	root = '\0';
	Sroot = '\0';
	WordCnt = 0;
};


AlphabetBST::~AlphabetBST()
{

};
void AlphabetBST::Insert(AlphabetNode* node)	// run
{
	AlphabetNode* temp = root; //declare alphabetnode temp and set as root
	if (temp == '\0') // root setting
	{
		root = node; //root is node
		return; //return
	}
	while (1)
	{
		if (node->GetAlphabet() < temp->GetAlphabet()) //if node getalphabet is less then temp getalphabet
		{
			if (temp->GetLeft() == '\0') //if temp getleft is null
			{
				temp->SetLeft(node); //temp setleft is node
				break;
			}
			temp = temp->GetLeft(); //temp is temp getleft
			continue;
		}
		else
		{
			if (temp->GetRight() == '\0') //if temp getright is null
			{
				temp->SetRight(node); //temp setright is node
				break; //break
			}
			temp = temp->GetRight(); //temp is temp getright
			continue; 
		}
	}
};
bool	AlphabetBST::Print(char* order)						// PRINT
{
	int nodeis = 0; //declare nodeis and set as 0
	char how[7][8] = { "R_PRE", "I_PRE", "R_IN", "I_IN", "R_POST", "I_POST", "I_LEVEL" };
	ofstream logfile; //declare logfile
	logfile.open("log.txt", ios::app); //open log.txt
	APreorder(root); //apreorder(root)
	AlphabetNode* al = Sroot; //declare alphabetnode al and set as sroot
	while (al) //confornt sroot link if alphabet node wordbst has node then nodeis is 1 gka
	{
		if (al->GetBST()->root != '\0')
			nodeis = 1;
		al = al->GetSNext();
	}
	if (nodeis == 0) //  if there is no node
	{
		logfile << "======== PRINT ========" << endl;
		logfile << "700" << endl;
		logfile << "=======================" << endl;
		logfile.close(); //close logfile

		cout << "======== PRINT ========" << endl;
		cout << "700" << endl;
		cout << "=======================" << endl;
		return false;
	}
	Sroot = '\0';

	if (strcmp(order, "R_PRE") == 0)// R_prev
	{
		cout << "========PRINT========" << endl;
		logfile << "========PRINT========" << endl;
		Preorder();
		cout << "=====================" << endl;
		logfile<< "=====================" << endl;
		logfile << endl;
		cout << endl;
		return true;
	}
	if (strcmp(order, "I_PRE") == 0)// I_PRE
	{
		cout << "========PRINT========" << endl;
		logfile << "========PRINT========" << endl;
		I_PRE();
		cout << "=====================" << endl;
		logfile << "=====================" << endl;
		logfile << endl; 
		cout << endl;
		return true;
	}
	if (strcmp(order,"R_IN") == 0)// R_IN
	{
		cout << "========PRINT========" << endl;
		logfile << "========PRINT========" << endl;
		Inorder();
		cout << "=====================" << endl;
		logfile << "=====================" << endl;
		logfile << endl;
		cout << endl;
		return true;
	}
	if (strcmp(order, "I_IN") == 0)// I_IN
	{
		cout << "========PRINT========" << endl;
		logfile << "========PRINT========" << endl;
		I_IN();
		cout << "=====================" << endl;
		logfile << "=====================" << endl;
		logfile << endl;
		cout << endl;
		return true;
	}
	if (strcmp(order, "R_POST") == 0)// R_POST
	{
		cout << "========PRINT========" << endl;
		logfile << "========PRINT========" << endl;
		Postorder();
		cout << "=====================" << endl;
		logfile << "=====================" << endl;
		logfile << endl;
		cout << endl;
		return true;
	}
	if (strcmp(order, "I_POST") == 0)// I_POST
	{
		cout << "========PRINT========" << endl;
		logfile << "========PRINT========" << endl;
		I_POST();
		cout << "=====================" << endl;
		logfile << "=====================" << endl;
		logfile << endl;
		cout << endl;
		return true;
	}
	if (strcmp(order, "I_LEVEL") == 0)// I_LEVEL
	{
		cout << "========PRINT========" << endl;
		logfile << "========PRINT========" << endl;
		I_LEVEL();
		cout << "=====================" << endl;
		logfile << "=====================" << endl;
		logfile << endl;
		cout << endl;
		return true;
	}
	logfile.close();
	return true;
};

AlphabetNode*	AlphabetBST::Search(char alpabet)			
{
	AlphabetNode* temp = root; //declare alphabetnode temp and set as root
	char a = alpabet; //declare a and set as alpabet
	if (alpabet>96 && alpabet<123) //if alpabet is bigger then 96 and smaller then 123
		a = alpabet - 32; //a is alpabet -32
	while (1)
	{
		if (a < temp->GetAlphabet()) //if a is smaller then temp getalphabet
		{
			temp = temp->GetLeft(); continue; //temp is temp getleft then continue
		}
		else if (a > temp->GetAlphabet()) //if a is bigger then getalphabet
		{
			temp = temp->GetRight(); continue; //temp is temp getright then continue
		}
		else
		{
			return temp; //return temp
		}
	}
};
void AlphabetBST::Saveroot(AlphabetNode* node)
{
	AlphabetNode* temp = Sroot; //declare alphabetnode temp and set as sroot
	if (Sroot == '\0') //if sroot is null
	{
		Sroot = node; //sroot is node
		Sroot->SetSNext('\0'); //sroot setsnext is null
		return;
	}
	while (1)
	{
		if (temp->GetSNext() == '\0') //if temp getsnext is null
			break; //break
		temp = temp->GetSNext(); //temp is temp getsnext
	}
	temp->SetSNext(node); //temp setsnext is node
	node->SetSNext('\0'); //node setsnext is null
}
void AlphabetBST::APreorder()// Driver of aPreorder
{
	APreorder(root);
};
void AlphabetBST::APreorder(AlphabetNode* currentNode)// Workhorse of aPreorder
{
	if (currentNode)// if currentNode's value is '\0', break this function
	{
		Saveroot(currentNode);
		APreorder(currentNode->GetLeft()); // activate aPreorder function by using currentNode's GetLeft(reculsivly activate)
		APreorder(currentNode->GetRight()); // activate aPreorder function by using currentNode's GetRight(reculsivly activate)
	}
};

bool	AlphabetBST::Save()							// SAVE 
{
	ofstream bstfile; //declare bstfile
	bstfile.open("memorizing_word.txt"); // open memorizing_word.txt
	bstfile.close(); //close bstfile
	if (bstfile.fail()) //if fail
		return false; //return false
	
	AlphabetNode* temp = root;
	if (temp == '\0')
	{
		bstfile.close();
		return false;
	}
	APreorder(temp); //apreorder temp
	temp = Sroot; //temp is sroot
	if (temp == '\0')
	{
		return false;
	}
	while (1)
	{
		if (temp == '\0') //if temp is null
			break; //break
		temp->GetBST()->Save(); //temp getbst is save
		temp = temp->GetSNext(); //temp is temp getsnext
	}
	return true;
};
void AlphabetBST::PlusWC()
{
	WordCnt++;
	return;
}
void AlphabetBST::Preorder()
{
	Preorder(root); //bring root
}
void AlphabetBST::Preorder(AlphabetNode* node)
{
	if (node)
	{
		node->GetBST()->Print("R_PRE");
		Preorder(node->GetLeft());// activate Preorder function by using currentNode's GetLeft(reculsivly activate)
		Preorder(node->GetRight());  // activate Preorder function by using currentNode's GetRight(reculsivly activate)
	}
}
void AlphabetBST::Inorder()
{
	Inorder(root); //bring root
}
void AlphabetBST::Inorder(AlphabetNode* node)
{
	
	if (node)
	{
		Inorder(node->GetLeft()); // activate inorder function by using currentNode's leftChild(reculsivly activate)
		node->GetBST()->Print("R_IN");
		Inorder(node->GetRight()); // activate inorder function by using currentNode's rightChild(reculsivly activate)
	}
}
void AlphabetBST::Postorder()
{
	Postorder(root); //bring root
}
void AlphabetBST::Postorder(AlphabetNode* node)
{
	if (node)
	{
		Postorder(node->GetLeft()); // activate Postorder function by using currentNode's GetLeft(reculsivly activate)
		Postorder(node->GetRight()); // activate Postorder function by using currentNode's GetRight(reculsivly activate)
		node->GetBST()->Print("R_POST");
	}
}

void	AlphabetBST::I_POST()
{
	Stack2 s;
	AlphabetNode *currentNode, *prevNode, *root1 = root;
	prevNode = '\0';  //prevnode is null
	s.Push(root1); //push root1

	while (!s.IsEmpty())  //until isempty
	{
		currentNode = s.Top(); //currentnode is top
		if ((prevNode == '\0') || (prevNode->GetLeft() == currentNode) || (prevNode->GetRight() == currentNode)) { //if prevnode is null or prevnode getleft is same as currentnode or prevnode getright is same as currentnode
			if (currentNode->GetLeft() != '\0')  //if currentnode getleft is not null
				s.Push(currentNode->GetLeft()); //push currentnode getleft
			else if (currentNode->GetRight() != '\0') //if currentnode getright is not null
				s.Push(currentNode->GetRight()); //push currentnode getright
			else
			{
				currentNode->GetBST()->Print("I_POST");
				s.Pop();
			}
		}
		else if (prevNode == currentNode->GetLeft())
		{
			if (currentNode->GetRight() != '\0')  //if currentnode getright is not null
				s.Push(currentNode->GetRight());
			else
			{
				currentNode->GetBST()->Print("I_POST");
				s.Pop();
			}
		}
		else if (prevNode == currentNode->GetRight()) //if prevnode is same as currentnode getright
		{
			currentNode->GetBST()->Print("I_POST");
			s.Pop();
		}
		prevNode = currentNode;
	}
}
void	AlphabetBST::I_LEVEL()
{
	Queue3 q; //declare queue q
	AlphabetNode *currentNode = root; //currentNode is root
	while (currentNode) { //while currentNode
		currentNode->GetBST()->Print("I_LEVEL");
		if (currentNode->GetLeft())
			q.Push(currentNode->GetLeft()); //if currentNode leftChild q.push currentNode GetLeft
		if (currentNode->GetRight())
			q.Push(currentNode->GetRight()); //if currentNode rightChild q.push currentNode GetRight
		if (q.empty())
			return; //if q.empty return
		currentNode = q.front(); //currentNode is q.front
		q.Pop(); //bring q.pop
	}
}
void	AlphabetBST::I_IN()
{
	Stack2 *s = new Stack2; //declare stack  s
	AlphabetNode *currentNode = root; //currentNode is root
	while (1) //while 1
	{
		while (currentNode) { //while(currentNode)
			s->Push(currentNode); //s.push currentNode
			currentNode = currentNode->GetLeft();
		}
		if (s->IsEmpty())
			return; //if s.empty return
		currentNode = s->Top(); //currentNode is s.top
		s->Pop(); //bring s.pop
		currentNode->GetBST()->Print("I_IN");
		currentNode = currentNode->GetRight();//currentNode is currentNode GetRight
	}
}
void	AlphabetBST::I_PRE()
{
	Stack2 s; //declare stack TreeNode template s
	AlphabetNode *currentNode = root; //currentNode is root
	while (1) //while 1
	{
		while (currentNode) { //while(currentNode)
			currentNode->GetBST()->Print("I_PRE");
			s.Push(currentNode); //s.push currentNode
			currentNode = currentNode->GetLeft();
		}
		if (s.IsEmpty())
			return; //if s.empty return
		currentNode = s.Top(); //currentNode is s.top
		s.Pop(); //bring s.pop

		currentNode = currentNode->GetRight();//currentNode is currentNode GetRight
	}
}


Stack2::Stack2()   //Stack
{
	pHead = 0;   //phead is 0
}

Stack2::~Stack2()   //Stack
{
	AlphabetNode* del;  //declare del

	while (pHead != '\0')   //until phead reach null
	{
		del = pHead;   //del is phead
		del->SetNext('\0');     //del setnext is null
		pHead = pHead->GetNext();   //phead is phead getnext set phead as next
		delete del;    //delete del memory relise
	}
	pHead = '\0';  //save null into phead
}

bool Stack2::IsEmpty()   //IsEmpty
{
	if (pHead == 0)   //if phead is 0
		return true;   //return true
	else   //if not 0
		return false;   //return false
}


bool Stack2::Push(AlphabetNode* pNode)   //Push
{
	if (pHead == 0)    //if phead is 0 meaning nothing inside
	{
		pHead = pNode;  //set phead as pnode
	}
	else  
	{
		pNode->SetNext(pHead);   //pnode setnext is phead
		pHead = pNode;  //phead is pnode
	}

	return true; //return true
}

AlphabetNode* Stack2::Pop()   //Pop
{
	AlphabetNode* temp;   //declare alphabetnode temp
	if (pHead == '\0')    //if phead is null
	{
		cout << "no node" << endl << endl;   //print
		return 0;   //return 0
	}
	else   
	{
		temp = pHead;   //temp is phead
		pHead = pHead->GetNext(); //phead is phead getnext2
		return temp;    //retuen temp
	}
}

AlphabetNode * Stack2::Top()
{
	return pHead;
}


Queue3::Queue3()
{
	pHead = 0;
	pTail = 0;
};


Queue3::~Queue3()
{
	AlphabetNode* del; //declare del

	while (pHead != '\0') //until phead is null
	{
		del = pHead;  //del is phead
		del->SetNext('\0'); //del setnext is null
		pHead = pHead->GetNext(); //phead is phead getnext
		delete del; //delete del
	}
	pHead = '\0'; //phead is null
};

void Queue3::Push(AlphabetNode* node)
{
	if (pHead == '\0') //if phead is null
	{
		pHead = node; //phead is node
		pTail = node; //ptail is node
		pTail->SetNext('\0'); //ptail setnext is null
	}
	else
	{
		pTail->SetNext(node); //ptail setnext is node
		pTail = node; //ptail is node
		pTail->SetNext('\0'); //ptail setnext is null
	}
}

AlphabetNode* Queue3::Pop()
{
	AlphabetNode* temp = pHead;
	if (temp == 0) //if temp is 0 return phead
		return pHead;
	else
	{
		pHead = temp->GetNext(); //phead is temp getnext
		temp->SetNext('\0'); //temp setnext is null
		return temp;
	}
}

AlphabetNode * Queue3::front()
{
	return pHead;
}


bool Queue3::empty()   
{
	if (pHead == 0)   //if hpead is 0 then return true else false
		return true;
	return false;
}
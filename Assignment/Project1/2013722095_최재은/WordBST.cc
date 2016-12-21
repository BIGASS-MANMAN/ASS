#include "WordBST.h"


WordBST::WordBST()
{
	root = '\0';
	Sroot = '\0';
}
WordBST::~WordBST()	
{
	if (root == '\0')
		return;
	WPostorder(root); // delete all nodes in WordBST
}

void WordBST::WPostorder()
{
	WPostorder(root); //recall root
}; // destructor
void WordBST::WPostorder(WordNode* currentNode)
{
	if (currentNode)// if currentNode's value is '\0', break this function
	{
		WPostorder(currentNode->GetLeft()); // activate WPostorder function by using currentNode's GetLeft(reculsivly activate)
		WPostorder(currentNode->GetRight()); // activate WPostorder function by using currentNode's GetRight(reculsivly activate)
		delete(currentNode); // delete currentNode
	}
};
void WordBST::Insert(WordNode* node)
{
	
	WordNode* temp = root; //declare temp and initialize into root
	if (temp == '\0') //if temp is null
	{
		root = node; //root is node
		return; //return
	}
	while (1) //while(1)
	{
		if (strcmp(node->GetWord(),temp->GetWord())<0) //if node getword, temp getword word length is -1
		{
			if (temp->GetLeft() == '\0') //temp getleft is null
			{
				temp->SetLeft(node); //temp setleft is node
				break; //break
			}
			temp = temp->GetLeft(); //temp is temp getleft
		}
		else if (strcmp(node->GetWord(), temp->GetWord()) >0) //if node getword, temp getword length is 1
		{
			if (temp->GetRight() == '\0') //temp getright is null
			{
				temp->SetRight(node); //temp setright is node
				break; //break
			}
			temp = temp->GetRight(); //temp is temp getright
		}
		else //if the same word is found then change the mean
			temp->SetMean(node->GetMean()); //temp setmean is node getmean

	}
};
char* WordBST::low(char* word)
{
	char arr[20] = { '\0' }; //declare arr and initialize to null
	for (int a = 0; word[a] != '\0'; a++) //until word[a] reach null
		arr[a] = tolower(word[a]); //arr[a] is tolower(word[a])
	return arr; //return arr
}
WordNode* WordBST::Delete(char* word)  
{
	WordNode* temp = root; //declare temp set as root
	WordNode* prev = '\0'; //declare prev set as null
	char wordarr[32] = {'\0'}; //declare wordarr and set as null
	strcpy(wordarr,low(word)); //copy wordarr as low(word)
	while (temp) //move temp until reach delete
	{
		prev = temp; //prev is temp
		if (strcmp(wordarr, temp->GetWord()) == 1) //if wordarr, temp getword length is 1
			temp = temp->GetRight(); //temp is temp getrigth
		else if (strcmp(wordarr, temp->GetWord()) == -1) //if wordarr, temp getword length is -1
			temp = temp->GetLeft(); //temp is temp getleft
		else //if length is same
			break; //break
	}

	if ((temp->GetLeft() == 0) && (temp->GetRight() == 0))// if temp getleft is 0 and temp getright is 0 
	{
		if (temp = root) //if temp is root
		{
			root = '\0'; //root is null
			return temp; //return temp
		}
		if (prev->GetLeft() == temp) //if prev getleft is same as temp
			prev->SetLeft('\0'); //prev setleft is null
		if (prev->GetRight() == temp) //if prev getright is same as temp
			prev->SetRight('\0'); //prev setright is null
		return temp; //return temp
	}

	else if (temp->GetLeft() == '\0') //if temp getleft is null
	{
		if (temp == root) // if temp is root
		{
			root = temp->GetRight(); //root is temp getright
			temp->SetRight('\0'); //temp setnext is null
			return temp; //return temp
		}
		else
		{
			prev->SetRight(temp->GetRight()); //prev setnext is temp getnext
			temp->SetRight('\0'); //temp setnext is null
			return temp; //return temp
		}
	}
	else if (temp->GetRight() == '\0') // if temp getright is null
	{
		WordNode* Biggest = temp; //declare biggest and set as temp
		WordNode* Bprev = Biggest; //declare bprev and sett as biggest
		Biggest = Biggest->GetLeft(); //biggest is biggest getleft
		while (1) //until break
		{
			if (Biggest->GetRight() == '\0') //if biggest getright is null
			{
				Bprev->SetRight('\0'); //bprv setnext is null
				break; //break
			}
			Bprev = Biggest; //bprev is biggest
			Biggest = Biggest->GetRight(); //biggest is biggest getright
		}
		
		Biggest->SetLeft(temp->GetLeft()); //biggest setnext is temp getnext
		prev->SetLeft(Biggest); //prev setnext is biggest
		if (temp == root) //if temp is root
			root = Biggest; //root is biggest
		temp->SetLeft('\0'); //temp setnext is null
		return temp; //return temp
	}
	else // temp has two child
	{
	
		WordNode* Bprevprev = temp; //declare bprevprev and set as temp
		WordNode* Bprev = temp->GetLeft(); //declare bprev and set as temp getright
		WordNode* Big = temp->GetLeft()->GetRight(); //declare big and set as temp getleft's getright
		while (Big) //until big reach null
		{
			Bprevprev = Bprev; //bprevprev is bprev
			Bprev = Big; //bprev is big
			Big = Big->GetRight(); //big is big getright
		}
	
		Bprevprev->SetRight('\0'); //bprevprev setright is null
		if (temp == root) //if temp is root
		{
			Bprev->SetLeft(temp->GetLeft()); //bprev setleft is temp getright
			Bprev->SetRight(temp->GetRight()); //bprev setright is temp getright
			temp->SetLeft('\0'); //temp setleft is null
			temp->SetRight('\0'); //temp setright is null
			root = Bprev;
			return temp; //return temp
		}
		Bprev->SetLeft(temp->GetLeft()); //bprev setleft is temp getright
		Bprev->SetRight(temp->GetRight()); //bprev setright is temp getright
		prev->SetLeft(Bprev); //prev setleft is bprev
		temp->SetLeft('\0'); //temp setleft into null
		temp->SetRight('\0'); //temp setright into null
		return temp; //return temp
	
	}

}
char* WordBST::up(char* word)
{
	char arr[20] = { '\0' }; //declare arr and set as null
	for (int a = 0; word[a] != '\0'; a++) 
		arr[a] = toupper(word[a]); //arr[a] is toupper word[a]
	return arr; //return arr
}
WordNode* WordBST::Search(char* word)			
{
	WordNode* temp = root; //declare wordnode temp and set as root
	char arrtemp[32] = { '\0' }; //delcare arrtemp and set as null
	char arrword[32] = { '\0' }; //declare arrword and set as null
	while (root)
	{
		if (temp == '\0') //if temp is null
		{
			return temp; //return temp
		}
		strcpy(arrtemp, up(temp->GetWord())); //copy arrtemp as up temp getword
		strcpy(arrword, up(word)); //copy arrwordas up word
		if (strcmp(arrword, arrtemp) <0) //if arrword and arrtemp length is -1
		{temp = temp->GetLeft(); continue;} //temp is temp getleft then continue
		else if (strcmp(arrword, arrtemp) >0) //if arrword and arrtemp length is 1
		{temp = temp->GetRight(); continue;} //temp is temp getright then continue
		else
		{return temp; break;} //return temp then break
	}
	temp = '\0'; //temp is null
	return temp; //return temp
};
void WordBST::Saveroot(WordNode* node)
{
	if (Sroot == '\0') //if sroot is null
	{
		Sroot = node; //sroot is node
		Sroot->SetSnext('\0'); //sroot is setsnext is null
		return; //return
	}
	WordNode* temp = Sroot; //declare temp and set as sroot
	while (1)
	{
		if (temp->GetSnext() == '\0') //if temp getsnext is null
			break; //break
		temp = temp->GetSnext(); //temp is temp getsnext
	}
	temp->SetSnext(node); //temp setsnext is node
	node->SetSnext('\0'); //node setsnext is null
}
void WordBST::WPreorder()// Driver of Preorder
{
	WPreorder(root);
};
void WordBST::WPreorder(WordNode* currentNode)// Workhorse of Preorder
{
	if(currentNode)// if currentNode's value is '\0', break this function
	{
		Saveroot(currentNode);
		WPreorder(currentNode->GetLeft() ); // activate Preorder function by using currentNode's GetLeft(reculsivly activate)
		WPreorder(currentNode->GetRight()); // activate Preorder function by using currentNode's GetRight(reculsivly activate)
	}
};
bool	WordBST::Save()											
{
	ofstream bstfile; //declare bstfile
	bstfile.open("memorizing_word.txt", ios::app); //open memorizing_word.txt
	WPreorder(root);//wpreorder(root)
	WordNode* temp = Sroot; //declare temp and set as sroot
	if (temp == '\0') // if there were no nodes to save
	{
		bstfile.close();
		return false; //return false
	}

	while (1)
	{
		if (temp == '\0') //if temp is null
			break; //break
		bstfile<< temp->GetWord() << "\t" << temp->GetMean()<<endl; //print
		temp = temp->GetSnext(); //temp is temp getsnext
	}
	bstfile.close(); //close bstfile
	return true; //return true
};
bool	WordBST::Print(char* order)					// PRINT
{
	char orderlist[8][8] = { "R_PRE", "I_PRE", "R_IN", "I_IN", "R_POST", "I_POST", "I_LEVEL" };
	if (strcmp(order, orderlist[0]) == 0) //if match R_PRE
	{
		R_PRE(); //implement R_PRE
		return true;
	}
	if (strcmp(order, orderlist[1]) == 0) //if match I_PRE
	{
		I_PRE(); //implement I_PRE
		return true;
	}
	if (strcmp(order, orderlist[2]) == 0)  //if match R_IN
	{
		R_IN(); //implement R_IN
		return true;
	}
	if (strcmp(order, orderlist[3]) == 0)  //if match I_IN
	{
		I_IN(); //implement I_IN
		return true;
	}
	if (strcmp(order, orderlist[4]) == 0)  //if match R_POST
	{
		R_POST(); //implement R_POST
		return true;
	}
	if (strcmp(order, orderlist[5]) == 0)  //if match I_POST
	{
		I_POST(); //implement I_POST
		return true;
	}
	if (strcmp(order, orderlist[6]) == 0)  //if match I_LEVEL
	{
		I_LEVEL(); //implement I_LEVEL
		return true;
	}
};

void WordBST::R_PRE()
{
	R_PRE(root); //bring root
}
void WordBST::R_PRE(WordNode * currentNode)
{
	ofstream logfile; //declare logfile
	logfile.open("log.txt", ios::app); //open log.txt
	if (currentNode)// if currentNode's value is '\0', break this function
	{
	
		logfile << currentNode->GetWord() << "\t"; //print
		logfile << currentNode->GetMean() << endl;
		cout << currentNode->GetWord() << "\t";
		cout << currentNode->GetMean() << endl;
		R_PRE(currentNode->GetLeft()); // activate Preorder function by using currentNode's GetLeft(reculsivly activate)
		R_PRE(currentNode->GetRight()); // activate Preorder function by using currentNode's GetRight(reculsivly activate)
	}
	logfile.close(); //close logfile
}
void WordBST::I_PRE()
{
	ofstream logfile; //declare logfile
	logfile.open("log.txt", ios::app);//open log.txt
	Stack s; //declare stack s
	WordNode *currentNode = root; //currentNode is root
	while (1) //while 1
	{
		while (currentNode) { //while(currentNode)
			logfile << currentNode->GetWord() << "\t";
			logfile << currentNode->GetMean() << endl;
			cout << currentNode->GetWord() << "\t"; //print
			cout << currentNode->GetMean() << endl;
			s.Push(currentNode); //s.push currentNode
			currentNode = currentNode->GetLeft(); //currentnode is currentnode getleft
		}
		if (s.IsEmpty())
			return; //if s.empty return
		currentNode = s.Top(); //currentNode is s.top
		s.Pop(); //bring s.pop

		currentNode = currentNode->GetRight();//currentNode is currentNode GetRight
	}
	logfile.close();
}
void WordBST::R_IN()
{
	R_IN(root);
}
void WordBST::R_IN(WordNode * currentNode)
{
	ofstream logfile;
	logfile.open("log.txt", ios::app);

	if (currentNode)// if currentNode's value is '\0', break this function
	{
		R_IN(currentNode->GetLeft()); // activate inorder function by using currentNode's leftChild(reculsivly activate)
		cout << currentNode->GetWord() << "\t"; // print currentNode
		cout << currentNode->GetMean() << endl;
		logfile << currentNode->GetWord() << "\t";
		logfile << currentNode->GetMean() << endl;

		R_IN(currentNode->GetRight()); // activate inorder function by using currentNode's rightChild(reculsivly activate)
	}
	logfile.close();
}
void WordBST::I_IN()
{
	ofstream logfile;
	logfile.open("log.txt", ios::app);

	Stack *s = new Stack; //declare stack TreeNode template s
	WordNode *currentNode = root; //declare currentnode, currentnode is root
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
		cout << currentNode->GetWord() << "\t"; //cout currentNode data
		cout << currentNode->GetMean() << endl;
		logfile << currentNode->GetWord() << "\t";
		logfile << currentNode->GetMean() << endl;

		currentNode = currentNode->GetRight();//currentNode is currentNode rightChild
	}
	logfile.close();
}
void WordBST::R_POST()
{
	R_POST(root);//bring root
}
void WordBST::R_POST(WordNode * currentNode)
{
	ofstream logfile; //declare logfile
	logfile.open("log.txt", ios::app); //open log.txt

	if (currentNode)// if currentNode's value is '\0', break this function
	{
		R_POST(currentNode->GetLeft()); // activate Postorder function by using currentNode's GetLeft(reculsivly activate)
		R_POST(currentNode->GetRight()); // activate Postorder function by using currentNode's GetRight(reculsivly activate)
		cout << currentNode->GetWord() << "\t"; // print 
		cout << currentNode->GetMean() << endl;
		logfile << currentNode->GetWord() << "\t";
		logfile << currentNode->GetMean() << endl;
	}
	logfile.close();//close logfile
}
void WordBST::I_POST()
{
	ofstream logfile; //declare logfile
	logfile.open("log.txt", ios::app); //open log.txt

	Stack s; //declare stack s
	WordNode *currentNode, *prevNode, *root1 = root; //declare node cuurentnode, prevnode, root1 set roo1 as root
	prevNode = '\0'; //prevnode is null
	s.Push(root1); //push root1

	while (!s.IsEmpty()) //until isempty
	{
		currentNode = s.Top(); //currentnode is top
		if ((prevNode == '\0') || (prevNode->GetLeft() == currentNode) || (prevNode->GetRight() == currentNode)) {//if prevnode is null or prevnode getleft is same as currentnode or prevnode getright is same as currentnode
			if (currentNode->GetLeft() != '\0') //if currentnode getleft is not null
				s.Push(currentNode->GetLeft()); //push currentnode getleft
			else if (currentNode->GetRight() != '\0') //if currentnode getright is not null
				s.Push(currentNode->GetRight()); //push currentnode getright
			else
			{
				logfile << currentNode->GetWord() << "\t";
				logfile << currentNode->GetMean() << endl;
				cout << currentNode->GetWord() << "\t"; //print
				cout << currentNode->GetMean() << endl;
				s.Pop(); //pop
			}
		}
		else if (prevNode == currentNode->GetLeft())
		{
			if (currentNode->GetRight() != '\0') //if currentnode getright is not null
				s.Push(currentNode->GetRight()); //push currentnode getright
			else
			{
				logfile << currentNode->GetWord() << "\t";
				logfile << currentNode->GetMean() << endl;
				cout << currentNode->GetWord() << "\t"; //print
				cout << currentNode->GetMean() << endl;
				s.Pop(); //pop
			}
		}
		else if (prevNode == currentNode->GetRight()) //if prevnode is same as currentnode getright
		{
			logfile << currentNode->GetWord() << "\t";
			logfile << currentNode->GetMean() << endl;
			cout << currentNode->GetWord() << "\t"; //print
			cout << currentNode->GetMean() << endl;
			s.Pop(); //pop
		}
		prevNode = currentNode; //prevnode is currentnode
	}
	logfile.close(); //close logfile
}

void WordBST::I_LEVEL()
{
	ofstream logfile; //declare logfile
	logfile.open("log.txt", ios::app); //open log.txt

	Queue2 q; //declare queue2 q
	WordNode *currentNode = root; //currentNode is root
	while (currentNode) { //while currentNode
		logfile << currentNode->GetWord() << "\t";
		logfile << currentNode->GetMean() << endl;
		cout << currentNode->GetWord() << "\t"; //print
		cout << currentNode->GetMean() << endl;
		if (currentNode->GetLeft())
			q.Push(currentNode->GetLeft()); //if currentNode GetLeft q.push currentNode GetLeft
		if (currentNode->GetRight())
			q.Push(currentNode->GetRight()); //if currentNode GetRight q.push currentNode GetRight
		if (q.empty())
			return; //if q.empty return
		currentNode = q.front(); //currentNode is q.front
		q.Pop(); //bring q.pop
	}
	logfile.close();//close logfile
}
Stack::Stack()   //Stack
{
	pHead = 0;   //phead is 0
}

Stack::~Stack()   //Stack
{
	WordNode* del;   //declare del

	while (pHead != '\0')   //until phead reach null
	{
		del = pHead;   //delis phead
		del->SetNext2('\0');   //del setnext2 is null
		pHead = pHead->GetNext2();   //phead is phead getnext2 set phead as next
		delete del;   //delete del memory relise
	}
	pHead = '\0';   //save null into phead
}

bool Stack::IsEmpty()   //IsEmpty
{
	if (pHead == 0)   //if phead is 0
		return true;   //return true
	else   //if not 0
		return false;   //return false
}


bool Stack::Push(WordNode* pNode)   //Push
{
	if (pHead == 0)   //if phead is 0 meaning nothing inside
	{
		pHead = pNode;   //set phead as pnode
	}
	else  
	{
		pNode->SetNext2(pHead);   //pnode setnext2 is phead
		pHead = pNode;   //phead is pnode
	}

	return true;   //return true
}

WordNode* Stack::Pop()   //Pop
{
	WordNode* temp;   //declare temp
	if (pHead == '\0')   //if phead is null
	{
		cout << "no node" << endl << endl;   //print
		return 0;   //return 0
	}
	else   
	{
		temp = pHead;   //temp is phead
		pHead = pHead->GetNext2(); //phead is phead getnext2
		return temp;   //retuen temp
	}
}

WordNode * Stack::Top()
{
	return pHead; //return phead
}


Queue2::Queue2()
{
	pHead = 0; //set phead as 0
	pTail = 0; //set ptail as 0
};


Queue2::~Queue2()
{
	WordNode* del; //declare del

	while (pHead != '\0') //until phead is null
	{
		del = pHead; //del is phead
		del->SetNext2('\0'); //del setnext2 is null
		pHead = pHead->GetNext2();//phead is phead getnext2
		delete del; //delete del
	}
	pHead = '\0'; //phead is null
};

void Queue2::Push(WordNode* node)
{
	if (pHead == '\0') //if phead is null
	{
		pHead = node;//phead is node
		pTail = node;//ptail is node
		pTail->SetNext2('\0'); //ptail setnext2 is null
	}
	else
	{
		pTail->SetNext2(node); //ptail setnext2 is node
		pTail = node; //ptail is node
		pTail->SetNext2('\0'); //ptail setnext2 is null
	}
}

WordNode* Queue2::Pop()
{
	WordNode* temp = pHead; //declare temp and set as phead
	if (temp == 0) //if temp is 0
		return pHead; //return phead
	else
	{
		pHead = temp->GetNext2(); //phead is temp getnext2
		temp->SetNext2('\0'); //temp setnext2 is null
		return temp;//return temp
	}
}

WordNode * Queue2::front() //to return the first node
{
	return pHead; //return phead
}


bool Queue2::empty()   //to find out if the queue2 node is empty
{
	if (pHead == 0)   //if phead is 0
		return true; //return true
	return false; //return false
}
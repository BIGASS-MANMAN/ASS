#include "WordBST.h"

WordBST::WordBST()
{
	root = '\0';
}

WordBST::~WordBST()
{
	Clear(root);
}

void WordBST::Insert(WordNode * node) {      // LOAD, MOVE
	WordNode * p = root, *pp = 0;
	char arr1[50] = { '\0', }, arr2[50] = { '\0', };

	for (int i = 0; i < strlen(node->GetWord()); i++) {      // the letter of 'new node' is changed to small letter 
		if (node->GetWord()[i] < 97)
			arr2[i] = (char)(node->GetWord()[i] + 32);
		else
			arr2[i] = node->GetWord()[i];
	}

	while (p) {         //loop
		pp = p;

		for (int i = 0; i<50; i++)      // initialize
			arr1[i] = '\0';
		for (int i = 0; i < strlen(p->GetWord()); i++) {      // the letter of 'new node' is changed to small letter 
			if (p->GetWord()[i] < 97)
				arr1[i] = (char)(p->GetWord()[i] + 32);
			else
				arr1[i] = p->GetWord()[i];
		}

		if (strcmp(arr1, arr2) > 0) { //perform if thePair's value is smaller than p's first value
			p = p->GetLeft(); //move to leftchild
		}
		else if (strcmp(arr1, arr2) < 0) { //perform if thePair's value is bigger than p's first value 
			p = p->GetRight(); //move to rightchild
		}
	}

	// insert
	if (root) { //root is not NULL
		for (int i = 0; i<50; i++)      // initialize
			arr1[i] = '\0';
		for (int i = 0; i < strlen(pp->GetWord()); i++) {      // the letter of 'new node' is changed to small letter 
			if (pp->GetWord()[i] < 97)
				arr1[i] = (char)(pp->GetWord()[i] + 32);
			else
				arr1[i] = pp->GetWord()[i];
		}

		if (strcmp(arr1, arr2) > 0) pp->SetLeft(node);
		else pp->SetRight(node);
	}
	else //root is NULL
		root = node; //set p to root
}
WordNode* WordBST::Search(char* word) {            // ADD, TEST, SEARCH, UPDATE
	WordNode * currentNode = root;
	char arr1[50] = { '\0' }; //currentNode's small letter version
	char arr2[50] = { '\0' }; //word's small letter version

	if (root == NULL) return NULL;

	for (int i = 0; i < strlen(word); i++) { //Loop for change word's capital letter
		if (word[i] < 97)
			arr2[i] = (char)(word[i] + 32);
		else
			arr2[i] = word[i];
	}

	while (currentNode) {
		for (int i = 0; i < 50; i++) //arr1 initialize
			arr1[i] = '\0';

		for (int i = 0; i < strlen(currentNode->GetWord()); i++) { //Loop for change currentNode's capital letter
			if (currentNode->GetWord()[i] < 97)
				arr1[i] = (char)(currentNode->GetWord()[i] + 32);
			else
				arr1[i] = currentNode->GetWord()[i];
		}

		if (strcmp(arr1, arr2) > 0) //compare arr1 with arr2 to move left or right direction
			currentNode = currentNode->GetLeft();
		else if (strcmp(arr1, arr2) < 0)
			currentNode = currentNode->GetRight();
		else //search success
			return currentNode;
	}
	return 0; //search fail
}

WordNode * WordBST::Delete(char * word)
{
	WordNode* Cur = root;            //declare Cur & initialize to root
	WordNode* parentNode = '\0';      //declare parentNode & initialize to '\0'
	WordNode* temp1 = new WordNode();

	while (Cur)                              //tree traversal
	{
		if (strcmp(word, Cur->GetWord()) == 0)               //if find target
			break;                           //escape loop

		if (strcmp(word, Cur->GetWord()) < 0)               //if word < Cur's data
		{
			parentNode = Cur;                  //initialize parentNode to Cur
			Cur = Cur->GetLeft();               //initialize Cur to GetLeft()
		}
		else                              //if word > Cur's data
		{
			parentNode = Cur;                  //initialize parentNode to Cur
			Cur = Cur->GetRight();               //initialize Cur to GetRight()
		}
	}
	if (Cur == root && Cur->GetLeft() == '\0' && Cur->GetRight() == '\0')      //if BST has only root Node
	{
		temp1->SetWord(Cur->GetWord());                              //data copy
		temp1->SetMean(Cur->GetMean());
		root = '\0';
		delete Cur;                                             //delete Node
	}

	else if (Cur->GetLeft() == '\0' && Cur->GetRight() == '\0')             //delete leaf Node
	{

		temp1->SetWord(Cur->GetWord());                           //data copy
		temp1->SetMean(Cur->GetMean());

		if (parentNode->GetLeft() == Cur)      //Cur is parentNode's GetLeft()
		{
			parentNode->SetLeft('\0');      //initialize parentNode's LeftNNode to '\0'            
			delete Cur;                  //delete temp
		}
		else
		{
			parentNode->SetRight('\0');      //initialize parentNode's RightNode to '\0'            
			delete Cur;               //delete temp
		}
	}

	//delete node which has one child

	else if (Cur->GetLeft() != '\0' && Cur->GetRight() == '\0')   //if Cur has left child
	{
		WordNode* tCur = Cur;               //declare tCur & initialize to Cur
		WordNode* tparentNode = tCur;         //declare parntNode & initialize to tCur

		temp1->SetWord(Cur->GetWord());                           //data copy
		temp1->SetMean(Cur->GetMean());

		tCur = tCur->GetLeft();                        //tCur is left sub Tree's root Node

		if (tCur->GetLeft() != '\0' && tCur->GetRight() != '\0')
		{
			while (tCur->GetRight() != '\0')               //tCur is the biggest data in left sub Tree
			{
				tparentNode = tCur;                        //initialize tparentNode to tCur
				tCur = tCur->GetRight();                  //initialize tCur to tCur's right Child
			}

			Cur->SetWord(tCur->GetWord());                        //initialize Cur's data to tCur's data
			Cur->SetMean(tCur->GetMean());

			if (tCur->GetLeft() == '\0')                  //if tCur is leaf Node
			{
				tparentNode->SetRight('\0');                //initialize tparentNode's rightChild to '\0'
				delete tCur;                            //delete temp
			}
			else                                    //if tCur has a child
			{
				tparentNode->SetRight(tCur->GetLeft());      //initialize tparentNode's rightChild to tCur's leftChild
				delete tCur;                           //delete temp
			}
		}

		else if (Cur == root)      //if Cur is root
		{
			root = Cur->GetLeft();               //initialize root to Cur's LeftNode
			delete Cur;                     //delete temp
		}
		else if (Cur == parentNode->GetLeft())   //if Cur is parentNode's left child
		{
			parentNode->SetLeft(Cur->GetLeft());       //initialize parentNode's LeftNode to Cur's LeftNode
			delete Cur;                         //delete temp
		}
		else                                  //if Cur is parentNode's right child
		{
			parentNode->SetRight(Cur->GetLeft());    //initialize parentNode's GetRight() to Cur's GetLeft()
			delete Cur;                         //delete temp
		}
	}

	else if (Cur->GetLeft() == '\0' && Cur->GetRight() != '\0') //if Cur has right child
	{
		WordNode* tCur = Cur;               //declare tCur & initialize to Cur
		WordNode* tparentNode = tCur;         //declare parntNode & initialize to tCur

		tCur = tCur->GetRight();                        //tCur is left sub Tree's root Node

		temp1->SetWord(Cur->GetWord());                           //data copy
		temp1->SetMean(Cur->GetMean());

		if (tCur->GetLeft() != '\0' && tCur->GetRight() != '\0')
		{
			while (tCur->GetLeft() != '\0')               //tCur is the biggest data in left sub Tree
			{
				tparentNode = tCur;                        //initialize tparentNode to tCur
				tCur = tCur->GetLeft();                  //initialize tCur to tCur's right Child
			}

			Cur->SetWord(tCur->GetWord());                        //initialize Cur's data to tCur's data
			Cur->SetMean(tCur->GetMean());

			if (tCur->GetRight() == '\0')                  //if tCur is leaf Node
			{
				tparentNode->SetLeft('\0');                //initialize tparentNode's rightChild to '\0'
				delete tCur;                            //delete temp
			}
			else                                    //if tCur has a child
			{
				tparentNode->SetLeft(tCur->GetRight());      //initialize tparentNode's leftChild to tCur's RightChild
				delete tCur;                           //delete temp
			}
		}

		else if (Cur == root)      //if Cur is root
		{
			root = Cur->GetRight();            //initialize root to Cur's GetRight()
			delete Cur;                  //delete temp
		}
		else if (Cur == parentNode->GetLeft())   //if Cur is parentNode's left child
		{
			parentNode->SetLeft(Cur->GetRight());     //initialize parentNode's LeftNode to Cur's RightNode         
			delete Cur;                          //delete temp
		}
		else                           //if Cur is parentNode's right child
		{
			parentNode->SetRight(Cur->GetRight());      //initialize parentNode's RightNode to Cur's LeftNode         
			delete Cur;                        //delete temp
		}
	}

	else                                       //delete node which has two children or only left child
	{
		WordNode* tCur = Cur;               //declare tCur & initialize to Cur
		WordNode* tparentNode = tCur;         //declare parntNode & initialize to tCur   

		temp1->SetWord(tCur->GetWord());                           //data copy
		temp1->SetMean(tCur->GetMean());

		tCur = tCur->GetLeft();                        //tCur is left sub Tree's root Node

		while (tCur->GetRight() != '\0')               //tCur is the biggest data in left sub Tree
		{
			tparentNode = tCur;                        //initialize tparentNode to tCur
			tCur = tCur->GetRight();                  //initialize tCur to tCur's right Child
		}

		Cur->SetWord(tCur->GetWord());                  //initialize Cur's data to tCur's data
		Cur->SetMean(tCur->GetMean());

		if (tCur->GetLeft() == '\0')                  //if tCur is leaf Node
		{
			if (tCur == tparentNode->GetLeft())
				tparentNode->SetLeft('\0');                //initialize tparentNode's LeftNode to '\0'
			else
				tparentNode->SetRight('\0');            //initialize tparentNode's RightNode to '\0'
			delete tCur;                            //delete temp         
		}
		else                                    //if tCur has a child
		{
			if (tCur == tparentNode->GetRight())
				tparentNode->SetRight(tCur->GetLeft());      //initialize tparentNode's RightNode to tCur's LeftNode
			else
				tparentNode->SetLeft(tCur->GetLeft());      //initialize tparentNode's LeftNode to tCur's LeftNode
			delete tCur;                           //delete temp
		}
	}
	return temp1;
}

bool WordBST::Save()
{
	ofstream ingfout;                     //for memorizing_word.txt file
	ingfout.open("memorizing_word.txt",ios::app);
	if (root != '\0')                     //if BST is exist
	{
		return preSave(root, ingfout);
	}
	else                              //if BST is not exist
	{
		ingfout.close();
		return false;
	}
}

bool WordBST::preSave(WordNode * CurrentNode, ofstream & ingfout)
{
	WordNode* temp = CurrentNode;
	if (temp)
	{
		ingfout << temp->GetWord() << " " << temp->GetMean() << endl;
		preSave(temp->GetLeft(), ingfout);
		preSave(temp->GetRight(), ingfout);
	}
	return true;
}

bool WordBST::Print(char * order)
{

	if (root != NULL)			//if wordBST is exist
	{
		ofstream fout;
		fout.open("log.txt", ios::app);			//for log file
		bool cond;
		if (strcmp(order, "R_PRE") == 0)		//Recursive Pre Order
		{

			cond = R_PRE();
			fout.close();
			return cond;
		}
		else if (strcmp(order, "I_PRE") == 0)	//Iterative Pre Order
		{

			cond = I_PRE();
			fout.close();
			return cond;
		}
		else if (strcmp(order, "R_IN") == 0)	//Recursie In Order
		{

			cond = R_IN();
			fout.close();
			return cond;
		}
		else if (strcmp(order, "I_IN") == 0)	//Iterative In Order
		{

			cond = I_IN();
			fout.close();
			return cond;
		}
		else if (strcmp(order, "R_POST") == 0)	//Recursive Post Order
		{

			cond = R_POST();
			fout.close();
			return cond;
		}
		else if (strcmp(order, "I_POST") == 0)	//Iterative Post Order
		{

			cond = I_POST();
			fout.close();
			return cond;
		}
		else if (strcmp(order, "I_LEVEL") == 0)	//Iterative Level Order
		{

			cond = I_LEVEL();
			fout.close();
			return cond;
		}
		else
		{
			fout.close();
			return false;
		}

	}
	else
		return false;

}

bool WordBST::R_IN()				//R_IN Driver
{
	if (root != NULL)
	{
		ofstream fout;
		fout.open("log.txt", ios::app);
		R_IN(root, fout);
		fout.close();
		return true;
	}
	else
		return false;
}

void WordBST::R_IN(WordNode * root, ofstream &fout)		//R_IN
{
	WordNode* CurrentNode = root;

	if (CurrentNode)
	{
		R_IN(CurrentNode->GetLeft(), fout);
		cout << CurrentNode->GetWord() << " " << CurrentNode->GetMean() << endl;
		fout << CurrentNode->GetWord() << " " << CurrentNode->GetMean() << endl;
		R_IN(CurrentNode->GetRight(), fout);
	}
}

bool WordBST::R_PRE()			//R_PRE Driver
{
	if (root != NULL)
	{
		ofstream fout;
		fout.open("log.txt", ios::app);
		R_PRE(root, fout);
		fout.close();
		return true;
	}
	else
		return false;
}

void WordBST::R_PRE(WordNode * root, ofstream &fout)	//R_PRE
{
	WordNode* CurrentNode = root;

	if (CurrentNode)
	{
		cout << CurrentNode->GetWord() << " " << CurrentNode->GetMean() << endl;
		fout << CurrentNode->GetWord() << " " << CurrentNode->GetMean() << endl;
		R_PRE(CurrentNode->GetLeft(), fout);
		R_PRE(CurrentNode->GetRight(), fout);
	}
}

bool WordBST::R_POST()				//R_POST Driver
{
	if (root != NULL)
	{
		ofstream fout;
		fout.open("log.txt", ios::app);
		R_POST(root, fout);
		fout.close();
		return true;
	}
	else
		return false;
}

void WordBST::R_POST(WordNode * root, ofstream &fout)	//R_POST
{
	WordNode* CurrentNode = root;

	if (CurrentNode)
	{
		R_POST(CurrentNode->GetLeft(), fout);
		R_POST(CurrentNode->GetRight(), fout);
		cout << CurrentNode->GetWord() << " " << CurrentNode->GetMean() << endl;
		fout << CurrentNode->GetWord() << " " << CurrentNode->GetMean() << endl;
	}
}

bool WordBST::I_IN()						//I_IN
{
	if (root == NULL)
		return false;
	else
	{
		WordNode* arr[101] = { '\0' };						//declare WordNode* array
		int cnt = 0;
		int top = 0;
		WordNode* CurrentNode = root;

		ofstream fout;							//for log file
		fout.open("log.txt", ios::app);

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
				fout.close();
				return true;
			}
			top--;
			CurrentNode = arr[top];
			arr[cnt] = '\0';
			cnt--;
			cout << CurrentNode->GetWord() << " " << CurrentNode->GetMean() << endl;		//print data in screen
			fout << CurrentNode->GetWord() << " " << CurrentNode->GetMean() << endl;		//print data in file
			CurrentNode = CurrentNode->GetRight();
		}
	}

}

bool WordBST::I_PRE()					//I_PRE
{



	if (root == NULL)
		return false;
	else
	{
		WordNode* arr[101] = {'\0'};					//declare WordNode* array
		int cnt = 0;
		int top = 0;
		WordNode* CurrentNode = root;

		ofstream fout;						//for log file
		fout.open("log.txt", ios::app);

		while (1)
		{
			while (CurrentNode)
			{
				arr[cnt] = CurrentNode;
				cout << CurrentNode->GetWord() << " " << CurrentNode->GetMean() << endl;		//print data in screen
				fout << CurrentNode->GetWord() << " " << CurrentNode->GetMean() << endl;		//print data in file
				CurrentNode = CurrentNode->GetLeft();
				cnt++;
				top++;
			}

			if (cnt == 0)
			{
				fout.close();
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

bool WordBST::I_POST()					//I_POST
{

	if (root == NULL)
		return false;
	else
	{
		WordNode* arr[101] = { '\0' };						//declare WordNode* array
		int cnt = 0;
		WordNode* CurrentNode = root;

		ofstream fout;							//for log file
		fout.open("log.txt", ios::app);

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
				fout.close();
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
				cout << CurrentNode->GetWord() << " " << CurrentNode->GetMean() << endl;		//print data in screen
				fout << CurrentNode->GetWord() << " " << CurrentNode->GetMean() << endl;		//print data in file
				CurrentNode = '\0';
				cnt++;
			}

		}
	}
}

bool WordBST::I_LEVEL()
{
	WordNode* arr[101] = { '\0' };
	int cnt = 0;
	int frt = cnt;
	WordNode* CurrentNode = root;
	if (root)
	{
		ofstream fout;							//for log file
		fout.open("log.txt", ios::app);
		while (CurrentNode)
		{
			cout << CurrentNode->GetWord() << " " << CurrentNode->GetMean() << endl;		//print data in screen
			fout << CurrentNode->GetWord() << " " << CurrentNode->GetMean() << endl;		//print data in file
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
				fout.close();
				return true;
			}
			CurrentNode = arr[frt];
			arr[frt] == '\0';
			frt++;
		}
	}
	return false;
}

void WordBST::Clear(WordNode * root)
{
	WordNode* CurrentNode = root;
	if (CurrentNode)
	{
		Clear(CurrentNode->GetLeft());
		Clear(CurrentNode->GetRight());
		delete CurrentNode;
	}

}

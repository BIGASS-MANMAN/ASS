#include "/usr/local/Auto_Scoring_System/src/signal.h"
#include "Manager.h"
Manager::Manager() // constructor
{
	cll = new CircularLinkedList;				//make cll, bst, queue and initialize array
	bst = new AlphabetBST;
	queue = new Queue;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 100; j++)
		comm[i][j] = 0;
}
Manager::~Manager()								//distructor
{ return;

	delete cll;									//delete all of data
	delete bst;
	delete queue;
}

void Manager::run(const char * command)						//Manager is run in this function
{
	struct sigaction sa;
	set_sigaction(sa);
	alarm(3);

	CommandFile.open(command);								//open command file to read command
	if (!CommandFile)										//if fail call file, 
	{
		return;												//end
	}
	char *context = NULL;
	char *temp;
	while (!CommandFile.eof())								//while command exist
	{
		CommandFile.getline(comm[0],100);					//get one line command in comm[0]
		if(*comm[0] == '0')
			continue;
		temp =  strtok_r(comm[0], " ",&context);			//and cut comm[0] delimiter is ' ' or '\0'
		if(temp != NULL)									//for prevent str function's factor is not NULL
		my_strcpy(comm[1], temp,strnlen(temp,100));			//copy 
		if (strcmp(context, ""))							//same acting
		{
		temp =  strtok_r(NULL, " ",&context);
		my_strcpy(comm[2], temp,strlen(temp));
		}
		else
			my_strcpy(comm[2], "", 0);
		if (strcmp(context, ""))
		{
		temp =  strtok_r(NULL, " ",&context);
		my_strcpy(comm[3], temp,strlen(temp));
		}
		else
			my_strcpy(comm[3], "", 0);
		if (strcmp(context, ""))
		{
		temp =  strtok_r(NULL, " ",&context);
		my_strcpy(comm[4], temp,strlen(temp));
		}
		else
			my_strcpy(comm[4], "", 0);

		if (!strcmp(comm[1], "LOAD"))						//compare to comm[1] and 8's function
		{													//and if error, go to error function, and some of function's sucess call error function to print success
			if(this->LOAD())
				this->ERROR(NULL, 100);
			else this->ERROR(comm[0], 101);
		}

		else if (!strcmp(comm[1], "ADD"))
		{
			if(this->ADD())
				this->ERROR(NULL, 200);
			else this->ERROR(comm[1], 101);
		}
		else if (!strcmp(comm[1], "MOVE"))
		{ 
			if (this->MOVE())
				this->ERROR(NULL, 300);
		}
		else if (!strcmp(comm[1], "SAVE")) {
			if(this->SAVE())
				this->ERROR(NULL, 400);
			else this->ERROR(comm[1], 101);
		}
		else if (!strcmp(comm[1], "TEST"))
		{ 
			if(this->TEST())
				this->ERROR(NULL, 500);
			else 
				this->ERROR(comm[1], 102);
		}
		else if (!strcmp(comm[1], "SEARCH"))
		{
			if (this->SEARCH())
				this->ERROR(NULL, 600);
		}
		else if (!strcmp(comm[1], "PRINT"))
		{
			if(!this->PRINT())
				this->ERROR(NULL, 700);
		}
		else if (!strcmp(comm[1], "UPDATE"))
		{ 
			if (this->UPDATE())
				this->ERROR(NULL, 800);
		}
		else break;
	}
	CommandFile.close();										//command close
}
bool Manager::LOAD()											//LOAD function
{
	if (strcmp(comm[2], ""))									//if command has unnecessary word, error
		return 1;
	if (!queue->Empty() || bst->WordCnt != 0 || cll->pHead != NULL)	//if already had date , error
	{
		return 1;
	}
	int count = 0;												//for error count
	for (int i = 0; i < 3; i++)
	{
		
		ifstream File;											//read file
		if (i == 0)
			File.open("to_memorize_word.txt");					//open file's one loop by one
		else if (i == 1)
			File.open("memorizing_word.txt");
		else
			File.open("memorized_word.txt");

		if (!File || File.eof())								//if file's data is empty or file is not exist, count ++
		{
			count++;
		}
		while (!File.eof())										//while file is not empty
		{
			char *word = new char[32];							//read in file copy in char pointer
			char *mean = new char[32];
			File >> word;
			File >> mean;
			if (*word == '\0')									//for prevant error
			{
				delete word;
				delete mean;
				continue;
			}
			WordNode *Node = new WordNode;						//set Node that had been copied infomation
			Node->SetWord(word);
			Node->SetMean(mean);
			if (i == 0 && count ==0)							//if not error and	 file is to_memorize_word
				queue->Push(Node);								//set in Node
			else if (i == 1 && count == 0)						//if not error and	 file is memorizing_word
			{
				if (bst->WordCnt < 100 && bst->Search(word[0]))							//if bst word's number is not bigger than 100
				{
					bst->Search(word[0])->GetBST()->Insert(Node);//insert in word bst and ++ WordCnt
					bst->WordCnt++;
				}
				else											//else delete
				{
					delete Node;
				}

			}
			else if(i==2 && count == 0)							//if not error and	 file is memorized.txt
				cll->Insert(Node);								//insert in circuitarlinkedlikst
			else												//if error, delete and return 0
			{
				delete Node;
				return 1;
			}
		}
		File.close();											//file close
	}
	return 0;
	
	
}
bool Manager::ADD()												//ADD function
{
	if (strcmp(comm[2], ""))									//if command has unnecessary word, error
		return 1;
	ifstream to_memorizing("word.txt");							//onpen word.txt
	if (!to_memorizing) return 1;								//if word.txt isn;t exist, error
	while (!to_memorizing.eof())								//while to_memorizing is not empty
	{
		WordNode *NewNode = new WordNode;						//save word.txt's infomation in New wordnode
		char *word = new char[32];
		char *mean = new char[32];
		to_memorizing >> word;
		to_memorizing >> mean;
		if (strcmp(word, "") && !queue->Search(word))			//and find it is already in queue or not
		{
			NewNode->SetWord(word);								//if not queue push New node
			NewNode->SetMean(mean);
			queue->Push(NewNode);
		}
		else
		{
				delete NewNode;									//else delete New node
		}
	}
	to_memorizing.close();										//close file
	if (queue->pHead == NULL)									//IF DATA is not save or data is empty , error
		return 1;
	return 0;
}
bool Manager::MOVE()											//Move function
{
	if (strcmp(comm[3], ""))									//if command has unnecessary word, error
		return 1;
	WordNode* pWork;
	char Num[4] = { 0 };										//take order's Number
	int num = 0;

	if (strlen(comm[2]) < 4)
		strcpy(Num, comm[2]);
	else
		return 1;
	num = atoi(Num);											//translate char -> int
	if (!queue->pHead || (bst->WordCnt + num)>100) return 1;	// for error

	while (num != 0)											//while all number data is transmission or queue is empty
	{															//transmission quere to bst
		if (!queue->pHead) 
			return 1;
		pWork = queue->Pop();
		bst->Search(*pWork->GetWord())->GetBST()->Insert(pWork);
		bst->WordCnt++;
		num--;
	}
	return 0;

}
bool Manager::SAVE()
{
	if (strcmp(comm[2], ""))									//if command has unnecessary word, error
		return 1;
	int arr[3] = { 0 };											//catch error
	arr[2] = queue->Save();
	arr[1] = bst->Save();
	arr[0] = cll->Save();
	if (arr[2] == 1 || arr[0] == 1|| arr[1] == 1)				//if at least one of file write is fail
		return 1;												//return 1;
	return 0;

}
bool Manager::TEST()											//TEST
{
	if (strcmp(comm[4], ""))									//if command has unnecessary word, error
		return 1;
	char word[32] = { 0 };										//copy command's infomoation
	char mean[32] = { 0 };
	strcpy(word, comm[2]);
	strcpy(mean, comm[3]);

	if (!word[0] || !mean[0]) return 1;							//if infomation not exist, error

	if (bst->Search(word[0]))									//find word in bst
	{
		if (bst->Search(word[0])->GetBST()->Search(word))
		{
			if (!cll->Search(word))								//if that word not exist in circlarlinkedlist
			{
				cll->Insert(bst->Search(word[0])->GetBST()->Delete(word));//set in circlarlinkedlist and delete in bst
				return 0;
			}
			else return 1;										//else error
		}
	}
	return 1;
}
bool Manager::SEARCH()											//Search Function
{
	if (strcmp(comm[3], ""))									//if command has unnecessary word, error
		return 1;
	char word[32] = { 0 };										//copy search word
	strcpy(word, comm[2]);
	if (!word[0]) return 1;

	if (queue->Search(word))									//find in queue and print
	{
		cout << "======== SEARCH ========" << endl;
		cout << queue->Search(word)->GetWord() << " "<<queue->Search(word)->GetMean()<<endl;
		cout << "=======================" << endl;
		Log << "======== SEARCH ========" << endl;
		Log << queue->Search(word)->GetWord() << " " << queue->Search(word)->GetMean() << endl;
		Log << "=======================" << endl;
		return 0;
	}
	else if (bst->Search(word[0]))								//find in bst and print
	{
		if (bst->Search(word[0])->GetBST()->Search(word))
		{
			cout << "======== SEARCH ========" << endl;
			cout << bst->Search(word[0])->GetBST()->Search(word)->GetWord() <<" "<<bst->Search(word[0])->GetBST()->Search(word)->GetMean() << endl;
			cout << "=======================" << endl;
			Log << "======== SEARCH ========" << endl;
			Log << bst->Search(word[0])->GetBST()->Search(word)->GetWord() << " " << bst->Search(word[0])->GetBST()->Search(word)->GetMean() << endl;
			Log << "=======================" << endl;
			return 0;
		}
	}
	if (cll->Search(word))										//find in cll and print
	{
		cout << "======== SEARCH ========" << endl;
		cout << cll->Search(word)->GetWord()<<" "<<cll->Search(word)->GetMean() << endl;
		cout << "=======================" << endl;
		Log << "======== SEARCH ========" << endl;
		Log << cll->Search(word)->GetWord() << " " << cll->Search(word)->GetMean() << endl;
		Log << "=======================" << endl;
		return 0;
	}
	return 1;													//if can't find, error

}
bool Manager::PRINT()											//Print function
{
	if (strcmp(comm[4], ""))									//if command has unnecessary word, error
		return 0;
	Log.open("Log.txt", ios::app);								//open Log.txt by ios::app
	char command[12] = { 0 };
	char order[9] = { 0 };
	strcpy(command, comm[2]);									//copy command
	if (!strcmp(command, "TO_MEMORIZE"))						//if command == TO_MEMORIZE
	{
		Log.close();											//close Log, call queue's print
		return queue->Print();
	}
	else if (!strcmp(command, "MEMORIZED"))						//if command == MEMORIZED
	{
		Log.close();											//close Log, call cll's print
		return cll->Print();
	}
	else if (!strcmp(command, "MEMORIZING"))					//if command == MEMORIZING
	{
		strcpy(order, comm[3]);									//copy order
		Log.close();											//close Log, call bst's print with order
		if (order[8] != 0)
			return 0;
		return bst->Print(order);
	}
	else
	{
		Log.close();											//close Log
		return 0;
	}
}
bool Manager::UPDATE()											//UPDATE FUNCTION
{
	if (strcmp(comm[4], ""))									//if command has unnecessary word, error
		return 1;
	char word[32] = { 0 };
	char *mean = new char[32];									//copy word and new mean
	char mean2[32] = { 0 };
	strcpy(word, comm[2]);
	strcpy(mean, comm[3]);
	int a = 0;
	if (queue->Search(word))									//if queue has that
	{
		my_strcpy(mean2, queue->Search(word)->GetMean(), sizeof(queue->Search(word)->GetMean()));//mean2 copy old infomation
		delete queue->Search(word)->GetMean();					//delete old mean
		queue->Search(word)->SetMean(mean);						//set new mean
		a++;													//error count
	}
	if (bst->Search(word[0]))									
	{
		if (bst->Search(word[0])->GetBST()->Search(word))		//if bst has that
		{
			my_strcpy(mean2, bst->Search(word[0])->GetBST()->Search(word)->GetMean(), sizeof(bst->Search(word[0])->GetBST()->Search(word)->GetMean()));//mean2 copy old infomation
			delete bst->Search(word[0])->GetBST()->Search(word)->GetMean();//delete old mean
			bst->Search(word[0])->GetBST()->Search(word)->SetMean(mean);   //set new mean
			a++;													//error count
		}
	}
	if (cll->Search(word))										//cll has that
	{
		my_strcpy(mean2, cll->Search(word)->GetMean(), sizeof(cll->Search(word)->GetMean()));//mean2 copy old infomation
		delete 	cll->Search(word)->GetMean();//delete old mean
		cll->Search(word)->SetMean(mean);	 //set new mean
		a++;												//error count
	}
	if(a == 0)
	{
		delete mean;
		return 1;
	}
	cout << "======== UPDATE ========" << endl; //print
	cout << word << mean2 << "->" << mean << endl;
	cout << "======================" << endl;
	Log << "======== UPDATE ========" << endl;
	Log << word << mean << "->" << mean2 << endl;
	Log << "======================" << endl;
	return 0;
}

void Manager::ERROR(const char *command,int num)
{
	//Error code 
	//LOAD 100
	//ADD 200
	//MOVE 300
	//SAVE 400
	//TEST 500
	//SEARCH 600
	//PRINT 700
	//UPDATE 800
	Log.open("Log.txt", ios::app);						// open log
	if (!(num % 10))									//error print
	{
		cout << "======== ERROR ========" << endl;
		cout << "         " << num << endl;
		cout << "======================" << endl;
		Log << "======== ERROR ========" << endl;
		Log << "         " << num << endl;
		Log << "======================" << endl;
	}
	else if (num == 102)								//success print
	{
		cout << "======== " << command << "========" << endl;
		cout << "         " << "pass" << endl;
		cout << "======================" << endl;
		Log << "======== " << command << "========" << endl;
		Log << "         " << "pass" << endl;
		Log << "======================" << endl;
	}
	else
	{
		cout << "======== " << command << "========" << endl;
		cout << "         " << "success" << endl;
		cout << "======================" << endl;
		Log << "======== " << command << "========" << endl;
		Log << "         " << "success" << endl;
		Log << "======================" << endl;
		
	}
	Log.close();
}

void Manager::my_strcpy(char* a,char *b,int size)//strcpy
{
	int a_size = strnlen(a,100);				//calculate size
	while(a_size != 0)							//delete a's sentence
	{
		*(a+a_size-1) = '\0';
		a_size--;
	}
	for(int i=0; i<size;i++)
		*(a + i) = *(b + i);					//a copy b
}

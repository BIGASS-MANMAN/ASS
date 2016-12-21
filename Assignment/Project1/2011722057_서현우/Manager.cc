#include "/usr/local/Auto_Scoring_System/src/signal.h"
#include "Manager.h"


Manager::Manager()//Initialization of variables
{
	cll = new CircularLinkedList;
	bst = new AlphabetBST;
	queue = new Queue;
	word='\0';
	mean='\0';
	order='\0';
	select='\0';
}


Manager::~Manager()// Frees memory
{ return;

	delete cll;
	delete bst;
	delete queue;
}

void Manager::run(const char * command)// command function
{
	struct sigaction sa;
	set_sigaction(sa);
	alarm(3);

	ifstream fin;
	fin.open(command);// open txt file // file name command
	if(fin.fail())
		return;
	char str[256][256];// declarations array using command
	int i=0;
	while(1)
	{
		fin.getline(str[i],256);
		if(strcmp(str[i],"")==0)
			break;
		i++;
	}
	str[i][0]=0;
	fin.close();
	ofstream log;
	log.open("log.txt", ios::app);
	if(log.fail())
		return;
	for(int j=0;j<i;j++)// Repeat number of txt file's line
	{
		char arr[3][256];
		strcpy(arr[0],strtok(str[j],"\r"));
		
		strcpy(arr[0],strtok(arr[0]," "));

		
		if(strcmp(arr[0],"LOAD")==0)// command is LOAD
		{
			if(LOAD()==0)//Call LOAD  if return value is 0
			{
				cout<<"======== ERROR ========"<<endl<<"100"<<endl<<"======================="<<endl;
				log<<"======== ERROR ========"<<endl<<"100"<<endl<<"======================="<<endl;
			}
			
			else//if return value is 0
			{
				cout<<"======== LOAD ========"<<endl<<"SUCCESS"<<endl<<"======================="<<endl;
				log<<"======== LOAD ========"<<endl<<"SUCCESS"<<endl<<"======================="<<endl;
			}
			
		}
		else if(strcmp(arr[0],"ADD")==0)// command is ADD
		{
			if(ADD()==0)//Call ADD  if return value is 0
			{
				cout<<"======== ERROR ========"<<endl<<"200"<<endl<<"======================="<<endl;
				log<<"======== ERROR ========"<<endl<<"200"<<endl<<"======================="<<endl;
			}
			else// if return value is 1
			{
				cout<<"========= ADD ========="<<endl<<"SUCCESS"<<endl<<"======================="<<endl;
				log<<"========= ADD ========="<<endl<<"SUCCESS"<<endl<<"======================="<<endl;
			}
		
			
		}
		else if(strcmp(arr[0],"MOVE")==0)// command is MOVE
		{
			int select=0;
			strcpy(arr[1],strtok(NULL," "));
			int num=atoi(arr[1]);// change array's number use atoi function
			for(int i=0;i<num;i++)// Repeat number of value num
			{
				if(MOVE() == 0)//Call MOVE  if return value is 0
				{
					cout<<"======== ERROR ========"<<endl<<"300"<<endl<<"======================="<<endl;
					log<<"======== ERROR ========"<<endl<<"300"<<endl<<"======================="<<endl;
					select=1;
					break;	
				}
		
			}
			if(select==1)
				continue;
			cout<<"======== MOVE ========"<<endl<<"SUCCESS"<<endl<<"======================="<<endl;
			log<<"======== MOVE ========"<<endl<<"SUCCESS"<<endl<<"======================="<<endl;
		
		}
		else if(strcmp(arr[0], "SAVE")==0)//command is SAVE
		{
			if(SAVE()==0)//Call SAVE  if return value is 0
			{
				cout<<"======== ERROR ========"<<endl<<"400"<<endl<<"======================="<<endl;
				log<<"======== ERROR ========"<<endl<<"400"<<endl<<"======================="<<endl;
			}
			else// if return value is 1
			{
				cout<<"======== SAVE ========"<<endl<<"SUCCESS"<<endl<<"======================="<<endl;
				log<<"======== SAVE ========"<<endl<<"SUCCESS"<<endl<<"======================="<<endl;
			}
		
		
		}
		else if(strcmp(arr[0], "TEST")==0)// command is TEST
		{
			strcpy(arr[1],strtok(NULL," "));
			strcpy(arr[2],strtok(NULL," "));
			for(int i=0;i<strlen(arr[1]);i++)
			{
				if(arr[1][i]>=65 && arr[1][i]<=90)
					arr[1][i]=arr[1][i]+32;
			}
			word=arr[1];
			mean=arr[2];
			if(TEST()==0)//Call TEST  if return value is 0
			{
				cout<<"======== ERROR ========"<<endl<<"500"<<endl<<"======================="<<endl;
				log<<"======== ERROR ========"<<endl<<"500"<<endl<<"======================="<<endl;
			}
			else// if return value is 1
			{
				cout<<"======== TEST ========"<<endl<<"PASS"<<endl<<"======================="<<endl;
				log<<"======== TEST ========"<<endl<<"PASS"<<endl<<"======================="<<endl;
			}
		
		
		}
		else if(strcmp(arr[0], "SEARCH")==0)//command is SEARCH
		{
			strcpy(arr[1],strtok(NULL," "));
			word=arr[1];
			if(SEARCH()==0)//Call SEARCH  if return value is 0
			{
				cout<<"======== ERROR ========"<<endl<<"600"<<endl<<"======================="<<endl;
				log<<"======== ERROR ========"<<endl<<"600"<<endl<<"======================="<<endl;
			}
		
		
		}
		else if(strcmp(arr[0], "PRINT")==0)// command is PRINT
		{
			int k=1;
			char* ptr;
			while(ptr = strtok(NULL," "))
			{
				strcpy(arr[k],ptr);
				k++;
			}
			select= arr[1];
			order=arr[2];
			if(PRINT()==0)//Call PRINT  if return value is 0
			{
				cout<<"======== ERROR ========"<<endl<<"700"<<endl<<"======================="<<endl;
				log<<"======== ERROR ========"<<endl<<"700"<<endl<<"======================="<<endl;
			}
			else
			{}
		}
		else if(strcmp(arr[0], "UPDATE")==0)//command is UPDATE
		{
			strcpy(arr[1],strtok(NULL," "));
			strcpy(arr[2],strtok(NULL," "));
			for(int i=0;i<strlen(arr[1]);i++)
			{
				if(arr[1][i]>=65 && arr[1][i]<=90)
					arr[1][i]=arr[1][i]+32;
			}
			word=arr[1];
			mean=arr[2];
			if(UPDATE()==0)//Call UPDATE  if return value is 0
			{
				cout<<"======== ERROR ========"<<endl<<"800"<<endl<<"======================="<<endl;
				log<<"======== ERROR ========"<<endl<<"800"<<endl<<"======================="<<endl;
			}
			else//if return value is 1
			{}
		}
		else if(strcmp(arr[0], "EXIT")==0)//command is EXIT
		{
			log.close();
			return;// EXIT program
		}
		else
		{
		
		}
	}
}

bool Manager::LOAD()
{
	ifstream memorize,memorizing, memorized;
	memorize.open("to_memorize_word.txt");// file open for load queue
	//QUEUE LOAD
	char str[1000][256], str2[100][256], str3[1000][256];
	char* word,*mean;
	int i=0;
	if(memorize.fail())
		return 0;
	while(1)
	{
		memorize.getline(str[i],256);
		if(strcmp(str[i],"")==0)
			break;
		i++;
		if(i==1000)
			break;
	}
	str[i][0]=0;
	for(int j =0;j<i;j++)
	{
		word=strtok(str[j],"	");
		mean=strtok(NULL,"	");
		WordNode* node=new WordNode;
		if(word !=NULL)
		{
			if(queue->Search(word)==NULL)// queue is empty
			{
				node->SetWord(word);
				node->SetMean(mean);
				queue->Push(node);
			}
			else if(word==queue->Search(word)->GetWord())// queue don't have input word
			{
				continue;
			}
			else// queue has input word
			{
				return 0;
			}
		}
	}
	memorize.close();
	// BST LOAD
	memorizing.open("memorizing_word.txt");
	if(memorizing.fail())
		return 0;
	i=0;
	while(1)
	{
		memorizing.getline(str2[i],256);
		if(strcmp(str2[i],"")==0)
			break;
		i++;
	}
	str2[i][0]=0;
	for(int j=0;j<i;j++)
	{
		word=strtok(str2[j],"	");
		mean=strtok(NULL,"	");
		WordNode* node = new WordNode;
		if(word!=NULL)
		{
			char first=0;
			if(word[0]>96 && word[0]<123)//if word's first alphabet is not capital change alphabet to capital
			first=word[0]-32;
			if(bst->Search(first)->GetBST()->Search(word)==NULL)//BST is empty
			{
				node->SetWord(word);
				node->SetMean(mean);
				if(bst->WordCnt<100)
				{
					bst->Search(first)->GetBST()->Insert(node);
					bst->WordCnt++;
				}
				else
					return 0;
			}
			else if(strcmp(word, bst->Search(first)->GetBST()->Search(word)->GetWord())==0)//BST don't have input word
			{
				continue;
			}
			else//BST has input word
			{
				return 0;
			}
		}
	}
	memorizing.close();
	//CLL LOAD
	memorized.open("memorized_word.txt");
	if(memorized.fail())
		return 0;
	i=0;
	while(1)
	{
		memorized.getline(str3[i],256);
		if(strcmp(str3[i],"")==0)
			break;
		i++;
	}
	str3[i][0]=0;
	for(int j=0;j<i;j++)
	{
		word=strtok(str3[j],"	");
		mean=strtok(NULL,"	");
		WordNode* node=new WordNode;
		if(word!=NULL)
		{
			if(cll->Search(word)==NULL)//CLL is empty
			{
				node->SetWord(word);
				node->SetMean(mean);
				cll->Insert(node);
			}
			else if(strcmp(word,cll->Search(word)->GetWord())==0)//CLL don't have input node's word
			{
				continue;
			}
			else//CLL has input node's word
			{
				return 0;
			}
		}
	}
	memorized.close();
	return 1;
}
bool Manager::ADD()// Move from word txt file to queue
{
	ifstream fin;
	fin.open("word.txt");
	if(fin.fail())
		return 0;
	char str[100][256]={0,};
	char* word,*mean;
	int i=0;
	while(1)
	{
		fin.getline(str[i],256);
		if(strcmp(str[i],"")==0)
			break;
		i++;
	}
	str[i][0]=0;
	fin.close();
	for(int j=0;j<i;j++)
	{
		word=strtok(str[j],"	");
		mean=strtok(NULL,"	");
		for(int k=0;k<strlen(word);k++)// if word have capital alphabet, change the small letter
		{
			if(word[k]>=65&&word[k]<=90)
				word[k]=word[k]+32;
		}
		WordNode* node=new WordNode;
		if(word!=NULL)
		{
			char first=0;
			if(word[0]>96 && word[0]<123)//if word's first alphabet is not capital change alphabet to capital
			first=word[0]-32;
			if(queue->Search(word)==NULL && bst->Search(first)->GetBST()->Search(word)==NULL && cll->Search(word)==NULL)// Queue don't have input node's word and BST don't have input node's word and CLL don't have input node's word
			{
				node->SetWord(word);
				node->SetMean(mean);
				queue->Push(node);
			}
			else if(queue->Search(word)==NULL || strcmp(word,queue->Search(word)->GetWord())==0 )// Searching queue return node is empty or Inserting node's word is not same returning node's word
			{
continue;
			}
			else
			{
			}
		}

	}
	return 1;
}
bool Manager::MOVE()
{
	WordNode* node=queue->Pop();
	char* arr=NULL;
	char first=0;
	if(node!=NULL)
	{
		arr=node->GetWord();
		if(arr[0]>96 && arr[0]<123)//if word's first alphabet is not capital, change alphabet to capital
			first=arr[0]-32;
	}
if(bst!=NULL && bst->Search(first)!=NULL)
{
	if(bst->Search(first)->GetBST()->Search(arr)==NULL)// if BST don't have node's word, move from queue to BST
	{
		
		if(bst->WordCnt<100)//if BST's word count < 100
		{
			bst->Search(first)->GetBST()->Insert(node);// insert BST
			bst->WordCnt++;
		}
		else// BST's word count >100 return error
			return 0;
		return 1;
	}
	else if(strcmp(node->GetWord(), bst->Search(first)->GetBST()->Search(arr)->GetWord())!=0)// queue's node's word is not same Searching node's word
	{
		if(bst->WordCnt<100)
		{
			bst->Search(first)->GetBST()->Insert(node);
			bst->WordCnt++;
		}
		else
			return 0;
		return 1;
	}
	else
	{
		return 0;
	}
}
}
bool Manager::SAVE()//Save function
{
	if(queue->Save()==1 && bst->Save() && cll->Save()==1)// call queue, bst, cll's function, if functions must return 1, this function return 1
		return 1;
	else
		return 0;
}
bool Manager::TEST()//TEST function BST's node move to CLL
{
	char first=0;
	if(word[0]>96 && word[0]<123)//if word's first alphabet is not capital change alphabet to capital
		first=word[0]-32;
	for(int i=0;i<strlen(word);i++)// if word have capital alphabet, change the small letter
	{
		if(word[i]>=65&&word[i]<=90)
			word[i]=word[i]+32;
	}
	
	WordNode* test=bst->Search(first)->GetBST()->Search(word);
	if(test!=NULL)// if find in the bst
	{
		if(strcmp(test->GetMean(), mean)==0)// test node's mean is same input node's mean
		{
			if(cll->Search(word)==NULL)// if cll don't have word
			{
				cll->Insert(test);// In CLL insert test node
				bst->Search(first)->GetBST()->Delete(word);// In BST delete node
				bst->WordCnt--;// bst's word count down
				return 1;
			}
			else//if CLL has word;
			{
				return 0;
			}
		}
		else// if test node's mean is not same inpujt node's mean
		{
			return 0;
		}
	}
	else// if don't find in the bst
	{
		return 0;
	}
}
bool Manager::SEARCH()//search function
{
	WordNode* node=queue->Search(word);
	ofstream log;
	log.open("log.txt", ios::app);
	if(log.fail())
		return 0;
	if(node!=NULL)// find word in queue
	{
		cout<<"======== SEARCH ========"<<endl<<node->GetWord()<<" "<<node->GetMean()<<endl<<"======================="<<endl;
		log<<"======== SEARCH ========"<<endl<<node->GetWord()<<" "<<node->GetMean()<<endl<<"======================="<<endl;
		log.close();
		return 1;	
	}
	else//find word
	{
		char first=0;
		if(word[0]>96 && word[0]<123)//if word's first alphabet is not capital change alphabet to capital
			first=word[0]-32;
			for(int i=0;i<strlen(word);i++)// if word have capital alphabet, change the small letter
		{
		if(word[i]>=65&&word[i]<=90)
			word[i]=word[i]+32;
		}
		node=bst->Search(first)->GetBST()->Search(word);//call word BST's search function
		if(node!=NULL)//find word in BST
		{
			cout<<"======== SEARCH ========"<<endl<<node->GetWord()<<" "<<node->GetMean()<<endl<<"======================="<<endl;
			log<<"======== SEARCH ========"<<endl<<node->GetWord()<<" "<<node->GetMean()<<endl<<"======================="<<endl;
			log.close();
			return 1;
		}
		else//find word in CLL
		{
			node=cll->Search(word);// call CLL's search function
			if(node!=NULL)
			{
				cout<<"======== SEARCH ========"<<endl<<node->GetWord()<<" "<<node->GetMean()<<endl<<"======================="<<endl;
				log<<"======== SEARCH ========"<<endl<<node->GetWord()<<" "<<node->GetMean()<<endl<<"======================="<<endl;
				log.close();
				return 1;
			}
			else
			{
				log.close();
				return 0;
			}
		}
	}
}
bool Manager::PRINT()//print function
{
	if(strcmp(select, "TO_MEMORIZE")==0)// queue print
	{
		if(queue->Print()==0)//call queue's print function
			return 0;
		else
			return 1;
	}
	else if(strcmp(select, "MEMORIZING")==0)//BST print
	{
		if(bst->Print(order)==0)//call bst's print function
			return 0;
		else
			return 1;
	}
	else if(strcmp(select, "MEMORIZED")==0)//CLL print
	{
		if(cll->Print()==0)//call CLL's print function
			return 0;
		else
			return 1;
	}
	else
		return 0;
		
	
}
bool Manager::UPDATE()//UODATE FUNCTION
{
	WordNode* node=queue->Search(word);
	ofstream log;
	log.open("log.txt", ios::app);
	if(log.fail())
		return 0;

	for(int i=0;i<strlen(word);i++)// if word have capital alphabet, change the small letter
	{
		if(word[i]>=65&&word[i]<=90)
			word[i]=word[i]+32;
	}
	if(node!=NULL)//if don't find word
	{
		char* x_mean=node->GetMean();
		node->SetWord(word);
		node->SetMean(mean);
		cout<<"======== UPDATE ========"<<endl<<node->GetWord()<<" "<<x_mean<<" -> "<< node->GetMean()<<endl<<"======================="<<endl;//if worde ==0 return faole
		log<<"======== UPDATE ========"<<endl<<node->GetWord()<<" "<<x_mean<<" -> "<< node->GetMean()<<endl<<"======================="<<endl;
		return 1;
	}
	else// if find word
	{
		char first=0;
		if(word[0]>96 && word[0]<123)//if word's first alphabet is not capital change alphabet to capital
			first=word[0]-32;
		node=bst->Search(first)->GetBST()->Search(word);//find BST's word node
		if(node!=NULL)
		{
			char* x_mean=node->GetMean();
			node->SetWord(word);
			node->SetMean(mean);
			cout<<"======== UPDATE ========"<<endl<<node->GetWord()<<" "<<x_mean<<" -> "<< node->GetMean()<<endl<<"======================="<<endl;
			log<<"======== UPDATE ========"<<endl<<node->GetWord()<<" "<<x_mean<<" -> "<< node->GetMean()<<endl<<"======================="<<endl;
			return 1;
		}
		else //if don't fine word
		{
			node=cll->Search(word);
			if(node!=NULL)
			{
				char* x_mean=node->GetMean();
				node->SetWord(word);
				node->SetMean(mean);
				cout<<"======== UPDATE ========"<<endl<<node->GetWord()<<" "<<x_mean<<" -> "<< node->GetMean()<<endl<<"======================="<<endl;
				log<<"======== UPDATE ========"<<endl<<node->GetWord()<<" "<<x_mean<<" -> "<< node->GetMean()<<endl<<"======================="<<endl;
				return 1;
			}
			else
				return 0;
		}
	}
}

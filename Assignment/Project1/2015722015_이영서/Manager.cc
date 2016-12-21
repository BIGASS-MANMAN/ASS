#include "/usr/local/Auto_Scoring_System/src/signal.h"
#include "Manager.h"
#include <cstring>
#include <stdlib.h>


Manager::Manager()
{
	cll = new CircularLinkedList;
	bst = new AlphabetBST;
	queue = new Queue;
	arg1=NULL;
	arg2=NULL;
}
Manager::~Manager()
{ return;

	delete cll;
	delete bst;
	delete queue;
	delete arg1;
	delete arg2;
}
void Manager::run(const char * command)
{
	struct sigaction sa;
	set_sigaction(sa);
	alarm(3);

	char** ins;
	int i=0,n=0;
	char* str=NULL;
	char* menu=NULL;
	char* context=NULL;

	ifstream fin;
	fin.open(command);
	if(!fin){
		exit(1);
	}//if there is not text file, the program will be ended

	ins=new char*[50];

	while(!fin.eof()){
		ins[i]=new char[50];
		fin.getline(ins[i],50);
		str=strtok_r(ins[i]," ",&context);	//tokenizing sentence
		menu=str;
		while(str!=NULL){
			str=strtok_r(NULL," ",&context);
			if(str==NULL)	//there is no token
				break;
			if(n==0){
				arg1=str;
			}
			if(n==1){
				arg2=str;
			}
			n++;
		}
		getins(menu);	//execute menu
		i++;
		n=0;
		menu=NULL;
		arg1=NULL;
		arg2=NULL;
		context=NULL;
		
	}
}
void Manager::getins(char* command)
{
	bool current=NULL;
	int n=0;

	if(!strcmp(command,"LOAD")){
		current=LOAD();
		n=100;
	}
	else if(!strcmp(command,"ADD")){
		current=ADD();
		n=200;
	}
	else if(!strcmp(command,"MOVE")){
		current=MOVE();
		n=300;
	}
	else if(!strcmp(command,"SAVE")){
		current=SAVE();
		n=400;
	}
	else if(!strcmp(command,"TEST")){
		current=TEST();
		n=500;
	}
	else if(!strcmp(command,"SEARCH")){
		current=SEARCH();
		n=600;
	}
	else if(!strcmp(command,"PRINT")){
		current=PRINT();
		n=700;
	}
	else if(!strcmp(command,"UPDATE")){
		current=UPDATE();
		n=800;
	}
	else if(!strcmp(command,"EXIT"))
		EXIT();
	
	ofstream fout;
	fout.open("log.txt",ios::app);

	if(current==true){
		if(!strcmp(command,"LOAD") || !strcmp(command,"ADD") || !strcmp(command,"MOVE") || !strcmp(command,"SAVE"))
		{
			cout<<"======== "<<command<<" ========"<<endl<<"Success"<<endl<<"====================="<<endl;
			fout<<"======== "<<command<<" ========"<<endl<<"Success"<<endl<<"====================="<<endl;
		}
	}
	else	//print error
	{
		cout<<"======== ERROR ========"<<endl<<n<<endl<<"======================="<<endl;
		fout<<"======== ERROR ========"<<endl<<n<<endl<<"======================="<<endl;
	}
	cout<<endl;
	fout<<endl;

	fout.close();
}

bool Manager::LOAD()
{
	ifstream fin1;
	fin1.open("to_memorize_word.txt");
	ifstream fin2;
	fin2.open("memorizing_word.txt");
	ifstream fin3;
	fin3.open("memorized_word.txt");

	if(fin1==0 && fin2==0 && fin3==0)//the files doesn't exist
		return false;
	if(arg1!=NULL || arg2!=NULL)//there are parameters
		return false;
	if(queue->GetHead()!=NULL || bst->GetWordCnt()!=0 || cll->GetHead()!=NULL)
		return false;//data already exists in data structures
	
	int i=0,e=0;
	char**word=new char*[500];
	char**mean=new char*[500];

	WordNode* node;

		
	/////////Reading MEMORIZE//////////////
	if(fin1){
		while(!fin1.eof()){
			word[i]=new char[30];
			fin1>>word[i];

			//checking linefeed
			if(word[i][0]==0)
				break;

			if(queue->Search(word[i])!=NULL)//the word exists in queue
				return false;
			mean[i]=new char[30];
			fin1>>mean[i];

			node=new WordNode();
			node->SetWord(word[i]);
			node->SetMean(mean[i]);

			queue->Push(node);
			i++;
		}
	}
	
	fin1.close();

	//////////Reading MEMORIZING//////////
	if(fin2)
	{
		while(!fin2.eof()){
			word[i]=new char[30];
			fin2>>word[i];

			//checking linefeed
			if(word[i][0]==0)
				break;

			if(bst->Search(word[i][0])->GetBST()->Search(word[i])!=NULL)//the word exists in bst
				return false;
			mean[i]=new char[30];
			fin2>>mean[i];
			node=new WordNode();
			node->SetWord(word[i]);
			node->SetMean(mean[i]);
			
			bst->Search(node->GetWord()[0])->GetBST()->Insert(node);	//insert node
			i++;
		}
	}
	fin2.close();

	if(fin3)
	{
		while(!fin3.eof()){
			word[i]=new char[30];
			fin3>>word[i];

			//checking linefeed
			if(word[i][0]==0)
				break;

			if(cll->Search(word[i])!=NULL)//the word exists in circular linked list 
				return false;
			mean[i]=new char[30];
			fin3>>mean[i];

			node=new WordNode();
			node->SetWord(word[i]);
			node->SetMean(mean[i]);
	
			cll->Insert(node);
			i++;
		}
	}
	fin3.close();

	return true;
}
bool Manager::ADD()
{
	char**word=new char*[300];
	char**mean=new char*[300];
	ifstream fin;
	fin.open("word.txt");

	int i=0;
	WordNode* node;
	while(!fin.eof()){
		word[i]=new char[30];
		fin>>word[i];
		if(word[i]==NULL&&i==0)////there are no words
			return false;
		if(queue->Search(word[i])!=NULL && bst->Search(word[i][0])->GetBST()->Search(word[i])!=NULL
			&& cll->Search(word[i])!=NULL)//the word exists in memories
			continue;

		mean[i]=new char[30];
			
		fin>>mean[i];
			
		node=new WordNode();
		node->SetWord(word[i]);
		node->SetMean(mean[i]);
		queue->Push(node);
		i++;
	}
	return true;
}
bool Manager::MOVE()
{
	if(arg1==NULL || arg2!=NULL)//too many parameters or no parameter
		return false;

	int num=atoi(arg1);	//invert char to int

	if(num<1 || num>100)//the integer range should be [1,100]
		return false;

	if(queue->GetHead()==NULL)//there is no word in queue
		return false;

	if(bst->GetWordCnt()+num>100 || queue->GetWordCnt()<num)
		return false;//number of words int bst over 100 and number of words in queue are less than input number

	WordNode* word=NULL;
	WordBST* wordbst=NULL;
	
	for(int i=0; i<num; i++)
	{
		word=queue->Pop();
		word->SetNext(NULL);
		wordbst=bst->Search(word->GetWord()[0])->GetBST();
		
		if(wordbst->Search(word->GetWord())==NULL)//input word is new node
		{
			wordbst->Insert(word);
			bst->SetWordCnt();
		}
		else
			return false;
	}
	return true;
}
bool Manager::SAVE()
{
	if(arg2!=NULL || arg1!=NULL)//too many parameters
		return false;

	/////////Save MEMORIZE//////////////
	if(queue->GetHead()!=NULL){
		queue->Save();
	}
	else
		return false;
	//////////Save MEMORIZING//////////
	if(bst->GetWordCnt()!=0){
		bst->Save();
	}
	else
		return false;
	/////////Save MEMORIZED//////////
	if(cll->GetHead()!=NULL){
		cll->Save();
	}
	else
		return false;

	return true;
}
bool Manager::TEST()
{
	if(arg2==NULL || arg1==NULL)//there are wrong parameters
		return false;

	WordNode* node=bst->Search(arg1[0])->GetBST()->Search(arg1);

	if(node==NULL)//the node is not found in bst
		return false;
	if(strcmp(node->GetMean(),arg2))//mean of node and input mean are not same
		return false;
	if(cll->Search(arg1)!=NULL)//the word exists in circular linked list already 
		return NULL;

	node=bst->Search(arg1[0])->GetBST()->Delete(arg1);
	node->SetLeft(NULL);
	node->SetRight(NULL);

	cll->Insert(node);


	ofstream fout;
	fout.open("log.txt",ios::app);
	
	cout<<"======== TEST ========"<<endl;
	fout<<"======== TEST ========"<<endl;
	cout<<"Pass"<<endl;
	fout<<"Pass"<<endl;
	cout<<"======================"<<endl;
	fout<<"======================"<<endl;

	fout.close();

	return true;
}
bool Manager::SEARCH()
{
	if(arg2!=NULL || arg1==NULL)//there are wrong parameters
		return false;

	WordNode* node=NULL;

	if(queue->Search(arg1)!=NULL)	//node location is queue
		node=queue->Search(arg1);
	else if(bst->Search(arg1[0])->GetBST()->Search(arg1)!=NULL)	//node location is bst
		node=bst->Search(arg1[0])->GetBST()->Search(arg1);
	else if(cll->Search(arg1)!=NULL)	//node location is cll
		node=cll->Search(arg1);
	else
		return false;

	ofstream fout;
	fout.open("log.txt",ios::app);

	cout<<"======== SEARCH ========"<<endl;
	fout<<"======== SEARCH ========"<<endl;
	cout<<arg1<<" "<<node->GetMean()<<endl;
	fout<<arg1<<" "<<node->GetMean()<<endl;
	cout<<"========================"<<endl;
	fout<<"========================"<<endl;

	fout.close();

	return true;
}
bool Manager::PRINT()
{
	bool check;

	if(arg1==NULL)//parameters are not enough
		return false;

	if(!strcmp(arg1,"TO_MEMORIZE"))	//print queue
	{
		if(arg2!=NULL)
			return false;
		check=queue->Print();
		if(check==false)	//disable
			return false;
	}

	else if(!strcmp(arg1,"MEMORIZING"))	//print bst
	{
		if(arg2==NULL)
			return false;
		check=bst->Print(arg2);
		if(check==false)	//disable
			return false;
	}

	else if(!strcmp(arg1,"MEMORIZED"))	//print cll
	{
		if(arg2!=NULL)
			return false;
		check=cll->Print();
		if(check==false)	//disable
			return false;
	}
	else
		return false;

	return true;
}
bool Manager::UPDATE()
{
	if(arg2==NULL || arg1==NULL)//parameters are not enough
		return false;

	if(queue->GetHead()==NULL && bst->GetWordCnt()==0 && cll->GetHead()==NULL)
		return false;//data doesn't exist in data structures
	
	WordNode* node=NULL;
	char* mean=NULL;

	if(queue->Search(arg1)!=NULL)	//searching queue
	{
		node=queue->Search(arg1);
		mean=node->GetMean();
		node->SetMean(arg2);
	}
	else if(bst->Search(arg1[0])->GetBST()->Search(arg1)!=NULL)	//searching bst
	{
		node=bst->Search(arg1[0])->GetBST()->Search(arg1);
		mean=node->GetMean();
		node->SetMean(arg2);
	}
	else if(cll->Search(arg1)!=NULL)	//searching cll
	{
		node=cll->Search(arg1);
		mean=node->GetMean();
		node->SetMean(arg2);
	}
	else
		return false;

	ofstream fout;
	fout.open("log.txt",ios::app);

	cout<<"======== UPDATE ========"<<endl;
	fout<<"======== UPDATE ========"<<endl;
	cout<<arg1<<" "<<mean<<" -> "<<node->GetMean()<<endl;
	fout<<arg1<<" "<<mean<<" -> "<<node->GetMean()<<endl;
	cout<<"========================"<<endl;
	fout<<"========================"<<endl;

	fout.close();

	return true;
}

void Manager::EXIT()
{
	exit(100);
}

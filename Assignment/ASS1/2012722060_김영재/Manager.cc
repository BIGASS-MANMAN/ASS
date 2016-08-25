#include "Manager.h"

void segfault_sigaction(int signal, siginfo_t *si, void *arg);

Manager::Manager()
{
	Q = new Queue;
	CQ = new CircularQueue;
	ALPTREE = new ALP_BST;
	
	MemorizingCount = 0;
}

Word* Manager::MakeNode(char* str)
{
    char word[32];
    char mean[32];
    char* token = NULL;
    WORD_BST* BSTCUR = NULL;

    memset(word, 0, 32);
    memset(mean, 0, 32);

    str[strlen(str)-1] = 0;

    token = strtok(str,"\t");
    strcpy(word, token);
    token = strtok(NULL, "\t");
    strcpy(mean, token);

    if(Q->Search(word) != NULL || CQ->Search(word) != NULL)
    {
//	cout<<"Already Word is exist"<<endl;
	return NULL;
    }
    if(ALPTREE->Search(word[0]) != NULL)
    {
	BSTCUR = ALPTREE->Search(word[0])->getBST();
	if(BSTCUR->Search(word) != NULL)
	{
//	    cout<<"Already Word is exist"<<endl;
	    return NULL;
	}
    }

    Word* pNew = new Word;

    pNew->setWord(word);
    pNew->setMean(mean);

    return pNew;
}
Alphabet* Manager::MakeNode2(char alp)
{
    Alphabet* pNew = new Alphabet;
    pNew->setAlp(alp);
    return pNew;
}

int Manager::InsertAlp(char* str)
{
    int i;
    for(i = 0; i<strlen(str); i++)
    {
	ALPTREE->Insert(MakeNode2(str[i]));
    }
    return 0;
}

int Manager::InsertWord(Word* Node)
{
    Alphabet* pCur = NULL;
    WORD_BST* BSTCur = NULL;

    
    pCur = ALPTREE->Search((Node->getWord())[0]);
    BSTCur = pCur->getBST();
    BSTCur->Insert(Node);

    return 0;
}

int Manager::InputFileOpen(char* file)
{
    //m_fin.open(file);
    m_fin=fopen(file,"r");

    //if(m_fin.fail())
    if(m_fin==NULL)
	return -1;

    return 0;
}

int Manager::InputFileOpen2(char* file)
{
    m_fin2=fopen(file,"r");

    if(m_fin2==NULL)
	return -1;

    return 0;
}

int Manager::OutputFileOpen(char* file)
{
    //m_fout.open(file);
    m_fout=fopen(file,"w");

    //if(m_fout.fail())
    if(m_fout==NULL)
	return -1;

    return 0;
}

int Manager::COMMAND(char* file)
{
    //////////////////////////////////////////////////////
    struct sigaction sa;                                //
    memset(&sa, 0, sizeof(struct sigaction));           //
    sigemptyset(&sa.sa_mask);                           //
    sa.sa_sigaction = segfault_sigaction;               //
    sa.sa_flags = SA_SIGINFO;                           //
    sigaction(SIGSEGV, &sa, NULL);                      //
    sigaction(SIGALRM, &sa, NULL);                      //
    alarm(50);                                          //
    //////////////////////////////////////////////////////

    char CommandLine[32];
    char Command[32];
    char Option1[32];
    char Option2[32];
    char* token = NULL;

    if(InputFileOpen2(file) == -1)
	return -1;


    //while(1)
    while(fgets(CommandLine,sizeof(CommandLine),m_fin2))
    {
	CommandLine[strlen(CommandLine)-1]=0;
	memset(Command,0,32);
	memset(Option1,0,32);
	memset(Option2,0,32);
	token = NULL;

	//cout<<"======================================="<<endl;
	//cout<<"Input Command"<<endl;
	//cin.getline(CommandLine,32);
	token = strtok(CommandLine," ");
	strcpy(Command, token);

	if(strcmp(Command,"LOAD") == 0)
	{
	    token = strtok(NULL," ");
	    if(token == NULL)
	    {
		LOAD();
	    }
	    else
	    {
		strcpy(Option1,token);
		LOAD(Option1);
	    }
	}
	else if(strcmp(Command, "SAVE") == 0)
	{
	    SAVE();
	}
	else if(strcmp(Command, "MEMORIZE") == 0)
	{
	    //cout<<"==================================="<<endl;
	    cout<<"MEMORIZE"<<endl;
	    token = strtok(NULL, " ");
	    strcpy(Option1, token);
	    token = strtok(NULL, " ");
	    strcpy(Option2, token);

	    MEMORIZE(Option1, Option2);
	}
	else if(strcmp(Command, "SEARCH") == 0)
	{
	    token = strtok(NULL, " ");
	    strcpy(Option1,token);

	    SEARCH(Option1);
	}
	else if(strcmp(Command, "TRAVERSAL") == 0)
	{
	    //cout<<"==================================="<<endl;
	    cout<<"TRAVERSAL"<<endl;
	    token = strtok(NULL, " ");
	    strcpy(Option1, token);

	    TRAVERSAL(token);
	}
	else if(strcmp(Command, "UPDATE") == 0)
	{
	    token = strtok(NULL, " ");
	    strcpy(Option1, token);
	    token = strtok(NULL, " ");
	    strcpy(Option2, token);

	    UPDATE(Option1, Option2);
	}
	else if(strcmp(Command, "EXIT") == 0)
	{
	    return 0;	
	}
	else
	{
	    cout<<"Incorrect syntax"<<endl;
	}
	continue;
    }
}

int Manager::LOAD()
{
    char file[128];
    char sentence[128];
    Word* pCur = NULL;

    memset(file,0,128);
    memset(sentence,0,128);

    strcpy(file,"memorized_words.txt");
    InputFileOpen(file);

    while(fgets(sentence,sizeof(sentence),m_fin))
    {
	//sentence[strlen(sentence)-1]=0;
	if((pCur = MakeNode(sentence)) != NULL)
	    CQ->Push(pCur);
    }
    fclose(m_fin);

    strcpy(file,"memorizing_words.txt");
    InputFileOpen(file);

    while(fgets(sentence,sizeof(sentence),m_fin))
    {
	sentence[strlen(sentence)-1]=0;
	if((pCur = MakeNode(sentence)) != NULL)
	    InsertWord(pCur);
    }
    fclose(m_fin);

    strcpy(file,"to_memorize_words.txt");
    InputFileOpen(file);

    while(fgets(sentence,sizeof(sentence),m_fin))
    {
	sentence[strlen(sentence)-1]=0;
	if((pCur = MakeNode(sentence)) != NULL)
	    Q->Push(pCur);
    }
    fclose(m_fin);

    return 0;
}

int Manager::LOAD(char* file)
{
    char sentence[128];
    Word* pCur = NULL;
    memset(sentence,0,128);

    InputFileOpen(file);
    while(fgets(sentence,sizeof(sentence),m_fin))
    {
	sentence[strlen(sentence)-1]=0;
//	cout<<"CURRENT SENTENCE IN LOAD FILE:"<<sentence<<endl;
	
	if((pCur = MakeNode(sentence)) == NULL)
	    continue;
	if(MemorizingCount >= 100)
	{
	    Q->Push(pCur);
	}
	else
	{
	    InsertWord(pCur);
	    MemorizingCount++;
	}
    }
    fclose(m_fin);
    return 0;
}

int Manager::SAVE()
{
    char file[128];
    char sentence[128];
    Word* pCur = NULL;

    memset(file,0,128);
    memset(sentence,0,128);

    strcpy(file,"memorized_words.txt");
    OutputFileOpen(file);


    pCur = CQ->getHead();
    while(pCur)
    {
	strcpy(sentence, pCur->getWord());
	strcat(sentence, "\t");
	strcat(sentence, pCur->getMean());
	strcat(sentence, "\n");
	fputs(sentence, m_fout);

	memset(sentence,0,128);
	pCur = pCur->getNext();
	if(pCur == CQ->getHead())
	    break;
    }
    fclose(m_fout);

    strcpy(file,"memorizing_words.txt");
    OutputFileOpen(file);

    PreTraversal(ALPTREE->getRoot());
    fclose(m_fout);

    strcpy(file,"to_memorize_words.txt");
    OutputFileOpen(file);

    pCur = Q->getHead();
    while(pCur)
    {
	strcpy(sentence, pCur->getWord());
	strcat(sentence, "\t");
	strcat(sentence, pCur->getMean());
	strcat(sentence, "\n");
	fputs(sentence, m_fout);

	memset(sentence,0,128);
	pCur = pCur->getNext();
    }
    fclose(m_fout);

    return 0;

    
}

int Manager::MEMORIZE(char* word, char* mean)
{
    Alphabet* pCur = NULL;
    WORD_BST* BSTCur = NULL;
    Word* WordCur = NULL;

    //If No word(No alphabet)
    if((pCur = ALPTREE->Search(word[0])) == NULL)
    {
	cout<<"No exist word"<<endl;
	return -1;
    }

    BSTCur = pCur->getBST();

    //If no word in Word BST
    if((WordCur = BSTCur->Search(word)) == NULL)
    {
	cout<<"No exist word"<<endl;
	return -1;
    }

    if(strcmp(WordCur->getMean(),mean) == 0)
    {
	BSTCur->Pop(word);
	CQ->Push(WordCur);
	if((WordCur = Q->Pop()) != NULL)
	{
	    InsertWord(WordCur);
	}

	return 0;
    }
    else
    {
	cout<<"Incorrect mean"<<endl;
	return -1;
    }
}

int Manager::SEARCH(char* word)
{
    Alphabet* pCur = NULL;
    WORD_BST* BSTCur = NULL;
    Word* WordCur = NULL;

    if((pCur = ALPTREE->Search(word[0])) != NULL)
    {
	BSTCur = pCur->getBST();
	if((WordCur = BSTCur->Search(word)) != NULL)
	{
	    cout<<WordCur->getWord()<<" : "<<WordCur->getMean()<<endl;
	    return 0;
	}
	else
	{}
    }
    if((WordCur = Q->Search(word)) != NULL)
    {
	cout<<WordCur->getWord()<<" : "<<WordCur->getMean()<<endl;
	return 0;
    }
    else if((WordCur = CQ->Search(word)) != NULL)
    {
	cout<<WordCur->getWord()<<" : "<<WordCur->getMean()<<endl;
	return 0;
    }
    else
    {
	cout<<"No exist word"<<endl;
	return -1;
    }
}

void Manager::PreTraversal(Alphabet* Node)
{
    WORD_BST* WB;

    if(Node == NULL)
	return;

    WB = Node->getBST();
    WB->PreTraversal(WB->getRoot(),m_fout);
    PreTraversal(Node->getLeft());
    PreTraversal(Node->getRight());
}

void Manager::TRAVERSAL(char* command)
{
    Word* WordCur = NULL;

    if(strcmp(command,"1") == 0)
    {
	cout<<"TRAVERSAL 1"<<endl;
	WordCur = CQ->getHead();
	while(WordCur)
	{
	    cout<<WordCur->getWord()<<" : "<<WordCur->getMean()<<endl;
	    WordCur = WordCur->getNext();
	    if(WordCur == CQ->getHead())
		break;
	}
	return;
    }
    else if(strcmp(command,"2") == 0)
    {
	cout<<"TRAVERSAL 2"<<endl;
	SubTraversal(ALPTREE->getRoot());
	return;
    }
    else
    {
	cout<<"Incorrect command"<<endl;
	return;
    }

}
void Manager::SubTraversal(Alphabet* Node)
{
    WORD_BST* WB;

    if(Node == NULL)
	return;

    SubTraversal(Node->getLeft());
    WB = Node->getBST();
    WB->Traversal(WB->getRoot());
    SubTraversal(Node->getRight());
}


int Manager::UPDATE(char* word, char* mean)
{
    Alphabet* pCur = NULL;
    WORD_BST* BSTCur = NULL;
    Word* WordCur = NULL;

    if((pCur = ALPTREE->Search(word[0])) != NULL)
    {
	BSTCur = pCur->getBST();
	//if(BSTCur->Update(word,mean) != NULL)
	if((WordCur = BSTCur->Search(word)) != NULL)
	{
	    WordCur->setMean(mean);
	    cout<<WordCur->getWord()<<" : "<<WordCur->getMean()<<endl;
	    return 0;
	}
	else
	{}
    }
    if((WordCur = Q->Search(word)) != NULL)
    {
	WordCur->setMean(mean);
	cout<<WordCur->getWord()<<" : "<<WordCur->getMean()<<endl;
	return 0;
    }
    else if((WordCur = CQ->Search(word)) != NULL)
    {
	WordCur->setMean(mean);
	cout<<WordCur->getWord()<<" : "<<WordCur->getMean()<<endl;
	return 0;
    }
    else
    {
	cout<<"No exist word"<<endl;
	return -1;
    }
}

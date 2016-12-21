#include "/usr/local/Auto_Scoring_System/src/signal.h"
#include "Manager.h"

Manager::Manager()
{
	//allocate each class
	queue = new Queue;
	bst = new AlphabetBST;
	cll = new CircularLinkedList;
	fileNode = NULL;
}
Manager::~Manager()
{ return;

	//deallocate each class
	if (queue!=NULL)
		delete queue;
	if (bst != NULL)
		delete bst;
	if (cll != NULL)
		delete cll;
	fileNode = NULL;
}
void Manager::run(const char* command)
{
	struct sigaction sa;
	set_sigaction(sa);
	alarm(3);
//run
	bool reFlag = true;
	char fileName[SIZE_32] = {'\0',};
	char Option[SIZE_32] = { '\0', };
	
	//Pasing fild & make file node
	reFlag = File.Parsing_command(command);
	if (reFlag == false)
	{
		return;
	}
	//Untill last file node
	while (!File.Is_empty())
	{
		//file node pop
		fileNode = File.Pop();
		//Which function
		switch (fileNode->GetFunc())
		{
		case D_LOAD:
			reFlag = LOAD();
			// call print format function
			File.Print_Logfile(reFlag, "LOAD", E_LOAD, NULL, NULL);
			break;
		case D_ADD:
			reFlag = ADD();
			File.Print_Logfile(reFlag, "ADD", E_ADD, NULL, NULL);
			break;
		case D_MOVE:
			reFlag = MOVE();
			File.Print_Logfile(reFlag, "MOVE", E_MOVE, NULL, NULL);
			break;
		case D_SAVE:
			reFlag = SAVE();
			File.Print_Logfile(reFlag, "SAVE", E_SAVE, NULL, NULL);
			break;
		case D_TEST:
			reFlag = TEST();
			File.Print_Logfile(reFlag, "TEST", E_TEST, NULL, NULL);
			break;
		case D_SEARCH:
			reFlag = SEARCH();
			break;
		case D_PRINT:
			reFlag = PRINT();
			File.Print_Logfile(reFlag, "PRINT", E_SEARCH, NULL, NULL);
			break;
		case D_UPDATE:
			reFlag = UPDATE();
			break;
		case D_EXIT:
			EXIT();
			delete fileNode;
			return;
		default:
			break;
		}
		delete fileNode;
	}
}
bool Manager::ADD()
{	
	//ADD
	FileClass FileQueue;
	FileClassNode* pFileNode = NULL;
	WordNode* pNew = NULL;
	bool fileopen = true;
	
	fileopen = FileQueue.Parsing_file("word.txt");//File open
	if (fileopen == false)//if file not open
		return false;

	while (!FileQueue.Is_empty())//if fileQueue is not empty
	{
		pFileNode = FileQueue.Pop();
		if (queue->Search(pFileNode->GetFileData1()) == NULL)
		{
			pNew = new WordNode(pFileNode->GetFileData1(), pFileNode->GetFileData2());
			queue->Push(pNew);
		}
		delete pFileNode;
	}
	return true;
}
bool Manager::LOAD()
{//Load
	FileClass FileReader;
	FileClassNode* pFileNode = NULL;
	AlphabetNode* pAlpNode = NULL;
	WordNode* pNewWord = NULL;
	WordBST* pNewWordBST = NULL;
	bool fopenFlag = true;
	//if tree structure already had a node
	if (queue->GetNodeCnt() != NULL || (bst->Get_Root())->GetBST() != NULL || cll->Get_Head() != NULL)
		return false;

	fopenFlag = FileReader.Parsing_file("to_memorize_word.txt");//parsing word
	if (fopenFlag == false)
		return false;
	//all File pop
	while (FileReader.Is_empty())
	{
		//pop
		pFileNode = FileReader.Pop();
		pNewWord = new WordNode(pFileNode->GetFileData1(), pFileNode->GetFileData2());
		//push
		queue->Push(pNewWord);
		delete pFileNode;
	}

	//file open and Parsing
	fopenFlag = FileReader.Parsing_file("memorizing_word.txt");//parsing word
	if (fopenFlag == false)
		return false;
	//All file pop
	while (FileReader.Is_empty())
	{
		pFileNode = FileReader.Pop();
		pAlpNode = bst->Search(*(pFileNode->GetFileData1()));//get binary search tree
		pNewWordBST = pAlpNode->GetBST();
		pNewWord = new WordNode(pFileNode->GetFileData1(), pFileNode->GetFileData2());	//make new
		pNewWordBST->Insert(pNewWord);	//insert to BST
		bst->WordCnt++;//increase word count
		delete pFileNode;
	}
	
	// Parsing and File open
	fopenFlag = FileReader.Parsing_file("memorized_word.txt");
	if (fopenFlag == false)
		return false;
	//All file node pop
	while (FileReader.Is_empty())
	{
		pFileNode = FileReader.Pop();	//pop
		pNewWord = new WordNode(pFileNode->GetFileData1(), pFileNode->GetFileData2());	//new node make
		cll->Insert(pNewWord);	//insert to cll
		delete pFileNode;
	}
	return true;
}
bool Manager::MOVE()
{
	AlphabetNode* pAlpNode = NULL;
	WordBST* pWordBST = NULL;
	WordNode* pMoveNode = NULL;
	int QueCnt = queue->GetNodeCnt();//node count
	int BSTCnt = 0, i = 0;
	int MoveCnt = fileNode->GetMoveCnt();//move count
	char alphabet = '0';

	if (QueCnt == 0 || QueCnt < MoveCnt || (MoveCnt + bst->WordCnt) > 100)//count is not over 100
		return false;
	
	
	for (i = 0; i < MoveCnt; i++)
	{
		pMoveNode = queue->Pop();//move to_memorize to memorizing
		pAlpNode = bst->Search(*(pMoveNode->GetWord()));
		if (pAlpNode == NULL)
		{
			delete pAlpNode;
			return false;
		}
		pWordBST = pAlpNode->GetBST();	//get word BST root
		bst->WordCnt++;
		pWordBST->Insert(pMoveNode);//insert binary search tree
	}
	return true;
}
bool Manager::SAVE()
{
	//call each save function
	if (!queue->Save())
		return false;
	else if (!bst->Save())
		return false;
	else if (!cll->Save())
		return false;
	else
		return true;
}
bool Manager::TEST()
{
	char* pWord = fileNode->GetFileData1();
	char* pMean = fileNode->GetFileData2();
	AlphabetNode* pAlpNode = NULL;
	WordBST* pWordBST = NULL;
	WordNode* pNode = NULL;

	pAlpNode = bst->Search(*(pWord));//get alphabetBST
	if (pAlpNode == NULL)
		return false;
	pWordBST = pAlpNode->GetBST();//get WordBST
	if (pWordBST->Get_Root() == NULL)
		return false;
	pNode = pWordBST->Search(pWord);//get same word
	if (pNode == NULL)
		return false;

	//if word & mean is correct
	if (strcmp(pNode->GetMean(), pMean) == 0)
	{
		cll->Insert(pWordBST->Delete(pWord));
		return true;
	}
	return false;
}
bool Manager::SEARCH()
{
	AlphabetNode* pAlpNode = NULL;
	WordBST* pBSTNode = NULL;
	WordNode* pNode = NULL;
	char* SearchWord = fileNode->GetFileData1();
	
	///////////////////////// queue
	pNode = queue->Search(SearchWord);
	if (pNode != NULL)
	{
		// no matching
		File.Print_Logfile(true, "SEARCH", E_SEARCH, pNode, NULL);
		return true;
	}
		
	//////////////////////// BST
	pAlpNode = bst->Search(*(SearchWord));	//serching alphabet in BST
	if (pAlpNode == NULL)
		return false;		// nomatcing
	pBSTNode = pAlpNode->GetBST();	// Get word bst root
	if (pBSTNode == NULL)
		return false;	// no node in word BST
	pNode = pBSTNode->Search(SearchWord);	//serch word in BST
	if (pNode != NULL)
	{
		File.Print_Logfile(true, "SEARCH", E_SEARCH, pNode, NULL);
		return true;
	}
	
	///////////////////////// CLL
	pNode = cll->Search(SearchWord);	//Serch word in cll
	if (pNode != NULL)
	{
		// no matching file
		File.Print_Logfile(true, "SEARCH", E_SEARCH, pNode, NULL);
		return true;
	}
	return false;
}
bool Manager::PRINT()
{
	ofstream pfout;
	bool printFlag = true;
	char* filename = fileNode->GetFileData1();
	char* option = fileNode->GetFileData2();
	
	if (strcmp("to_memorize.txt", filename) == 0)
	{
		//call print queue func
		printFlag = queue->Print();
		pfout.close();
		return printFlag;
	}
	else if (strcmp("memorizing_word.txt", filename) == 0)
	{
		//file open to log
		pfout.open("log.txt", ios::app);
		pfout << "============PRINT============" << endl;
		printFlag = bst->Print(option);	//call BST print fun
		if (printFlag == false)	//There are errors
		{
			pfout << E_PRINT << endl;
			pfout << "=====================" << endl << endl;
			pfout.close();
			return true;
		}
		else //no error
		{
			pfout << "=====================" << endl << endl;
			pfout.close();
			return true;
		}
	}

	else if (strcmp("memorized_word.txt", filename) == 0)
	{
		//call CLL print func
		printFlag = cll->Print();
		pfout.close();
		return printFlag;
	}
	else
	{
		//no matching file save error log
		File.Print_Logfile(false, "PRINT", E_PRINT, NULL, NULL);
		pfout.close();
		return false;		
	}		
}
bool Manager::UPDATE()
{
	AlphabetNode* pAlpNode = NULL;
	WordBST* pBSTNode = NULL;
	WordNode* pNode = NULL;
	char preMean[SIZE_32] = { '\0', };
	char* UpdateWord = fileNode->GetFileData1();
	char* UpdateMean = fileNode->GetFileData2();
	
	//File search in queue
	pNode = queue->Search(UpdateWord);
	if (pNode != NULL)
	{
		//found word & set new word
		strcpy(preMean, pNode->GetMean());
		pNode->SetMean(UpdateMean);
		File.Print_Logfile(true, "UPDATE", E_SEARCH, pNode, preMean);
		return true;
	}
	
	//File alphabet in alp BST tree
	pAlpNode = bst->Search(*(UpdateWord));
	if (pAlpNode == NULL)
		return false;
	//Get Word BST
	pBSTNode = pAlpNode->GetBST();
	if (pBSTNode == NULL)
		return false;
	//Seach word in word BST tree
	pNode = pBSTNode->Search(UpdateWord);
	if (pNode != NULL)
	{
		//found word & set new word
		strcpy(preMean,pNode->GetMean());
		pNode->SetMean(UpdateMean);
		File.Print_Logfile(true, "UPDATE", E_SEARCH, pNode, preMean);
		return true;
	}
	
	pNode = cll->Search(UpdateWord);
	if (pNode != NULL)
	{
		strcpy(preMean, pNode->GetMean());
		pNode->SetMean(UpdateMean);
		File.Print_Logfile(true, "UPDATE", E_SEARCH, pNode, preMean);
		return true;
	}
	return false;
}
void Manager::EXIT()
{
	//deallocate value
	delete queue;
	delete bst;
	delete cll;
	queue = NULL;
	bst = NULL;
	cll = NULL;
}

FileClass::FileClass()
{
	pHeadFile = NULL;
}
FileClass::~FileClass()
{
	FileClassNode* pDel = NULL;
	while (pHeadFile)
	{
		pDel = pHeadFile;
		pHeadFile = pHeadFile->GetNext();
		delete pDel;
	}
}
bool FileClass::Is_empty()
{
	if (pHeadFile == NULL)
		return true;
	return false;
}
FileClassNode* FileClass::Pop()
{
	FileClassNode* pCur = pHeadFile;

	//pop first node and make 2nd header
	if (pHeadFile == NULL)
		return NULL;
	pHeadFile = pHeadFile->GetNext();
	return pCur;
}
void FileClass::Push(FileClassNode* node)
{
	FileClassNode* pCur = pHeadFile;
	//push node in queue
	if (pHeadFile == NULL)	pHeadFile = node;
	else
	{
		//link node to end node
		while (pCur->GetNext())	pCur = pCur->GetNext();
		pCur->SetNext(node);
	}
}
bool FileClass::Parsing_command(const char* filename)
{
	char filebuffer[SIZE_64];
	char* tokFunc = NULL;
	char* tokArg1 = NULL;
	char* tokArg2 = NULL;
	int funcFlag = 0, optionFlag = 0;
	int moveCnt = 0;

	fin.open(filename);
	if (fin.fail())
	{
		fin.close();
		return false;
	}

	while (!fin.eof())
	{
		//get file line & parsing 1 word
		memset(filebuffer, '\0', SIZE_64);
		fin.getline(filebuffer, SIZE_64);
		// Command parsing
		tokFunc = strtok(filebuffer, "\t ");
		if (tokFunc == NULL || tokFunc[FIRST_WORD] < 'A' || tokFunc[FIRST_WORD] > 'Z')
			continue;
		// 2nd argument parsing & file name parsing
		tokArg1 = strtok(NULL, "\t ");
		if (tokArg1 != NULL)
			tokArg2 = strtok(NULL, "t ");
		//Check function
		funcFlag = Check_FuncFlag(tokFunc);
		switch (funcFlag)
		{
		case D_LOAD:
			Push(new FileClassNode(funcFlag));
			break;
		case D_ADD:
			Push(new FileClassNode(funcFlag));
			break;
		case D_MOVE:
			if (tokArg1 != NULL && tokArg2 == NULL)
			{
				moveCnt = atoi(tokArg1);
				Push(new FileClassNode(funcFlag, moveCnt));
			}
			break;
		case D_SAVE:
			Push(new FileClassNode(funcFlag));
			break;
		case D_TEST:
			if (tokArg1 != NULL && tokArg2 != NULL)
				Push(new FileClassNode(funcFlag, tokArg1, tokArg2));
			break;
		case D_SEARCH:
			if (tokArg1 != NULL && tokArg2 == NULL)
				Push(new FileClassNode(funcFlag, tokArg1));
			break;
		case D_PRINT:
			if (tokArg1 != NULL)
			{
				//check file name
				if (strcmp(tokArg1, "TO_MEMORIZE") == 0 && tokArg2 == NULL)
					Push(new FileClassNode(funcFlag, "to_memorize_word.txt"));
				//check file name
				else if (strcmp(tokArg1, "MEMORIZING") == 0 && tokArg2 != NULL)
				{
					//check seach option
					optionFlag = Check_OptionFlag(tokArg2);
					if (optionFlag == D_ERROR)
						break;
					Push(new FileClassNode(funcFlag, "memorizing_word.txt", tokArg2));
				}
				//check file name
				else if (strcmp(tokArg1, "MEMORIZED") == 0 && tokArg2 == NULL)
					Push(new FileClassNode(funcFlag, "memorized_word.txt"));
				else
					// no matchiing file. error
					Push(new FileClassNode(funcFlag, "error"));
					break;
			}
			break;
		case D_UPDATE:
			//check word & word has inputed
			if (tokArg1 != NULL && tokArg2 != NULL)
				Push(new FileClassNode(funcFlag, tokArg1, tokArg2));
			break;
		case D_EXIT:
			Push(new FileClassNode(funcFlag));
			break;
		default:
			break;
		}
	}
	fin.close();
	return true;
}
bool FileClass::Parsing_file(const char* file_name)
{
	char wordmean[SIZE_64];
	char* tokWord = NULL;
	char* tokMean = NULL;
	char* tokNULL = NULL;
	
	fin.open(file_name);
	if (fin.fail())
	{
		cout << "No such file : %s\n" << file_name;
		fin.close();
		return false;
	}

	while (!fin.eof())
	{
		//get file line & parsing 1 word
		memset(wordmean, '\0', SIZE_64);
		fin.getline(wordmean, SIZE_64);
		tokWord = strtok(wordmean, "\t ");
		// check word
		if (tokWord == NULL || tokWord[FIRST_WORD] <= 'A' || tokWord[FIRST_WORD] >= 'z')
			continue;
		// check mean
		tokMean = strtok(NULL, "\n \t");
		if (tokMean == NULL)
			continue;

		Push(new FileClassNode(tokWord, tokMean));
	}
	fin.close();
	return true;
}
int FileClass::Check_FuncFlag(char* function)
{
	//return int accoding to each function type
	if (strcmp(function, "LOAD") == 0)
		return D_LOAD;
	else if (strcmp(function, "ADD") == 0)
		return D_ADD;
	else if (strcmp(function, "MOVE") == 0)
		return D_MOVE;
	else if (strcmp(function, "SAVE") == 0)
		return D_SAVE;
	else if (strcmp(function, "TEST") == 0)
		return D_TEST;
	else if (strcmp(function, "SEARCH") == 0)
		return D_SEARCH;
	else if (strcmp(function, "PRINT") == 0)
		return D_PRINT;
	else if (strcmp(function, "UPDATE") == 0)
		return D_UPDATE;
	else if (strcmp(function, "EXIT") == 0)
		return D_EXIT;
	else
		return D_ERROR;
}
void FileClass::Print_Logfile(bool fileSuccess, char* funcType, int Err, WordNode* node, char* preMean)
{
	int Func = Check_FuncFlag(funcType);
	fout.open("log.txt", ios::app);
	if (fout.fail())
		return;
	// if each function failed
	if (fileSuccess == false)
	{
		fout << "======== Error ========" << endl;
		fout << Err << endl;
		fout << "=====================" << endl << endl;
		fout.close();
		return;
	}
	// if each function return true
	else if(Func != D_PRINT)
	{
		fout << "======== " << funcType << " ========" << endl;
		switch (Func)
		{
		case D_TEST:
			fout << "Pass" << endl;
			fout << "========================" << endl << endl;
			break;
		case D_SEARCH:
			fout << node->GetWord() << " " << node->GetMean() << endl;
			fout << "========================" << endl << endl;
			break;
		case D_UPDATE:
			fout << node->GetWord() << " " << preMean << " -> " << node->GetMean() << endl;
			fout << "========================" << endl << endl;
			break;
		case D_PRINT:
			break;
		default:
			fout << "Success" << endl;
			fout << "=====================" << endl << endl;
			break;
		}
	}
	fout.close();
	return;
}
int FileClass::Check_OptionFlag(char* option)
{
	if (strcmp(option, "R_PRE") == 0)
		return R_PRE;
	else if (strcmp(option, "I_PRE") == 0)
		return I_PRE;
	else if (strcmp(option, "R_IN") == 0)
		return R_IN;
	else if (strcmp(option, "I_IN") == 0)
		return I_IN;
	else if (strcmp(option, "R_POST") == 0)
		return R_POST;
	else if (strcmp(option, "I_POST") == 0)
		return I_POST;
	else if (strcmp(option, "I_LEVEL") == 0)
		return I_LEVEL;
	else
		return D_ERROR;
}

FileClassNode::FileClassNode()
{
	fileData[0] = NULL;
	fileData[1] = NULL;
	pNext = NULL;
	Opt = 0;
	Func = 0;
}
FileClassNode::FileClassNode(int func)
{
	Func = func;
	fileData[0] = NULL;
	fileData[1] = NULL;
	pNext = NULL;
	Opt = 0;
}
FileClassNode::FileClassNode(int func, int opt)
{
	Func = func;
	Opt = opt;
	fileData[0] = NULL;
	fileData[1] = NULL;
	pNext = NULL;
}
FileClassNode::FileClassNode(int func, char* arg)
{
	int str_len = strlen(arg) + 1;
	fileData[0] = new char[str_len];
	strcpy(fileData[0],  arg);

	fileData[1] = NULL;	
	pNext = NULL;
	Opt = 0;
	Func = func;
}
FileClassNode::FileClassNode(char* arg1, char* arg2)
{
	int str_len = strlen(arg1) + 1;
	fileData[0] = new char[str_len];
	strcpy(fileData[0],  arg1);

	str_len = strlen(arg2) + 1;
	fileData[1] = new char[str_len];
	strcpy(fileData[1],  arg2);

	pNext = NULL;
	Opt = 0;
	Func = 0;
}
FileClassNode::FileClassNode(int func, int opt, char* arg1)
{
	int str_len = strlen(arg1) + 1;
	fileData[0] = new char[str_len];
	strcpy(fileData[0], arg1);

	fileData[1] = NULL;
	pNext = NULL;
	Opt = opt;
	Func = func;
}
FileClassNode::FileClassNode(int func, char* arg1, char* arg2)
{
	int str_len = strlen(arg1) + 1;
	fileData[0] = new char[str_len];
	strcpy(fileData[0],  arg1);

	str_len = strlen(arg2) + 1;
	fileData[1] = new char[str_len];
	strcpy(fileData[1],  arg2);

	pNext = NULL;
	Opt = 0;
	Func = func;
}
FileClassNode::~FileClassNode()
{
	if(fileData[0] != NULL)
		delete fileData[0];
	if (fileData[1] != NULL)
		delete fileData[1];
	pNext = NULL;
}
FileClassNode* FileClassNode::GetNext()
{
	return pNext;
}
char* FileClassNode::GetFileData1()
{
	return fileData[0];
}
char* FileClassNode::GetFileData2()
{
	return fileData[1];
}
int FileClassNode::GetFunc()
{
	return Func;
}
int FileClassNode::GetMoveCnt()
{
	return Opt;
}
int FileClassNode::GetOpt()
{
	return Opt;
}
void FileClassNode::SetNext(FileClassNode* next)
{
	pNext = next;
}

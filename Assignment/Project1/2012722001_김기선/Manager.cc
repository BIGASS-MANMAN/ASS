#include "/usr/local/Auto_Scoring_System/src/signal.h"
#include "Manager.h"
Manager::Manager()
{
	cll = new CircularLinkedList;				//variable for bring the circularlinkedlist
	bst = new AlphabetBST;					//variable for bring the AlphabetBST
	queue = new Queue;					//variable for bring the Queue
	file_word1 = new char();				//command file variable
	file_word2 = new char();				//command file variable
	file_wordcnt = 0;					//command file variable for BST
}


Manager::~Manager()
{ return;

	delete cll;				//delete
	delete bst;				//delete
	delete queue;				//delete
}

void Manager::run(const char * command)		//read command file and conduct the command
{
	struct sigaction sa;
	set_sigaction(sa);
	alarm(3);

	ofstream fout("log.txt", ios::app);	//file open for write
	ifstream fopen;			
	fopen.open(command);			//file open for read
	if (!fopen.is_open())			//if file is not exist
	{
	///////////////print error message////////////////	
		fout << "======== ERROR ========" << endl;
		fout << "100" << endl;
		fout << "======================" << endl;
		fopen.close();			//file close
		fout.close();			//file close
		return;				//return
	}
	int check = 0;				//variable for check the error
	while (!fopen.eof())
	{
		char line[100] = { 0, };					//array for read the comman file
		char* Command = new char[32];				//Dynamic allocation for bring the command
		fopen.getline(line, sizeof(line));			//read the file's one line
			Command = strtok(line, "\t");			//bring the command by using the token
			if (Command != NULL)				//if command is exist
			{
				if (strcmp(Command, "LOAD") == 0)	//if command==LOAD
				{
					if (strtok(NULL, "\t") == NULL)	//token for find command error
					{
						if (LOAD() == 0)	//LOAD function error
						{
							//////////error message///////////
							fout << "======== ERROR ========" << endl;
							fout << "100" << endl;
							fout << "======================" << endl;
						}
						else			//LOAD function success
						{
							/////////success message//////////////
							fout << "========LOAD=========" << endl << "Success" << endl << "=====================" << endl << endl;
						}
					}
					else                //command error
					{	
						//////////error message///////////
						fout << "======== ERROR ========" << endl;
						fout << "100" << endl;
						fout << "======================" << endl;
					}
				}
				else if (strcmp(Command, "ADD") == 0)	//if command==LOAD
				{
					if (strtok(NULL, "\t") == NULL)	//token for find command error
					{
						if (ADD() == 0)		//ADD function error
						{
							//////////error message///////////
							fout << "======== ERROR ========" << endl;
							fout << "200" << endl;
							fout << "======================" << endl;
						}
						else
						{
							/////////success message//////////////
							fout << "========ADD=========" << endl << "Success" << endl << "=====================" << endl << endl;
						}
					}
					else
					{
						//////////error message///////////
						fout << "======== ERROR ========" << endl;
						fout << "200" << endl;
						fout << "======================" << endl;
					}
				}
				else if (strcmp(Command, "MOVE") == 0)	//if command==MOVE
				{
					file_wordcnt = 0;		//reset
					char* ptr = strtok(NULL, "\t");	//variable for bring the move number

					if (ptr == NULL)		//command error
					{
						//////////error message///////////
						fout << "======== ERROR ========" << endl;
						fout << "300" << endl;
						fout << "======================" << endl;
						continue;
					}

					file_wordcnt = atoi(ptr);//move 100

					if (file_wordcnt > 100 || file_wordcnt < 1)//max input value is 100 (constraints)
					{
						//////////error message///////////
						fout << "======== ERROR ========" << endl;
						fout << "300" << endl;
						fout << "======================" << endl;
						continue;
					}

					if (MOVE() == false)	//move failed
					{
						//////////error message///////////
						fout << "======== ERROR ========" << endl;
						fout << "300" << endl;
						fout << "======================" << endl;
					}
					else//success
					{
						/////////success message//////////////
						fout << "========MOVE=========" << endl << "Pass" << endl << "=====================" << endl << endl;
					}
				}
				else if (strcmp(Command, "SAVE") == 0)	//if command==SAVE
				{
					if (strtok(NULL, "\t") == NULL)	//token for find command error
					{
						if (SAVE() == 0)	//save filed
						{
							//////////error message///////////
							fout << "======== ERROR ========" << endl;
							fout << "400" << endl;
							fout << "======================" << endl;
						}
						else			//success
						{
							/////////success message//////////////
							fout << "========SAVE=========" << endl << "Success" << endl << "=====================" << endl << endl;
						}
					}
					else	//command error
					{
						//////////error message///////////
						fout << "======== ERROR ========" << endl;
						fout << "400" << endl;
						fout << "======================" << endl;
					}
				}
				else if (strcmp(Command, "TEST") == 0)		//if command==TEST
				{
					file_word1 = strtok(NULL, "\t");	//token for save command's word
					file_word2 = strtok(NULL, "\t");	//token for save command's mean
					if (TEST() == 0)			//TEST failed
					{
						//////////error message///////////
						fout << "======== ERROR ========" << endl;
						fout << "500" << endl;
						fout << "======================" << endl;
					}
					else					//success
					{
						/////////success message//////////////
						fout << "========TEST=========" << endl << "Success" << endl << "=====================" << endl << endl;
					}
				}
				else if (strcmp(Command, "SEARCH") == 0)	//if command==SEARCH
				{
					file_word1 = strtok(NULL, "\t");	//token for save command's word
					if (file_word1 == NULL)			//if word empty
					{
						//////////error message///////////
						fout << "======== ERROR ========" << endl;
						fout << "200" << endl;
						fout << "======================" << endl;
						continue;
					}
					if (SEARCH() == 0)			//search failed
					{
						//////////error message///////////
						fout << "======== ERROR ========" << endl;
						fout << "600" << endl;
						fout << "======================" << endl;
					}
				}
				else if (strcmp(Command, "PRINT") == 0)		//if command==PRINT
				{
					file_word1 = strtok(NULL, "\t");	//token for save command's file name
					file_word2 = strtok(NULL, "\t");	//token check the command error
					if (file_word1 != NULL)
					{
						if (PRINT() == 0)		//print error
						{
							//////////error message///////////
							fout << "======== ERROR ========" << endl;
							fout << "700" << endl;
							fout << "======================" << endl;
						}
					}
					else          //command error
					{
						//////////error message///////////
						fout << "======== ERROR ========" << endl;
						fout << "700" << endl;
						fout << "======================" << endl;
					}
				}
				else if (strcmp(Command, "UPDATE") == 0)		//if command==UPDATE
				{
					file_word1 = strtok(NULL, "\t");		//token for save command's word
					if (file_word1 != NULL)				//if empty
					{
						char* check = new char();		//variable for save the command's mean
						check = strtok(NULL, "\t");		//token
						if (check != NULL)			//if empty
						{
							file_word2 = check;		//copy
							if (UPDATE() == 0)		//update failed
							{
								//////////error message///////////
								fout << "======== ERROR ========" << endl;
								fout << "800" << endl;
								fout << "======================" << endl;
								continue;
							}
							else				//success
								continue;
						}
					}
					//////////error message///////////
					fout << "======== ERROR ========" << endl;
					fout << "800" << endl;
					fout << "======================" << endl;
				}
				else if (strcmp(Command, "EXIT") == 0)			//if command==EXIT
				{
					if (strtok(NULL, "\t") == NULL)			//command error check
					{
						check = 1;				//set the check
						break;					//break
					}
					else						//command error
					{
						fout << "error" << endl;
					}
				}				
				else		//if command is not match any word
				{
					fout << "error" << endl;
					continue;
				}
				check = 1;	//set the check
			}
			else                 //if command is empty
			{
				check = 2;	
				continue;
			}
		}
	
	if (check != 1)		//there is not valid command
		fout << "error" << endl;
	fopen.close();		//file close
	fout.close();		//file close
	return;
}

bool Manager::LOAD()		//LOAD function
{
	ifstream fin1;		//file variable
	ifstream fin2;
	ifstream fin3;

	fin1.open("to_memorize_word.txt");	//to_memorize
	fin2.open("memorizing_word.txt");	//memorizing
	fin3.open("memorized_word.txt");	//memorized

///////////////////if data type is full already//////////////////////////
	if (queue->GetHead() != NULL)					//if not empty
	{
		fin1.close();		//file close
		fin2.close();
		fin3.close();
		return 0;						//return for error message
	}

	if (cll->Gethead() != NULL)					//if not empty
	{
		fin1.close();		//file close
		fin2.close();
		fin3.close();
		return 0;						//return for error message
	}


/////////////////여기 채워 놓기 자료형에 자료 있는지 확인/////////////////
	//if (bst->Getroot()!=NULL)					//if empty
	//{
	//	return 0;						//return for error message
	//}
//////////////////////////////////////////////////////////////////////


	/*QUEUE*/
	if (fin1.is_open())						//if not empty
	{
		while (!fin1.eof())						//queue insert
		{
			char Wordmean[100] = { 0, };				//variable for save the file one line
			char* word = new char[32];				//word
			char* mean = new char[32];				//mean
			WordNode* pNode = new WordNode();			//Dynamic allocation
			fin1.getline(Wordmean, sizeof(Wordmean));		//read the file
			if (strlen(Wordmean) != 0)				//if not empty
			{
				strcpy(word, strtok(Wordmean, "\t"));		//copy
				strcpy(mean, strtok(NULL, "\t"));		//copy
				pNode->SetWord(word);				//setting
				pNode->SetMean(mean);				//setting
				queue->Push(pNode);				//push
			}
		}
	}
	/*BST*/
	if (fin2.is_open())						//if not empty
	{
		while (!fin2.eof())
		{
			if (bst->getWordCnt() >= 100) //constraints saved word's num
				break; //break;
	
			char input_first[64] = { 0, };		//initial input
			char input_alphabet = 0;		//word's first alphabet
			char* input_word = new char[32];
			char* input_mean = new char[32];
			char* ptr = NULL;				//for using strtok
			AlphabetNode* pHere = NULL;		//result of alphabet bst; search
			WordBST* pFind = NULL;			//pHere's word bst
			WordNode* pNew = new WordNode;			//insert node
	
			for (int i = 0; i<32; i++) {
				input_word[i] = 0;
				input_mean[i] = 0;
			}

			fin2.getline(input_first, 64);	//load line by line

			input_alphabet = input_first[0];//get input word's first alphabet
			if (input_alphabet > 96)		//transform small -> capital letter
				input_alphabet = input_alphabet - 32;
	
			if (input_alphabet == 0)	//exceptin 
				break;
	
			pHere = bst->Search(input_alphabet);//search alphabet
			
			ptr = strtok(input_first, "\t");	//token input first by space
			strcpy(input_word, ptr);
			pNew->SetWord(input_word);				//setting new word node
			ptr = strtok(NULL, "\t");		//about mean
			strcpy(input_mean, ptr);
			pNew->SetMean(input_mean);
	
			pFind = pHere->GetBST();//get word bst
			pFind->Insert(pNew);	//insert new node
			bst->wordcnt_up();		//increase wordcnt
		}
	}

	/*Circular*/
	
	if (fin3.is_open())						//if not empty
	{
		while (!fin3.eof())			//cll insert
		{
			char Wordmean[100] = { 0, };	//variable for save the file one line
			char* word = new char[32];	//word
			char* mean = new char[32];	//mean
			WordNode* pNode = new WordNode();	//Dynamic allocation
			fin3.getline(Wordmean, sizeof(Wordmean));	//read one line
			if (strlen(Wordmean) != 0)	//if not empty
			{
				strcpy(word, strtok(Wordmean, "\t"));	//copy
				strcpy(mean, strtok(NULL, "\t"));	//copy
				pNode->SetWord(word);			//setting
				pNode->SetMean(mean);			//setting
				cll->Insert(pNode);			//insert
			}
		}
	}
	fin1.close();		//file close
	fin2.close();
	fin3.close();


///////////////////if data type is empty //////////////////////////////
	if (queue->GetHead() == NULL)					//if empty
	{
		return 0;						//return for error message
	}

	if (cll->Gethead() == NULL)					//if empty
	{
		return 0;						//return for error message
	}

	if(bst->getWordCnt()==0)
		return false;

	return 1;
}

bool Manager::ADD()			//ADD function
{
	ifstream fin;			//file variable
	fin.open("word.txt");		//file open
	if (!fin.is_open())		//if empty
	{
		fin.close();
		return 0;							//return for error message
	}
	int check = 0;			//variable for check error
	while (!fin.eof())		//inset in the queue
	{
		char Wordmean[100] = { 0, };	//variable for save the file one line
		char* word = new char[32];	//word
		char* mean = new char[32];	//mean
		WordNode* pNode = new WordNode();	//Dynamic allocation
		fin.getline(Wordmean, sizeof(Wordmean));	//read the file
		if (strlen(Wordmean) != 0)	//if not empty
		{
			strcpy(word, strtok(Wordmean, "\t"));	//copy
			strcpy(mean, strtok(NULL, "\t"));
			pNode->SetWord(word);		//setting
			pNode->SetMean(mean);
			queue->Push(pNode);		//push
			check = 1;
		}
		else
		{
			continue;
		}
		//delete word;
		//delete mean;
	}
	fin.close();		//file close
	if (check != 1)
		return 0;								//return for error message
	return 1;
}

bool Manager::MOVE()
{
	if (file_wordcnt > queue->getWordCnt())		//if the number of queue is smaller than input number
		return false;								//return for error message

	if (file_wordcnt + bst->getWordCnt() > 100)	//if the input number + bst number bigger than 100
		return false;								//return for error message

	if (bst->getWordCnt() > 100)			//if bst number if full
		return false;								//return for error message

	while (file_wordcnt != 0)
	{
		WordNode*pNew = queue->Pop();
		AlphabetNode* pHere = NULL;	// find alphabet
		WordBST* pHere_bst = NULL;  // word_bst in alphabet
		char input_word[32] = { 0, };// moved word
		strcpy(input_word, pNew->GetWord()); //save data

		pHere = bst->Search(input_word[0] - 32);	//find alphabet
		if (pHere == NULL)	//fail(conversion or not char)
			return false;							//return for error message

		pHere_bst = pHere->GetBST();	//get alphabet's bst

		if (pHere_bst->Search(input_word) == NULL)//°°Àº ÀÎŒö ÁžÀçÇÏÁö ŸÊÀœ
		{
			pHere_bst->Insert(pNew);//insert
			bst->wordcnt_up();	//increase saved word's num
			file_wordcnt--;
			continue;//success
		}
		else
			return false;							//return for error message

		file_wordcnt--;
	}


	return true;
}
bool Manager::SAVE()			//save function
{
	int flag = 0;
	
	if (queue->Save() == false)	//queue save failed
		flag++;

////////////호영이가 채우기/////////////////////
	if(bst->getWordCnt()==0)
		flag++;
	else
		bst->Save();

//////////////////////////////////////////////

	if (cll->Save() == false)	//cll save failed
		flag++;
	
	if (flag == 3)	//all fail
		return 0;									//return for error message
	else
		return 1;
}
bool Manager::TEST()			//test function
{
	char test_word[32] = { 0, };	//variable for save the file one line
	strcpy(test_word, file_word1);	//copy

	
	AlphabetNode* pHere = NULL;//result find alphabet
	WordBST* pHere_bst = NULL;//wordbst in alphabet node
	WordNode* pMove = NULL;//will move to memorized

	Conversion(test_word);		//conversion capital to small letter
	char ch = test_word[0] - 32;

	pHere = bst->Search(ch);		// find where wordnode is in

	if (pHere == NULL)	//fail case1 (coversion or not char)
		return false;						//return for error message

	pHere_bst = pHere->GetBST();	//get word bst
	pMove = pHere_bst->Search(test_word);
	if (pMove != NULL)
	{
		if (strcmp(file_word2, pMove->GetMean()) == 0)
			pMove = pHere_bst->Delete(test_word);		// delete node in bst
		else
			return false;							//return for error message
	}
	else
		return false;							//return for error message

	cll->Insert(pMove);	//cll insert
	bst->wordcnt_down();	//count down
	return true;//success
}
bool Manager::SEARCH()		//search function
{
	ofstream fout("log.txt", ios::app);	//file open
	WordNode* pCur = NULL;
	AlphabetNode* pHere = NULL;//result find alphabet
	WordBST* pHere_bst = NULL;//wordbst in alphabet node
	WordNode* pResult = NULL;//will move to memorized

	char test_word[32] = { 0, };	//variable for save the file one line
	strcpy(test_word, file_word1);	//copy

	Conversion(test_word);		//conversion
	/*QUEUE*/
	pCur = queue->Search(test_word);	//queue search
	if (pCur != NULL)	//not empty
	{
		//////////////success message////////////////
		fout << "======== SEARCH =======" << endl;
		fout << pCur->GetWord() << "  " << pCur->GetMean() << endl;
		fout << "=======================" << endl << endl;
		return true;
	}
	/*BST*/
	pHere = bst->Search(test_word[0] - 32);		// find where wordnode is in

	pHere_bst = pHere->GetBST();	//get word bst

	pResult = pHere_bst->Search(test_word);		// delete node in bst
	if (pResult != NULL)	//fail case2 (cannot found word)
	{
		//////////////success message////////////////
		fout << "======== SEARCH =======" << endl;
		fout << pResult->GetWord() << "  " << pResult->GetMean() << endl;
		fout << "=======================" << endl << endl;
		return true;
	}
	/*CLL*/
	pCur = cll->Search(test_word);	//cll search
	if (pCur != NULL)
	{
		//////////////success message////////////////
		fout << "======== SEARCH =======" << endl;
		fout << pCur->GetWord() << "  " << pCur->GetMean() << endl;
		fout << "=======================" << endl << endl;
		return true;
	}

	return false;								//return for error message
}
bool Manager::PRINT()		//print function
{
	ofstream fout("log.txt", ios::app);	//file open
//	file_word2 = strtok(NULL, "\t");	//variable for save the file name
	bool result;		//variable for save the result

	if (strcmp(file_word1, "MEMORIZED") == 0)	//cll print
		result = cll->Print();
	else if (strcmp(file_word1, "TO_MEMORIZE") == 0)	//queue print
		result = queue->Print();
	else if (strcmp(file_word1, "MEMORIZING") == 0)		//bst print
	{
		if (file_word2 != NULL)
			result = bst->Print(file_word2);
	}
	else		//there is no valid file name
	{
		result = false;
	}
	fout.close();
	/*return result*/
	if (result == false)
		return false;							//return for error message
	else
		return true;
}
bool Manager::UPDATE()		//update function
{
	ofstream fout("log.txt", ios::app);	//file open
	AlphabetNode* pHere = NULL;	//result find alphabet
	WordBST* pHere_bst = NULL;	// wordbst in alphabet node
	WordNode* pUpdate = NULL;//node will be updated


	char up_word[32] = { 0, };
	strcpy(up_word, file_word1);
	char* up_mean = new char[32];
	for (int i = 0; i < 32; i++)	//reset
		up_mean[i] = 0;
	strcpy(up_mean, file_word2);	//copy

	Conversion(up_word);	//conversion capital to small

	/*queue*/						
	pUpdate = queue->Search(up_word);	//queue search
	if (pUpdate)		//update success
	{
		/////////////success message//////////////////
		fout << "========UPDATE=========" << endl;
		fout << up_word << "  " << pUpdate->GetMean();
		char* save = new char();
		strcpy(save, up_mean);	//save
		pUpdate->SetMean(save);	//setting
		fout << " -> " << pUpdate->GetMean() << endl << "=====================" << endl << endl;
		fout.close();	//file close
		return true;
	}

	/*BST*/
	pUpdate = NULL;		//reset
	pHere = bst->Search(up_word[0] - 32); //search alphabet 

	if (pHere != NULL) //err( conversion or not char )
	{	//return false;				//fail

		pHere_bst = pHere->GetBST();	//get alpha's word_bst

		pUpdate = pHere_bst->Search(up_word);  //setting update node
		if (pUpdate != NULL) //err( cannot found word )
		{
			/////////////success message//////////////////
			fout << "========UPDATE=========" << endl;
			fout << up_word << "  " << pUpdate->GetMean();
			char* save = new char();
			strcpy(save, up_mean);
			pUpdate->SetMean(save); // update mean
			fout << " -> " << pUpdate->GetMean() << endl << "=====================" << endl << endl;
			fout.close();
			return true;
		}
	}

	/*CCL*/
	pUpdate = NULL;
	pUpdate = cll->Search(up_word);		//cll search
	if (pUpdate)
	{
		/////////////success message//////////////////
		fout << "========UPDATE=========" << endl;
		fout << up_word << "  " << pUpdate->GetMean();
		char* save = new char();
		strcpy(save, up_mean);
		pUpdate->SetMean(save);
		fout << " -> " << pUpdate->GetMean() << endl << "=====================" << endl << endl;
		fout.close();
		return true;
	}
	else
	{
		fout.close();		//file close
		return false;									//return for error message
	}
		
}



void Manager::Conversion(char* input)	//conversion function
{
/////change capital letter to small letter by using askycode////////////
	for (int i = 0; i < 32; i++)
	{
		if (input[i] == 0)
			return;

		if (input[i] < 91)      //transform letter capital to small 
			input[i] = input[i] + 32;
	}
}

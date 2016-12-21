#include "/usr/local/Auto_Scoring_System/src/signal.h"
#include "Manager.h"
#include <stdlib.h>
#pragma warning(disable:4996) 
Manager::Manager()
{
	cll = new CircularLinkedList;
	bst = new AlphabetBST;
	queue = new Queue;
}


Manager::~Manager()
{ return;

	delete cll;
	delete bst;
	delete queue;
}
void Manager::run(const char* command)
{
	struct sigaction sa;
	set_sigaction(sa);
	alarm(3);

	ofstream logfile; //declare logfile
	logfile.open("log.txt"); //open log.txt

	char alphalist[27] = { "PHXDLTZBFJNRVYACEGIKMOQSUW" };
	for (int a = 0; a < 26; a++)// When you start this progam, make AlphabetBST
	{
		AlphabetNode* node = new AlphabetNode(); //declare alphanode node
		node->SetAlphabet(alphalist[a]); //node setalphabet(alphalist[a])
		bst->Insert(node); //implement bst insert(node)
	}
	char comm[30] = { '\0' };
	ifstream commandfile;
	commandfile.open(command); // command file open
	while (!commandfile.eof())
	{
		tok1 = '\0';
		tok2 = '\0';
		tok3 = '\0';

		commandfile.getline(comm, 30);
		tok1 = strtok(comm, " "); //token and save tok1
		if (strcmp(comm, "EXIT") == 0) //if comm is same as exit then return
			return;
		tok2 = strtok('\0', " "); //token and save tok2
		tok3 = strtok('\0', " "); //token and save tok3
		ComImple(tok1, tok2, tok3);
	}
	commandfile.close(); //close commandfile
	logfile.close(); //close logfile
}

bool Manager::LOAD()
{

	int SuccessFlag = 1; //declare successflag and set as 1
	int first = 1; //declare first and set as 1
	ofstream logfile; //declare logfile
	logfile.open("log.txt", ios::app); //open log.txt
	if (queue->pHead == '\0') // checking data's existence
	{
		if (bst->WordCnt == 0)
		{
			if (cll->pHead == '\0')
			{
				ifstream memorized, tomemorize, memorizing; //delcare memorized, tomemorize, memorizing
				tomemorize.open("to_memorize_word.txt"); //open to memorize word.txt
				memorizing.open("memorizing_word.txt"); //open memorizing word.txt
				memorized.open("memorized_word.txt"); //open memorized word.txt
				char arr[50] = { '\0' }; //declare arr and set as null 
				char* token; //declare token
				if (tomemorize.fail())
				{
					SuccessFlag = 0; //successflag is 0
				}
				else
				{
					while (!tomemorize.eof())
					{
						tomemorize.getline(arr, 50);
						if (arr[0] == '\0') //if arr is null
						{
							if (first == 0) //if first is 0
								break; //break
							break; //break
						}
						WordNode* node = new WordNode(); //delcare node and set as new
						token = strtok(arr, "\t"); //token until tap
						node->SetWord(token); //node setword token
						token = strtok('\0', "\t"); //token until null
						node->SetMean(token); //node setmean token
						queue->Push(node); //queue push node
						first = 0;//first is 0
					}
					tomemorize.close();
				}
				if (memorizing.fail())
				{
					SuccessFlag = 0;
				}
				else
				{
					first = 1;
					while (!memorizing.eof())
					{
						memorizing.getline(arr, 50);

						if (arr[0] == '\0') //if arr is null
						{
							if (first == 0)
								break;
							SuccessFlag = 0; //successflag set as 0
						}
						else
						{
							WordNode* node = new WordNode(); //declare node and set as new
							token = strtok(arr, "\t"); //token until tap
							node->SetWord(token); //node setword is token
							token = strtok('\0', "\t"); //token until null
							node->SetMean(token); //node setmean is token
							bst->Search(node->GetWord()[0])->GetBST()->Insert(node); //bst search node getword  get bst inset node
							bst->PlusWC();//implement bst pluswc
							first = 0; //first is 0
						}
					}
					memorizing.close();
				}
				if (memorized.fail()) //if memorized fail
				{
					SuccessFlag = 0; //successflag is 0
				}
				else
				{
					first = 1; //set first as 1
					while (!memorized.eof()) //while not memorized.eof 
					{
						memorized.getline(arr, 50);
						if (arr[0] == '\0') //if arr is null
						{
							if (first == 0) //if first is 0
								break; //break

							SuccessFlag = 0; //success falg
						}
						else
						{
							WordNode* node = new WordNode(); //declare wordnode node and set as new
							token = strtok(arr, "\t"); //token until tap
							node->SetWord(token); //node setword is token
							token = strtok('\0', "\t"); //token until null
							node->SetMean(token); //node setmean is token
							cll->Insert(node); //cll insert is node
							first = 0; //declare first and set as 0
						}
					}
					memorized.close(); //close memorized
				}
				if (SuccessFlag == 0)
				{
					logfile << "========ERROR========" << endl;
					logfile << "100" << endl;
					logfile << "======================" << endl;
					cout << "========ERROR========" << endl;
					cout << "100" << endl;
					cout << "======================" << endl;
					logfile.close();
					return false;
				}
				logfile << "========LOAD========" << endl;
				logfile << "Success" << endl;
				logfile << "====================" << endl;
				logfile.close();
				cout << "========LOAD========" << endl;
				cout << "Success" << endl;
				cout << "====================" << endl;
				return true;
			}
		}
	}
	else
	{
		logfile << "========ERROR========" << endl;
		logfile << "100" << endl;
		logfile << "======================" << endl;
		cout << "========ERROR========" << endl;
		cout << "100" << endl;
		cout << "======================" << endl;
		logfile.close();
		return false;

	}
};
bool Manager::ADD() 
{
	int first = 1; //declare first and set as 1
	ifstream infile; //declare infile
	infile.open("word.txt"); //open word.txt

	ofstream logfile; //declare logfile 
	logfile.open("log.txt", ios::app); //open log.txt
	if (infile.fail())
	{
		cout << "========ERROR========" << endl;
		cout << "200" << endl;
		cout << "=======================" << endl;
		logfile << "========ERROR========" << endl;
		logfile << "200" << endl;
		logfile << "=======================" << endl;
		logfile.close();
		return false;
	}
	while (!infile.eof())
	{

		char wordlist[50] = { '\0' };
		tok1 = '\0';
		tok2 = '\0';
		WordNode* node = new WordNode(); //declare node and set as new

		infile.getline(wordlist, 50); //open wordlist
		if (first == 0 && wordlist[0] == '\0') //if first is 0 and wordlist is null
			break;
		if (wordlist[0] == '\0') //if wordlist is null
		{
			cout << "========ERROR========" << endl;
			cout << "200" << endl;
			cout << "=======================" << endl;
			logfile << "========ERROR========" << endl;
			logfile << "200" << endl;
			logfile << "=======================" << endl;
			logfile.close();
			return false;
		}
		tok1 = strtok(wordlist, "\t"); //tok1 is wordlist until tap
		node->SetWord(tok1); //node setword tok1
		tok2 = strtok('\0', "\t"); //tok2 is until null
		node->SetMean(tok2); //node setmean is tok2

		
		WordNode* temp; //declare wordnode temp
		temp = queue->Search(tok1);//temp is queue search tok1
		if (temp != '\0')  //if temp is not a null
		{
			delete node;  //delete node
			continue; //continue
		}

		temp = bst->Search(tok1[0])->GetBST()->Search(tok1); //temp is bst search tok1[0] getbst search tok1
		if (temp != '\0') //if temp is not a null
		{
			delete node; //delete node
			continue; //continue
		}

		temp = cll->Search(tok1); //temp is cll search tok1
		if (temp != '\0')  //if temp is not a null
		{
			delete node; //delete node
			continue; //continue
		}
		queue->Push(node); //queue push is node
		first = 0; //first is 0
	}

	cout << "========ADD========" << endl;
	cout << "Success" << endl;
	cout << "===================" << endl;

	logfile << "========ADD========" << endl;
	logfile << "Success" << endl;
	logfile << "===================" << endl;
	logfile.close();
	infile.close();
	return true;
}
bool Manager::MOVE()
{
	ofstream logfile; //declare logfile
	logfile.open("log.txt", ios::app); //open log.txt
	int number = 0; //declare number
	number = atoi(tok2); // exchange char type into int type
						 /* in 'if' case, print ERROR sentence*/
	if (number > 100)
	{
		cout << "========ERROR========" << endl;
		cout << "300" << endl;
		cout << "======================" << endl;
		logfile << "========ERROR========" << endl;
		logfile << "300" << endl;
		logfile << "======================" << endl;
		logfile.close();
		return false;
	}
	if (queue->Cntqueue() < number) //  There were less nodes  than number in queue
	{
		cout << "========ERROR========" << endl;
		cout << "300" << endl;
		cout << "======================" << endl;
		logfile << "========ERROR========" << endl;
		logfile << "300" << endl;
		logfile << "======================" << endl;
		logfile.close();
		return false;
	}
	if ((number + bst->WordCnt)>100) // number + bst's nodes is bigger than 100
	{
		cout << "========ERROR========" << endl;
		cout << "300" << endl;
		cout << "======================" << endl;
		logfile << "========ERROR========" << endl;
		logfile << "300" << endl;
		logfile << "======================" << endl;
		logfile.close(); //close logfile
		return false;
	}
	WordNode* temp; //declare wordnode temp

	for (int a = 0; a < number; a++)
	{
		temp = queue->Pop(); // temp is the poped node in queue 
		bst->Search(temp->GetWord()[0])->GetBST()->Insert(temp); // search and insert in wordBST 
		bst->PlusWC();
	}

	cout << "========MOVE=========" << endl;
	cout << "Success" << endl;
	cout << "=======================" << endl;
	logfile << "========MOVE=========" << endl;
	logfile << "Success" << endl;
	logfile << "=======================" << endl;
	logfile.close();
	return true;

}
bool Manager::SAVE()
{
	ofstream logfile;
	logfile.open("log.txt", ios::app);
	queue->Save(); //implement queue save
	bst->Save(); //implement bst save
	cll->Save();//implement cll save
	if (queue->Save() == true)
	{
		if (bst->Save() == true)
		{
			if (cll->Save() == true)
			{
				logfile << "========SAVE========" << endl;
				logfile << "Success" << endl;
				logfile << "=====================" << endl;
				cout << "========SAVE========" << endl;
				cout << "Success" << endl;
				cout << "=====================" << endl;
				logfile.close();
				return true;
			}
		}
	}
	logfile << "========ERROR========" << endl;
	logfile << "400" << endl;
	logfile << "======================" << endl;
	logfile.close();
	cout << "========ERROR========" << endl;
	cout << "400" << endl;
	cout << "======================" << endl;
	return true;
}
char* Manager::up(char* word)
{
	char arr[20] = { '\0' }; //declare arr and set as null
	for (int a = 0; word[a] != '\0'; a++)
		arr[a] = toupper(word[a]); //arr[a] is toupper word[a]
	return arr; //return arr
}
bool Manager::TEST()
{
	ofstream logfile; //declare logfile
	logfile.open("log.txt", ios::app); //open log.txt
	AlphabetNode* temp; //declare alphabetnode temp
	
	temp = bst->Search(tok2[0]);  //temp is bst search(tok2[0])

	if (temp->GetBST()->Search(tok2) == '\0') 
	{
		cout << "========ERROR========" << endl;
		cout << "500" << endl;
		cout << "======================" << endl;
		logfile << "========ERROR========" << endl;
		logfile << "500" << endl;
		logfile << "======================" << endl;
		logfile.close();
		return false;
	}
	char word[32] = { '\0' }; //declare word and set as null
	char word2[32] = { '\0' }; //declare word2 and set as null 
	strcpy(word, up(temp->GetBST()->Search(tok2)->GetWord()));//copy word into up(temp getbst search tok2 getword)
	strcpy(word2, up(tok2)); //copy word2 into up tok2

	if (strcmp(word, word2) == 0) //if word is same as word2
	{
		if (strcmp(temp->GetBST()->Search(tok2)->GetMean(), tok3) == 0) //if temp getbst search tok2 getmean is same as tok3
		{
			cout << "========TEST========" << endl;
			cout << " PASS" << endl;
			cout << "====================" << endl;
			logfile << "========TEST========" << endl;
			logfile << " PASS" << endl;
			logfile << "====================" << endl;
			cll->Insert(temp->GetBST()->Delete(tok2)); 
		}
		else 
		{
			cout << "========ERROR========" << endl;
			cout << "500" << endl;
			cout << "======================" << endl;
			logfile << "========ERROR========" << endl;
			logfile << "500" << endl;
			logfile << "======================" << endl;
			logfile.close();
			return false;
		}
	}
	else
	{
		cout << "========ERROR========" << endl;
		cout << "500" << endl;
		cout << "======================" << endl;
		logfile << "========ERROR========" << endl;
		logfile << "500" << endl;
		logfile << "======================" << endl;
		logfile.close();
		return false;
	}

	return true;
}

bool Manager::SEARCH()
{
	int is = 1; //declare is and set as 1
	WordNode* temp; //declare wordnode temp
	ofstream logfile; //declare logfile
	logfile.open("log.txt", ios::app); //open log.txt
	temp = queue->Search(tok2); //temp is queue search tok2
	if (temp == '\0') //if temp is null
	{
		is = 0; //is is 0
	}
	else
	{
		cout << "========SEARCH========" << endl;
		cout << temp->GetWord() << " " << temp->GetMean() << endl;
		cout << "=======================" << endl;
		logfile << "========SEARCH========" << endl;
		logfile << temp->GetWord() << " " << temp->GetMean() << endl;
		logfile << "=======================" << endl;
		logfile.close();
		return true;
	}


	temp = bst->Search(tok2[0])->GetBST()->Search(tok2); //temp is bst search tok2[0] getbst search tok2
	if (temp == '\0') //if temp is null
	{
		is = 0;
	}
	else
	{
		cout << "========SEARCH========" << endl;
		cout << temp->GetWord() << " " << temp->GetMean() << endl;
		cout << "=======================" << endl;
		logfile << "========SEARCH========" << endl;
		logfile << temp->GetWord() << " " << temp->GetMean() << endl;
		logfile << "=======================" << endl;
		logfile.close();
		return true;
	}

	temp = cll->Search(tok2); //temp is cll search tok2
	if (temp == '\0') //if temp is null
	{
		is = 0; //is is 0
	}
	else
	{
		cout << "========SEARCH========" << endl;
		cout << temp->GetWord() << " " << temp->GetMean() << endl;
		cout << "=======================" << endl;
		logfile << "========SEARCH========" << endl;
		logfile << temp->GetWord() << " " << temp->GetMean() << endl;
		logfile << "=======================" << endl;
		logfile.close(); //close logfile
		return true;
	}
	if (is == 0) //if is is 0
	{
		cout << "========ERROR=========" << endl;
		cout << "600" << endl;
		cout << "=======================" << endl;
		logfile << "========ERROR=========" << endl;
		logfile << "600" << endl;
		logfile << "=======================" << endl;
		logfile.close();
		return false;
	}
}
bool Manager::UPDATE()
{
	ofstream logfile; //declare logfile
	logfile.open("log.txt", ios::app); //open log.txt
	WordNode* temp; //declare wordnode temp
	temp = queue->Search(tok2);
	if (temp != '\0')
	{
		cout << "========UPDATE========" << endl;
		cout << temp->GetWord() << " " << temp->GetMean();

		logfile << "========UPDATE========" << endl;
		logfile << temp->GetWord() << " " << temp->GetMean();
		temp->SetMean(tok3); // update mean
		cout << " -> " << temp->GetMean() << endl;
		cout << "=======================" << endl;

		logfile << " -> " << temp->GetMean() << endl;
		logfile << "=======================" << endl;
		logfile.close();
		return true;
	}

	temp = bst->Search(tok2[0])->GetBST()->Search(tok2); //temp is bst serach tok2[0] getbst search tok2
	if (temp != '\0') // if temp is not a null
	{
		cout << "========UPDATE========" << endl;
		cout << temp->GetWord() << " " << temp->GetMean();
		logfile << "========UPDATE========" << endl;
		logfile << temp->GetWord() << " " << temp->GetMean();
		temp->SetMean(tok3); // update mean
		cout << " -> " << temp->GetMean() << endl;
		cout << "=======================" << endl;
		logfile << " -> " << temp->GetMean() << endl;
		logfile << "=======================" << endl;
		logfile.close(); //close logfile
		return true;
	}

	temp = cll->Search(tok2); //temp is cll search tok2
	if (temp != '\0') //if temp is not null
	{
		cout << "========UPDATE========" << endl;
		cout << temp->GetWord() << " " << temp->GetMean();
		logfile << "========UPDATE========" << endl;
		logfile << temp->GetWord() << " " << temp->GetMean();
		temp->SetMean(tok3); // update mean
		cout << " -> " << temp->GetMean() << endl;
		cout << "=======================" << endl;
		logfile << " -> " << temp->GetMean() << endl;
		logfile << "=======================" << endl;
		logfile.close();
		return true;
	}
	cout << "========ERROR========" << endl;
	cout << "800" << endl;
	cout << "=======================" << endl;
	logfile << "========ERROR========" << endl;
	logfile << "800" << endl;
	logfile << "=======================" << endl;
	logfile.close(); //close logfile

}
bool Manager::PRINT()
{
	ChoosePrint(tok2, tok3);//implement tok2, tok3
	return true;
}
void Manager::ChoosePrint(char* a2, char* a3)
{
	char whichfile[3][13] = { "TO_MEMORIZE", "MEMORIZING", "MEMORIZED" };

	if (strcmp(a2, whichfile[0]) == 0) //if a2 is same as whichfile[0]
	{
		queue->Print(); //implement queue print
		return;
	}
	if (strcmp(a2, whichfile[1]) == 0) //if a2 is same as whichfile[1]
	{
		bst->Print(a3); //implement bst print(a3)
		return;
	}
	if (strcmp(a2, whichfile[2]) == 0) //if a2 is same as whichfile[2]
	{
		cll->Print(); //implement cll print
		return;
	}

}
void Manager::ComImple(char* tok1, char* tok2, char* tok3)
{
	ofstream logfile; //declare lofile
	logfile.open("log.txt", ios::app); //open log.txt
	if (strcmp(tok1, "LOAD") == 0) //if tok1 is same as load
	{
		if (tok2 != '\0') //if tok2 is not same as null
		{
			logfile << "========ERROR========" << endl;
			logfile << "100" << endl;
			logfile << "======================" << endl;
			cout << "========ERROR========" << endl;
			cout << "100" << endl;
			cout << "======================" << endl;
			return;
		}
		LOAD(); //implement load
		return;
	}
	if (strcmp(tok1, "ADD") == 0) //if oke1 is same as add
	{
		if (tok2 != '\0') //if tok2 is not null
		{
			logfile << "========ERROR========" << endl;
			logfile << "200" << endl;
			logfile << "======================" << endl;
			cout << "========ERROR========" << endl;
			cout << "200" << endl;
			cout << "======================" << endl;
			return;
		}
		ADD(); //implement ADD
		return; //return
	}
	if (strcmp(tok1, "MOVE") == 0) //if tok1 is same as move
	{
		if (tok3 != '\0')//if tok3 is not null
		{
			logfile << "========ERROR========" << endl;
			logfile << "300" << endl;
			logfile << "======================" << endl;
			cout << "========ERROR========" << endl;
			cout << "300" << endl;
			cout << "======================" << endl;
			return;
		}
		MOVE(); //implement MOVE
		return;
	}
	if (strcmp(tok1, "SAVE") == 0)//if tok1 is same as save
	{

		if (tok2 != '\0') //if tok2 is not null
		{
			logfile << "========ERROR========" << endl;
			logfile << "400" << endl;
			logfile << "======================" << endl;

			cout << "========ERROR========" << endl;
			cout << "400" << endl;
			cout << "======================" << endl;
			return;
		}
		SAVE();//implement SAVE
		return;
	}
	if (strcmp(tok1, "TEST") == 0)//TEST
	{
		TEST(); //implement TEST
		return;
	}
	if (strcmp(tok1, "SEARCH") == 0)//SEARCH
	{
		SEARCH(); //implement SEARCH
		return;
	}
	if (strcmp(tok1, "PRINT") == 0) //PRINT
	{
		PRINT();//implement PRINT
		return;
	}
	if (strcmp(tok1, "UPDATE") == 0)//UPDATE
	{
		UPDATE();//implement UPDATE
		return;
	}

	logfile.close(); //close 
};

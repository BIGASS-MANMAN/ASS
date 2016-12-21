#include "/usr/local/Auto_Scoring_System/src/signal.h"
#include "Manager.h"  // include header
#include <iostream>
using namespace std;
char print_struc[128] = { 0 };    //To declare grobal value for saving data
char print_struc_method[128] = { 0 };

char test_word[128] = { 0 };
char test_mean[128] = { 0 };

char update_word[128] = { 0 };
char update_mean[128] = { 0 };

char search_word[128] = { 0 };

char* Strlwr(char *s1)       //change for lowercase 
{
	char* s2 = NULL;
	for (s2 = s1;*s2; ++s2)
	{
		if ('A' <= *s2  && *s2 <= 'Z')
		{
			*s2 += 'a' - 'A';
		}
	}
	return s1;
}

Manager::Manager()  //constructor
{
	cll = new CircularLinkedList;
	bst = new AlphabetBST;
	queue = new Queue;
}


Manager::~Manager() //destructor
{ return;

	delete cll;
	delete bst;
	delete queue;
}


void Manager::run(const char * command)	//perform until end of file command
{
	struct sigaction sa;
	set_sigaction(sa);
	alarm(3);

	int i = 0; int want_move = 0; int check = 0;
	char data2[50][30] = { 0 };
	char *pStr = NULL;    // To save str_r return value 
	char *ppStr = NULL;   // To save in remain string pointer 
	ifstream fin; ofstream ouf;
	fin.open(command);
	char  log[8] = "log.txt";
	ouf.open(log, ios::app);

	while (!fin.eof())
	{
		fin.getline(data2[i], 30);
		pStr = new char[strlen(data2[i]) + 1];
		pStr = strtok(data2[i], " \n");      //command
		if (pStr != NULL)           //command exist
		{
			if (strcmp(pStr, "LOAD") == 0)//if command LOAD
			{
				ppStr = new char[strlen(pStr) + 1];
				ppStr = strtok(NULL, "\n");
				if (!LOAD() || ppStr != NULL) //exception handling, if other string exist after command LOAD
				{
					ouf << "======== ERROR ========" << endl;
					ouf << "100" << endl;
					ouf << "=======================" << endl << endl; //command LOAD error code is 100
				}		 
				ppStr = 0;

			}
			else if (strcmp(pStr, "ADD") == 0)		//if command ADD
			{
				if (ADD())
				{
					ouf << "======== ADD ========" << endl;
					ouf << "Success" << endl;
					ouf << "======================" << endl << endl;
				}
				else		//exception handling, if other string exist after command ADD 
				{
					ouf << "======== ERROR ========" << endl;
					ouf << "200" << endl;
					ouf << "=======================" << endl << endl;
				}					
				ppStr = strtok(NULL, "\n");
				if (ppStr != NULL)		//command ADD error code is 200
				{
					ouf << "======== ERROR ========" << endl;
					ouf << "200" << endl;
					ouf << "=======================" << endl << endl;
				}
			}

			else if (strcmp(pStr, "MOVE") == 0)
			{
				ppStr = strtok(NULL, "\n");   
				if (ppStr == NULL)	//if don't give how many number of word to move, print error
				{
					ouf << "======== ERROR ========" << endl;
					ouf << "300" << endl;
					ouf << "=======================" << endl << endl;
				}			//command MOVE error code is 300
				else
				{
					want_move = atoi(ppStr);  //push user's wants move number

					WordNode* current = NULL;

					current = queue->getHead();

					while (current)
					{
						current = current->GetNext();  //queue's number of data is checked
						check++;
					}
					//if A user wants to save data in bst over than 100, print error message
					if (want_move + this->bst->GetWordCnt() > 100  || check == 0)
					{
						ouf << "======== ERROR ========" << endl;
						ouf << "300" << endl;
						ouf << "=======================" << endl << endl;

					}
					else if (want_move + bst->GetWordCnt() < 101)
					{
						for (int j = 0; j < want_move; j++)
						{
							//MOVE word to_memorize -> memorizing , number of want_move
							MOVE();
						}
						ouf << "======== MOVE =========" << endl;
						ouf << "Success" << endl;
						ouf << "======================" << endl << endl;
					}
				}
			}

			else if (strcmp(pStr, "SAVE") == 0)		//if command SAVE
			{
				ppStr = strtok(NULL, "\n");
				if (ppStr != NULL)
				{
					ouf << "======== ERROR ========" << endl;		//exception handling, if other string exist after command SAVE
					ouf << "400" << endl;
					ouf << "=======================" << endl << endl;
				}													//command SAVE error code is 400
				else
				{
					SAVE();
				}
			}

			else if (strcmp(pStr, "TEST") == 0)	//if command TEST
			{

				ppStr = strtok(NULL, " ");      	//exception handling, if word want to test doesn't exist after command TEST
				if (ppStr == NULL)
				{
					ouf << "======== ERROR ========" << endl;
					ouf << "500" << endl;
					ouf << "=======================" << endl << endl;
				}
				else			//command TEST error code is 500
				{

					strcpy(test_word,  Strlwr(ppStr) );	//if word is null, print error code
					ppStr = strtok(NULL, "\n");

					if (!ppStr)
					{
						ouf << "======== ERROR ========" << endl;
						ouf << "500" << endl;
						ouf << "=======================" << endl << endl;
					}
					else
					{
						//divide string word and mean, copy into each array and test
						strcpy(test_mean, Strlwr(ppStr));
						TEST();
					}
				}

			}
			else if (strcmp(pStr, "SEARCH") == 0)		//if command SEARCH
			{
				ppStr = strtok(NULL, "\n");	//exception handling, if word doesn't exist after command SEARCH
				if (ppStr == NULL)
				{
					ouf << "======== ERROR ========" << endl;
					ouf << "600" << endl;
					ouf << "=======================" << endl << endl;
				}			//command SEARCH error code is 600
				else
				{
					strcpy(search_word, ppStr);
					if (!SEARCH())		//if queue or bst or circularlinkedlist is null, print error message
					{
						ouf << "======== ERROR ========" << endl;
						ouf << "600" << endl;
						ouf << "======================" << endl << endl;
					}

				}
			}

			else if (strcmp(pStr, "PRINT") == 0)
			{
				ppStr = strtok(NULL, " ");//if queue or bst or circularlinkedlist is null, print error message
				if (ppStr == NULL)
				{
					ouf << "======== ERROR ========" << endl;
					ouf << "700" << endl;
					ouf << "=======================" << endl << endl;
				}		//command PRINT error code is 700
				else
				{
					strcpy(print_struc, ppStr);
					if (strcmp(print_struc, "MEMORIZING") == 0)
					{
						ppStr = strtok(NULL, "\n");   
						if (ppStr == NULL)
						{
							ouf << "======== ERROR ========" << endl;
							ouf << "700" << endl;
							ouf << "=======================" << endl << endl;
						}
						else
						{
							strcpy(print_struc_method, ppStr);
							if (!PRINT())//if bst is null
							{
								ouf << "======== ERROR ========" << endl;
								ouf << "700" << endl;
								ouf << "=======================" << endl << endl;
							}

						}
					}
					else if ((strcmp(print_struc, "TO_MEMORIZE") == 0) )		//command PRINT MEMORIZING
					{
						if (!PRINT())		//if queue is null
						{
							ouf << "======== ERROR ========" << endl;
							ouf << "700" << endl;
							ouf << "=======================" << endl << endl;
						}
					}
					else if (strcmp(print_struc, "MEMORIZED") == 0)	//command PRINT MEMORIZED
					{
						if (!PRINT())	//if circularlinkedlist is null
						{
							ouf << "======== ERROR ========" << endl;
							ouf << "700" << endl;
							ouf << "=======================" << endl << endl;
						}
					}
					else
					{
						ouf << "======== ERROR ========" << endl;
						ouf << "700" << endl;
						ouf << "=======================" << endl << endl;
					}
				}
			}
			else if (strcmp(pStr, "UPDATE") == 0)	//command UPDATE
			{
				ppStr = strtok(NULL, " ");	//after string UPDATE, if there is no word
				if (ppStr == NULL)
				{
					ouf << "======== ERROR ========" << endl;
					ouf << "800" << endl;
					ouf << "=======================" << endl << endl;
				}		//command UPDATE error code is 800
				else
				{
					strcpy(update_word, ppStr);
					ppStr = strtok(NULL, "\n");
					if (ppStr == NULL)
					{		//if there is no word mean
						ouf << "======== ERROR ========" << endl;
						ouf << "800" << endl;
						ouf << "=======================" << endl << endl;
					}
					else
					{
						strcpy(update_mean, ppStr);
						UPDATE();	  //update
					}
				}
			}

			else if (strcmp(pStr, "EXIT") == 0)	//command EXIT
			{
				return;
			}
		}
		i++;
	}
	pStr = 0;
	ppStr = 0;         //close fild and initialization value
	fin.close();
	ouf.close();
	return;
}


bool Manager::LOAD()
{
	ifstream inf_to; ifstream inf_ing; ifstream inf_ed;
	ofstream ouf;
	char  log[8]= "log.txt";
	char  to_memorize_word[21] = "to_memorize_word.txt";
	char  memorizing_word[20] = "memorizing_word.txt";
	char  memorized_word[19]= "memorized_word.txt";
	ouf.open(log, ios::app);
	inf_to.open(to_memorize_word); inf_ing.open(memorizing_word); inf_ed.open(memorized_word);
	WordNode * current = NULL; WordNode * temp = NULL;	//open to memorize and memorizing and memorized 

	char check1[128] = { 0 }; 	char check2[128] = { 0 }; 	char check3[128] = { 0 };
	if (!(inf_to.is_open()) || !(inf_ing.is_open()) || !(inf_ed.is_open()) ||
		(queue->IsEmpty()) || (this->bst->GetWordCnt() == 0) || (cll->IsEmpty()))
	{	//if to there is trouble open each text file or queue is empty or bst word is empty or CircularLinkedList is empty 
		inf_to.close();
		inf_ing.close();
		inf_ed.close();
		ouf.close();
		return false;
	}	//close to memorize and memorizing and memorized  and return false

	inf_to.getline(check1, 128); inf_ing.getline(check2, 128); inf_ed.getline(check3, 128);	
	if ( (strcmp(check1,"\0")==0) || (strcmp(check2, "\0") == 0) || (strcmp(check3, "\0") == 0) ||check1==NULL||check2==NULL||check3==NULL)
	{							// get line by line each text file to_memorize, memorizing, memorized word
		inf_to.close();
		inf_ing.close();
		inf_ed.close();
		ouf.close();
		return false;
	}				//If check1 eqaul \0 or check2 equal \0 or check equal \0 or check1 is NULL or check2 is NULL or check3 is NULL, close file and return false
	int i = 0;
	char data3[1000][128] = { 0 };
	char *word = NULL;    // To save word
	char *mean = NULL;   // To save in remain string pointer 

	current = cll->GetHead();	//is not until end of to memorized file
	temp = NULL;

	while (!inf_ed.eof())
	{
		inf_ed.getline(data3[i], 128);
		word = strtok(data3[i], "	");
		mean = strtok(NULL, "\n");	   //get line by line memorized word and mean
		if (word == NULL || mean == NULL)
		{
			break;
		}								// if word is NULL or mean is NULL, break
		if (current == NULL && queue->Search(word) == NULL && this->bst->Search(toupper(word[0]))->GetBST()->Search(word) == NULL&&
			cll->Search(word) == NULL)
		{
			current = new WordNode;
			current->SetWord(word);
			current->SetMean(mean);
			cll->Insert(current);
			i++;
		}									//insert set word and set mean at the head point
		else if (queue->Search(word) == NULL && this->bst->Search(toupper(word[0]))->GetBST()->Search(word) == NULL&&
			cll->Search(word) == NULL)
		{
			current = new WordNode;
			current->SetWord(word);
			current->SetMean(mean);
			cll->Insert(current);
			i++;
		}
	}									//insert set word and set mean at the rest point
	i = 0;


	temp = NULL;
	while (!inf_ing.eof())			//is not until end of memorizing file
	{
		inf_ing.getline(data3[i], 128);
		word = strtok(data3[i], "	");
		mean = strtok(NULL, "\n");		//get line by line memorizing word and mean
		if (word == NULL || mean == NULL)
		{
			break;
		}									//if word is NULL or mean is NULL, break
		current = this->bst->Search(toupper(word[0]))->GetBST()->GetRoot();

		if (current == NULL && queue->Search(word) == NULL && this->bst->Search(toupper(word[0]))->GetBST()->Search(word) == NULL&&
			cll->Search(word) == NULL)
		{
			current = new WordNode;
			current->SetWord(word);
			current->SetMean(mean);
			this->bst->Search(toupper(word[0]))->GetBST()->Insert(current);
			i++;
			bst->WordCount(1);					//Insert setword and setmean at the Head point

		}
		else if (queue->Search(word) == NULL && bst->Search(toupper(word[0]))->GetBST()->Search(word) == NULL&&
			cll->Search(word) == NULL)
		{
			current = new WordNode;
			current->SetWord(word);
			current->SetMean(mean);
			bst->Search(toupper(word[0]))->GetBST()->Insert(current);
			i++;
			bst->WordCount(1);
			if (bst->GetWordCnt() >= 100) break;		//Insert setword and setmean at the rest point up to 100
		}
	}
	i = 0;

	current = queue->getHead();

	while (!inf_to.eof())	//is not until end of to memorize file
	{
		inf_to.getline(data3[i], 128);
		word = strtok(data3[i], "	");
		mean = strtok(NULL, "\n");
		if (word == NULL || mean == NULL)
		{
			break;		//if word is NULL or mean is NULL, break
		}

		if (current == NULL && queue->Search(word) == NULL && this->bst->Search(toupper(word[0]))->GetBST()->Search(word) == NULL&&
			cll->Search(word) == NULL)
		{
			current = new WordNode;
			current->SetWord(word);
			current->SetMean(mean);
			queue->Push(current);
			i++;
		}		//Head point is push set word and set mean
		else if (queue->Search(word) == NULL &&this->bst->Search(toupper(word[0]))->GetBST()->Search(word) == NULL&&
			cll->Search(word) == NULL)
		{
			current = new WordNode;
			current->SetWord(word);
			current->SetMean(mean);
			queue->Push(current);
			i++;
		}			//The rest point is push set word and set mean
	}
	i = 0;

	ouf << "======== LOAD ========" << endl;
	ouf << "Success" << endl;
	ouf << "======================" << endl << endl;
	inf_to.close();
	inf_ing.close();
	inf_ed.close();				//Print LOAD and close to memorize and memorizing and memorized and return true
	ouf.close();
	return true;
}

bool Manager::ADD()
{
	ifstream inf;  ofstream ouf;
	char *word = NULL;    // To save word
	char *mean = NULL;   // To save in remain string pointer 
	char data[310][128] = { 0 }; int j = 0;

	char  word2[9] = "word.txt";
	inf.open(word2);
	char  log[8] = "log.txt";
	ouf.open(log, ios::app);
	inf.getline(data[j], 128);		// get line by line word.txt 

	word = strtok(data[j], "	");      //command
	mean = strtok(NULL, "\n");			//didvide string into word and mean
	if (!inf || inf.eof() || word == NULL || strcmp(word,"\0")==0)	//exception handling if word.txt no exist or word in the text file is null or \0
	{
		ouf << "======== ERROR ========" << endl;
		ouf << "200" << endl;
		ouf << "=======================" << endl << endl;;
		inf.close();
		return false;						//command ADD error code is 200
	}
	else
	{
		WordNode* current = queue->getHead();
		WordNode* temp = NULL;
		if (current == NULL)
		{
			if (queue->Search(word) == NULL && this->bst->Search(toupper(word[0]))->GetBST()->Search(word) == NULL&&
				cll->Search(word) == NULL)        
			{
				temp = new WordNode;
				temp->SetWord(word);
				temp->SetMean(mean);
				queue->Push(temp);
				j++;					//insert set word and set mean at the head point
			}
		}

		while (!inf.eof())			// get line by line word.txt 
		{
			inf.getline(data[j], 128);
			word = strtok(data[j], "	");
			mean = strtok(NULL, "\n");
			if (mean == NULL)
			{
				break;
			}
			if (queue->Search(word) == NULL &&this->bst->Search(toupper(word[0]))->GetBST()->Search(word) == NULL&&
				cll->Search(word) == NULL)						//insert set word and set mean	
			{
				temp = new WordNode;
				temp->SetWord(word);
				temp->SetMean(mean);
				queue->Push(temp);
				j++;
			}
		}
		inf.close();         //close the fild and return 
		ouf.close();
		return true;
	}

}

bool Manager::MOVE()				 //MOVE
{
	char* read = NULL;
	WordNode * temp = NULL;
	AlphabetNode* MoveNode = NULL;

	temp = queue->Pop();

	if (temp == NULL && bst->GetWordCnt() > 100)
	{
		return false;				//temp is NULL and bst word is more than 100, return false
	}

	read = new char[strlen(temp->GetWord()) + 1];		 // word copy at the read
	strcpy(read, temp->GetWord());

	if (this->bst->Search(toupper(read[0]))->GetBST()->Search(read)==NULL)
	{
		this->bst->Search(toupper(read[0]))->GetBST()->Insert(temp);
		this->bst->WordCount(1);				 //if search word of bst is NULL, Insert Pop of Queue and Count is 1

	}
	delete read;			//delete read and return true
	return true;
}


bool Manager::SAVE()
{
	ofstream ouf;
	char  log[8] = "log.txt";			//log.txt file open
	ouf.open(log,ios::app);
	if (!(queue->Save() && this->bst->Save() && cll->Save()))
	{

		ouf << "======== ERROR ========" << endl;
		ouf << "400" << endl;
		ouf << "=======================" << endl << endl;
		ouf.close();
		return false;				//if saved queue is not exist and saved bst is exist and CircularLinkedList is exist, Print ERROR and Close File and return false
	}
	else
	{
		ouf << "======== SAVE ========" << endl;
		ouf << "Success" << endl;
		ouf << "======================" << endl << endl; 
		ouf.close();
		return true;			//print Success Save and close file and return true
	}
}

bool Manager::TEST()            
{
	WordNode * test = NULL;
	WordNode * temp = NULL;
	ofstream ouf;
	char  log[8] = "log.txt";          //open log fild
	ouf.open(log, ios::app);

	test = this->bst->Search(toupper(test_word[0]))->GetBST()->Search(test_word);
	//search data and store to tset value
	if (test==NULL ||strcmp(test_mean, test->GetMean()) != 0) //if not found data
	{

		ouf << "======== ERROR ========" << endl;
		ouf << "500" << endl;
		ouf << "=======================" << endl << endl;
		return false;
	}

	else
	{

		ouf << "======== TEST ========" << endl;
		ouf << "Pass" << endl;
		ouf << "=======================" << endl << endl;
		temp = this->bst->Search(toupper(test_word[0]))->GetBST()->Delete(test_word); //get information about test
		this->bst->WordCount(2); //wordcount --;
		cll->Insert(temp);  //insert to CLL
		ouf.close();        //close the fild and return 
		return true;
	}

}

bool Manager::SEARCH()     
{
	ofstream ouf; 
	char  log[8] = "log.txt";      //open fild
	ouf.open(log, ios::app);
	WordNode* Queue = NULL;
	WordNode* BST = NULL;
	WordNode* CLL = NULL;
	WordNode* temp = NULL;
	Queue = queue->Search(Strlwr(search_word));          //Search Queue, BST, CLL
	BST = this->bst->Search(toupper(search_word[0]))->GetBST()->Search(Strlwr(search_word));
	CLL = cll->Search(Strlwr(search_word));

	if (Queue == NULL&&BST == NULL&&CLL == NULL)    //if not found data, return false
	{
		return false;
	}
	else
	{
		if (Queue == NULL)
		{
			if (BST == NULL)
			{
				temp = CLL;    //if it is founded in cll, temp is cll       
			}
			else
			{
				temp = BST;         //if it is founded in bst, temp is bst
			}
		}
		else
		{
			temp = Queue;       //if it is founded in queue, temp is queue
		}
		ouf << "======== SEARCH ========" << endl;        //print result
		ouf << temp->GetWord() << " " << temp->GetMean() << endl;
		ouf << "=======================" << endl << endl;
		return true;
	}
}

bool Manager::PRINT()
{
	ofstream ouf;
	char  log[8] = "log.txt";           //open file
	ouf.open(log, ios::app);
	if (strcmp(print_struc, "TO_MEMORIZE") == 0)     //print queue
	{
		WordNode* current = queue->getHead();
		if (current == NULL)               //exception handling
		{
			return false;
		}
		ouf << "======== PRINT ========" << endl;
		while (current)
		{
			if (current->GetWord() == NULL || current->GetMean() == NULL)
			{

				return false;
			}
			ouf << current->GetWord() << " " << current->GetMean() << endl;
			current = current->GetNext();
		}
		ouf << "=====================" << endl << endl;
		ouf.close();
		return true;
	}
	else if (strcmp(print_struc, "MEMORIZED") == 0)       //print cll
	{
		WordNode* current = cll->GetHead();
		if (current == NULL)		//exception handling
		{
			return false;
		}
		ouf << "======== PRINT ========" << endl;
		while (current)
		{
			;
			if (current->GetWord() == NULL || current->GetMean() == NULL)  
			{
				return false;
			}
			ouf << current->GetWord() << " " << current->GetMean() << endl;
			if (current->GetNext() == cll->GetHead())
			{
				break;
			}
			current = current->GetNext();
		}
		ouf << "=====================" << endl << endl;
		ouf.close();
		return true;
	}
	else if (strcmp(print_struc, "MEMORIZING") == 0)	 //print bst
	{
		if (print_struc_method == NULL)			//exception handling
		{
			ouf.close();
			return false;
		}
		else
		{
			if (this->bst->Print(print_struc_method)) 
			{
				ouf.close();
				return true; // if print is true, return true
			}
			else 
			{
				ouf.close();
				return	false;                                   //or false

			}
		}
	}
	return false;
}

bool Manager::UPDATE()      //update
{
	ofstream ouf;
	char  log[8] = "log.txt";
	ouf.open(log, ios_base::app);      //open file
	WordNode * current = NULL;
	if (queue->Search(update_word) != NULL || this->bst->Search(toupper(update_word[0]))->GetBST()->Search(Strlwr(update_word)) != NULL || cll->Search(update_word) != NULL)
	{                                                      //If the data is found in structure,

		if (queue->Search(update_word) != NULL)            //if the data is found in queue
		{
			ouf << "======== UPDATE ========" << endl;          //print the data before updating
			ouf << queue->Search(update_word)->GetWord() << " " << queue->Search(update_word)->GetMean() << " -> ";
			queue->Search(update_word)->SetMean(update_mean);
			ouf << queue->Search(update_word)->GetMean() << endl;	//print the data after updating
			ouf << "=======================" << endl << endl;
		}
		else if (cll->Search(update_word) != NULL)  //if the data is found in cll
		{
			ouf << "======== UPDATE ========" << endl;		//print the data before updating
			ouf << cll->Search(update_word)->GetWord() << " " << cll->Search(update_word)->GetMean() << " -> ";
			cll->Search(update_word)->SetMean(update_mean);
			ouf << cll->Search(update_word)->GetMean() << endl;			//print the data after updating
				ouf << "=======================" << endl << endl;
		}
		else										  //if the data is found in bst
		{

			ouf << "======== UPDATE ========" << endl;			//print the data before updating
			ouf << bst->Search(toupper(update_word[0]))->GetBST()->Search(Strlwr(update_word))->GetWord() << " " <<
				bst->Search(toupper(update_word[0]))->GetBST()->Search(Strlwr(update_word))->GetMean() << " -> ";
			bst->Search(toupper(update_word[0]))->GetBST()->Search(Strlwr(update_word))->SetMean(update_mean);		//print the data after updating
				ouf << bst->Search(toupper(update_word[0]))->GetBST()->Search(Strlwr(update_word))->GetMean() << endl;
			ouf << "=======================" << endl << endl;
		}
		ouf.close();                //close the fild and return
		return true;
	}
	else
	{
		ouf << "======== ERROR ========" << endl;			//exception handling
		ouf << "800" << endl;
		ouf << "=======================" << endl << endl;
		ouf.close();					         //close the fild and return
		return false;
	}
}

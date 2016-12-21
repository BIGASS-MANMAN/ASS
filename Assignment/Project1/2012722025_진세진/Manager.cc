#include "/usr/local/Auto_Scoring_System/src/signal.h"
#include <iostream>
#include "Manager.h"
#include <fstream>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
using namespace std;


Manager::Manager()
{
	cll = new CircularLinkedList;
	bst = new AlphabetBST;
	queue = new Queue;
	
	cmd = new char[256]();
	cmd1 = new char[256]();
	cmd2 = new char[256]();
	cmd3 = new char[256]();
	cmd4 = new char[256]();
}


Manager::~Manager()
{ return;

	delete bst;
	delete queue;

	delete cmd;
	delete cmd1;
	delete cmd2;
	delete cmd3;
	delete cmd4;
}

void Manager::run(const char * command)
{
	struct sigaction sa;
	set_sigaction(sa);
	alarm(3);

	ifstream fin; //input file stream
	ofstream log; //output file strea
	int i = 0; 
	char* ptr;

	fin.open(command); //connect command.txt 
	log.open("log.txt",ios::trunc); //connect log.txt
	if(!fin.is_open())
		return;

	while (!fin.eof()) //get one line on command.txt
	{
		fin.getline(cmd, 256);
		//command parameter 1, 2, 3 reset
		memset(cmd1,'\0',256);//command reset;
		memset(cmd2,'\0',256);//command reset;
		memset(cmd3,'\0',256);//command reset;
		memset(cmd4,'\0',256);//command reset;

		//command parameter 1 set
		ptr = strtok(cmd," ");
		if(ptr != '\0')
			strcpy(cmd1,ptr);
		for(i=0;cmd1[i]!='\0';i++)
		{
			if(cmd1[i] == '\r')
			{
				cmd1[i] = '\0';
				break;
			}
		}
		ptr = strtok(NULL," ");
		if(ptr != NULL)
			strcpy(cmd2,ptr);
		for(i=0;cmd2[i]!='\0';i++)
		{
			if(cmd2[i] == '\r')
			{
				cmd2[i] = '\0';
				break;
			}
		}
		ptr = strtok(NULL," ");
		if(ptr != NULL)
			strcpy(cmd3,ptr);
		for(i=0;cmd3[i]!='\0';i++)
		{
			if(cmd3[i] == '\r')
			{
				cmd3[i] = '\0';
				break;
			}
		}
		ptr = strtok(NULL," ");
		if(ptr != NULL)
			strcpy(cmd4,ptr);
		for(i=0;cmd4[i]!='\0';i++)
		{
			if(cmd4[i] == '\r')
			{
				cmd4[i] = '\0';
				break;
			}
		}

		

		//if command parameter 4 exists (parameter too many), error prints. 
		if (cmd4[0])	
		{
			if(!strcmp(cmd1, "LOAD")) //LOAD error print
			{
				log << "======= ERROR ======" << endl;
				log << "100" << endl;
				log << "====================" << endl;
				cout << "======= ERROR ======" << endl;
				cout << "100" << endl;
				cout << "====================" << endl;
			}
			else if(!strcmp(cmd1, "ADD")) //ADD error print
			{
				log << "======= ERROR ======" << endl;
				log << "200" << endl;
				log << "====================" << endl;
				cout << "======= ERROR ======" << endl;
				cout << "200" << endl;
				cout << "====================" << endl;
			}
			else if(!strcmp(cmd1, "MOVE")) //MOVE error print
			{
				log << "======= ERROR ======" << endl;
				log << "300" << endl;
				log << "====================" << endl;
				cout << "======= ERROR ======" << endl;
				cout << "300" << endl;
				cout << "====================" << endl;
			}
			else if(!strcmp(cmd1, "SAVE")) //SAVE error print
			{
				log << "======= ERROR ======" << endl;
				log << "400" << endl;
				log << "====================" << endl;
				cout << "======= ERROR ======" << endl;
				cout << "400" << endl;
				cout << "====================" << endl;
			}
			else if(!strcmp(cmd1, "TEST")) //TEST error print
			{
				log << "======= ERROR ======" << endl;
				log << "500" << endl;
				log << "====================" << endl;
				cout << "======= ERROR ======" << endl;
				cout << "500" << endl;
				cout << "====================" << endl;
			}
			else if(!strcmp(cmd1, "SEARCH")) //SEARCH error print
			{
				log << "======= ERROR ======" << endl;
				log << "600" << endl;
				log << "====================" << endl;
				cout << "======= ERROR ======" << endl;
				cout << "600" << endl;
				cout << "====================" << endl;
			}
			else if(!strcmp(cmd1, "PRINT")) //PRINT error print
			{
				log << "======= ERROR ======" << endl;
				log << "700" << endl;
				log << "====================" << endl;
				cout << "======= ERROR ======" << endl;
				cout << "700" << endl;
				cout << "====================" << endl;
			}
			else if(!strcmp(cmd1, "UPDATE")) //UPDATE error print
			{
				log << "======= ERROR ======" << endl;
				log << "800" << endl;
				log << "====================" << endl;
				cout << "======= ERROR ======" << endl;
				cout << "800" << endl;
				cout << "====================" << endl;
			}
			else				 //command error print
			{
				log << "======= ERROR ======" << endl;
				log << "command error" << endl;
				log << "====================" << endl;
				cout << "======= ERROR ======" << endl;
				cout << "command error" << endl;
				cout << "====================" << endl;
			}

			memset(cmd, '\0', 256); //command reset;
				

			continue; //go next command
		}

		/* 
		if each command has too many or too little parameter, error prints.
		if each command function fails, error prints.
			else, print success message depending on each command.
			PRINT, SERCH and UPDATE print success message in function.
		*/
		
		if (!strcmp(cmd1, "LOAD")) //LOAD
		{
			if (cmd3[0] || cmd2[0]) //if parameter 2 or 3 exists(too many parameter)
			{
				//LOAD error print
				log << "======= ERROR ======" << endl;
				log << "100" << endl;
				log << "====================" << endl;
				cout << "======= ERROR ======" << endl;
				cout << "100" << endl;
				cout << "====================" << endl;
			}
			else
			{
				if (!LOAD())// if LOAD function fails,
				{
					//LOAD error print
					log << "======= ERROR ======" << endl;
					log << "100" << endl;
					log << "====================" << endl;
					cout << "======= ERROR ======" << endl;
					cout << "100" << endl;
					cout << "====================" << endl;
				}
				else //if LOAD function succeed
				{
					//print LOAD success message
					log << "======= LOAD ======" << endl;
					log << "Success" << endl;
					log << "====================" << endl;
					cout << "======= LOAD ======" << endl;
					cout << "Success" << endl;
					cout << "====================" << endl;
				}
			}
		}
		else if (!strcmp(cmd1, "ADD")) //ADD
		{
			if (cmd3[0] || cmd2[0]) //if parameter 2 or 3 exists(too many parameter)
			{
				//ADD error print
				log << "======= ERROR ======" << endl;
				log << "200" << endl;
				log << "====================" << endl;
				cout << "======= ERROR ======" << endl;
				cout << "200" << endl;
				cout << "====================" << endl;
			}
			else
			{
				if (!(ADD()))// if ADD function fails,
				{
					//ADD error print
					log << "======= ERROR ======" << endl;
					log << "200" << endl;
					log << "====================" << endl;
					cout << "======= ERROR ======" << endl;
					cout << "200" << endl;
					cout << "====================" << endl;
				}
				else //if LOAD function succeed
				{
					//print ADD success message
					log << "======= ADD ======" << endl;
					log << "Success" << endl;
					log << "====================" << endl;
					cout << "======= ADD ======" << endl;
					cout << "Success" << endl;
					cout << "====================" << endl;
				}
			}
		}
		else if (!strcmp(cmd1, "MOVE")) //MOVE
		{
			if (cmd3[0])//if parameter 3  exists(too many parameter)
			{
				//MOVE error print
				log << "======= ERROR ======" << endl;
				log << "300" << endl;
				log << "====================" << endl;
				cout << "======= ERROR ======" << endl;
				cout << "300" << endl;
				cout << "====================" << endl;
			}
			else if(cmd2[0])//if parameter 2  exists
			{
				if (!(MOVE()))// if MOVE function fails,
				{
					//MOVE error print
					log << "======= ERROR ======" << endl;
					log << "300" << endl;
					log << "====================" << endl;
					cout << "======= ERROR ======" << endl;
					cout << "300" << endl;
					cout << "====================" << endl;
				}
				else//if MOVE function succeed
				{
					//MOVE success message
					log << "======= MOVE ======" << endl;
					log << "Success" << endl;
					log << "====================" << endl;
					cout << "======= MOVE ======" << endl;
					cout << "Success" << endl;
					cout << "====================" << endl;
				}
			}
			else //if parameter 2 do not exist(parameter not enough)
			{
				//MOVE error print
				log << "======= ERROR ======" << endl;
				log << "300" << endl;
				log << "====================" << endl;
				cout << "======= ERROR ======" << endl;
				cout << "300" << endl;
				cout << "====================" << endl;
			}

		}
		else if (!strcmp(cmd1, "SAVE")) //SAVE
		{
			if (cmd3[0] || cmd2[0])//if parameter 2 or 3 exists(too many parameter)
			{
				//SAVE error print
				log << "======= ERROR ======" << endl;
				log << "400" << endl;
				log << "====================" << endl;
				cout << "======= ERROR ======" << endl;
				cout << "400" << endl;
				cout << "====================" << endl;
			}
			else
			{
				if (!(SAVE())) // if SAVE function fails,
				{
					//SAVE error print
					log << "======= ERROR ======" << endl;
					log << "400" << endl;
					log << "====================" << endl;
					cout << "======= ERROR ======" << endl;
					cout << "400" << endl;
					cout << "====================" << endl;
				}
				else	//if SAVE function succeed
				{
					//SAVE success message
					log << "======= SAVE ======" << endl;
					log << "Success" << endl;
					log << "====================" << endl;
					cout << "======= SAVE ======" << endl;
					cout << "Success" << endl;
					cout << "====================" << endl;
				}
			}

		}
		else if (!strcmp(cmd1, "TEST")) //TEST
		{
			if (!cmd3[0] || !cmd2[0]) //if parameter 2 or 3 do not exist(parameter not enough)
			{
				//TEST error print
				log << "======= ERROR ======" << endl;
				log << "500" << endl;
				log << "====================" << endl;
				cout << "======= ERROR ======" << endl;
				cout << "500" << endl;
				cout << "====================" << endl;
			}
			else
			{
				if (!(TEST())) // if TEST function fails,
				{
					//TEST error print
					log << "======= ERROR ======" << endl;
					log << "500" << endl;
					log << "====================" << endl;
					cout << "======= ERROR ======" << endl;
					cout << "500" << endl;
					cout << "====================" << endl;
				}
				else //if TEST function succeed
				{
					//TEST success message
					log << "======= TEST ======" << endl;
					log << "Pass" << endl;
					log << "====================" << endl;
					cout << "======= TEST ======" << endl;
					cout << "Pass" << endl;
					cout << "====================" << endl;
				}
			}
		}
		else if (!strcmp(cmd1, "SEARCH")) //SEARCH 
		{
			if (cmd3[0]) //if parameter 3  exists(too many parameter)
			{
				//SEARCH error print
				log << "======= ERROR ======" << endl;
				log << "600" << endl;
				log << "====================" << endl;
				cout << "======= ERROR ======" << endl;
				cout << "600" << endl;
				cout << "====================" << endl;
			}
			else if (cmd2[0])//if parameter 2  exists
			{
				// SEARCH success message is in SEARCH function
				if (!(SEARCH())) // if SEARCH function fails,
				{
					//SEARCH error print
					log << "======= ERROR ======" << endl;
					log << "600" << endl;
					log << "====================" << endl;
					cout << "======= ERROR ======" << endl;
					cout << "600" << endl;
					cout << "====================" << endl;
				}
			}
			else //if parameter 2 do not exist(parameter not enough)
			{
				//SEARCH error print
				log << "======= ERROR ======" << endl;
				log << "600" << endl;
				log << "====================" << endl;
				cout << "======= ERROR ======" << endl;
				cout << "600" << endl;
				cout << "====================" << endl;
			}

		}
		else if (!strcmp(cmd1, "PRINT")) //PRINT
		{
			if (!cmd2[0])//if parameter 2 do not exists(parameter not enough)
			{
				//PRINT error print
				log << "======= ERROR ======" << endl;
				log << "700" << endl;
				log << "====================" << endl;
				cout << "======= ERROR ======" << endl;
				cout << "700" << endl;
				cout << "====================" << endl;
			}
			//if prameter 2 is "MEMORIZING" and parameter 3 do not exist(parameter not enough)
			else if (!strcmp(cmd2, "MEMORIZING") && !cmd3[0])
			{
				
				//PRINT error print
				log << "======= ERROR ======" << endl;
				log << "700" << endl;
				log << "====================" << endl;
				cout << "======= ERROR ======" << endl;
				cout << "700" << endl;
				cout << "====================" << endl;
				
			}
			else
			{
				// PRINT success message is in PRINT function
				if (!(PRINT())) // if PRINT function fails,
				{
					//PRINT error print
					log << "======= ERROR ======" << endl;
					log << "700" << endl;
					log << "====================" << endl;
					cout << "======= ERROR ======" << endl;
					cout << "700" << endl;
					cout << "====================" << endl;
				}
			}
		}
		else if (!strcmp(cmd1, "UPDATE")) //UPDATE
		{
			if (!cmd3[0] || !cmd2[0]) //if parameter 2 or 3 do not exist(parameter not enough)
			{
				//UPDATE error print
				log << "======= ERROR ======" << endl;
				log << "800" << endl;
				log << "====================" << endl;
				cout << "======= ERROR ======" << endl;
				cout << "800" << endl;
				cout << "====================" << endl;
			}
			else
			{
				// UPDATE success message is in UPDATE function
				if (!(UPDATE())) // if UPDATE function fails,
				{
					//UPDATE error print
					log << "======= ERROR ======" << endl;
					log << "800" << endl;
					log << "====================" << endl;
					cout << "======= ERROR ======" << endl;
					cout << "800" << endl;
					cout << "====================" << endl;
				}

			}
		}
		else if (!strcmp(cmd1, "EXIT")) //EXIT
		{
			break;
		}

		memset(cmd,'\0',256); //command reset;

	}
	fin.close(); //disconnect command.txt
	log.close(); //disconnaect log.txt
	
	return; 
}

bool Manager::LOAD()
{
	WordBST* wbst;
	ifstream fin;
	char buf[256];
	char word[256],mean[256];
	char* ptr;
	
	fin.open("to_memorize_word.txt");	//connect to_memorize_word.txt
	if(!fin.is_open())			//if file doesn't exist return false
		return false;
	while(!fin.eof())			//until end of file
	{
		fin.getline(buf,256);		//get line by line
		ptr = strtok(buf,"	");	//take token with tab
		if(ptr == NULL)			//if string has some problem file is over
			break;
		strcpy(word,ptr);
		ptr = strtok(NULL, "	");
		if(ptr == NULL)
			break;
		strcpy(mean,ptr);
		queue->Push(word,mean);		//if there isn't any problems push into Queue
		memset(word, '\0', 256);	//reset buffers
		memset(mean, '\0', 256);
		memset(buf, '\0', 256);
	}
	fin.close();

	fin.open("memorizing_word.txt");	//connect to memorizing_word.txt
	if(!fin.is_open())			//if there isn't such file return false
		return false;
	while(!fin.eof())			//until end of file
	{
		fin.getline(buf,256);
		ptr = strtok(buf,"	");
		if(ptr == NULL)
			break;
		strcpy(word,ptr);
		ptr = strtok(NULL, "	");
		if(ptr == NULL)
			break;
		strcpy(mean,ptr);
		wbst = bst->Search((char)toupper(word[0]))->GetBST();
		wbst->Insert(word,mean);
		bst->WordCnt++;
		memset(word, '\0', 256);
		memset(mean, '\0', 256);
		memset(buf, '\0', 256);
	}
	fin.close();

	fin.open("memorized_word.txt");
	if(!fin.is_open())
		return false;
	while(!fin.eof())
	{
		fin.getline(buf,256);
		ptr = strtok(buf,"	");
		if(ptr == NULL)
			break;
		strcpy(word,ptr);
		ptr = strtok(NULL, "	");
		if(ptr == NULL)
			break;
		strcpy(mean,ptr);
		cll->Insert(word,mean);
		memset(word, '\0', 256);
		memset(mean, '\0', 256);
		memset(buf, '\0', 256);
	}
	fin.close();
	return true;
}

bool Manager::ADD()
{
	ifstream fin;
	char buf[256];
	char word[256],mean[256];
	char* ptr;
	WordNode* ptr1,*ptr2,*ptr3;
	
	fin.open("word.txt");
	if(!fin.is_open())
		return false;
	while(!fin.eof())
	{
		memset(buf,'\0',256);
		memset(word,'\0',256);
		memset(mean,'\0',256);
		fin.getline(buf,256);
		ptr = strtok(buf,"\t");
		if(ptr == NULL)
			break;
		strcpy(word,ptr);
		ptr = strtok(NULL, "\t");
		if(ptr == NULL)
			break;
		strcpy(mean,ptr);
		if(queue->pHead == '\0')
			ptr1 = '\0';
		else
			ptr1 = queue->Search(word);
		if(bst->Search((char)toupper(word[0]))->GetBST()->root == '\0')
			ptr2 = '\0';
		else
			ptr2 = bst->Search((char)toupper(word[0]))->GetBST()->Search(word);
		if(cll->pHead == '\0')
			ptr3 = '\0';
		else
			ptr3 = cll->Search(word);
		if((ptr1==NULL)&&(ptr2==NULL)&&(ptr3==NULL))
			queue->Push(word,mean);
		memset(word, '\0', 256);
		memset(mean, '\0', 256);
		memset(buf, '\0', 256);
	}
	fin.close();
	return true;
}

bool Manager::MOVE()
{
	if(queue->pHead == '\0')
		return false;
	WordNode* node;
	WordBST* wbst;
	int cnt = atoi(cmd2);
	int i;
	if((cnt+bst->WordCnt) > 100)
		return false;
	for(i=0;(i<cnt)&&(queue->pHead == '\0');i++)
	{
		node = queue->Pop();
		wbst = bst->Search((char)toupper(node->GetWord()[0]))->GetBST();
		wbst->Insert(node);
		bst->WordCnt++;
	}
	return true;
}

bool Manager::SAVE()
{
	if(queue->pHead == '\0')
		return false;
	else
		queue->Save();
	if(bst->root == '\0')
		return false;
	else
		bst->Save();
	if(cll->pHead == '\0')
		return false;
	else
		cll->Save();
	return true;
}

bool Manager::TEST()
{
	for(int i=0;i<256;i++)
		cmd2[i] = (char)tolower(cmd2[i]);
	WordNode* node = bst->Search((char)toupper(cmd2[0]))->GetBST()->Search(cmd2);
	if(node == NULL)
		return false;
	if(strcmp(node->GetMean(), cmd3) == 0)
	{
		cll->Insert(bst->Search((char)toupper(cmd2[0]))->GetBST()->Delete(cmd2));
		return true;
	}
	else
		return false;
}

bool Manager::SEARCH()
{
	ofstream log;
	log.open("log.txt",ios::app);
	WordNode* ptr1,*ptr2,*ptr3;
	for(int i=0;cmd2[i]!='\0';i++)
		cmd2[i] = (char)tolower(cmd2[i]);
	if(queue->pHead == '\0')
		ptr1 = '\0';
	else
		ptr1 = queue->Search(cmd2);
	if(bst->Search((char)toupper(cmd2[0]))->GetBST()->root == '\0')
		ptr2 = '\0';
	else
		ptr2 = bst->Search((char)toupper(cmd2[0]))->GetBST()->Search(cmd2);
	if(cll->pHead == '\0')
		ptr3 = '\0';
	else
		ptr3 = cll->Search(cmd2);
	if((ptr1!=NULL) && (ptr2==NULL) && (ptr3==NULL))
	{
		log << "======= SEARCH ======" << endl;
		log << ptr1->GetWord() << "	" <<ptr1->GetMean() << endl;
		log << "=====================" << endl;
		cout << "======= SEARCH ======" << endl;
		cout << ptr1->GetWord() << "	" <<ptr1->GetMean() << endl;
		cout << "=====================" << endl;
	}
	else if((ptr1==NULL) && (ptr2!=NULL) && (ptr3==NULL))
	{
		log << "======= SEARCH ======" << endl;
		log << ptr2->GetWord() << "	" <<ptr2->GetMean() << endl;
		log << "=====================" << endl;
		cout << "======= SEARCH ======" << endl;
		cout << ptr2->GetWord() << "	" <<ptr2->GetMean() << endl;
		cout << "=====================" << endl;
	}
	else if((ptr1==NULL) && (ptr2==NULL) && (ptr3!=NULL))
	{
		log << "======= SEARCH ======" << endl;
		log << ptr3->GetWord() << "	" <<ptr3->GetMean() << endl;
		log << "=====================" << endl;
		cout << "======= SEARCH ======" << endl;
		cout << ptr3->GetWord() << "	" <<ptr3->GetMean() << endl;
		cout << "=====================" << endl;
	}
	else
	{
		log.close();
		return false;
	}


	log.close();
	return true;
}

bool Manager::PRINT()
{
	ofstream fout;
	fout.open("log.txt", ios::app);
	if(!fout)
	{
		return false;
	}
	
	if(strcmp(cmd2,"TO_MEMORIZE")==0)
	{
		fout << "==========PRINT==========" << endl;
		cout << "==========PRINT==========" << endl;
		if(!queue->Print())
			return false;
		fout << "=========================" << endl;
		cout << "=========================" << endl;
	}
	else if(strcmp(cmd2,"MEMORIZING")==0)
	{
		if((strcmp(cmd3,"R_PRE")==0) || (strcmp(cmd3,"I_PRE")==0) || (strcmp(cmd3,"R_IN")==0)||(strcmp(cmd3,"I_IN")==0)||(strcmp(cmd3,"R_POST")==0)||(strcmp(cmd3,"I_POST")==0)||(strcmp(cmd3,"I_LEVEL")==0))
		{
			fout << "==========PRINT==========" << endl;
			cout << "==========PRINT==========" << endl;
			if(!bst->Print(cmd3))
				return false;
			fout << "=========================" << endl;
			cout << "=========================" << endl;
		}
		else
		{
			fout.close();
			return false;
		}
	}
	else if(strcmp(cmd2,"MEMORIZED")==0)
	{
		fout << "==========PRINT==========" << endl;
		cout << "==========PRINT==========" << endl;
		if(!cll->Print())
			return false;
		fout << "=========================" << endl;
		cout << "=========================" << endl;
	}
	else
	{
		fout.close();
		return false;
	}
	fout.close();
	return true;
}

bool Manager::UPDATE()
{
	ofstream log;
	log.open("log.txt",ios::app);
	WordNode* ptr1,*ptr2,*ptr3;
	for(int i=0;cmd2[i]!='\0';i++)
		cmd2[i] = (char)tolower(cmd2[i]);
	if(queue->pHead == '\0')
		ptr1 = '\0';
	else
		ptr1 = queue->Search(cmd2);
	if(bst->Search((char)toupper(cmd2[0]))->GetBST()->root == '\0')
		ptr2 = '\0';
	else
		ptr2 = bst->Search((char)toupper(cmd2[0]))->GetBST()->Search(cmd2);
	if(cll->pHead == '\0')
		ptr3 = '\0';
	else
		ptr3 = cll->Search(cmd2);
	if((ptr1!=NULL) && (ptr2==NULL) && (ptr3==NULL))
	{
		log << "======= UPDATE ======" << endl;
		log << ptr1->GetWord() << "	" <<ptr1->GetMean() << " -> " << cmd3 << endl;
		log << "=====================" << endl;
		cout << "======= UPDATE ======" << endl;
		cout << ptr1->GetWord() << "	" <<ptr1->GetMean() << " -> " << cmd3 << endl;
		cout << "=====================" << endl;
		ptr1->SetMean(cmd3);
	}
	else if((ptr1==NULL) && (ptr2!=NULL) && (ptr3==NULL))
	{
		log << "======= UPDATE ======" << endl;
		log << ptr2->GetWord() << "	" <<ptr2->GetMean() << " -> " << cmd3 << endl;
		log << "=====================" << endl;
		cout << "======= UPDATE ======" << endl;
		cout << ptr2->GetWord() << "	" <<ptr2->GetMean() << " -> " << cmd3 << endl;
		cout << "=====================" << endl;
		ptr2->SetMean(cmd3);
	}
	else if((ptr1==NULL) && (ptr2==NULL) && (ptr3!=NULL))
	{
		log << "======= UPDATE ======" << endl;
		log << ptr3->GetWord() << "	" <<ptr3->GetMean() << " -> " << cmd3 << endl;
		log << "=====================" << endl;
		cout << "======= UPDATE ======" << endl;
		cout << ptr3->GetWord() << "	" <<ptr3->GetMean() << " -> " << cmd3 << endl;
		cout << "=====================" << endl;
		ptr3->SetMean(cmd3);
	}
	else
	{
		log.close();
		return false;
	}


	log.close();
	return true;
}

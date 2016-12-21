#include "/usr/local/Auto_Scoring_System/src/signal.h"
#include "Manager.h"


Manager::Manager() //constructor
{
	cll = new CircularLinkedList;  //allocation
	bst = new AlphabetBST;
	queue = new Queue;
	flog.open("log.txt", ios::app); //file open
}


Manager::~Manager() //destructor
{ return;

	delete cll;
	delete bst;
	delete queue;
	flog.close();
}

void Manager::run(const char * command)  //management
{
	struct sigaction sa;
	set_sigaction(sa);
	alarm(3);

	{
		fin.open(command);  //file open
		if (!fin)  //file is not open
		{
			flog << "File Error" << endl;
			return;
		}
		char temp[32];
		AlphabetNode *pNew;

		char alpha[26] = { 'p', 'h', 'x', 'd', 'l', 't', 'z', 'b', 'f', 'j', 'n', 'r', 'v', 'y', 'a', 'c', 'e', 'g', 'i', 'k', 'm', 'o', 'q', 's', 'u', 'w' };
		for (int i = 0; i < 26; i++)
		{
			pNew = new AlphabetNode;  //allocation
			pNew->SetAlphabet(alpha[i]);
			bst->Insert(pNew);
		}
		while (!fin.eof()) //until last line in the file
		{
			fin >> temp;
			if (('a' > temp[0] || 'z' < temp[0]) && ('A' > temp[0] || 'Z' < temp[0])) //if not alphabet
				break;
			if (strcmp(temp, "LOAD") == 0)  //command is Load
			{
				if (LOAD() == 0) //Load Error
				{
					flog << "======== ERROR ========" << endl;
					flog << "100" << endl;
					flog << "====================" << endl;
					flog << endl;
				}
				else //Load Success
				{
					flog << "======== LOAD ========" << endl;
					flog << "Success" << endl;
					flog << "=====================" << endl;
					flog << endl;
				}
			}
			else if (strcmp(temp, "ADD") == 0)  //command is ADD
			{
				if (ADD() == 0)  //add Error
				{
					flog << "======== ERROR ========" << endl;
					flog << "200" << endl;
					flog << "====================" << endl;
					flog << endl;
				}
				else //add Success
				{
					flog << "======== ADD ========" << endl;
					flog << "Success" << endl;
					flog << "=====================" << endl;
					flog << endl;
				}
			}
			else if (strcmp(temp, "MOVE") == 0)  //command is MOVE
			{
				if (MOVE() == 0)  //move Error
				{
					flog << "======== ERROR ========" << endl;
					flog << "300" << endl;
					flog << "====================" << endl;
					flog << endl;
				}
				else  // move Success
				{
					flog << "======== MOVE ========" << endl;
					flog << "Success" << endl;
					flog << "=====================" << endl;
					flog << endl;
				}
			}
			else if (strcmp(temp, "SAVE") == 0)  //command is SAVE
			{
				if (SAVE() == 0) //save Error
				{
					flog << "======== ERROR ========" << endl;
					flog << "400" << endl;
					flog << "====================" << endl;
					flog << endl;
				}
				else //save Success
				{
					flog << "======== SAVE ========" << endl;
					flog << "Success" << endl;
					flog << "=====================" << endl;
					flog << endl;
				}
			}
			else if (strcmp(temp, "TEST") == 0) //command is TEST
			{
				if (TEST() == 0)//Test Error
				{
					flog << "======== ERROR ========" << endl;
					flog << "500" << endl;
					flog << "====================" << endl;
					flog << endl;
				}
				else//Test Success
				{
					flog << "======== TEST ========" << endl;
					flog << "Pass" << endl;
					flog << "=====================" << endl;
					flog << endl;
				}
			}
			else if (strcmp(temp, "SEARCH") == 0) //command is SEARCH
			{
				if (SEARCH() == 0)  //Search Error
				{
					flog << "======== ERROR ========" << endl;
					flog << "600" << endl;
					flog << "====================" << endl;
					flog << endl;
				}
			}
			else if (strcmp(temp, "PRINT") == 0) //command is PRINT
			{
				if (PRINT() == 0) //Print Error
				{
					flog << "======== ERROR ========" << endl;
					flog << "700" << endl;
					flog << "====================" << endl;
					flog << endl;
				}
			}
			else if (strcmp(temp, "UPDATE") == 0) //command is UPDATE
			{
				if (UPDATE() == 0) //UPDATE Error
				{
					flog << "======== ERROR ========" << endl;
					flog << "800" << endl;
					flog << "====================" << endl;
					flog << endl;
				}
			}
			else if (strcmp(temp, "EXIT") == 0) //command is EXIT
			{
				break; //END
			}
			else //command is not same
			{
				flog << "Command Error" << endl;  //Error
				break;
			}
		}
		fin.close(); //file close
	}
}
	bool Manager::LOAD() //Load file
	{
		ifstream fin1; //Read file
		fin1.open("to_memorize_word.txt"); //file open Queue
		ifstream fin2; //Read file
		fin2.open("memorizing_word.txt"); //file open BST
		ifstream fin3; //Read file
		fin3.open("memorized_word.txt");  //file open cll
		if (!fin1 || !fin2 || !fin3) //file is not open
		{
			return 0; //Error
		}

		char temp[32];
		while (!fin1.eof()) //until last line in the file1
		{
			WordNode *pNew;
			pNew = new WordNode; //allocation
			fin1 >> temp;
			if (('a' > temp[0] || 'z' < temp[0]) && ('A' > temp[0] || 'Z' < temp[0]))  //Not word in the file1
			{
				delete pNew; //delete Node
				break;
			}
			pNew->SetWord(temp);
			fin1 >> temp;
			pNew->SetMean(temp);
			queue->Push(pNew);  //queue Insert
		}
		fin1.close(); //file1 close
		while (!fin2.eof()) //until last line in the file2
		{
			WordNode *pNew;
			pNew = new WordNode; //allocation
			fin2 >> temp;
			if (('a' > temp[0] || 'z' < temp[0]) && ('A' > temp[0] || 'Z' < temp[0]))  //Not word in the file2
			{
				delete pNew;  //delete Node
				break;
			}
			pNew->SetWord(temp);
			fin2 >> temp;
			pNew->SetMean(temp);
			bst->Search(*(pNew->GetWord()))->GetBST()->Insert(pNew); //BST Insert
			bst->WordCnt++;
		}
		fin2.close();//file2 close
		while (!fin3.eof())  //until last line in the file3
		{
			WordNode *pNew;
			pNew = new WordNode;//allocation
			fin3 >> temp;
			if ((('a' > temp[0] || 'z' < temp[0]) && ('A' > temp[0] || 'Z' < temp[0])) || fin3.eof()) //Not word in the file3
			{
				delete pNew; //delete Node
				break;
			}
			pNew->SetWord(temp);
			fin3 >> temp;
			pNew->SetMean(temp);
			cll->Insert(pNew); //Cll Insert
		}
		fin3.close(); //file3 close
		return 1; //Success
	}
	bool Manager::ADD() //Add Node
	{
		ifstream fin; //Read file
		fin.open("word.txt"); //file open
		if (!fin) //file is not open
		{
			return 0; //Error
		}
		char temp[32];
		while (!fin.eof()) //until last line in the file
		{
			WordNode *pNew;
			pNew = new WordNode; //allocation
			fin >> temp;
			if (('a' > temp[0] || 'z' < temp[0]) && ('A' > temp[0] || 'Z' < temp[0]))
			{
				delete pNew; //delete Node
				break;
			}
			if (queue->Search(temp) != 0 || bst->Search(temp[0])->GetBST()->Search(temp) != 0 || cll->Search(temp) != 0)
			{
				delete pNew; //delete Node
				fin >> temp; //jump the mean
				continue;
			}
			pNew->SetWord(temp);
			fin >> temp;
			pNew->SetMean(temp);
			queue->Push(pNew); //queue Insert
		}
		fin.close(); //file close
		if (temp[0] == '\0') //Not word in the file
		{
			return 0;//Error
		}
		return 1; //Success
	}
	bool Manager::MOVE() //MOVE Node
	{
		int num;
		int num2 = 0;
		WordNode *temp, *pWork;
		pWork = queue->pHead;

		fin >> num;
		if (bst->WordCnt + num > 100) //word count exceed 100 number
		{
			return 0; //Error
		}
		for (int i = 0; i < num; i++)
		{
			while (pWork != NULL) //until pWork is last Node
			{
				num2++;
				pWork = pWork->GetNext();
			}
			if (num2 < num) //word doesn't exist Input number
			{
				return 0; //Error
			}
			temp = queue->Pop();
			if (bst->Search(*(temp->GetWord()))->GetBST()->Search(temp->GetWord()) == 0)
			{
				bst->Search(*(temp->GetWord()))->GetBST()->Insert(temp);
				bst->WordCnt++;
			}
		}
		return 1; //Success
	}
	bool Manager::SAVE() //Save list in the file
	{
		if (queue->Save() == 0) //queue save is Error
		{
			return 0; //Error
		}
		if (bst->Save() == 0) //bst save is Error
		{
			return 0; //Error
		}
		if (cll->Save() == 0) //cll save is Error
		{
			return 0; //Error
		}
		return 1; //Success
	}
	bool Manager::TEST() //Test Word
	{
		char temp[32], temp2[32];

		fin >> temp;
		fin >> temp2;
		if (bst->Search(temp[0])->GetBST()->Search(temp) == 0) //Not find BST Node
		{
			return 0; //Error
		}
		if (strcmp(bst->Search(temp[0])->GetBST()->Search(temp)->GetWord(), temp) == 0) //find BST Word
		{
			if (strcmp(bst->Search(temp[0])->GetBST()->Search(temp)->GetMean(), temp2) == 0) //find BST Mean
			{
				cll->Insert(bst->Search(temp[0])->GetBST()->Delete(temp));//cll Insert
				return 1;
			}
			else
				return 0; //Error
		}
		else
			return 0; //Error
	}
	bool Manager::SEARCH() //Search Node
	{
		char temp[32];

		fin >> temp;
		if (queue->Search(temp) == NULL) //Not Search Queue word
		{
			if (bst->Search(temp[0])->GetBST()->Search(temp) == NULL) //Not Search BST word
			{
				if (cll->Search(temp) == NULL) //Not Search Cll word
				{
					return 0; //Error
				}
				else
				{
					flog << "======== SEARCH ========" << endl;
					flog << temp << " " << cll->Search(temp) << endl;
					flog << "====================" << endl << endl;
					return 1; //Success
				}
			}
			else
			{
				flog << "======== SEARCH ========" << endl;
				flog << temp << " " << bst->Search(temp[0])->GetBST()->Search(temp) << endl;
				flog << "====================" << endl << endl;
				return 1; //Success
			}
		}
		else
		{
			flog << "======== SEARCH ========" << endl;
			flog << temp << " " << queue->Search(temp) << endl;
			flog << "====================" << endl << endl;
			return 1; //Success
		}
	}
	bool Manager::PRINT() //Print list
	{
		char temp[32], temp2[32];

		fin >> temp;
		if (strcmp(temp, "TO_MEMORIZE") == 0) //command is TO_MEMORIZE
		{
			if (queue->Print() == 0) //queue Print fail
			{
				return 0; //Error
			}
			return 1; //Success
		}
		else if (strcmp(temp, "MEMORIZING") == 0) //command is MEMORIZING
		{
			fin >> temp2;
			if (bst->Print(temp2) == 0) //bst Print fail 
			{
				return 0; //Error
			}
			return 1; //Success
		}
		else if (strcmp(temp, "MEMORIZED") == 0) //command is MOMORIZED
		{
			if (cll->Print() == 0) //cll Print fail
			{
				return 0; //Error
			}
			return 1; //Success
		}
		else
			return 0; //Error
	}
	bool Manager::UPDATE() //Update word
	{
		char temp[32], temp2[32];

		fin >> temp;
		fin >> temp2;
		if (queue->Search(temp) == 0) //Not find queue word
		{
			if (bst->Search(temp[0])->GetBST()->Search(temp) == 0) //Not find BST word
			{
				if (cll->Search(temp) == 0) //Not find cll word
				{
					return 0; //Error
				}
				else
				{
					if (strcmp(cll->Search(temp)->GetMean(), temp2) == 0) //mean is same
					{
						return 0;
					}
					flog << "========UPDATE========\n" << temp << " " << cll->Search(temp)->GetMean();
					cll->Search(temp)->SetMean(temp2);
					flog << " -> " << temp2 << endl;
					flog << "====================\n" << endl;
					return 1; //Success
				}
			}
			else
			{
				if (strcmp(bst->Search(temp[0])->GetBST()->Search(temp)->GetMean(), temp2) == 0)
				{
					return 0; //Error
				}
				flog << "========UPDATE========\n" << temp << " " << bst->Search(temp[0])->GetBST()->Search(temp)->GetMean();
				bst->Search(temp[0])->GetBST()->Search(temp)->SetMean(temp2);
				flog << " -> " << temp2 << endl;
				flog << "====================\n" << endl;
				return 1; //Success
			}
		}
		else
		{
			if (strcmp(queue->Search(temp)->GetMean(), temp2) == 0) //mean is same
			{
				return 0; //Error
			}
			flog << "========UPDATE========\n" << temp << " " << queue->Search(temp)->GetMean();
			queue->Search(temp)->SetMean(temp2);
			flog << " -> " << temp2 << endl;
			flog << "====================\n" << endl;
			return 1; //Success
		}
	}
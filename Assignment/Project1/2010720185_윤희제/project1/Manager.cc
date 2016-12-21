#include "Manager.h"


Manager::Manager()
{
	cll = new CircularLinkedList;
 	bst = new AlphabetBST;
	queue = new Queue;

	command_text[10] = '\0';
	arg1[100] = '\0';
	arg2[100] = '\0';

	/* when the program start, program makes alphabet bst */
	char arr[27] = "phxdltzbfjnrvyacegikmoqsuw";
	for (int i = 0; i < 26; i++)
	{
		AlphabetNode* temp = new AlphabetNode;
		temp->SetAlphabet(arr[i]);
		bst->Insert(temp);
	}
}

Manager::~Manager()
{
	delete cll;
	delete bst;
	delete queue;
}

void Manager::run(const char * command)
{
	ifstream fin("command.txt");
	string temp;

	while (!(fin.eof()))
	{
		getline(fin, temp);

		int flag = 0;
		int cnt = (int)temp.length();
		int index = 0;

		for (int i = 0; i < cnt; i++)
		{
			if (temp[index] == ' ')
			{
				temp.replace(0, index + 1, "\0");
				flag++;
				index = 0;
			}
			if (flag == 0)
				command_text[index] = temp[index];
			if (flag == 1)
				arg1[index] = temp[index];
			if (flag == 2)
				arg2[index] = temp[index];
			
			index++;
		}

		if (strcmp(command_text, "LOAD") == 0)
			LOAD();
		if (strcmp(command_text, "ADD") == 0)
			ADD();
		if (strcmp(command_text, "MOVE") == 0)
			MOVE();
		if (strcmp(command_text, "SAVE") == 0)
			SAVE();
		if (strcmp(command_text, "TEST") == 0)
			TEST();
		if (strcmp(command_text, "SEARCH") == 0)
			SEARCH();
		if (strcmp(command_text, "PRINT") == 0)
			PRINT();
		if (strcmp(command_text, "UPDATE") == 0)
			UPDATE();
		if (strcmp(command_text, "EXIT") == 0)
			break;
		
		Manager::initialize_arr(command_text, arg1, arg2);
	}
}

bool Manager::LOAD()
{
	ofstream log_file("log.txt", ios::app);
	ifstream to_memorize("to_memorize_word.txt");
	ifstream memorizing("memorizing_word.txt");
	ifstream memorized("memorized_word.txt");
		
	if ((strcmp("to_memorize_word.txt", arg1) != 0) || (strcmp("memorizing_word.txt", arg1) != 0) || (strcmp("memorized_word.txt", arg1) != 0) ||
		(queue->pHead != '\0') || (bst->root != '\0') || (cll->pHead != '\0')) // if data structure has data
	{
		log_file << "======== ERROR ========"   << endl;
		log_file << "100"                       << endl;
		log_file << "=======================\n" << endl;
		log_file.close();
		return 0;
	}
	
	WordNode* node = new WordNode;
	string temp;
	
	while (!(to_memorize.eof()))
	{
		getline(to_memorize, temp);
		int blank = 0;
		string word = temp;
		string mean = temp;
		for (int i = 0; i < (int)temp.length(); i++)
		{
			if (temp[i] == ' ')
			{
				word.replace(blank, (int)word.length(), "\0");
				mean.replace(0, blank + 1, "\0");
				break;
			}
			blank++;
		}
		node->SetWord((char*)word.c_str());
		node->SetMean((char*)mean.c_str());
		queue->Push(node);
	}
	while (!(memorizing.eof()))
	{
		getline(memorizing, temp);
		int blank = 0;
		string word = temp;
		string mean = temp;
		for (int i = 0; i < (int)temp.length(); i++)
		{
			if (temp[i] == ' ')
			{
				word.replace(blank, (int)word.length(), "\0");
				mean.replace(0, blank + 1, "\0");
				break;
			}
			blank++;
		}
		node->SetWord((char*)word.c_str());
		node->SetMean((char*)mean.c_str());
		bst->Search(node->GetWord()[0])->GetBST()->Insert(node);
		bst->WordCnt++;
	}
	while (!(memorized.eof()))
	{
		getline(memorized, temp);
		int blank = 0;
		string word = temp;
		string mean = temp;
		for (int i = 0; i < (int)temp.length(); i++)
		{
			if (temp[i] == ' ')
			{
				word.replace(blank, (int)word.length(), "\0");
				mean.replace(0, blank + 1, "\0");
				break;
			}
			blank++;
		}
		node->SetWord((char*)word.c_str());
		node->SetMean((char*)mean.c_str());
		cll->Insert(node);
	}

	log_file << "======== LOAD ========"    << endl;
	log_file << "Success"                   << endl;
	log_file << "=======================\n" << endl;
	log_file.close();
	return 1;
}

bool Manager::ADD()
{
	ofstream log_file("log.txt", ios::app);
	ifstream word_txt("word.txt");
	int count = 0;

	if (!word_txt || word_txt.eof())
	{
		log_file << "======== ERROR ========"   << endl;
		log_file << "200"                       << endl;
		log_file << "=======================\n" << endl;
		log_file.close();
		return 0;
	}

	string word, mean;
	while (!(word_txt.eof()))
	{			
		WordNode* node = new WordNode;		
		string temp;
		int flag = 0;
		int blank = 0;
		getline(word_txt, temp);

		word = temp;
		mean = temp;

		for (int i = 0; i < (int)temp.length(); i++)
		{
			if (temp[i] == ' ')
			{
				word.replace(blank, (int)word.length(), "\0");
				mean.replace(0, blank + 1, "\0");
				break;
			}
			blank++;
		}		

		node->SetWord((char*)word.c_str());
		node->SetMean((char*)mean.c_str());

		/* if there is no same word */
		if (queue->pHead != '\0')
		{
			if (queue->Search(node->GetWord()) != 0)
				flag++;
		}
		if (bst->Search((char)node->GetWord()[0])->GetBST() != '\0')
		{
			if (bst->Search((char)node->GetWord()[0])->GetBST()->Search(node->GetWord()) != 0)
				flag++;
		}
		if (cll->pHead != '\0')
		{
			if (cll->Search(node->GetWord()) != 0)
				flag++;
		}
		if (flag == 0)
		{
			queue->Push(node);
			count++;
		}			
	}
	if (count != 0)
	{
		log_file << "======== ADD ========" << endl;
		log_file << "Success" << endl;
		log_file << "=====================\n" << endl;
		log_file.close();
		return 1;
	}
	else
	{
		log_file << "======== ERROR ========"   << endl;
		log_file << "200" << endl;
		log_file << "=======================\n" << endl;
		log_file.close();
		return 0;
	}	
}

bool Manager::MOVE()
{
	ofstream log_file("log.txt", ios::app);

	if (atoi(arg1) + bst->WordCnt > 100)   // arg1 is the number of node to be moved
	{
		log_file << "======== ERROR ========"   << endl;
		log_file << "300"                       << endl;
		log_file << "=======================\n" << endl;
		log_file.close();
		return 0;
	}

	if (queue->pHead == '\0') // there is no node in queue
	{
		log_file << "======== ERROR ========"   << endl;
		log_file << "300" << endl;
		log_file << "=======================\n" << endl;
		log_file.close();
		return 0;
	}
	else
	{
		for (int i = 0; i < atoi(arg1); i++)
		{
			/* queue에서 pop해서 bst에 삽입 */
			bst->Search(queue->Pop()->GetWord()[0])->GetBST()->Insert(queue->Pop());
			bst->WordCnt++;
		}		
		return 1;
	}
}

bool Manager::SAVE()
{
	ofstream log_file("log.txt", ios::app);

	if (queue->Save() == 0 && bst->Save() == 0 && cll->Save() == 0)
	{
		log_file << "======== ERROR ========"   << endl;
		log_file << "400" << endl;
		log_file << "=======================\n" << endl;
		log_file.close();
		return 0;
	}
	else
	{
		log_file << "======== SAVE ========" << endl;
		log_file << "Success" << endl;
		log_file << "======================\n" << endl;
		log_file.close();
		return 0;
	}	
}

bool Manager::TEST()
{
	ofstream log_file("log.txt", ios::app);

	WordNode* search_node = bst->Search(arg1[0])->GetBST()->Search(arg1);
	if (search_node == 0) // 찾는 단어가 memorizing에 없거나 memorizing이 비어있을 때
	{
		log_file << "======== ERROR ========"   << endl;
		log_file << "500" << endl;
		log_file << "=======================\n" << endl;
		log_file.close();
		return 0;
	}
	else
	{
		if (strcmp(search_node->GetMean(), arg2) == 0) // 입력한 뜻이 맞을 경우
		{
			/* memorizing에서 삭제 후 memorized로 이동 */
			cll->Insert(bst->Search(arg1[0])->GetBST()->Delete(search_node->GetWord()));
			bst->WordCnt--;
			return 1;
		}
		else
		{
			log_file << "======== ERROR ========"   << endl;
			log_file << "500" << endl;
			log_file << "=======================\n" << endl;
			log_file.close();
			return 0;
		}
	}
}

bool Manager::SEARCH()
{
	ofstream log_file("log.txt", ios::app);

	if (queue->Search(arg1) != 0)
	{
		log_file << "======== SEARCH ========" << endl;
		log_file << queue->Search(arg1)->GetWord() << " " << queue->Search(arg1)->GetMean() << endl;
		log_file << "=======================\n" << endl;
		log_file.close();
		return 1;
	}
	else if (bst->Search(arg1[0])->GetBST()->Search(arg1) != 0)
	{
		WordNode* temp = bst->Search(arg1[0])->GetBST()->Search(arg1);
		log_file << "======== SEARCH ========" << endl;
		log_file << temp->GetWord() << " " << temp->GetMean() << endl;
		log_file << "=======================\n" << endl;
		log_file.close();
		return 1;
	}
	else if (cll->Search(arg1) != 0)
	{
		log_file << "======== SEARCH ========" << endl;
		log_file << cll->Search(arg1)->GetWord() << " " << cll->Search(arg1)->GetMean() << endl;
		log_file << "=======================\n" << endl;
		log_file.close();
		return 1;
	}
	else
	{
		log_file << "======== ERROR ========"   << endl;
		log_file << "600" << endl;
		log_file << "=======================\n" << endl;
		log_file.close();
		return 0;
	}
}

bool Manager::PRINT()
{
	ofstream log_file("log.txt", ios::app);

	if (strcmp(arg1, "TO_MEMORIZE") == 0)     // queue 전체 출력
		queue->Print();
	else if (strcmp(arg1, "MEMORIZING") == 0) // bst 전체 출력
	{
		log_file << "======== PRINT ========" << endl;

		if (bst->Print(arg2) == 0)
		{
			// Print 문구 log 파일에서 없애야함
			log_file << "======== ERROR ========"   << endl;
			log_file << "700" << endl;
			log_file << "=======================\n" << endl;
		}
		else
			log_file << "=======================\n" << endl;
		log_file.close();
	}		
	else if (strcmp(arg1, "MEMORIZED") == 0)  // circular linked list 전체 출력
		cll->Print();
	else // 명령어를 잘못 입력했을 때
	{
		log_file << "======== ERROR ========"   << endl;
		log_file << "700" << endl;
		log_file << "=======================\n" << endl;
		log_file.close();
		return 0;
	}
	return 1;
}

bool Manager::UPDATE()
{
	ofstream log_file("log.txt", ios::app);
	WordNode* node;
	char* temp_mean = '\0';

	if (queue->Search(arg1) != 0)
	{
		node = queue->Search(arg1);
		strcpy_s(temp_mean, sizeof(temp_mean), node->GetMean());
		node->SetMean(arg2);
		log_file << "======== UPDATE ========" << endl;
		log_file << node->GetWord() << " " << temp_mean << " -> " << node->GetMean() << endl;
		log_file << "========================\n" << endl;
		log_file.close();
		return 1;
	}
	else if (bst->Search(arg1[0])->GetBST()->Search(arg1) != 0)
	{
		node = bst->Search(arg1[0])->GetBST()->Search(arg1);
		strcpy_s(temp_mean, sizeof(temp_mean), node->GetMean());
		node->SetMean(arg2);
		log_file << "======== UPDATE ========" << endl;
		log_file << node->GetWord() << " " << temp_mean << " -> " << node->GetMean() << endl;
		log_file << "========================\n" << endl;
		log_file.close();
		return 1;
	}
	else if (cll->Search(arg1) != 0)
	{
		node = cll->Search(arg1);
		strcpy_s(temp_mean, sizeof(temp_mean), node->GetMean());
		node->SetMean(arg2);
		log_file << "======== UPDATE ========" << endl;
		log_file << node->GetWord() << " " << temp_mean << " -> " << node->GetMean() << endl;
		log_file << "========================\n" << endl;
		log_file.close();
		return 1;
	}
	else // update할 단어가 없을 시
	{
		log_file << "======== ERROR ========"   << endl;
		log_file << "800" << endl;
		log_file << "=======================\n" << endl;
		log_file.close();
		return 0;
	}
}

void Manager::initialize_arr(char* command_text, char* arg1, char* arg2)
{
	for (int i = 0; i < 10; i++)
		command_text[i] = '\0';
	for (int i = 0; i < 100; i++)
	{
		arg1[i] = '\0';
		arg2[i] = '\0';
	}		
}
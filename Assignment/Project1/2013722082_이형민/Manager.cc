#include "/usr/local/Auto_Scoring_System/src/signal.h"
#include "Manager.h"
#include <cstdlib>
Manager::Manager()//constructor
{
	cll = new CircularLinkedList;
	bst = new AlphabetBST;
	queue = new Queue;
}

Manager::~Manager()//destructor
{ return;

	delete cll;
	delete bst;
	delete queue;
}

void Manager::run(const char * command)
{
	struct sigaction sa;
	set_sigaction(sa);
	alarm(3);

	std::ifstream f(command);
	std::ofstream log("log.txt", std::ios::app);

	if (f.is_open() == 0)
		return;
	char str[256];
	char *ch;


	while (f.getline(str, 256))//reads one line stored in token, repeatlly
	{
		ch = strtok(str, "\t \0");
		int i = 0;
		while (ch != 0)
		{
			if (i >= 3)
			{
				break;
			}
			strcpy(command_text[i++],ch);
			ch = strtok(0, "\t \0");
		}

		if (strcmp("LOAD", command_text[0]) == 0)// when token word is LOAD
		{
			if (!LOAD())
			{
				cout << "========ERROR========" << std::endl;			
				log << "========ERROR========" << std::endl;
				log << LOAD_ERROR << std::endl;
				cout << LOAD_ERROR << std::endl;
				log << "=====================\n\n" << std::endl;
				cout << "=====================\n\n" << std::endl;
			}
			else {
				log << "=========LOAD========" << std::endl;
				cout << "=========LOAD========" << std::endl;
				log << "Success\n";
				cout << "Success\n";
				log << "=====================\n\n" << std::endl;
				cout << "=====================\n\n" << std::endl;
			}
		}
		else if (strcmp("ADD", command_text[0]) == 0)//when token word is ADD
		{

			if (!ADD()) {
				log << "========ERROR========" << std::endl;
				cout<< "========ERROR========" << std::endl;
				log << ADD_ERROR << std::endl;
				cout << ADD_ERROR << std::endl;
				log << "=====================\n\n" << std::endl;
				cout<< "=====================\n\n" << std::endl;
			}

			else {
				log << "=========ADD=========" << std::endl;
				cout << "=========ADD=========" << std::endl;
				log << "Success\n";
				cout << "Success\n";
				log << "=====================\n\n" << std::endl;
				cout << "=====================\n\n" << std::endl;
			}
		}
		else if (strcmp("MOVE", command_text[0]) == 0)//when token word is MOVE
		{

			if (!MOVE()) {
				log << "========ERROR========" << std::endl;
				log << MOVE_ERROR << std::endl;
				log << "=====================\n\n" << std::endl;
				cout << "========ERROR========" << std::endl;
				cout << MOVE_ERROR << std::endl;
				cout << "=====================\n\n" << std::endl;
			}

			else
			{
				log << "========MOVE=========" << std::endl;
				log << "Success\n";
				log << "=====================\n\n" << std::endl;
				cout << "========MOVE=========" << std::endl;
				cout << "Success\n";
				cout << "=====================\n\n" << std::endl;
			}
		}
		else if (strcmp("SAVE", command_text[0]) == 0)//when token word is SAVE
		{

			if (!SAVE())
			{
				log << "========ERROR========" << std::endl;
				log << SAVE_ERROR << std::endl;
				log << "=====================\n\n" << std::endl;
				cout << "========ERROR========" << std::endl;
				cout << SAVE_ERROR << std::endl;
				cout << "=====================\n\n" << std::endl;
			}

			else {
				log << "=========SAVE========" << std::endl;
				log << "Success\n";
				log << "=====================\n\n" << std::endl;
				cout << "=========SAVE========" << std::endl;
				cout << "Success\n";
				cout << "=====================\n\n" << std::endl;
			}

		}
		else if (strcmp("TEST", command_text[0]) == 0)//when token word is TEST
		{

			if (!TEST())
			{
				log << "========ERROR========" << std::endl;
				log << TEST_ERROR << std::endl;
				log << "=====================\n\n" << std::endl;
				cout << "========ERROR========" << std::endl;
				cout << TEST_ERROR << std::endl;
				cout << "=====================\n\n" << std::endl;
			}

			else
			{
				log << "========TEST=========" << std::endl;
				log << "Pass\n";
				log << "=====================\n\n" << std::endl;
				cout << "========TEST=========" << std::endl;
				cout << "Pass\n";
				cout << "=====================\n\n" << std::endl;
			}
		}
		else if (strcmp("SEARCH", command_text[0]) == 0)//when token word is SEARCH
		{

			if (!SEARCH())
			{
				log << "========ERROR========" << std::endl;
				log << SEARCH_ERROR << std::endl;
				log << "=====================\n\n" << std::endl;
				cout << "========ERROR========" << std::endl;
				cout << SEARCH_ERROR << std::endl;
				cout << "=====================\n\n" << std::endl;
			}
		}

		else if (strcmp("PRINT", command_text[0]) == 0)//when token word is PRINT
		{
			if (!PRINT())
			{
				log << "========ERROR========" << std::endl;
				log << PRINT_ERROR << std::endl;
				log << "=====================\n\n" << std::endl;
				cout<< "========ERROR========" << std::endl;
				cout << PRINT_ERROR << std::endl;
				cout << "=====================\n\n" << std::endl;

			}
		}
		else if (strcmp("UPDATE", command_text[0]) == 0)//when token word is UPDATE
		{
			if (!UPDATE())
			{
				log << "========ERROR========" << std::endl;
				log << UPDATE_ERROR << std::endl;
				log << "=====================\n\n" << std::endl;
				cout << "========ERROR========" << std::endl;
				cout << UPDATE_ERROR << std::endl;
				cout << "=====================\n\n" << std::endl;
			}

		}
		else if (strcmp("EXIT", command_text[0]) == 0)//when token word is EXIT
		{
			log.close();
			return;
		}
	}
	log.close();
	return;
}

bool Manager::LOAD()//LOAD
{
	if (queue->count() != 0 || bst->GetwordCnt() != 0 || cll->GetHead() != 0)//if node exist each part
		return 0;
	char *ch, *context;
	char str[256];

	std::ifstream to_mem, meming, memed;
	to_mem.open("to_memorize_word.txt");//file open
	meming.open("memorizing_word.txt");
	memed.open("memorized_word.txt");

	if (!to_mem.is_open() || !meming.is_open() || !memed.is_open() )//if file not exist
	{
		to_mem.close();
		meming.close();
		memed.close();
		return 0;
	}

	while (to_mem.getline(str, 256))//reads one line and push to the queue
	{
		WordNode *a = new WordNode;
		ch = strtok(str, "\t \0");
		while (ch != 0)
		{
			if ('A' <= ch[0] && ch[0] <= 'z')
				a->SetWord(ch);
			else
				a->SetMean(ch);
			ch = strtok(0, "\t \0");
		}
		queue->Push(a);
	}

	while (meming.getline(str, 256))//reads one line and insert to the wordBST
	{
		WordNode *a = new WordNode;
		ch = strtok(str, "\t \0");
		while (ch != 0)
		{
			if ('A' <= ch[0] && ch[0] <= 'z')
				a->SetWord(ch);
			else
				a->SetMean(ch);
			ch = strtok(0, "\t \0");
		}
		bst->SetWordCnt(bst->GetwordCnt() + 1);//for couting word
		bst->Search(a->GetWord()[0])->GetBST()->Insert(a);

	}

	while (memed.getline(str, 256))//reads one line and insert to the circularlinkedlist
	{
		WordNode *a = new WordNode;
		ch = strtok(str, "\t \0");
		while (ch != 0)
		{
			if ('A' <= ch[0] && ch[0] <= 'z')
				a->SetWord(ch);
			else
				a->SetMean(ch);
			ch = strtok(0, "\t \0");
		}
		cll->Insert(a);
	}
	to_mem.close();//file close
	meming.close();
	memed.close();
	return 1;
}

bool Manager::ADD()//ADD
{
	std::ifstream f;

	f.open("word.txt");//file open
	if (!f)
	{
		f.close();
		return 0;
	}
	char *ch, *context;
	char str[256] = { 0, };
	while (f.getline(str, 256))//reads one line and push to the queue
	{

		WordNode *a = new WordNode;
		ch = strtok(str, "\t \0");
		while (ch != 0)
		{
			if ('A' <= ch[0] && ch[0] <= 'z')// english only accepted
				a->SetWord(ch);
			else
				a->SetMean(ch);
			ch = strtok(0, "\t \0");
		}
		if (cll->Search(a->GetWord()) != 0)// if the same word
		{
			delete a;
			continue;
		}
		else if(queue->Search(a->GetWord()) != 0) // if the same word
		{
			delete a;
			continue;
		}
		else if( bst->Search(a->GetWord()[0])->GetBST()->Search(a->GetWord()) != 0)// if the same word
		{
			delete a;
			continue;
		}
		else
			queue->Push(a);

	}

	if (str[1] == 0)
		return 0;
	return true;

}

bool Manager::MOVE()//MOVE
{
	int queue_count = queue->count();//for counting queuqe word
	int a = atoi(command_text[1]);//char number -> int number
	if (queue_count <  a || a + bst->GetwordCnt() > 100 || queue_count == 0)//exception point
		return 0;
	
	for (int i = 0; i < a; i++) {// repeat push number of a

		WordNode* q = queue->Pop();
		bst->Search(q->GetWord()[0])->GetBST()->Insert(q);
		bst->SetWordCnt(bst->GetwordCnt() + 1);
	}
	return 1;
}

bool Manager::SAVE()//SAVE
{
	if (bst->Save() == 0 || cll->Save() == 0 || queue->Save() == 0)// recall save each part
		return 0;
	return 1;
}

bool Manager::TEST()//TEST
{
	WordNode * word = (bst->Search(command_text[1][0]))->GetBST()->Search(command_text[1]);// test word

	if (word)
	{
		if (strcmp(word->GetMean(), command_text[2]) == 0)// if right meant this mean
		{
			cll->Insert(bst->Search(command_text[1][0])->GetBST()->Delete(word->GetWord()));// insert cll this word 
			bst->SetWordCnt(bst->GetwordCnt() - 1);// count -1 wordBST
			return 1;
		}
	}

	return 0;
}

bool Manager::SEARCH()//SEARCH
{
	std::ofstream log("log.txt", std::ios::app);

	if (cll->Search(command_text[1]))//for searching 
	{
		log << "========SEARCH=======" << std::endl;
		log << cll->Search(command_text[1])->GetWord() << "  ";
		log << cll->Search(command_text[1])->GetMean() << std::endl;
		log << "=====================\n\n" << std::endl;
		cout << "========SEARCH=======" << std::endl;
		cout << cll->Search(command_text[1])->GetWord() << "  ";//print word
		cout << cll->Search(command_text[1])->GetMean() << std::endl;//print mean
		cout << "=====================\n\n" << std::endl;
		log.close();
		return 1;
	}
	if (bst->Search(command_text[1][0])->GetBST()->Search(command_text[1]))//for searching 
	{
		log << "========SEARCH=======" << std::endl;
		log << bst->Search(command_text[1][0])->GetBST()->Search(command_text[1])->GetWord() << "  ";
		log << bst->Search(command_text[1][0])->GetBST()->Search(command_text[1])->GetMean() << std::endl;
		log << "=====================\n\n" << std::endl;
		cout << "========SEARCH=======" << std::endl;
		cout << bst->Search(command_text[1][0])->GetBST()->Search(command_text[1])->GetWord() << "  ";
		cout << bst->Search(command_text[1][0])->GetBST()->Search(command_text[1])->GetMean() << std::endl;
		cout << "=====================\n\n" << std::endl;
		log.close();
		return 1;
	}
	else if (queue->Search(command_text[1]))//for searching 
	{
		log << "========SEARCH=======" << std::endl;
		log << queue->Search(command_text[1])->GetWord() << "  ";
		log << queue->Search(command_text[1])->GetMean() << std::endl;
		log << "=====================\n\n" << std::endl;
		cout << "========SEARCH=======" << std::endl;
		cout << queue->Search(command_text[1])->GetWord() << "  ";
		cout << queue->Search(command_text[1])->GetMean() << std::endl;
		cout << "=====================\n\n" << std::endl;
		log.close();
		return 1;
	}
	log.close();
	return 0;
}

bool Manager::PRINT()//PRINT
{
	if (strcmp(command_text[1], "TO_MEMORIZE") == 0)// recall print fucntion each parts
	{
		return queue->Print();
	}
	else if (strcmp(command_text[1], "MEMORIZING") == 0)// recall print fucntion each parts
	{
		return bst->Print(command_text[2]);
	}
	if (strcmp(command_text[1], "MEMORIZED") == 0)// recall print fucntion each parts
	{
		return cll->Print();
	}


	return 0;
}

bool Manager::UPDATE()//UPDATE
{
	std::ofstream log("log.txt", std::ios::app);
	if (queue->Search(command_text[1]))// case queue
	{
		log << "========UPDATE=======" << std::endl;
		log << command_text[1] << "  " <<" " << queue->Search(command_text[1])->GetMean() << " -> " << command_text[2] << "\n";
		log << "=====================\n\n" << std::endl;
		cout << "========UPDATE=======" << std::endl;
		cout << command_text[1] << "  " <<" " << queue->Search(command_text[1])->GetMean() << " -> " << command_text[2] << "\n";
		cout << "=====================\n\n" << std::endl;
		queue->Search(command_text[1])->SetMean(command_text[2]);// mean change to comman_text2
		log.close();
		return 1;
	}
	else if (bst->Search(command_text[1][0])->GetBST()->Search(command_text[1]))//case wordBST
	{

		log << "========UPDATE=======" << std::endl;
		log << command_text[1] << " " << bst->Search(command_text[1][0])->GetBST()->Search(command_text[1])->GetMean() << " -> " << command_text[2] << "\n";
		log << "=====================\n\n" << std::endl;
		cout << "========UPDATE=======" << std::endl;
		cout << command_text[1] << " " << bst->Search(command_text[1][0])->GetBST()->Search(command_text[1])->GetMean() << " -> " << command_text[2] << "\n";
		cout << "=====================\n\n" << std::endl;
		bst->Search(command_text[1][0])->GetBST()->Search(command_text[1])->SetMean(command_text[2]);// mean change to comman_text2
		log.close();
		return 1;
	}
	else if (cll->Search(command_text[1]))//case circularlinkedlist
	{
		log << "========UPDATE=======" << std::endl;
		log << command_text[1] << " " << cll->Search(command_text[1])->GetMean() << " -> " << command_text[2] << "\n";
		log << "=====================\n\n" << std::endl;
		cout << "========UPDATE=======" << std::endl;
		cout << command_text[1] << " " << cll->Search(command_text[1])->GetMean() << " -> " << command_text[2] << "\n";
		cout << "=====================\n\n" << std::endl;
		cll->Search(command_text[1])->SetMean(command_text[2]);// mean change to comman_text2
		log.close();
		return 1;
	}
	log.close();
	return 0;
}

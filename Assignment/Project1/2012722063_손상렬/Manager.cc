#include "/usr/local/Auto_Scoring_System/src/signal.h"
#include "Manager.h"

// Constructor
Manager::Manager()
{
	cll = new CircularLinkedList;
	bst = new AlphabetBST;
	queue = new Queue;
}

// Destructor
Manager::~Manager()
{ return;

	delete cll;
	delete bst;
	delete queue;
}

// The starting function.
void Manager::run(const char * command)
{
	struct sigaction sa;
	set_sigaction(sa);
	alarm(3);

	// All the alphabet node setting.

	/* Put into the AlphabetNode BST */
	AlphabetNode * an = new AlphabetNode;
	an->SetAlphabet('P');
	bst->setRoot(bst->Insert(an));

	an = new AlphabetNode;
	an->SetAlphabet('H');
	bst->setRoot(bst->Insert(an));

	an = new AlphabetNode;
	an->SetAlphabet('X');
	bst->setRoot(bst->Insert(an));

	an = new AlphabetNode;
	an->SetAlphabet('D');
	bst->setRoot(bst->Insert(an));

	an = new AlphabetNode;
	an->SetAlphabet('L');
	bst->setRoot(bst->Insert(an));

	an = new AlphabetNode;
	an->SetAlphabet('T');
	bst->setRoot(bst->Insert(an));

	an = new AlphabetNode;
	an->SetAlphabet('Z');
	bst->setRoot(bst->Insert(an));

	an = new AlphabetNode;
	an->SetAlphabet('B');
	bst->setRoot(bst->Insert(an));

	an = new AlphabetNode;
	an->SetAlphabet('F');
	bst->setRoot(bst->Insert(an));

	an = new AlphabetNode;
	an->SetAlphabet('J');
	bst->setRoot(bst->Insert(an));

	an = new AlphabetNode;
	an->SetAlphabet('N');
	bst->setRoot(bst->Insert(an));

	an = new AlphabetNode;
	an->SetAlphabet('R');
	bst->setRoot(bst->Insert(an));

	an = new AlphabetNode;
	an->SetAlphabet('V');
	bst->setRoot(bst->Insert(an));

	an = new AlphabetNode;
	an->SetAlphabet('Y');
	bst->setRoot(bst->Insert(an));

	an = new AlphabetNode;
	an->SetAlphabet('A');
	bst->setRoot(bst->Insert(an));

	an = new AlphabetNode;
	an->SetAlphabet('C');
	bst->setRoot(bst->Insert(an));

	an = new AlphabetNode;
	an->SetAlphabet('E');
	bst->setRoot(bst->Insert(an));

	an = new AlphabetNode;
	an->SetAlphabet('G');
	bst->setRoot(bst->Insert(an));

	an = new AlphabetNode;
	an->SetAlphabet('I');
	bst->setRoot(bst->Insert(an));

	an = new AlphabetNode;
	an->SetAlphabet('K');
	bst->setRoot(bst->Insert(an));

	an = new AlphabetNode;
	an->SetAlphabet('M');
	bst->setRoot(bst->Insert(an));

	an = new AlphabetNode;
	an->SetAlphabet('O');
	bst->setRoot(bst->Insert(an));

	an = new AlphabetNode;
	an->SetAlphabet('Q');
	bst->setRoot(bst->Insert(an));

	an = new AlphabetNode;
	an->SetAlphabet('S');
	bst->setRoot(bst->Insert(an));

	an = new AlphabetNode;
	an->SetAlphabet('U');
	bst->setRoot(bst->Insert(an));

	an = new AlphabetNode;
	an->SetAlphabet('W');
	bst->setRoot(bst->Insert(an));

	// The command text fild will be opened.
	ifstream input(command);
	if (!input.is_open())
	{
		return;
	}
	// Read all the line.
	while (!input.eof())
	{
		char* inputString = new char[50];
		input >> inputString;
		char* load = "LOAD";
		char* add = "ADD";
		char* move = "MOVE";
		char* save = "SAVE";
		char* test = "TEST";
		char* search = "SEARCH";
		char* print = "PRINT";
		char* update = "UPDATE";
		char* memorized = "MEMORIZED";
		char* memorizing = "MEMORIZING";
		char* to_memorized = "TO_MEMORIZE";
		char* exit = "EXIT";
		// If the command is load
		if (strcmp(inputString, load) == 0)
		{
			LOAD();
		}
		// If the command is add
		else if (strcmp(inputString, add) == 0)
		{
			ADD();
		}
		// If the command is move
		else if (strcmp(inputString, move) == 0)
		{
			int how;
			input >> how;
			MOVE(how);
		}
		// If the command is print
		else if (strcmp(inputString, print) == 0)
		{
			char* type = new char[50];
			char* style = new char[50];
			input >> type;
			// get the type.
			if (strcmp(type, memorizing) == 0)
			{
				input >> style;
				char * temp = new char[1001];
				strcpy(temp, style);
				PRINT("MEMORIZING", temp);
			}
			if (strcmp(type, memorized) == 0)
			{
				PRINT("MEMORIZED", "");
			}
			if (strcmp(type, to_memorized) == 0)
			{
				PRINT("TO_MEMORIZED", "");
			}
		} 
		// If the command is update
		else if (strcmp(inputString, update) == 0)
		{
			char* word = new char[32];
			char* mean = new char[32];
			input >> word;
			input >> mean;
			char * temp1 = new char[32];
			strcpy(temp1, word);
			char * temp2 = new char[32];
			strcpy(temp2, mean);
			UPDATE(temp1, temp2);
		}
		// If the command is search
		else if (strcmp(inputString, search) == 0)
		{
			char* word = new char[32];
			input >> word;
			char * temp = new char[32];
			strcpy(temp, word);
			SEARCH(temp);
		}
		// If the command is test
		else if (strcmp(inputString, test) == 0)
		{
			char* word = new char[32];
			char* mean = new char[32];
			input >> word;
			input >> mean;
			char * temp1 = new char[32];
			strcpy(temp1, word);
			char * temp2 = new char[32];
			strcpy(temp2, mean);
			TEST(temp1, temp2);
		}
		// If the command is save
		else if (strcmp(inputString, save) == 0)
		{
			SAVE();
		}
		// If the command is exit
		else if (strcmp(inputString, exit) == 0)
		{
			return;
		}
	}
}

// The load function.
bool Manager::LOAD()
{
	FILE *fr = fopen("memorized_word.txt", "r");
	ofstream out("log.txt", ios::app);
	// If the file is not allowed opening.
	if (fr == NULL)
	{
		cout << "======= ERROR =======" << endl;
		cout << "100" << endl;
		cout << "=====================" << endl;
		out << "======= ERROR =======" << endl;
		out << "100" << endl;
		out << "=====================" << endl;
		return false;
	}
	// the word character.
	char *temp = new char[32];
	WordNode * x = new WordNode;
	if (fscanf(fr, "%s", temp) == EOF)
	{
		cout << "======= ERROR =======" << endl;
		cout << "100" << endl;
		cout << "=====================" << endl;
		out << "======= ERROR =======" << endl;
		out << "100" << endl;
		out << "=====================" << endl;
		return false;
	}
	x->SetWord(temp);
	temp = new char[32];
	fscanf(fr, "%s", temp);
	x->SetMean(temp);
	cll->Insert(x);
	x = new WordNode;
	temp = new char[32];
	while (fscanf(fr, "%s", temp) != EOF)
	{
		x->SetWord(temp);
		temp = new char[32];
		fscanf(fr, "%s", temp);
		x->SetMean(temp);
		cll->Insert(x);
		x = new WordNode;
		temp = new char[32];
	}
	fclose(fr);

	// word got from the to_mermorize_word.txt
	FILE *fr2 = fopen("to_memorize_word.txt", "r");
	if (fr2 == NULL)
	{
		cout << "======= ERROR =======" << endl;
		cout << "100" << endl;
		cout << "=====================" << endl;
		out << "======= ERROR =======" << endl;
		out << "100" << endl;
		out << "=====================" << endl;
		return false;
	}
	char * temp2 = new char[32];
	WordNode * y = new WordNode;
	if (fscanf(fr2, "%s", temp2) == EOF)
	{
		cout << "======= ERROR =======" << endl;
		cout << "100" << endl;
		cout << "=====================" << endl;
		out << "======= ERROR =======" << endl;
		out << "100" << endl;
		out << "=====================" << endl;
		return false;
	}
	y->SetWord(temp2);
	temp2 = new char[32];
	fscanf(fr2, "%s", temp2);
	y->SetMean(temp2);
	queue->Push(y);
	y = new WordNode;
	temp2 = new char[32];
	while (fscanf(fr2, "%s", temp2) != EOF)
	{
		y->SetWord(temp2);
		temp2 = new char[32];
		fscanf(fr2, "%s", temp2);
		y->SetMean(temp2);
		queue->Push(y);
		y = new WordNode;
		temp2 = new char[32];
	}
	fclose(fr2);

	FILE *fr3 = fopen("memorizing_word.txt", "r");
	if (fr3 == NULL)
	{
		cout << "======= ERROR =======" << endl;
		cout << "100" << endl;
		cout << "=====================" << endl;
		out << "======= ERROR =======" << endl;
		out << "100" << endl;
		out << "=====================" << endl;
		return false;
	}
	char * temp3 = new char[32];
	WordNode * z = new WordNode;
	if (fscanf(fr3, "%s", temp3) == EOF)
	{
		cout << "======= ERROR =======" << endl;
		cout << "100" << endl;
		cout << "=====================" << endl;
		out << "======= ERROR =======" << endl;
		out << "100" << endl;
		out << "=====================" << endl;
		return false;
	}
	z->SetWord(temp3);
	temp3 = new char[32];
	fscanf(fr3, "%s", temp3);
	z->SetMean(temp3);
	char enter = 'A';
	// The lower case, upper case is not considered.
	if (z->GetWord()[0] >= 97 && z->GetWord()[0] <= 122)
	{
		enter = z->GetWord()[0] - 32;
	}
	bst->Search(enter)->GetBST()->setRoot(bst->Search(enter)->GetBST()->Insert(z));
	z = new WordNode;
	temp3 = new char[32];
	while (fscanf(fr3, "%s", temp3) != EOF)
	{
		z->SetWord(temp3);
		temp3 = new char[32];
		fscanf(fr3, "%s", temp3);
		z->SetMean(temp3);
		bst->Search(enter)->GetBST()->setRoot(bst->Search(enter)->GetBST()->Insert(z));
		z = new WordNode;
		temp3 = new char[32];
	}
	fclose(fr3);

	// load success.
	cout << "======= LOAD =======" << endl;
	cout << "Success" << endl;
	cout << "====================" << endl;
	out << "======= LOAD =======" << endl;
	out << "Success" << endl;
	out << "====================" << endl;
	return true;
}

// If the command is add
bool Manager::ADD()
{
	// the log.txt will be writen follwing from now the word lists.
	ofstream out("log.txt", ios::app);
	FILE *fr = fopen("word.txt", "r");
	if (fr == NULL)
	{
		cout << "======= ERROR =======" << endl;
		cout << "200" << endl;
		cout << "=====================" << endl;
		out << "======= ERROR =======" << endl;
		out << "200" << endl;
		out << "=====================" << endl;
		return false;
	}
	char *temp = new char[32];
	WordNode * x = new WordNode;
	if (fscanf(fr, "%s", temp) == EOF)
	{
		cout << "======= ERROR =======" << endl;
		cout << "200" << endl;
		cout << "=====================" << endl;
		out << "======= ERROR =======" << endl;
		out << "200" << endl;
		out << "=====================" << endl;
		return false;
	}
	x->SetWord(temp);
	temp = new char[32];
	fscanf(fr, "%s", temp);
	x->SetMean(temp);
	if (queue->Search(x->GetWord()) == NULL)
	{
		queue->Push(x);
	}
	x = new WordNode;
	temp = new char[32];
	while (fscanf(fr, "%s", temp) != EOF)
	{
		x->SetWord(temp);
		temp = new char[32];
		fscanf(fr, "%s", temp);
		x->SetMean(temp);
		if (queue->Search(x->GetWord()) == NULL)
		{
			queue->Push(x);
		}
		x = new WordNode;
		temp = new char[32];
	}
	fclose(fr);
	cout << "======= ADD ========" << endl;
	cout << "Success" << endl;
	cout << "====================" << endl;
	out << "======= ADD ========" << endl;
	out << "Success" << endl;
	out << "====================" << endl;
	return true;
}

// If the command is save
bool Manager::SAVE()
{
	ofstream out("log.txt", ios::app);
	if (!queue->Save())
	{
		cout << "======= ERROR =======" << endl;
		cout << "400" << endl;
		cout << "=====================" << endl;
		out << "======= ERROR =======" << endl;
		out << "400" << endl;
		out << "=====================" << endl;
		return false;
	}
	if (!bst->Save())
	{
		cout << "======= ERROR =======" << endl;
		cout << "400" << endl;
		cout << "=====================" << endl;
		out << "======= ERROR =======" << endl;
		out << "400" << endl;
		out << "=====================" << endl;
		return false;
	}
	if (!cll->Save())
	{
		cout << "======= ERROR =======" << endl;
		cout << "400" << endl;
		cout << "=====================" << endl;
		out << "======= ERROR =======" << endl;
		out << "400" << endl;
		out << "=====================" << endl;
		return false;
	}
	cout << "======= SAVE =======" << endl;
	cout << "Success" << endl;
	cout << "====================" << endl;
	out << "======= SAVE =======" << endl;
	out << "Success" << endl;
	out << "====================" << endl;
	return true;
}

// If the command is move
bool Manager::MOVE(int number)
{
	ofstream out("log.txt", ios::app);
	while (number-- > 0)
	{
		WordNode * z = queue->Pop();
		if (z == NULL)
		{
			cout << "======= ERROR =======" << endl;
			cout << "300" << endl;
			cout << "=====================" << endl;
			out << "======= ERROR =======" << endl;
			out << "300" << endl;
			out << "=====================" << endl;
			return false;
		}
		char enter = 'A';
		if (z->GetWord()[0] >= 97 && z->GetWord()[0] <= 122)
		{
			enter = z->GetWord()[0] - 32;
		}
		if (bst->Search(enter)->GetBST()->getCount() >= 100)
		{
			cout << "======= ERROR =======" << endl;
			cout << "300" << endl;
			cout << "=====================" << endl;
			out << "======= ERROR =======" << endl;
			out << "300" << endl;
			out << "=====================" << endl;
			return false;
		}
		bst->Search(enter)->GetBST()->setRoot(bst->Search(enter)->GetBST()->Insert(z));
	}
	cout << "======= MOVE =======" << endl;
	cout << "Success" << endl;
	cout << "====================" << endl;
	out << "======= MOVE =======" << endl;
	out << "Success" << endl;
	out << "====================" << endl;
	return true;
}

// If the command is test
bool Manager::TEST(char * word, char * mean)
{
	ofstream out("log.txt", ios::app);
	WordNode * x = new WordNode;
	x->SetWord(word);
	x->SetMean(mean);
	char enter = 'A';
	if (x->GetWord()[0] >= 97 && x->GetWord()[0] <= 122)
	{
		enter = x->GetWord()[0] - 32;
	}
	if (bst->Search(enter)->GetBST()->Search(x->GetWord()) == NULL
		|| strcmp(bst->Search(enter)->GetBST()->Search(x->GetWord())->GetMean(), x->GetMean()) != 0)
	{
		cout << "======= ERROR =======" << endl;
		cout << "500" << endl;
		cout << "=====================" << endl;
		out << "======= ERROR =======" << endl;
		out << "500" << endl;
		out << "=====================" << endl;
		return false;
	}
	else
	{
		bst->Search(enter)->GetBST()->Delete(x->GetWord());
		cll->Insert(x);
	}
	cout << "======= TEST =======" << endl;
	cout << "Success" << endl;
	cout << "====================" << endl;
	out << "======= TEST =======" << endl;
	out << "Success" << endl;
	out << "====================" << endl;
	return true;
}

// If the command is search
bool Manager::SEARCH(char * word)
{
	ofstream out("log.txt", ios::app);
	char enter = 'A';
	if (word[0] >= 97 && word[0] <= 122)
	{
		enter = word[0] - 32;
	}
	if (bst->Search(enter)->GetBST()->Search(word) != NULL)
	{
		cout << "====== SEARCH ======" << endl;
		cout << bst->Search(enter)->GetBST()->Search(word)->GetWord() << " " << bst->Search(enter)->GetBST()->Search(word)->GetMean() << endl;
		cout << "====================" << endl;
		out << "====== SEARCH ======" << endl;
		out << bst->Search(enter)->GetBST()->Search(word)->GetWord() << " " << bst->Search(enter)->GetBST()->Search(word)->GetMean() << endl;
		out << "====================" << endl;
		return true;
	}
	else if (cll->Search(word) != NULL)
	{
		cout << "====== SEARCH ======" << endl;
		cout << cll->Search(word)->GetWord() << " " << cll->Search(word)->GetMean() << endl;
		cout << "====================" << endl;
		out << "====== SEARCH ======" << endl;
		out << cll->Search(word)->GetWord() << " " << cll->Search(word)->GetMean() << endl;
		out << "====================" << endl;
		return true;
	}
	else if (queue->Search(word) != NULL)
	{
		cout << "====== SEARCH ======" << endl;
		cout << queue->Search(word)->GetWord() << " " << queue->Search(word)->GetMean() << endl;
		cout << "====================" << endl;
		out << "====== SEARCH ======" << endl;
		out << queue->Search(word)->GetWord() << " " << queue->Search(word)->GetMean() << endl;
		out << "====================" << endl;
		return true;
	}
	else
	{
		cout << "======= ERROR =======" << endl;
		cout << "600" << endl;
		cout << "=====================" << endl;
		out << "======= ERROR =======" << endl;
		out << "600" << endl;
		out << "=====================" << endl;
		return false;
	}
}

// If the command is print
bool Manager::PRINT(char * word, char * kind)
{
	ofstream out("log.txt", ios::app);
	if (strcmp(word, "MEMORIZED") == 0)
	{
		cout << "======== PRINT ========" << endl;
		out << "======== PRINT ========" << endl;
		cll->Print();
		cout << "=======================" << endl;
		out << "=======================" << endl;
	}
	else if (strcmp(word, "TO_MEMORIZE") == 0)
	{
		cout << "======== PRINT ========" << endl;
		out << "======== PRINT ========" << endl;
		queue->Print();
		cout << "=======================" << endl;
		out << "=======================" << endl;
	}
	else if (strcmp(word, "MEMORIZING") == 0)
	{
		cout << "======== PRINT ========" << endl;
		out << "======== PRINT ========" << endl;
		bst->Print(kind);
		cout << "=======================" << endl;
		out << "=======================" << endl;
	}
	else
	{
		cout << "======= ERROR =======" << endl;
		cout << "700" << endl;
		cout << "=====================" << endl;
		out << "======= ERROR =======" << endl;
		out << "700" << endl;
		out << "=====================" << endl;
		return false;
	}
	return true;
}

// If the command is update
bool Manager::UPDATE(char * word, char * to)
{
	ofstream out("log.txt", ios::app);
	char enter = 'A';
	if (word[0] >= 97 && word[0] <= 122)
	{
		enter = word[0] - 32;
	}
	if (bst->Search(enter)->GetBST()->Search(word) != NULL)
	{
		cout << "====== UPDATE ======" << endl;
		cout << bst->Search(enter)->GetBST()->Search(word)->GetWord() << " " << bst->Search(enter)->GetBST()->Search(word)->GetMean() << " -> " << to << endl;
		cout << "====================" << endl;
		out << "====== UPDATE ======" << endl;
		out << bst->Search(enter)->GetBST()->Search(word)->GetWord() << " " << bst->Search(enter)->GetBST()->Search(word)->GetMean() << " -> " << to << endl;
		out << "====================" << endl;
		bst->Search(enter)->GetBST()->Search(word)->SetMean(to);
		return true;
	}
	else if (cll->Search(word) != NULL)
	{
		cout << "====== UPDATE ======" << endl;
		cout << cll->Search(word)->GetWord() << " " << cll->Search(word)->GetMean() << " -> " << to << endl;
		cout << "====================" << endl;
		out << "====== UPDATE ======" << endl;
		out << cll->Search(word)->GetWord() << " " << cll->Search(word)->GetMean() << " -> " << to << endl;
		out << "====================" << endl;
		cll->Search(word)->SetMean(to);
		return true;
	}
	else if (queue->Search(word) != NULL)
	{
		cout << "====== UPDATE ======" << endl;
		cout << queue->Search(word)->GetWord() << " " << queue->Search(word)->GetMean() << " -> " << to << endl;
		cout << "====================" << endl;
		out << "====== UPDATE ======" << endl;
		out << queue->Search(word)->GetWord() << " " << queue->Search(word)->GetMean() << " -> " << to << endl;
		out << "====================" << endl;
		queue->Search(word)->SetMean(to);
		return true;
	}
	else
	{
		cout << "======= ERROR =======" << endl;
		cout << "800" << endl;
		cout << "=====================" << endl;
		out << "======= ERROR =======" << endl;
		out << "800" << endl;
		out << "=====================" << endl;
		return false;
	}
}
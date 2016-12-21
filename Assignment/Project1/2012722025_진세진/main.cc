#include "Manager.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(void)
{
	
	Manager manager;
	manager.run("command.txt");
	/*
	Queue* test = new Queue();
	test->Push("apple","사과");
	test->Push("pen", "펜");
	test->Push("pineapple", "파인애플");
	test->Push("break", "개박살");
	test->Print();
	test->Save();
	WordNode* ptr = test->Search("break");
	cout << ptr->GetWord() << " " << ptr->GetMean() << endl;
	*/
	
	/*
	WordBST* test = new WordBST();
	test->Insert("asdf","adf");
	test->Insert("banana","nanan");
	test->Insert("gse","ew");
	test->Insert("hse","ew");
	test->Insert("cse","ew");
	test->Insert("dse","ew");
	test->Insert("ese","ew");
	test->Insert("fse","ew");
	test->Print("I_PRE");
	//test->Print("I_IN");
	//test->Print("I_POST");
	//test->Print("I_LEVEL");
	test->Save();
	*/
	/*
	CircularLinkedList* test = new CircularLinkedList();
	test->Insert("asdf","adf");
	test->Insert("banana","nanan");
	test->Insert("gse","ew");
	test->Insert("hse","ew");
	test->Insert("cse","ew");
	test->Insert("dse","ew");
	test->Insert("ese","ew");
	test->Insert("fse","ew");
	test->Print();
	test->Save();
	*/

	return 0;
}

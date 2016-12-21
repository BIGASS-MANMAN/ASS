#include "Manager.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(void)
{
	Manager manager; //  declare manager
	manager.run("command.txt"); // execute the commands

	// print all text in log.txt file
	ifstream input("log.txt");
 	string temp;
	while (!(input.eof()))
	{
		getline(input, temp);
		cout << temp << endl;
	}
	input.close();

	return 0;
}

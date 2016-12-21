#include "Manager.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(void)
{
	
	Manager manager;		// Manager runs this program
	manager.run("command.txt");		// With "command" text file, the run function runs this program
	
	return 0;

}

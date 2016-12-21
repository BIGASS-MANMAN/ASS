#include "Manager.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(void)
{
	Manager manager;		// Make Manager object
	manager.run("command.txt");	// run

	return 0;			// Program exit
}


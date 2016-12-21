#include "Manager.h"
#include <iostream>
#include <fstream>

using namespace std;

// The main function.
int main(void)
{
	// initiate the manager instance and start.
	Manager manager;
	manager.run("command.txt");
	return 0;
}
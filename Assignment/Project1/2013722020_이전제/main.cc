#include "Manager.h"  //include header
#include <iostream>
#include <fstream>

using namespace std;

int main(void)  //start of main
{
	
	Manager manager;  //Manager instance
	manager.run("command.txt");

	return 0;
}

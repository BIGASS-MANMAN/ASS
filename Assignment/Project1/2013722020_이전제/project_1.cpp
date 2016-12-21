#include  "Manager.h"

int main(void)  //start of main
{

	Manager manager;   //instance of Manager class
	char * text = "command.txt";
	manager.run(text); //run manager

	return 0;  // end of main
}

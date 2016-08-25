#include "Manager.h"

void main()
{
	Manager manager;
	manager.OutputFileOpen("result.txt");
	manager.ProcessRoute("route.in");
}

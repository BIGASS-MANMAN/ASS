#include "Manager.h"

int main()
{
    char AlpList[] = "qazplmwsxoknedcijbrfvtguhy";

    Manager manager;
    manager.InsertAlp(AlpList);
    manager.COMMAND("Scenario1.txt");
    return 0;
}

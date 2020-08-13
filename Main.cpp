#include <string>

#include "Manager.h"

int main(int argc, char** argv)
{
    srand( time(NULL) );

    Manager* manager = new Manager();
    bool fail;

    fail = manager->Init(); //Initializing...

    if( !fail )
    {
        fail = manager->Start("Megalopolis", 800, 600); //Starting the window and the program...
        if( !fail )
            manager->MainMenu();
    }


    manager->Close(); //Closing...
    delete manager;

    Logger::Get().PrintMessage("Program closed.");
    return 0;
}

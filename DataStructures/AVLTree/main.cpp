#include <iostream>
#include "InputHandler.cpp"

using namespace std;

void PrintMenu();

int main()
{
    int64_t input;
    while(true)
    {
        system("CLS");
        PrintMenu();
        input = InputHandler::StandardGetInt();
        switch(input)
        {
            case 1:
                InputHandler::HandleReadFile();
                continue;
            case 2:
                InputHandler::HandlePrintTree();
                continue;
            case 3:
                InputHandler::HandleExists();
                continue;
            case 4:
                InputHandler::HandlePrintLevelOfValue();
                continue;
            case 5:
                InputHandler::HandlePrintValuesSmallerThan();
                continue;
            case 6:
                InputHandler::HandleAppend();
                continue;
            case 7:
                InputHandler::HandleRemove();
                continue;
            case 8:
                return 0;
            default:
                cout << "Invalid option!" << endl;
                system("PAUSE");
                continue;
        }
    }
}

void PrintMenu()
{
    cout << "1) Read From File" << endl;
    cout << "2) Print Tree" << endl;
    cout << "3) Check if element exists" << endl;
    cout << "4) Print level of node" << endl;
    cout << "5) Print values smaller than" << endl;
    cout << "6) Insert value" << endl;
    cout << "7) Remove value" << endl;
    cout << "8) Exit" << endl;
}
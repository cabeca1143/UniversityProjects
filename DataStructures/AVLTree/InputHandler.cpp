#ifndef INPUT_HANDLER
#define INPUT_HANDLER

#include "iostream"
#include "string"
#include "istream"
#include "fstream"
#include "AVLNode.cpp"

using namespace std;

class InputHandler
{
    inline static AVLNode* _node;
public:
    static void HandleReadFile()
    {
        system("CLS");
        string text;
        getline(cin>>ws, text);
        _node = AVLNode::ReadFromFile(text);
    }

    static void HandlePrintTree()
    {
        system("CLS");
        _node->PrintTree();
        system("PAUSE");
    }

    static void HandleExists()
    {
        system("CLS");
        cout << (_node->Contains(StandardGetInt()) ? "true" : "false") << endl;
        system("PAUSE");
    }

    static void HandlePrintLevelOfValue()
    {
        system("CLS");
        _node->PrintLevelOfValue(StandardGetInt());
        system("PAUSE");
    }

    static void HandlePrintValuesSmallerThan()
    {
        system("CLS");
        _node->PrintLesser(StandardGetInt());
        system("PAUSE");
    }

    static void HandleAppend()
    {
        system("CLS");
        _node = _node->Append(StandardGetInt());
        system("PAUSE");
    }

    static void HandleRemove()
    {
        system("CLS");
        _node = _node->Remove(StandardGetInt());
        system("PAUSE");
    }

    static int64_t StandardGetInt()
    {
        cout << "Value: ";
        int64_t input;

        cin >> ws;
        cin >> input;
        return input;
    }

};

#endif
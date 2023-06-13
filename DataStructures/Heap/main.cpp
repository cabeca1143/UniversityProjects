#include <iostream>
#include "MinHeap.cpp"

using namespace std;

void PrintMenu();

int main()
{
	//MaxHeap heap;
	MinHeap heap;
	string input;
	while(true)
	{
		system("CLS");
		PrintMenu();
		getline(cin >> ws, input);
		
		switch(input.front())
		{
			case '1':
				int32_t value;
				system("CLS");
				cout << "Value: ";
				cin >> value;
				heap.Push(value);
				continue;
			case '2':
				system("CLS");
				cout << heap.Pop() << endl;
				system("PAUSE");
				continue;
			case '3':
				system("CLS");
				heap.PrintAll();
				system("PAUSE");
				continue;
			case '4':
				return 0;
			default:
				cout << "Invalid Option!" << endl;
				system("Pause");
				continue;
		}
	}
}

void PrintMenu()
{
	cout << "1) Insert Element" << endl;
	cout << "2) Remove Element" << endl;
	cout << "3) Print Heap" << endl;
	cout << "4) Exit" << endl;
}

//Rafael Belinger Bastos de Araújo
//Feito sozinho
//Não lembro se era para colocar algo mais no cabeçalho
//OBS: O programa pode apresentar Incompatibilidades com sistemas operacionais que não sejam Windows devido a alguns comandos de console que usei ("CLS" e "PAUSE").

#include <iostream>
#include <thread>
#include "SearchNode.cpp"

using namespace std;

void Pause();
void PrintMenu();
void MagicStuff();
void ClearConsole();
string BoolToString(bool value);

SearchNode* tree = nullptr;

int main()
{
	int currentOption = -1;
	int64_t inputInt64;
	string input;

	do
	{
		ClearConsole();
		PrintMenu();
		cin >> currentOption;
		ClearConsole();
		switch (currentOption)
		{
			case 1:
				cout << "Tree: ";
				cin >> input;
				tree = SearchNode::ReadFromString(input);
				continue;
			case 2:
				tree->PrintTree();
				Pause();
				continue;
			case 3:
				cout << "Value: ";
				cin >> inputInt64;
				cout << BoolToString(tree->Contains(inputInt64)) << endl;
				Pause();
				continue;
			case 4:
				cout << "Level: ";
				cin >> inputInt64;
				tree->PrintLevel(inputInt64);
				Pause();
				continue;
			case 5:
				cout << "Value: ";
				cin >> inputInt64;
				tree->PrintLesserOrEqual(inputInt64);
				Pause();
				continue;
			case 6:
				cout << "Value: ";
				cin >> inputInt64;
				tree->Append(inputInt64);
				continue;
			case 7:
				cout << "Value: ";
				cin >> inputInt64;
				tree->Remove(inputInt64);
				continue;
			case 8:
				tree->DeleteTree();
				return 0;
			case 420:
				MagicStuff();
			default:
				cout << "Invalid Option!" << endl;
				Pause();
				break;
		}

	} while (true);

	return 0;
}

void Pause()
{
	//Might be incompatible accross systems
	system("PAUSE");
}

void ClearConsole()
{
	//Might be incompatible accross systems
	system("CLS");
}

string BoolToString(bool value)
{
	return value ? "True" : "False";
}

void PrintMenu()
{
	cout << "1) Read Binary Search Tree" << endl;
	cout << "2) Print Tree" << endl;
	cout << "3) Check If Value Exists" << endl;
	cout << "4) Print Level" << endl;
	cout << "5) Print Smaller or Equal Values" << endl;
	cout << "6) Append Value" << endl;
	cout << "7) Remove Value" << endl;
	cout << "8) Exit" << endl;
}

//Credits: https://github.com/GarvitSinghh/Donuts/blob/main/Donuts/Donut.cpp;
void MagicStuff()
{
	float A = 0, B = 0;
	float i, j;
	int k;
	float z[1760];
	char b[1760];
	cout << "\x1b[2J";
	for (;;)
	{
		memset(b, 32, 1760);
		memset(z, 0, 7040);
		for (j = 0; j < 6.28; j += 0.07)
		{
			for (i = 0; i < 6.28; i += 0.02)
			{
				float c = sin(i);
				float d = cos(j);
				float e = sin(A);
				float f = sin(j);
				float g = cos(A);
				float h = d + 2;
				float D = 1 / (c * h * e + f * g + 5);
				float l = cos(i);
				float m = cos(B);
				float n = sin(B);
				float t = c * h * g - f * e;
				int x = 40 + 30 * D * (l * h * m - t * n);
				int y = 12 + 15 * D * (l * h * n + t * m);
				int o = x + 80 * y;
				int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
				if (22 > y && y > 0 && x > 0 && 80 > x && D > z[o])
				{
					z[o] = D;
					b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
				}
			}
		}
		cout << "\x1b[H";
		for (k = 0; k < 1761; k++)
		{
			putchar(k % 80 ? b[k] : 10);
			A += 0.00004;
			B += 0.00002;
		}
		this_thread::sleep_for(chrono::milliseconds(16));
	}
}

#ifndef TREE_READER
#define TREE_READER

#include <iostream>
#include "Node.cpp"
#include <fstream>
#include <sstream>

using namespace std;

static struct TreeReader
{
	static Node* ReadFromFile(const string& path)
	{
		ifstream stream(path);
		Node* toReturn = AuxReader(stream);
		stream.close();
		return toReturn;
	}

	static Node* ReadFromString(const string& str)
	{
		stringstream stream(str);
		Node* toReturn = AuxReader(stream);
		stream.clear();
		return toReturn;
	}

private:
	static Node* AuxReader(istream& stream)
	{
		Node* toReturn = NULL;
		int num;
		char character;

		stream >> character;
		stream >> num;

		if (num >= 0)
		{
			toReturn = new Node(num);
			toReturn->Left = AuxReader(stream);
			toReturn->Right = AuxReader(stream);
		}

		stream >> character;
		return toReturn;
	}
};

#endif
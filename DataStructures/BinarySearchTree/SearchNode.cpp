#ifndef SEARCH_NODE
#define SEARCH_NODE

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct SearchNode
{
	SearchNode* Left = nullptr;
	SearchNode* Right = nullptr;
	int64_t Data = -1;

	explicit SearchNode(const int64_t data)
	{
		Data = data;
	}

	void Append(SearchNode& node)
	{
		if (node.Data < Data)
		{
			if (Left == nullptr)
			{
				Left = &node;
				return;
			}
			Left->Append(node);
			return;
		}

		if (Right == nullptr)
		{
			Right = &node;
			return;
		}
		Right->Append(node);
	}

	void Append(int64_t value)
	{
		AuxAppendValue(value);
	}

	void PrintTree()
	{
		if (this != nullptr)
		{
			cout << Data << endl;
			Left->PrintTree();
			Right->PrintTree();
		}
	}

	bool Contains(const size_t value)
	{
		return Find(value) != nullptr;
	}

	SearchNode* Max()
	{
		if (Right != nullptr)
		{
			return Right->Max();
		}

		return this;
	}

	SearchNode* Min()
	{
		if (Left != nullptr)
		{
			return Left->Min();
		}

		return this;
	}

	SearchNode* Find(const int64_t value)
	{
		if (this == nullptr || Data == value)
		{
			return this;
		}

		if (value > Data)
		{
			return Right->Find(value);
		}

		return Left->Find(value);
	}

	void Remove(const int64_t value)
	{
		AuxRemove(value);
	}

	void PrintGreaterOrEqual(const int64_t value)
	{
		if (this == nullptr)
		{
			return;
		}

		if (Data >= value)
		{
			cout << Data << endl;
			Left->PrintGreaterOrEqual(value);
		}
		Right->PrintGreaterOrEqual(value);
	}

	void PrintLesserOrEqual(const int64_t value)
	{
		if (this == nullptr)
		{
			return;
		}

		if (Data <= value)
		{
			cout << Data << endl;
			Right->PrintLesserOrEqual(value);
		}
		Left->PrintLesserOrEqual(value);
	}

	size_t Count()
	{
		return AuxCount() + 1;
	}

	size_t CountAtLevel(const size_t level)
	{
		return AuxCountAtLevel(0, level);
	}

	void PrintLevel(const size_t level)
	{
		AuxPrintLevel(0, level);
	}

	vector<SearchNode*>& GetAllNodes()
	{
		vector<SearchNode*>* toReturn = new vector<SearchNode*>();
		AuxGetAllNodes(*toReturn);
		return *toReturn;
	}

	void PrintLeafNodes()
	{
		if (this == nullptr)
		{
			return;
		}

		if (IsLeafNode())
		{
			cout << Data << endl;
		}
		else
		{
			Left->PrintLeafNodes();
			Right->PrintLeafNodes();
		}
	}

	bool IsLeafNode()
	{
		return Left == nullptr && Right == nullptr;
	}

	static SearchNode* ReadFromFile(const string& path)
	{
		ifstream stream(path);
		SearchNode* toReturn = AuxReader(stream);
		stream.close();
		return toReturn;
	}

	static SearchNode* ReadFromString(const string& str)
	{
		stringstream stream(str);
		SearchNode* toReturn = AuxReader(stream);
		stream.clear();
		return toReturn;
	}

	void DeleteTree()
	{
		if (this != nullptr)
		{
			Left->DeleteTree();
			Right->DeleteTree();
			delete(this);
		}
	}

private:

	size_t AuxCount()
	{
		return (Left == nullptr ? 0 : Left->AuxCount() + 1) + (Right == nullptr ? 0 : Right->AuxCount() + 1);
	}

	size_t AuxCountAtLevel(const size_t currentLevel, const size_t level)
	{
		if (this == nullptr)
		{
			return 0;
		}

		if (currentLevel == level)
		{
			return 1;
		}

		return Left->AuxCountAtLevel(currentLevel + 1, level) + Right->AuxCountAtLevel(currentLevel + 1, level);
	}

	void AuxPrintLevel(size_t level, size_t desiredLevel)
	{
		if (this == nullptr)
		{
			return;
		}
		if (level < desiredLevel)
		{
			Left->AuxPrintLevel(++level, desiredLevel);
			Right->AuxPrintLevel(level, desiredLevel);
			return;
		}
		cout << Data << endl;
	}

	void AuxGetAllNodes(vector<SearchNode*>& nodeVector)
	{
		if (this == nullptr)
		{
			return;
		}

		nodeVector.push_back(this);

		Left->AuxGetAllNodes(nodeVector);
		Right->AuxGetAllNodes(nodeVector);
	}

	SearchNode* AuxAppendValue(int64_t value)
	{
		if (this == nullptr)
		{
			return new SearchNode(value);
		}

		if (Data > value)
		{
			Left = Left->AuxAppendValue(value);
		}
		else
		{
			Right = Right->AuxAppendValue(value);
		}

		return this;
	}

	SearchNode* AuxRemove(int64_t value)
	{
		if (this == nullptr)
		{
			return nullptr;
		}

		if (Data == value)
		{
			SearchNode* buffer = nullptr;

			if (Left != nullptr && Right != nullptr)
			{
				buffer = Left;
				while (buffer->Right != nullptr)
				{
					buffer = buffer->Right;
				}
				Data = buffer->Data;
				Left = Left->AuxRemove(Data);
				return this;
			}
			else if (Left == nullptr)
			{
				buffer = Right;
			}
			else if (Right == nullptr)
			{
				buffer = Left;
			}

			delete(this);
			return buffer;
		}

		if (Data > value)
		{
			Left = Left->AuxRemove(value);
		}
		else
		{
			Right = Right->AuxRemove(value);
		}

		return this;
	}

	static SearchNode* AuxReader(istream& stream)
	{
		SearchNode* toReturn = NULL;
		int num;
		char character;

		stream >> character;
		stream >> num;

		if (num >= 0)
		{
			toReturn = new SearchNode(num);
			toReturn->Left = AuxReader(stream);
			toReturn->Right = AuxReader(stream);
		}

		stream >> character;
		return toReturn;
	}
};

#endif
